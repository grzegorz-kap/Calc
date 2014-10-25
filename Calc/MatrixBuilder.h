#pragma once

#include "Matrix.h"
#include "IMatrixBuilder.h"
#include "TypePromotor.h"
#include "Data.h"
#include "Token.h"

namespace PR
{
	template<class T>
	class MatrixBuilder
		: public IMatrixBuilder
	{
	private:
		shared_ptr<Matrix<T>> matrix_ptr;
		vector < vector<ComplexNumber<T>>> *mx;
		int m_s;
		int n_s;
		int m;
		int n;
		vector<vector<ComplexNumber<T>>> *mx_s;
		shared_ptr<Matrix<T>> matrix_s_ptr;
		TYPE type;
		unsigned int idx;
		bool new_row_flag;
		TYPE d_type;

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
			d_type = matrix_ptr->_type;
		};

		~MatrixBuilder()
		{
		}

		bool onScalar(shared_ptr<Data> &data)
		{
			
			TYPE s_type = data->_type;
			if (s_type == TYPE::DOUBLE && d_type == TYPE::M_DOUBLE
				||s_type==TYPE::R_DOUBLE && d_type==TYPE::RM_DOUBLE)
			{
				auto ptr = dynamic_cast<ComplexNumber<T> *>(data.get());
				m_s = 1;
				prepareRows();
				mx->at(idx).push_back(*ptr);
				return true;
			}

			if (data->isNumeric() && data->_type != d_type)
				TypePromotor::convertTo(d_type, data, data);
			return false;
		}

		virtual void add(shared_ptr<Data> &data) override
		{
			if (onScalar(data))
				return;

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

		virtual shared_ptr<Data> getPtr()  const override
		{ 
			return matrix_ptr; 
		}

		virtual void setAndCheckSize(bool f = true) override
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

			mx->insert(mx->end(), idx + m_s - mx->size(), vector<ComplexNumber<T>>());
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

