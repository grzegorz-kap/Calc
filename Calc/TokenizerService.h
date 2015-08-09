#pragma once

#include <boost/scoped_ptr.hpp>

#include "TokenizerContext.h"
#include "TokenizeException.h"
#include "TokenizerContextService.h"
#include "TokenMatcher.h"

namespace KLab {
	class TokenizerService {
	protected:
		boost::scoped_ptr<TokenizerContextService> contextService;
		boost::scoped_ptr<TokenMatcher> tokenMatcher;

	private:
		shared_ptr<TokenizerContext> tokenizerContext;

	public:
		TokenizerService();
		~TokenizerService();
		shared_ptr<TokenList> readTokens(string inputText);

	protected:

		virtual void onNumber() = 0;
		virtual void onWord() = 0;
		virtual void onSpace() = 0;
		virtual void onNewLine() = 0;
		virtual void onSingleLineComment() = 0;
		virtual void onMultiLineCommentStart() = 0;
		virtual bool checkForOperatorAndReact() = 0;
		virtual bool checkForOtherSymbolsAndReact() = 0;

	private:
		void process();
	};
}
