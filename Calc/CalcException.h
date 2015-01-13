#pragma once

#include <exception>
#include <string>

using std::exception;
using std::string;

namespace PR
{
	class CalcException :
		public exception
	{
		string message;
		string command;
		int position;
		int line;
	public:
		CalcException(const string &message, const string &command = "", int position = 1, int line = 0);
		CalcException(const string &messageA, int positionA);
		~CalcException();

		string getMessage()const{ return message; }
		const string& getMessageR()const{ return message; }
		string getCommand()const{ return command; }
		int getPosition()const{ return position; }
		int getLine()const{ return line; }
	};

}
