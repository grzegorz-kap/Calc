#include "stdafx.h"
#include "ForIterator.h"

namespace KLab
{
	ForIterator::ForIterator(Variables &ref)
		:vars(ref)
	{
	}

	ForIterator::~ForIterator()
	{
	}

	void ForIterator::setData(vector<shared_ptr<Data>> &&a)
	{
		if (a.size() != 1)
			throw CalcException("Too many or too few operands for for-loop!");
		data = std::move(a.front());
		TypePromotor::promote(data, data->max_type());
		size = data->get_cols_int();
		idx = 0;
	}

	void ForIterator::loadNext()
	{
		if (idx >= size)
			throw CalcException("For-loop out of range!");
		vars.set(iterator_name, data->getColumn(idx++));
	}
}