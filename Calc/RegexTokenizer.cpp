#include "stdafx.h"
#include "RegexTokenizer.h"

namespace KLab
{
	/*const vector<TOKEN_CLASS> RegexTokenizer::FOR_SPACE_DELETE = {
		TOKEN_CLASS::NEW_LINE, TOKEN_CLASS::OPEN_PARENTHESIS,
		TOKEN_CLASS::CLOSE_PARENTHESIS, TOKEN_CLASS::SPACE, TOKEN_CLASS::COLON,
		TOKEN_CLASS::SEMICOLON, TOKEN_CLASS::COMMA
		};

		const vector<string> RegexTokenizer::END_SYNONIMS = {
		"endfor", "endif", "endwhile", "endfunction"
		};

		const unordered_map<char, TOKEN_CLASS> RegexTokenizer::OTHERS = {
		{ '(', TOKEN_CLASS::OPEN_PARENTHESIS },
		{ ')', TOKEN_CLASS::CLOSE_PARENTHESIS },
		{ '[', TOKEN_CLASS::MATRIX_START },
		{ ']', TOKEN_CLASS::MATRIX_END },
		{ ':', TOKEN_CLASS::COLON },
		{ ';', TOKEN_CLASS::SEMICOLON },
		{ ',', TOKEN_CLASS::COMMA }
		};*/

	RegexTokenizer::RegexTokenizer() {
		N = 0;
		i = 0;
	}

	RegexTokenizer::~RegexTokenizer() {
	}

	void RegexTokenizer::setInput(const string &in) {
		command = in;
		init();
	}

	void RegexTokenizer::setInput(string &&in) {
		command = std::move(in);
		init();
	}

	void RegexTokenizer::readOthers() {
		auto result = OTHERS.find(command[i]);
		if (result == OTHERS.end())
			throwMessage("Unrecognized symbol");
		tokens.push_back(make_unique<Token>(result->second));
		setLine();
		inc();
	}

	bool RegexTokenizer::readOperator() {
		if (command[i] == '\'' && prevChar() != '.' && !find(TokenizerHelper::NO_STRING_PRECURSORS, prev())) {
			readString();
			return true;
		}

		int length;
		auto result = OperatorsFactory::get(command, i, length);
		if (result != nullptr) {
			tokens.push_back(std::move(result));
			setLine();
			inc(length);
			return true;
		}
		return false;
	}

	void RegexTokenizer::readNumber() {
		try {
			tokens.push_back(make_unique<SNumber>(Token(NumberReader::read(command, i), TOKEN_CLASS::NUMBER)));
			setLine();
			inc(tokens.back()->getLexemeR().size());
		}
		catch (const CalcException &ex) {
			throwMessage(ex.getMessageR());
		}
	}

	void RegexTokenizer::readWord() {
		string lexame = "";
		/* Wczytanie identyfikatora*/
		while (i < N &&
			(TokenizerHelper::isLetter(command[i]) ||
			TokenizerHelper::isDigit(command[i]))
			)
			lexame += command[i++];

		/* Zamiana endfor, endif, endwhile, endfunction na end. */
		if (std::find(END_SYNONIMS.cbegin(), END_SYNONIMS.cend(), lexame)
			!= END_SYNONIMS.end())
			lexame = "end";

		/* Dodanie do tablicy rozpoznanych symboli leksykalnych. */
		tokens.push_back(make_unique<Token>(std::move(lexame),
			TokenizerHelper::keyWordOrId(lexame)));
		setLine();
		_position += tokens.back()->getLexemeR().size();
	}

	void RegexTokenizer::readString() {
		string lexame = "";
		bool found = false;
		i++;
		while (i < N && command[i] != '\n') {
			if (command[i] == '\'') {
				if (i < N - 1 && command[i + 1] == '\'') {
					i += 2;
					lexame += '\'';
					continue;
				}
				found = true;
				i++;
				break;
			}
			lexame += command[i++];
		}
		if (!found)
			throwMessage("A KapiLab string constant is not terminated properly.");
		tokens.push_back(make_unique<String>(std::move(lexame)));
		setLine();
		_position += tokens.back()->getLexemeR().size();
	}

	void RegexTokenizer::readWhiteSpace() {
		switch (command[i]) {
		case '\n':
			tokens.push_back(make_unique<Token>("\n", TOKEN_CLASS::NEW_LINE));
			setLine();
			i++;
			onNewLine();
			break;
		case '\t':
		case ' ':
		case '\r':
			if (tokens.size() != 0 && !find(FOR_SPACE_DELETE, tokens.back()->getTokenClass())) {
				tokens.push_back(make_unique<Token>(TOKEN_CLASS::SPACE));
				setLine();
			}
			inc();
			break;
		}
	}

	void RegexTokenizer::skipBlockComment() {
		while (i < N - 1) {
			if (command[i] == '%'&&command[i + 1] == '}')
				break;
			else if (command[i] == '\n')
				onNewLine();
			inc();
		}
		inc(2);
	}

	void RegexTokenizer::skipLineComment() {
		while (i < N &&command[i] != '\n')
			inc();
		//i--;
	}

	void RegexTokenizer::deleteUneccessary() {
		if (i < N) {
			char z = command[i];
			if (i < N - 1 && z == '%' && command[i + 1] == '{') {
				skipBlockComment();
				deleteUneccessary();
			}
			else if (z == '%' || (i < N - 1 && z == '/'&&command[i + 1] == '/')) {
				skipLineComment();
				deleteUneccessary();
			}
			else if ((z == '\n' && (prev() == TOKEN_CLASS::NEW_LINE || prev() == TOKEN_CLASS::SEMICOLON)) || (i < N - 1 && z == '\n'&&z == ';')) {
				onNewLine();
				i++;
				deleteUneccessary();
			}
		}
	}

	void RegexTokenizer::tokenize() {
		deleteUneccessary();
		while (i < N) {
			if (TokenizerHelper::isDigit(command[i]))
				readNumber();
			else if (TokenizerHelper::isLetter(command[i]))
				readWord();
			else if (TokenizerHelper::isWhiteSpace(command[i]))
				readWhiteSpace();
			else if (onDot())
				continue;
			else if (readOperator())
				continue;
			else readOthers();
			deleteUneccessary();
		}
	}

	bool RegexTokenizer::onDot() {
		if (i < N - 2 && command[i] == '.'&& command[i + 1] == '.' && command[i + 2] == '.') {
			inc(3);
			while (i < N && command[i] != '\n')
				inc();
			i++;
			onNewLine();
		}
		else
			return false;
		return true;
	}

	void RegexTokenizer::whiteSpacesBegin() {
		while (i < N&&TokenizerHelper::isWhiteSpace(command[i])) {
			i++;
			if (command[i] == '\n')
				onNewLine();
			else
				_position++;
		}
	}

	void RegexTokenizer::whiteSpacesEnd() {
		while (N > 0 && TokenizerHelper::isWhiteSpace(command[N - 1]))
			N--;
	}

	vector<unique_ptr<Token>> RegexTokenizer::getTokens() {
		return std::move(tokens);
	}

	TOKEN_CLASS RegexTokenizer::prev() {
		if (tokens.size() == 0)
			return TOKEN_CLASS::NONE;
		return tokens.back()->getTokenClass();
	}

	void RegexTokenizer::init() {
		N = command.size();
		i = 0;
		_line = 1;
		_position = 1;
		whiteSpacesEnd();
		whiteSpacesBegin();
	}

	char RegexTokenizer::prevChar() {
		if (i == 0)
			return 0;
		return command[i - 1];
	}

	void RegexTokenizer::throwMessage(const string &message) {
		throw CalcException(message, "", _position, _line);
	}

	void RegexTokenizer::inc(int val) {
		i += val;
		_position += val;
	}

	void RegexTokenizer::onNewLine() {
		_position = 1;
		_line++;
	}

	void RegexTokenizer::setLine() {
		if (tokens.size()) {
			tokens.back()->setLine(_line);
			tokens.back()->setColumn(_position);
		}
	}
}