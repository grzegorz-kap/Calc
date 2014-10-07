#pragma once

#include <memory>
using std::shared_ptr;

#include "Data.h"
#include "IMatrix.h"
#include "TokensTypes.h"
#include "Token.h"



namespace PR
{
	class MatrixBuilder
	{
	public:
		MatrixBuilder();
		~MatrixBuilder();

		void add(const shared_ptr<Data> &data);
		shared_ptr<Data> getPtr() { return matrix_ptr; }
		void setAndCheckSize(bool f=true);
	private:
		shared_ptr<IMatrix<mytype>> matrix_ptr;
		vector < vector<ComplexNumber<mytype>>> *mx;
		int m_s;
		int n_s;
		int m;
		int n;
		vector<vector<ComplexNumber<mytype>>> *mx_s;
		shared_ptr<IMatrix<mytype>> matrix_s_ptr;
		DATA_TYPE type;
		unsigned int idx;
		bool new_row_flag;

		void init_source(const shared_ptr<Data> &data);
		void addMatrix();
		void prepareRows();
		void changeIdxToEnd();
		
	};
}

