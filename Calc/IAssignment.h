#pragma once

#include "Token.h"
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

	typedef vector<shared_ptr<Token>>::iterator instr_iter;
	typedef vector<shared_ptr<Data>>::iterator stack_iterator;

	class IAssignment : public Token
	{
	public:
		const ASSIGNMENT_TYPE _assignment_type;

		IAssignment(const ASSIGNMENT_TYPE &_type);
		~IAssignment();	
		virtual void loadTarget(instr_iter &start, instr_iter &end);
		virtual void doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment);
		virtual int getTargetSize() const;
		
		static variables_map_pair assign(Variables &vars, const string &key, const shared_ptr<Data> &data);
	};
}

