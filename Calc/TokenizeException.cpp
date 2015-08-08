#include "stdafx.h"
#include "TokenizeException.h"

KLab::TokenizeException::TokenizeException() : std::exception() {
}

KLab::TokenizeException::TokenizeException(string message) : std::exception(message.c_str()) {
}

KLab::TokenizeException::TokenizeException(string message, const shared_ptr<TokenizerContext> &tokenizerContext) : std::exception(message.c_str()) {
	this->tokenizerContext = tokenizerContext;
}