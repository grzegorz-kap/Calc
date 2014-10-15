#include "stdafx.h"
#include "CodeExecutor.h"


namespace PR
{
	const vector<TOKEN_CLASS> CodeExecutor::IF_FIND = { TOKEN_CLASS::END_KEYWORD, TOKEN_CLASS::ELSE_KEYWORD };

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
			if (isKeyword(TOKEN_CLASS::IF_KEYWORD))
				onIF();

			run();
			code.inc();
		}
	}

	void CodeExecutor::onIF()
	{
		balance++;
		next();
		if (*run() == true)
			next();
		else
		{	
			next();
			setIPTo(IF_FIND);
			next();
		}
	}

	void CodeExecutor::setIPTo(const vector<TOKEN_CLASS> &set)
	{
		if (set.size() == 0)
			return;
		int balance = 0;
		while (1)
		{
			if (ip->size() == 1)
			{
				auto _class = ip->at(0)->getClass();
				if (_class == TOKEN_CLASS::WHILE_KEYWORD || _class == TOKEN_CLASS::FOR_KEYWORD || _class == TOKEN_CLASS::IF_KEYWORD)
				{
					balance++;
					next();
					continue;
				}

				if (std::find(set.begin(), set.end(), _class) != set.end() && balance == 0)
					break;
				
				if (_class == TOKEN_CLASS::END_KEYWORD)
					balance--;	
			}
			next();
		}
	}

	shared_ptr<Data> CodeExecutor::run()
	{
		stack.clear();
		for (i = ip->begin(); i != ip->end(); i++)
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
		return stack.back();
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
