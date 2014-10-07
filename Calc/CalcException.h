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
	public:
		CalcException(const string &message,const string &command = "", int position = 1);
		CalcException(const string &messageA, int positionA);
		~CalcException();

		string getMessage(){ return message; }
		string getCommand(){ return command; }
		int getPosition(){ return position; }
	};

}
