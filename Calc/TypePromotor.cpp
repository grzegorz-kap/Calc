#include "stdafx.h"
#include "TypePromotor.h"

namespace PR
{
	TypePromotor::TypePromotor()
	{
	}


	TypePromotor::~TypePromotor()
	{
	}

	void TypePromotor::promote(shared_ptr<Data> &a, shared_ptr<Data> &b)
	{
		if (a < b)
			convertTo(b->_type, a, a);
		else if (a>b)
			convertTo(a->_type, b, b);
	}

	void TypePromotor::promote(vector<shared_ptr<Data>> &vec)
	{
		auto max = std::max_element(vec.begin(), vec.end(),
			[](const shared_ptr<Data> &a, const shared_ptr<Data> &b)->bool{
			return a->_type < b->_type;
		})->get()->_type;

		for (auto iter = vec.begin(); iter != vec.end(); iter++)
		{
			if ((*iter)->_type != max)
				convertTo(max, *iter, *iter);
		}
	}

	void TypePromotor::convertTo(TYPE type, shared_ptr<Data> &a , shared_ptr<Data> &dest)
	{
		switch (type)
		{
		case TYPE::M_INT:
			dest = a->convert_numeric<Matrix<int>>();
			break;
		case TYPE::M_FLOAT:
			dest = a->convert_numeric<Matrix<float>>();
			break;
		case TYPE::M_DOUBLE:
			dest = a->convert_numeric<Matrix<float>>();
			break;
		case TYPE::INT:
			dest = a->convert_numeric<Value<int>>();
			break;
		case TYPE::FLOAT:
			dest = a->convert_numeric<Value<float>>();
			break;
		case TYPE::DOUBLE:
			dest = a->convert_numeric<Value<double>>();
		}
	}
}
