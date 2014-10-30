#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	void CodeExecutor::onMatrixEnd()
	{
		vector<shared_ptr<Data>>::iterator ii;
		TYPE max_type = TYPE::TOKEN;


		for (ii = stack.end() - 1; ii >= stack.begin(); ii--)
		{
			auto _type = (*ii)->max_type();
			if (_type > max_type)
				max_type = _type;

			if ((*ii)->_type == TYPE::TOKEN)
			{
				Token *ptr = (*ii)->cast_token();
				if (ptr->getClass() == TOKEN_CLASS::MATRIX_START)
				{
					if (ptr->getEvType() > TYPE::TOKEN)
						max_type = ptr->getEvType();
					break;
				}
			}
		}
		
		max_type = max_type>=TYPE::DOUBLE ? IMatrixBuilder::TYPES.at(max_type) : TYPE::M_DOUBLE;

		if (ii < stack.begin())
			throw CalcException("Matrix start not found");

		auto builder = MatrixBuilderFactory::get(max_type);
		for (auto k = std::next(ii); k != stack.end(); k++)
		{
			builder->add(*k);
		}
		builder->setAndCheckSize();
		stack.erase(ii, stack.end());
		stack.push_back(builder->getPtr());
	}
}