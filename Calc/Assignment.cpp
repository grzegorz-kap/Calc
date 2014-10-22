#include "stdafx.h"
#include "Assignment.h"


namespace PR
{
	Assignment::Assignment()
	{
		set_class(TOKEN_CLASS::ASSIGNMENT_TARGET);
	}


	Assignment::~Assignment()
	{
	}

	void Assignment::loadTarget(vector<shared_ptr<Token>> &vec)
	{
		bool multi = vec.front()->getClass() == TOKEN_CLASS::MATRIX_START ? true : false;
		decltype(vec.begin()) i;
		for (i = multi ? std::next(vec.begin()) : vec.begin(); i != vec.end(); i++)
		{
			if (multi && (*i)->getClass() == TOKEN_CLASS::VERSE_END)
			{
				i = std::next(i);
				if ((*i)->getClass() != TOKEN_CLASS::MATRIX_END)
					throw CalcException("Wrong assignment");
				break;
			}

			if ((*i)->getClass() != TOKEN_CLASS::ID)
				throw CalcException("Unexpected symbol in assignment target", (*i)->getPosition());

			target.push_back(std::move(*i));

			if (!multi)
				break;
		}
		vec.erase(vec.begin(),++i);
	}
}
