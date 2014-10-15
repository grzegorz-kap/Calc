#include "stdafx.h"
#include "CodeExecutor.h"


namespace PR
{

	CodeExecutor::CodeExecutor()
	{
	}

	CodeExecutor::CodeExecutor(const string &name)
		:code(name)
	{
	}

	CodeExecutor::CodeExecutor(FileLoader &&file)
		: code(file)
	{
	}

	CodeExecutor::~CodeExecutor()
	{
	}

	void CodeExecutor::start()
	{
		while (!code.eof())
		{
			ip = code.getInstruction();
			code.inc();
		}
	}

	shared_ptr<Data> CodeExecutor::run(const Instruction &tokens)
	{
		for (i = tokens.begin(); i != tokens.end(); i++)
		{
			switch ((*i)->getClass())
			{
			case TOKEN_CLASS::NUMBER:
				stack.push_back(shared_ptr<Data>((*i)->evaluate()));
				break;
			case TOKEN_CLASS::OPERATOR:
				onOperator();
				break;
			case TOKEN_CLASS::MATRIX_START:
				stack.push_back(make_shared<Token>(MATRIX_START));
				break;
			case TOKEN_CLASS::VERSE_END:
				stack.push_back(make_shared<Token>(VERSE_END));
				break;
			case TOKEN_CLASS::MATRIX_END:
				onMatrixEnd();
				break;
			default:
				throw CalcException("!");
			}
		}
		return shared_ptr<Data>(new Data());
	}

	void CodeExecutor::onOperator()
	{
		auto p = dynamic_cast<Operator *>(i->get());
		p->setArguments(stack);
 		stack.push_back(shared_ptr<Data>(p->evaluate()));
	}

	bool CodeExecutor::isKeyword(TOKEN_CLASS _class)
	{
		return ip->size() == 1 && ip->at(0)->getClass() == _class;
	}
	
}
