#pragma once

#include "commons.h"
#include "TokenClass.h"

namespace KLab{
	class SymbolsTokenizeHelper {
		const static unordered_map<char, TOKEN_CLASS> OTHER_SYMBOLS;
	public:
		SymbolsTokenizeHelper() = delete;

		bool static find(TOKEN_CLASS &tokenClass, char search);
	};
}
