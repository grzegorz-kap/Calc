#pragma once
#include "Token.h"
#include "Output.h"
#include "Variables.h"

#include <vector>
#include <memory>
#include <map>
#include <string>

using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

namespace PR
{
	enum ASSIGNMENT_TYPE : char
	{
		SINGLE,
		MULTI,
		SUBSCRIPTED
	};

	class IAssignment :
		public Token
	{
	public:
		IAssignment(const ASSIGNMENT_TYPE &_type);
		~IAssignment();
		
		const ASSIGNMENT_TYPE _assignment_type;

		virtual void loadTarget(vector<shared_ptr<Token>>::iterator &start, vector<shared_ptr<Token>>::iterator &end) {};	
		
		virtual void doAssignment(Variables &vars,
								  vector<shared_ptr<Data>>::iterator &first,
								  vector<shared_ptr<Data>>::iterator &last, 
								  vector<std::pair<std::map<string, shared_ptr<Data>>::iterator, bool>> &assignment) 
		{
			throw CalcException("Unimplemented assignment");
		};
		
		static auto assign(Variables &vars, const string &key, const shared_ptr<Data> &data)
			 -> std::pair<std::map<string,shared_ptr<Data>>::iterator,bool> ;
		 
		virtual int getTargetSize() const 
		 { 
			 return 0; 
		 }

	};
}

