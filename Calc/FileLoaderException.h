#pragma once
#include "CalcException.h"

namespace KLab
{
	class FileLoaderException :
		public CalcException
	{
	public:
		FileLoaderException(const string &message, int position = 0);
		~FileLoaderException();
	};
}
