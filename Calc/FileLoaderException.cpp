#include "stdafx.h"
#include "FileLoaderException.h"


namespace PR
{
	FileLoaderException::FileLoaderException(const string &message,int position)
		:CalcException(message,position)
	{
	}


	FileLoaderException::~FileLoaderException()
	{
	}
}
