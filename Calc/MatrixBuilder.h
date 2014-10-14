#pragma once

#include "Matrix.h"

namespace PR
{
	template<class T>
	class MatrixBuilder
	{
	private:
		shared_ptr<Matrix<T>> matrix_ptr;
		vector < vector<T>> *mx;
		int m_s;
		int n_s;
		int m;
		int n;
		vector<vector<T>> *mx_s;
		shared_ptr<Matrix<T>> matrix_s_ptr;
		TYPE type;
		unsigned int idx;
		bool new_row_flag;

	public:
		
		MatrixBuilder()
			:
			matrix_ptr(make_shared<Matrix<T>>(0,0)),
			idx(0),
			m(0),
			n(0),
			new_row_flag(true)
		{
			mx = matrix_ptr->getVector();
		};

		~MatrixBuilder()
		{
		}

		void add(shared_ptr<Data> &data)
		{
			init_source(data);
			if (data->isNumeric())
			{
				addMatrix();
			}
			else if (type == TYPE::TOKEN && std::dynamic_pointer_cast<Token>(data)->getClass() == TOKEN_CLASS::VERSE_END)
			{
				setAndCheckSize();
				changeIdxToEnd();
			}
		}

		shared_ptr<Data> getPtr() 
		{ 
			return matrix_ptr; 
		}

		void setAndCheckSize(bool f = true)
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

	private:

		void init_source(const shared_ptr<Data> &data)
		{
			type = data->_type;
			if (!data->isNumeric())
				return;

			matrix_s_ptr = std::dynamic_pointer_cast<Matrix<T>>(data);
			mx_s = matrix_s_ptr->getVector();
			m_s = matrix_s_ptr->rows();
			n_s = matrix_s_ptr->cols();
		}

		void addMatrix()
		{
			prepareRows();

			for (int i = 0; i < m_s; i++)
			{
				mx->at(idx + i).insert(mx->at(idx + i).end(), mx_s->at(i).begin(), mx_s->at(i).end());
			}
		}

		void prepareRows()
		{
			if (idx + m_s <= mx->size())
				return;

			if (!new_row_flag)
				throw CalcException("Matrix sizes not match!");

			new_row_flag = false;

			mx->insert(mx->end(), idx + m_s - mx->size(), vector<T>());
		}
		
		void changeIdxToEnd()
		{
			if (idx != mx->size())
			{
				new_row_flag = true;
				idx = mx->size();
			}
		}
		
	};
}

