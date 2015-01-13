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
	public:
		FileLoader(const string &name);
		~FileLoader();

		bool is_open() const;
		string getLine();
		string loadAll();
		bool eof() const;
		string getFileName() const{ return name; }
	
		static void changeWorkingDirectory(const string &directory);
		static string getWorkingDirectory() { return working_directory; }
	private:
		std::ifstream file;
		std::string name;
		static string working_directory;

		void onReadAttempt();
	};
}

