#include "stdafx.h"
#include "CodeExecutor.h"


namespace PR
{
	const vector<TOKEN_CLASS> CodeExecutor::IF_FIND = { TOKEN_CLASS::END_IF, TOKEN_CLASS::ELSE_KEYWORD };
	const vector<TOKEN_CLASS> CodeExecutor::ELSE_FIND = { TOKEN_CLASS::END_IF };
	const vector<TOKEN_CLASS> CodeExecutor::WHILE_FIND = { TOKEN_CLASS::END_WHILE };

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

	bool CodeExecutor::checkIF()
	{
		if (isKeyword(TOKEN_CLASS::IF_KEYWORD))
		{
			onIF();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::END_IF))
		{
			code.inc();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::ELSE_KEYWORD))
		{
			setIPTo(ELSE_FIND, ip->at(0)->getKeywordBalance());
			code.inc();
			return true;
		}

		return false;
	}

	bool CodeExecutor::checkWhile()
	{
		if (isKeyword(TOKEN_CLASS::WHILE_KEYWORD))
		{
			int balance = ip->at(0)->getKeywordBalance();
			next();
			if (*run() == false)
			{
				next();
				setIPTo(WHILE_FIND, balance);
			}
			code.inc();
			return true;
		}
		return false;
	}

	void CodeExecutor::start()
	{
		while (!code.eof())
		{
			ip = code.getInstruction();
			
			if (checkIF())
				continue;
			
			run();
			code.inc();
		}
	}

	void CodeExecutor::onIF()
	{
		int balance = ip->at(0)->getKeywordBalance();
		next();
		if (*run() == false)
		{
			next();
			setIPTo(IF_FIND,balance);
		}
		code.inc();
	}

	void CodeExecutor::setIPTo(const vector<TOKEN_CLASS> &set,int balance)
	{
		if (set.size() == 0)
			return;
		while (1)
		{
			if ( ip->size()==1 && balance == ip->at(0)->getKeywordBalance() &&
				std::find(set.begin(), set.end(), ip->at(0)->getClass()) != set.end())
				return;
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
