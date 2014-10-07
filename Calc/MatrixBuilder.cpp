#include "stdafx.h"
#include "MatrixBuilder.h"


namespace PR
{
	MatrixBuilder::MatrixBuilder()
	{
		matrix_ptr = std::make_shared<IMatrix<mytype>>(0, 0);
		mx = matrix_ptr->getVector();
		idx = 0;
		m = 0;
		n = 0;
		new_row_flag = true;
	}


	MatrixBuilder::~MatrixBuilder()
	{
	}

	void MatrixBuilder::add(const shared_ptr<Data> &data)
	{
		init_source(data);

		if (data->isNumeric())
		{
			addMatrix();
		}
		else if (type == DATA_TYPE::TOKEN && std::dynamic_pointer_cast<Token>(data)->getType() == TOKEN_CLASS::VERSE_END)
		{
			setAndCheckSize();
			changeIdxToEnd();
		}

		
	}

	void MatrixBuilder::addMatrix()
	{
		prepareRows();

		for (int i = 0; i < m_s; i++)
		{
			mx->at(idx+i).insert(mx->at(idx+i).end(), mx_s->at(i).begin(), mx_s->at(i).end());
		}
	}

	void MatrixBuilder::setAndCheckSize(bool f)
	{
		m = mx->size();
		n = m ? mx->at(0).size() : 0;

		for (auto i = mx->begin(); i != mx->end(); i++)
			if (i->size() != n)
				throw CalcException("Inconsintent cols count");
		if (f)
		{
			matrix_ptr->rows(m);
			matrix_ptr->cols(n);
		}
	}

	void MatrixBuilder::changeIdxToEnd()
	{
		if (idx != mx->size())
		{
			new_row_flag = true;
			idx = mx->size();
		}
	}

	void MatrixBuilder::prepareRows()
	{
		if (idx + m_s <= mx->size())
			return;

		if (!new_row_flag)
			throw CalcException("Matrix sizes not match!");

		new_row_flag = false;

		mx->insert(mx->end(), idx + m_s - mx->size(), vector<ComplexNumber<mytype>>());
	}

	void MatrixBuilder::init_source(const shared_ptr<Data> &data)
	{
		type = data->get_ty();
		if (!data->isNumeric())
			return;

		matrix_s_ptr = std::dynamic_pointer_cast<IMatrix<mytype>>(data);
		mx_s = matrix_s_ptr->getVector();
		m_s = matrix_s_ptr->rows();
		n_s = matrix_s_ptr->cols();
	}
}
