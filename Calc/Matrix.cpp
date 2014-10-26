#include "stdafx.h"
#include "Matrix.h"

namespace PR
{
	template <class T> Matrix<T>::Matrix()
		:M(0), N(0)
	{
		_type = Data::find_type(typeid(*this));
	};

	template <class T> Matrix<T>::Matrix(const ComplexNumber<T> &b)
		:Matrix(1, 1, b)
	{
		_type = Data::find_type(typeid(*this));
	}

	template <class T> Matrix<T>::Matrix(Matrix<T> &&other)
		: M(0), N(0)
	{
		*this = std::move(other);
		_type = Data::find_type(typeid(*this));
	}

	template <class T> Matrix<T>::Matrix(const Matrix<T> &b)
		:mx(b.mx), M(b.M), N(b.N)
	{
		_type = Data::find_type(typeid(*this));
	}

	template <class T> Matrix<T>::Matrix(string &&scalar)
		: Matrix(1,1)
	{
		mx[0][0] = ComplexNumber<T>(std::move(scalar));
	}

	template <class T> Matrix<T>::Matrix(int m, int n)
		: M(m), N(n)
	{
		_type = Data::find_type(typeid(*this));
		mx.assign(m, vector<ComplexNumber<T>>(n));
	}

	template <class T> Matrix<T>::Matrix(int m, int n, const ComplexNumber<T> &value)
		:M(m), N(n)
	{
		_type = Data::find_type(typeid(*this));
		mx.assign(m, vector<ComplexNumber<T>>(n, value));
	}

	template <class T>
	Matrix<T>::~Matrix()
	{

	}

	template class Matrix < double > ;
	template class Matrix < hdouble > ;
}