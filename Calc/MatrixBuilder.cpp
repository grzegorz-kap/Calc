#include "stdafx.h"
#include "MatrixBuilder.h"

namespace KLab
{
	extern template class Matrix < double > ;
	extern template class Matrix < hdouble > ;
	extern template class ComplexNumber < double > ;
	extern template class ComplexNumber < hdouble > ;

	template <class T>
	MatrixBuilder<T>::MatrixBuilder()
		:
		matrix_ptr(make_shared<Matrix<T>>(0, 0)),
		idx(0),
		m(0),
		n(0),
		new_row_flag(true)
	{
		mx = matrix_ptr->getVector();
		d_type = matrix_ptr->_type;
	};

	template <class T>
	MatrixBuilder<T>::~MatrixBuilder()
	{
	}

	template <class T>
	shared_ptr < Data > MatrixBuilder<T>::getPtr() const
	{
		return matrix_ptr;
	}

	template <class T>
	void MatrixBuilder<T>::setAndCheckSize(bool f = true)
	{
		m = mx->size();
		n = m ? mx->at(0).size() : 0;

		for (auto i = mx->begin(); i != mx->end(); i++)
			if (i->size() != n)
				throw CalcException("Dimensions of matrices being concatenated are not consistent.");
		if (f)
		{
			matrix_ptr->rows(m);
			matrix_ptr->cols(n);
		}
	}

	template <class T>
	bool MatrixBuilder<T>::onScalar(shared_ptr<Data> &data)
	{
		TYPE s_type = data->_type;
		if (data->isComplexNumber() && IMatrixBuilder::getAssociatedType(s_type) == d_type)
		{
			auto ptr = dynamic_cast<ComplexNumber<T> *>(data.get());
			m_s = 1;
			prepareRows();
			mx->at(idx).push_back(*ptr);
			return true;
		}
		if (data->isNumeric())
			TypePromotor::promote(data, d_type);
		return false;
	}

	template <class T>
	void MatrixBuilder<T>::add(shared_ptr<Data> &data)
	{
		if (onScalar(data))
			return;

		init_source(data);
		if (data->isNumeric() && m_s != 0 && n_s != 0)
		{
			addMatrix();
		}
		else if (type == TYPE::TOKEN && data->cast_token()->getTokenClass() == TOKEN_CLASS::VERSE_END)
		{
			setAndCheckSize();
			changeIdxToEnd();
		}
	}

	template <class T>
	Matrix<T> MatrixBuilder<T>::buildEye(int m, int n)
	{
		Matrix<T> out(m, n, 0);
		for (int i = 0; i < m && i < n; i++)
			out.mx[i][i] = ComplexNumber<T>(1);
		return out;
	}

	template <class T>
	Matrix<T> MatrixBuilder<T>::buildOnes(int m, int n)
	{
		Matrix<T> out(m, n, 1);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				out.mx[i][j] = ComplexNumber<T>(1);
		return out;
	}

	template <class T>
	Matrix<T> MatrixBuilder<T>::buildRand(int m, int n)
	{
		if (m < 0 || n < 0)
			return Matrix<T>();

		Matrix<double> out(m, n);
		for (auto &vec : out.mx)
			for (auto &element : vec)
				element = ComplexNumber<T>(rand());
		return out;
	}

	template <class T>
	void MatrixBuilder<T>::init_source(const shared_ptr<Data> &data)
	{
		type = data->_type;
		if (!data->isNumeric())
			return;

		matrix_s_ptr = std::dynamic_pointer_cast<Matrix<T>>(data);
		mx_s = matrix_s_ptr->getVector();
		m_s = matrix_s_ptr->rows();
		n_s = matrix_s_ptr->cols();
	}

	template <class T>
	void MatrixBuilder<T>::addMatrix()
	{
		prepareRows();
		for (int i = 0; i < m_s; i++)
			mx->at(idx + i).insert(mx->at(idx + i).end(), mx_s->at(i).begin(), mx_s->at(i).end());
	}

	template <class T>
	void MatrixBuilder<T>::prepareRows()
	{
		if (idx + m_s <= mx->size())
			return;

		if (!new_row_flag)
			throw CalcException("Matrix sizes not match!");

		new_row_flag = false;

		mx->insert(mx->end(), idx + m_s - mx->size(), vector<ComplexNumber<T>>());
	}

	template <class T>
	void MatrixBuilder<T>::changeIdxToEnd()
	{
		if (idx != mx->size())
		{
			new_row_flag = true;
			idx = mx->size();
		}
	}

	template class MatrixBuilder < double > ;
	template class MatrixBuilder < hdouble > ;
}