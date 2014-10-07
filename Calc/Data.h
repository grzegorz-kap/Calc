#pragma once

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

#include "functions.h"
#include "CalcException.h"

typedef double mytype;
#define TYPE_C PR::DATA_TYPE::DOUBLE

namespace PR
{
	enum class DATA_TYPE :char{
		STRING,TOKEN,FLOAT,DOUBLE,INT,OUTPUT
	};

	class Data
	{
	protected:
		DATA_TYPE _ty;
		Data();
		
	public:
		DATA_TYPE get_ty()const{ return _ty; }
		bool isNumeric();

		virtual bool numeric(void) const { return false; }

		virtual shared_ptr<Data> operator + (const shared_ptr<Data> &data);
		virtual shared_ptr<Data> operator * (const shared_ptr<Data> &data);
		virtual shared_ptr<Data> operator / (const shared_ptr<Data> &data);
		virtual shared_ptr<Data> operator - (const shared_ptr<Data> &data);
		virtual shared_ptr<Data> operator - ();
		virtual string toString() const;

		virtual shared_ptr<Data> mult_t(const shared_ptr<Data> &data);
		virtual shared_ptr<Data> div_t(const shared_ptr<Data> &data);
		~Data();


	};

}
