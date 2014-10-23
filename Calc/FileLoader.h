#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "FileLoaderException.h"

using std::unique_ptr;
using std::string;

namespace PR
{
	class FileLoader
	{
		std::ifstream file;
		std::string name;
	public:
		FileLoader(const string &name);
		~FileLoader();

		bool is_open() const { return file.is_open(); }
		string getLine();
		string loadAll();
		bool eof() const { return file.eof(); }
	
	private:
		void onReadAttempt()
		{
			if (!file.is_open())
				throw FileLoaderException("File: '" + name + "' is not opened or does not exist. ");
		}
	};
}

