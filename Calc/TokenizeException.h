#pragma once

#include <exception>

#include "TokenizerContext.h"

namespace KLab {
	class TokenizeException : public std::exception {
	private:
		shared_ptr<TokenizerContext> tokenizerContext;
	public:

		TokenizeException();

		TokenizeException(string message);

		TokenizeException(string message, const shared_ptr<TokenizerContext> &tokenizerContext);
	};
}