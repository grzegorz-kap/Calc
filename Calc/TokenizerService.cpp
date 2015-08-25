#include "stdafx.h"
#include "TokenizerService.h"

namespace KLab
{
	const vector<TOKEN_CLASS> TokenizerService::FOR_SPACE_DELETE = {
		TOKEN_CLASS::NEW_LINE, TOKEN_CLASS::OPEN_PARENTHESIS,
		TOKEN_CLASS::CLOSE_PARENTHESIS, TOKEN_CLASS::SPACE, TOKEN_CLASS::COLON,
		TOKEN_CLASS::SEMICOLON, TOKEN_CLASS::COMMA, TOKEN_CLASS::IF_KEYWORD, FOR_KEYWORD,
		TOKEN_CLASS::WHILE_KEYWORD, TOKEN_CLASS::CONTINUE_KEYWORD, TOKEN_CLASS::BREAK_KEYWORD, TOKEN_CLASS::END_KEYWORD,
		TOKEN_CLASS::FUNCTION_KEYWORD, TOKEN_CLASS::ELSEIF_KEYWORD, TOKEN_CLASS::RETURN_KEYWORD
	};

	const vector<string> TokenizerService::END_SYNONIMS = {
		"endfor", "endif", "endwhile", "endfunction"
	};

	const unordered_map<char, TOKEN_CLASS> TokenizerService::OTHERS = {
		{ '(', TOKEN_CLASS::OPEN_PARENTHESIS },
		{ ')', TOKEN_CLASS::CLOSE_PARENTHESIS },
		{ '[', TOKEN_CLASS::MATRIX_START },
		{ ']', TOKEN_CLASS::MATRIX_END },
		{ ':', TOKEN_CLASS::COLON },
		{ ';', TOKEN_CLASS::SEMICOLON },
		{ ',', TOKEN_CLASS::COMMA }
	};

	TokenizerService::TokenizerService(const string &input)
		: tokenizerContext(input), tokenizerContextService(tokenizerContext) {
		init();
	}

	TokenizerService::TokenizerService(string &&input)
		: tokenizerContext(std::move(input)), tokenizerContextService(tokenizerContext) {
		init();
	}

	TokenizerService::~TokenizerService() {
	}

	void TokenizerService::readOthers() {
		auto result = OTHERS.find(at(0));
		if (result == OTHERS.end())
			throwMessage("Unrecognized symbol");
		tokenizerContext.pushToken(make_unique<Token>(result->second));
		setLine();
		inc();
	}

	bool TokenizerService::readOperator() {
		if (at(0) == '\'' && prevChar() != '.' && !find(TokenizerHelper::NO_STRING_PRECURSORS, prev())) {
			readString();
			return true;
		}

		int length;
		auto result = OperatorsFactory::get(tokenizerContext.getTextRef(), tokenizerContext.getIndex(), length);
		if (result != nullptr) {
			tokenizerContext.pushToken(std::move(result));
			setLine();
			inc(length);
			return true;
		}
		return false;
	}

	void TokenizerService::readWord() {
		string lexame = "";
		while (!EoI() && (TokenizerHelper::isLetter(at(0)) || TokenizerHelper::isDigit(at(0)))) {
			lexame += at(0);
			tokenizerContext.increment(1);
		}

		if (std::find(END_SYNONIMS.cbegin(), END_SYNONIMS.cend(), lexame)
			!= END_SYNONIMS.end())
			lexame = "end";

		tokenizerContext.pushToken(make_unique<Token>(std::move(lexame),
			TokenizerHelper::keyWordOrId(lexame)));
		setLine();
		_position += tokenizerContext.tokensBack().getLexemeR().size();
	}

	void TokenizerService::readString() {
		string lexame = "";
		bool found = false;
		while (!EoI() && at(0) != '\n') {
			if (at(0) == '\'') {
				if (at(1) == '\'') {
					tokenizerContext.increment(2);
					lexame += '\'';
					continue;
				}
				found = true;
				tokenizerContext.increment(1);
				break;
			}
			lexame += at(0);
			tokenizerContext.increment(1);
		}
		if (!found)
			throwMessage("A KapiLab string constant is not terminated properly.");
		tokenizerContext.pushToken(make_unique<String>(std::move(lexame)));
		setLine();
		_position += tokenizerContext.tokensBack().getLexemeR().size();
	}

	void TokenizerService::readWhiteSpace() {
		switch (at(0)) {
		case '\n':
			tokenizerContext.pushToken(make_unique<Token>("\n", TOKEN_CLASS::NEW_LINE));
			setLine();
			tokenizerContext.increment(1);
			onNewLine();
			break;
		case '\t':
		case ' ':
		case '\r':
			if (tokenizerContext.tokensCount() != 0 && !find(FOR_SPACE_DELETE, tokenizerContext.tokensBack().getClass())) {
				tokenizerContext.pushToken(make_unique<Token>(TOKEN_CLASS::SPACE));
				setLine();
			}
			inc();
			break;
		}
	}

	void TokenizerService::skipBlockComment() {
		while (tokenizerContext.getIndex() < tokenizerContext.getLength() - 1) {
			if (at(0) == '%'&&at(1) == '}')
				break;
			else if (at(0) == '\n')
				onNewLine();
			inc();
		}
		inc(2);
	}

	void TokenizerService::skipLineComment() {
		while (!EoI() && at(0) != '\n')
			inc();
		//i--;
	}

	void TokenizerService::deleteUneccessary() {
		if (!EoI()) {
			char z = at(0);
			if (z == '%' && at(1) == '{') {
				skipBlockComment();
				deleteUneccessary();
			}
			else if (z == '%' || (z == '/'&&at(1) == '/')) {
				skipLineComment();
				deleteUneccessary();
			}
			else if ((z == '\n' && (prev() == TOKEN_CLASS::NEW_LINE || prev() == TOKEN_CLASS::SEMICOLON))) {
				onNewLine();
				tokenizerContext.increment(1);
				deleteUneccessary();
			}
		}
	}

	void TokenizerService::tokenize() {
		deleteUneccessary();
		while (!EoI()) {
			if (TokenizerHelper::isDigit(at(0)))
				onNumber();
			else if (TokenizerHelper::isLetter(at(0)))
				readWord();
			else if (TokenizerHelper::isWhiteSpace(at(0)))
				readWhiteSpace();
			else if (onDot())
				continue;
			else if (readOperator())
				continue;
			else readOthers();
			deleteUneccessary();
		}
	}

	bool TokenizerService::onDot() {
		if (at(0) == '.'&& at(1) == '.' && at(3) == '.') {
			inc(3);
			while (!EoI() && at(0) != '\n')
				inc();
			tokenizerContext.increment(1);
			onNewLine();
		}
		else
			return false;
		return true;
	}

	void TokenizerService::whiteSpacesBegin() {
		while (!EoI() && TokenizerHelper::isWhiteSpace(at(0))) {
			tokenizerContext.increment(0);
			if (at(0) == '\n')
				onNewLine();
			else
				_position++;
		}
	}

	void TokenizerService::whiteSpacesEnd() {
		while (!EoI() && TokenizerHelper::isWhiteSpace(tokenizerContext.last()))
			tokenizerContext.decrementLength(1);
	}

	vector<unique_ptr<Token>> TokenizerService::getTokens() {
		return std::move(tokenizerContext.getTokens()->getTokens());
	}

	char TokenizerService::at(int index) {
		return tokenizerContext.at(index);
	}

	bool TokenizerService::EoI() const {
		return tokenizerContext.EoI();
	}

	TOKEN_CLASS TokenizerService::prev() {
		if (tokenizerContext.tokensCount() == 0)
			return TOKEN_CLASS::NONE;
		return tokenizerContext.tokensBack().getClass();
	}

	void TokenizerService::init() {
		_line = 1;
		_position = 1;
		whiteSpacesEnd();
		whiteSpacesBegin();
	}

	char TokenizerService::prevChar() {
		return at(-1);
	}

	void TokenizerService::throwMessage(const string &message) {
		throw CalcException(message, "", _position, _line);
	}

	void TokenizerService::inc(int val) {
		tokenizerContext.increment(val);
		_position += val;
	}

	void TokenizerService::onNewLine() {
		_position = 1;
		_line++;
	}

	void TokenizerService::setLine() {
		if (tokenizerContext.tokensCount()) {
			tokenizerContext.tokensBack().setLine(_line);
			tokenizerContext.tokensBack().setPosition(_position);
		}
	}
}