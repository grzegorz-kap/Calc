#include "stdafx.h"
#include "Data.h"


namespace PR
{

	Data::Data()
	{
	}

	Data::~Data()
	{
	}

	bool Data::isNumeric()
	{
		return _ty == DATA_TYPE::DOUBLE || _ty == DATA_TYPE::FLOAT || _ty == DATA_TYPE::INT;
	}

    shared_ptr<Data> Data::operator + (const shared_ptr<Data> &b)
	{
		throw "tra";
	}

	shared_ptr<Data> Data::operator - (const shared_ptr<Data> &b)
	{
		throw "tra";
	}

	shared_ptr<Data> Data::operator * (const shared_ptr<Data> &b)
	{
		throw "tra";
	}

	shared_ptr<Data> Data::operator / (const shared_ptr<Data> &b)
	{
		throw "tra";
	}

	shared_ptr<Data> Data::operator - ()
	{
		throw "tra";
	}

	shared_ptr<Data> Data::mult_t(const shared_ptr<Data> &b)
	{
		throw "tra";
	}

	shared_ptr<Data> Data::div_t(const shared_ptr<Data> &b)
	{
		throw "tra";
	}

	string Data::toString() const
	{
		throw "tra";
	}
}