#include "stdafx.h"
#include "TokenizerContextService.h"

namespace KLab {
	TokenizerContextService::TokenizerContextService(TokenizerContext *context) {
		this->context = context;
	}

	TokenizerContextService::~TokenizerContextService() {
	}

	bool TokenizerContextService::isCharacterToProccess() const {
		return context->isCharacterToProccess();
	}

	void TokenizerContextService::addTokenToContext(unique_ptr<Token>&& token) {
		processBeforePut(*token);
		context->addToken(std::move(token));
	}

	void TokenizerContextService::addTokenToContext(const string &lexame, TOKEN_CLASS tokenClass) {
		addTokenToContext(unique_ptr<Token>(new Token(lexame, tokenClass)));
	}

	void TokenizerContextService::addTokenToContext(string &&lexame, TOKEN_CLASS tokenClass) {
		addTokenToContext(unique_ptr<Token>(new Token(std::move(lexame), tokenClass)));
	}

	void TokenizerContextService::addTokenToContext(const regex &reg, TOKEN_CLASS tokenClass) {
		const string& text = context->getText();
		std::smatch match;
		bool result = std::regex_search(text.cbegin() + context->textPosition(), text.cend(), match, reg);
		addTokenToContext(match[0], tokenClass);
	}

	void TokenizerContextService::processBeforePut(Token &token) {
		context->incrementPosition(token.getLexemeLength());
		token.setLine(context->getLine());
		token.setColumn(context->getColumn());
		updateColumnAndLine(token);
	}

	void TokenizerContextService::updateColumnAndLine(const Token &token) {
		switch (token.getTokenClass()) {
		case TOKEN_CLASS::NEW_LINE:
			onNewLine(token.getLexemeLength());
			break;
		case TOKEN_CLASS::MULTILINE_COMMENT:
			onMultilineComment(token);
			break;
		default:
			context->setColumn(context->getColumn() + token.getLexemeLength());
			break;
		}
	}

	void TokenizerContextService::onNewLine(int tokenLength) {
		context->setLine(context->getLine() + tokenLength);
		context->setColumn(1);
	}

	void TokenizerContextService::onMultilineComment(const Token & token) {
		auto newLinesCount = std::count_if(token.cbegin(), token.cend(), [](char c){return c == '\n'; });
		if (newLinesCount > 0) {
			context->setLine(context->getLine() + (int)newLinesCount);
			context->setColumn(token.getLexemeLength() - token.lastIndexOf('\n'));
		}
		else
			context->setColumn(context->getColumn() + token.getLexemeLength());
	}
}