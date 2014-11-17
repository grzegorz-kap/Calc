#pragma once

#include <cstdlib>
#include <ctime>

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
		MatrixBuilder();
		~MatrixBuilder();
		virtual shared_ptr<Data> getPtr()  const override;
		virtual void add(shared_ptr<Data> &data) override;
		virtual void setAndCheckSize(bool f = true) override;
		static Matrix<T> buildEye(int m, int n);
		
		static Matrix<T> buildRand(int m, int n)
		{
			if (m < 0 || n < 0)
				return Matrix<T>();

			Matrix<double> out(m, n);
			for (auto &vec : out.mx)
				for (auto &element : vec)
					element = ComplexNumber<T>(rand() / 1000.0);
			return out;
		}

	private:	
		bool onScalar(shared_ptr<Data> &data);	
		void init_source(const shared_ptr<Data> &data);
		void addMatrix();
		void prepareRows();	
		void changeIdxToEnd();
		
	};
}

