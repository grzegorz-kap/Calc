#include "stdafx.h"
#include "FileLoader.h"


namespace PR
{
	FileLoader::FileLoader(const string &name)
		:file(name,std::ios::in|std::ios::binary)
		, name(name)
	{
	}


	FileLoader::~FileLoader()
	{
		if (file.is_open())
			file.close();
	}

	string FileLoader::getLine()
	{
		onReadAttempt();
		string temp = "";
		std::getline(file, temp);
		return temp;
	}

	string FileLoader::loadAll()
	{
		onReadAttempt();
		return string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	}
}
