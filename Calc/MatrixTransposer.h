#pragma once

#include "Matrix.h"
#include "IMatrix.h"
#include "Data.h"

namespace PR
{
	class MatrixTransposer
	{

	private:
		MatrixTransposer();
	public:
		
		static shared_ptr<Data> transpose(const shared_ptr<Data> &data);
		~MatrixTransposer();

	private:

		template <typename T>
		static shared_ptr<Data> transpose(const IMatrix<T> &data);
	};


}