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
	
	}

	void TypePromotor::promote(vector<shared_ptr<Data>> &vec)
	{
		
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
