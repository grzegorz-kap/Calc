#pragma once

#include <string>

using std::string;

#include "Matrix.h"
#include "Data.h"

namespace PR
{
	template<class T>
	class IMatrix : public Matrix<T> , public Data
	{
	public:

		IMatrix(const Matrix<T> &b)
			:Matrix(b)
		{
			setType();
		}

		IMatrix()
		{
			setType();
		};

		IMatrix(const string &value)
			:Matrix(value)
		{
			setType();
		}

		IMatrix(int m, int n)
			:Matrix(m,n)
		{
			setType();
		}

		IMatrix(int m, int n, T re, T im = 0.0)
			:Matrix(m,n,re,im)
		{
			setType();
		}

		IMatrix(int m, int n, const ComplexNumber<T> &value)
			:Matrix(m,n,value)
		{
			setType();
		}

		~IMatrix(){};

		virtual string toString() const
		{
			return Matrix::toString();
		}

		static shared_ptr<Matrix<T>> cast(const shared_ptr<Data> &b,bool withEx = true)
		{
			auto temp = std::dynamic_pointer_cast<Matrix<T>>(b);
			
			

			if (withEx && temp == nullptr)
				throw CalcException("Cannot convert to numeric type");

			return temp;
		}

		operator IMatrix<int>()
		{
			return (IMatrix<int>)*this;
		}

		static shared_ptr<IMatrix<T>> cast_i(const shared_ptr<Data> &b, bool withEx = true)
		{
			auto temp = std::dynamic_pointer_cast<IMatrix<T>>(b);

			if (withEx && temp == nullptr)
				throw CalcException("Cannot convert to numeric type");

			return temp;
		}

		virtual shared_ptr<Data> operator+(const shared_ptr<Data> &b)
		{
			auto p_b = IMatrix::cast(b);
			return shared_ptr<Data>(new IMatrix<T>(*p_b + *dynamic_cast<Matrix<T> *>(this)));
		}

		virtual shared_ptr<Data> operator-(const  shared_ptr<Data> &b)
		{
			auto p_b = IMatrix::cast(b);
			return shared_ptr<Data>(new IMatrix<T>(*p_b - *this));
		}

		virtual shared_ptr<Data> div(const shared_ptr<Data> a, const  shared_ptr<Data> b)
		{
			auto p_a = IMatrix::cast(a);
			auto p_b = IMatrix::cast(b);
			return shared_ptr<Data>(new IMatrix<T>(*p_a / *p_b));
		}

		virtual shared_ptr<Data> operator/(const shared_ptr<Data> &b)
		{
			return shared_ptr<Data>(new IMatrix<T>(*IMatrix::cast(b) / *this));
		}

		virtual shared_ptr<Data> operator*(const  shared_ptr<Data> &b)
		{
			auto p_b = IMatrix::cast(b);
			return shared_ptr<Data>(new IMatrix<T>(*p_b**this));
		}

		virtual shared_ptr<Data> operator-()
		{
			return shared_ptr<Data>(new IMatrix<T>(neg()));
		}

		virtual shared_ptr<Data> mult_t(const shared_ptr<Data> &b)
		{
			auto p_b = IMatrix::cast(b);
			return shared_ptr<Data>(new IMatrix<T>(p_b->mult_t(*this)));
		}

		virtual shared_ptr<Data> div_t(const shared_ptr<Data> &b)
		{
			auto p_b = IMatrix::cast(b);
			return shared_ptr<Data>(new IMatrix<T>(p_b->div_t(*this)));
		}

	private:
		void setType()
		{
			if (std::is_same<T, float>::value)
				_ty = DATA_TYPE::FLOAT;
			else if (std::is_same<T, int>::value)
				_ty = DATA_TYPE::INT;
			else if (std::is_same<T, double>::value)
				_ty = DATA_TYPE::DOUBLE;
		}
	};

}
