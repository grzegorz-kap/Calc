#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{

	void CodeExecutor::onMatrixStart()
	{
		stack.push_back(shared_ptr<Data>(new Token(**i)));
	}

	void CodeExecutor::onMatrixEnd()
	{
		vector<shared_ptr<Data>>::iterator ii;
		for (ii = stack.end() - 1; ii >= stack.begin(); ii--)
		{
			if ((*ii)->get_ty() == DATA_TYPE::TOKEN && std::dynamic_pointer_cast<Token>(*ii)->getType() == TOKEN_CLASS::MATRIX_START)
				break;
		}

		if (ii < stack.begin())
			throw CalcException("Matrix start not found");

		MatrixBuilder builder;
		for (auto k = std::next(ii); k != stack.end(); k++)
		{
			builder.add(*k);
		}
		builder.setAndCheckSize();
		stack.erase(ii, stack.end());
		stack.push_back(builder.getPtr());
	}

	void CodeExecutor::onMatrixVerseEnd()
	{
		stack.push_back(shared_ptr<Data>(new Token(**i)));
	}
}