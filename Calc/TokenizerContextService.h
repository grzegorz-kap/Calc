#pragma once

#include "commons.h"
#include "TokenizerContext.h"

namespace KLab {
	class TokenizerContextService {
		TokenizerContext *context;
	public:
		TokenizerContextService(TokenizerContext *context);
		TokenizerContextService(const TokenizerContextService &other) = delete;
		TokenizerContextService& operator = (const TokenizerContextService &other) = delete;
		~TokenizerContextService();
		bool isCharacterToProccess() const;
		void addTokenToContext(const string &lexame, TOKEN_CLASS tokenClass);
		void addTokenToContext(string &&lexame, TOKEN_CLASS tokenClass);
		void addTokenToContext(const regex &reg, TOKEN_CLASS tokenClass);

	private:
		void addTokenToContext(unique_ptr<Token>&& token);
		void processBeforePut(Token &token);
		void updateColumnAndLine(const Token &token);
		void onNewLine(int tokenLength);
		void onMultilineComment(const Token & token);
	};
}
