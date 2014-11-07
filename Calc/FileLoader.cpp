#include "stdafx.h"
#include "FileLoader.h"


namespace PR
{
	string FileLoader::working_directory = "";

	FileLoader::FileLoader(const string &nameA)
	{
		name = working_directory + nameA;
		file.open(name, std::ios::in | std::ios::binary);
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

	void FileLoader::changeWorkingDirectory(const string &directory)
	{
		working_directory = directory;
		if (working_directory.size() && working_directory.back() != '/')
			working_directory += "/";
	}
}
