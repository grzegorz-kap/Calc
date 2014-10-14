#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <memory>

using std::unique_ptr;
using std::string;

namespace PR
{
	class FileLoader
	{
		std::ifstream file;
	public:
		FileLoader();
		FileLoader(const string &name);
		~FileLoader();

		bool is_open() const { return file.is_open(); }
		string getLine();
		string loadAll();
		bool eof() const { return file.eof(); }
	
	};
}

