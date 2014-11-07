#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	bool CodeExecutor::checkFor()
	{
		if (isKeyword(TOKEN_CLASS::FOR_KEYWORD))
		{
			onForKeyword();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::END_FOR))
		{
			onForEndKeyword();
			return true;
		}
		return false;
	}

	void CodeExecutor::onForKeyword()
	{
		for_iterators.push_back(ForIterator(vars_ref));
		ForIterator & _iterator = for_iterators.back();
		InstructionFor * _for  = dynamic_cast<InstructionFor *>(ip->at(0).get());
		
		_iterator.setName(_for->getLexeme());
		_iterator.setData(run_single(_for->getOnp(), vars_ref));

		int balance = ip->at(0)->getKeywordBalance();
		next();
		_iterator.setCodeBegin(code.getLP());
		setIPTo(FOR_FIND, balance);
		_iterator.setCodeEnd(code.getLP() + 1);
		if (!_iterator.eof())
		{
			_iterator.loadNext();
			code.setIp(_iterator.getCodeBegin());
		}
		else
			code.inc();
	}

	void CodeExecutor::onForEndKeyword()
	{
		if (for_iterators.size() == 0)
			throw CalcException("END-FOR found , but there is no for-iterators in memory!");
		ForIterator & _iterator = for_iterators.back();
		if (_iterator.eof())
		{
			code.inc();
			for_iterators.pop_back();
		}
		else
		{
			_iterator.loadNext();
			code.setIp(_iterator.getCodeBegin());
		}
	}
}