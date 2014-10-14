#include "stdafx.h"
#include "FileLoader.h"


namespace PR
{
	FileLoader::FileLoader()
	{
	}

	FileLoader::FileLoader(const string &name)
		:file(name,std::ios::in|std::ios::binary)
	{
	}


	FileLoader::~FileLoader()
	{
	}

	string FileLoader::getLine()
	{
		string temp = "";
		std::getline(file, temp);
		return temp;
	}

	string FileLoader::loadAll()
	{
		return string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	}
}
