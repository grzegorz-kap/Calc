#include "stdafx.h"
#include "CodeExecutor.h"


namespace PR
{
	char TEST = 0;

	CodeExecutor::CodeExecutor()
	{
	}


	CodeExecutor::~CodeExecutor()
	{
	}

	shared_ptr<Data> CodeExecutor::run(const INSTRUCTION &tokens)
	{
		for (i = tokens.begin(); i != tokens.end(); i++)
		{
			switch ((*i)->getType())
			{
			case TOKEN_CLASS::NUMBER:
				if (TEST++%2==0)
					stack.push_back(shared_ptr<Data>(new IMatrix<mytype>((*i)->getLexeme())));
				else
					stack.push_back(shared_ptr<Data>(new IMatrix<int>((*i)->getLexeme())));
				break;
			case TOKEN_CLASS::OPERATOR:
				onOperator();
				break;
			case TOKEN_CLASS::MATRIX_START:
				onMatrixStart();
				break;
			case TOKEN_CLASS::MATRIX_END:
				onMatrixEnd();
				break;
			case TOKEN_CLASS::VERSE_END:
				onMatrixVerseEnd();
				break;
			case TOKEN_CLASS::FUNCTION:
				onFunction();
				break;
			case TOKEN_CLASS::FUNCTON_ARGS_END:
				pushToken(TOKEN_CLASS::FUNCTON_ARGS_END);
				break;
			}

		}
		if (stack.size())
			return stack.back();
		else
			throw CalcException("Error eval instruction");
	}

	shared_ptr<Data> CodeExecutor::pop()
	{
		shared_ptr<Data> a = stack.back();
		stack.pop_back();
		return a;
	}

	void CodeExecutor::pushToken(TOKEN_CLASS t)
	{
		stack.push_back(shared_ptr<Data>(new Token(t)));
	}

	vector<shared_ptr<Data>>::iterator CodeExecutor::find(TOKEN_CLASS _class,bool ex)
	{
		for (auto ii = stack.end()-1; ii >= stack.begin();ii--)
		{
			if ((*ii)->get_ty() == DATA_TYPE::TOKEN && Token::cast(*ii)->getType() == _class)
				return ii;
		}

		if (ex)
			throw CalcException("Expected token not found!");
		else
			return stack.end();
	}
}
