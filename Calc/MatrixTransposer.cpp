#include "stdafx.h"
#include "MatrixTransposer.h"


namespace PR
{
	/*shared_ptr<Data> MatrixTransposer::transpose(const shared_ptr<Data> &data)
	{
		switch (data->get_ty())
		{
		case DATA_TYPE::DOUBLE:
			return MatrixTransposer::transpose(*IMatrix<double>::cast_i(data));
			break;
		case DATA_TYPE::FLOAT:
			return MatrixTransposer::transpose(*IMatrix<float>::cast_i(data));
			break;
		case DATA_TYPE::INT:
			return MatrixTransposer::transpose(*IMatrix<int>::cast_i(data));
			break;
		}
	}

	template <typename T>
	shared_ptr<Data> MatrixTransposer::transpose(const IMatrix<T> &data)
	{
		int M = data.rows();
		int N = data.cols();
		
		auto result = std::make_shared<IMatrix<T>>(N, M);
		IMatrix<T> &ref = *result;

		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				ref.mx[j][i] = data.mx[i][j];
		return result;
	}*/
}
