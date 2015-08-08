#include "stdafx.h"
#include "SymbolsTokenizeHelper.h"

namespace KLab {
	decltype(SymbolsTokenizeHelper::OTHER_SYMBOLS) SymbolsTokenizeHelper::OTHER_SYMBOLS = {
		{ ',', TOKEN_CLASS::COMMA },
		{ ':', TOKEN_CLASS::COLON },
		{ ';', TOKEN_CLASS::SEMICOLON },
		{ '(', TOKEN_CLASS::OPEN_PARENTHESIS },
		{ ')', TOKEN_CLASS::CLOSE_PARENTHESIS },
		{ '[', TOKEN_CLASS::OPEN_BRACKET },
		{ ']', TOKEN_CLASS::CLOSE_BRACKET },
	};

	bool SymbolsTokenizeHelper::find(TOKEN_CLASS &tokenClass, char search) {
		auto iter = OTHER_SYMBOLS.find(search);
		if (iter != OTHER_SYMBOLS.end()) {
			tokenClass = iter->second;
			return true;
		}
		return false;
	}
}