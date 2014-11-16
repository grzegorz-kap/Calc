#include "stdafx.h"
#include "TypePromotor.h"

namespace PR
{
	decltype(TypePromotor::ptr_max_lambda) TypePromotor::ptr_max_lambda = 
		[](const shared_ptr<Data> &a, const shared_ptr<Data> &b)->bool
	{
		return a->max_type() < b->max_type();
	};

	TypePromotor::TypePromotor()
	{
	}

	TypePromotor::~TypePromotor()
	{
	}

	TYPE TypePromotor::promoteToMatrixHelper(shared_ptr<Data> &data)
	{
		if (data->isNumeric())
			return IMatrixBuilder::TYPES.at(data->max_type());
		return data->max_type();
	}

	void TypePromotor::promoteToMatrix(vector<shared_ptr<Data>> &vec)
	{
		auto max = std::max_element(vec.begin(), vec.end(), ptr_max_lambda);
		auto _type = promoteToMatrixHelper(*max);
		promote(vec, _type);
	}

	void TypePromotor::promoteToMatrix(shared_ptr<Data> &a, shared_ptr<Data> &b)
	{
		auto _type_a = a->max_type();
		auto _type_b = b->max_type();
		TYPE max;
		if (_type_a >= _type_b)
		{
			max = promoteToMatrixHelper(a);
		}
		else if (_type_a < _type_b)
		{
			max = promoteToMatrixHelper(b);
		}
		promote(a, max);
		promote(b, max);
	}

	void TypePromotor::promote(shared_ptr<Data> &a, shared_ptr<Data> &b)
	{
		auto a_m = a->max_type();
		auto b_m = b->max_type();

		if (a_m < b_m)
			convertTo(b_m, a, a);
		else if (a_m>b_m)
			convertTo(a_m, b, b);
		
		if (a->_type == TYPE::OUTPUT)
		{
			convertTo(a_m, a, a);
		}
		if (b->_type == TYPE::OUTPUT)
		{
			convertTo(b_m, b, b);
		}
			
	}

	void TypePromotor::promote(vector<shared_ptr<Data>> &vec)
	{
		auto max = std::max_element(vec.begin(), vec.end(),ptr_max_lambda)->get()->max_type();

		for (auto iter = vec.begin(); iter != vec.end(); iter++)
		{
			if ((*iter)->_type != max)
				convertTo(max, *iter, *iter);
		}
	}

	void TypePromotor::promote(vector<shared_ptr<Data>> &vec,TYPE _type, bool(*cond)(shared_ptr<Data> &b))
	{
		for (auto &ref : vec)
		{
			if (ref->_type != _type && (cond == nullptr || cond(ref)))
				convertTo(_type, ref, ref);
		}
	}

	void TypePromotor::promote(shared_ptr<Data> &a, const TYPE &type)
	{
		if (a->_type != type)
			convertTo(type, a, a);
	}

	void TypePromotor::convertTo(TYPE type,const shared_ptr<Data> &a , shared_ptr<Data> &dest)
	{
		if (a->isOutput())
		{
			convertOutputTo(type, a, dest);
			return;
		}

		switch (type)
		{
		case TYPE::DOUBLE:
			dest = a->convert_numeric<ComplexNumber<double>>();
			break;
		case TYPE::M_DOUBLE:
			dest = a->convert_numeric<Matrix<double>>();
			break;
		case TYPE::R_DOUBLE:
			dest = a->convert_numeric<ComplexNumber<hdouble>>();
			break;
		case TYPE::RM_DOUBLE:
			dest = a->convert_numeric<Matrix<hdouble>>();
			break;
		default:
			throw "!";
		}
	}

	void TypePromotor::convertOutputTo(TYPE type,const shared_ptr<Data> &a, shared_ptr<Data> &dest)
	{
		auto vec = std::dynamic_pointer_cast<Output>(a)->getOutput();
		auto builder =  MatrixBuilderFactory::get(type);

		if (builder == nullptr)
			builder = MatrixBuilderFactory::get(TYPE::DOUBLE);

		if (builder == nullptr&&vec.size())
		{
			if (type == vec[0]->_type)
				dest = vec[0];
			else
				convertTo(type, vec[0], dest);
			return;
		}

		for (auto iter = vec.begin(); iter != vec.end(); iter++)
		{
			convertTo(type, *iter, *iter);
			builder->add(*iter);
		}
		builder->setAndCheckSize();
		dest = builder->getPtr();
	}
}
