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

	template <class T> Matrix<T>::~Matrix()
	{

	}

	template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix<T> &b)
	{
		if (this != &b)
		{
			mx = b.mx;
			M = b.M;
			N = b.N;
		}
		return *this;
	}

	template <class T> Matrix<T>& Matrix<T>::operator=(Matrix<T> &&other)
	{
		if (this != &other)
		{
			mx = std::move(other.mx);
			M = other.M;
			N = other.N;
			other.M = 0;
			other.N = 0;

		}
		return *this;
	}

	template <class T> template <class U>
	auto Matrix<T>::rdivide(const Matrix<U> &b) const -> Matrix<decltype(T() + U())>
	{
		if (b.M == 1 && b.N == 1)
			return *this / b.mx[0][0];
		else if (M == 1 && N == 1)
			return b.ldivide(mx[0][0]);

		if (M != b.M || N != b.N)
			throw NumericException("/ Matrix dimensions must agree");

		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] / b.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::rdivide(const ComplexNumber<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] / b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::ldivide(const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = b / mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::times(const Matrix<U> &b) const -> Matrix<decltype(T() + U())>
	{
		if (b.M == 1 && b.N == 1)
			return *this * b.mx[0][0];
		else if (M == 1 && N == 1)
			return b * mx[0][0];

		if (b.N != N || b.M != M)
			throw CalcException("Incompatibile matrix m x n");
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] + b.mx[i][j];
		return C;
	}

	template <class T>
	Matrix<T> Matrix<T>::transpose() const
	{
		Matrix<T> C(N, M);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[j][i] = mx[i][j];
		return std::move(C);
	}

	template <class T> int Matrix<T>::rows() const
	{
		return mx.size();
	}

	template <class T> int Matrix<T>::cols() const
	{
		if (mx.size() > 0)
			return (int)mx[0].size();
		else
			return 0;
	}

	template <class T> Matrix<T> Matrix<T>::neg() const
	{
		Matrix<T> out(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				out.mx[i][j] = mx[i][j].neg();
		return out;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator + (const Matrix<U> &B) const -> Matrix<decltype(T() + U())>
	{
		if (B.M == 1 && B.N == 1)
			return *this + B.mx[0][0];
		else if (M == 1 && N == 1)
			return B + mx[0][0];

		if (M != B.M || N != B.N)
			throw NumericException("+ Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] + B.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator + (const ComplexNumber<U> &b) const -> Matrix<decltype(T() + U())>
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] + b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator - (const Matrix<U> &B) const -> Matrix<decltype(T() + U())>
	{
		if (B.M == 1 && B.N == 1)
			return *this - B.mx[0][0];
		else if (M == 1 && N == 1)
			return B.sub(mx[0][0]);

		if (M != B.M || N != B.N)
			throw NumericException("- Matrix dimensions must agree");

		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] - B.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::sub(const ComplexNumber<U> &b) const -> Matrix<decltype(T() + U())>
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = b - mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator - (const ComplexNumber<U> &b) const -> Matrix<decltype(T() + U())>
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] - b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator * (const Matrix<U> &B) const -> Matrix<decltype(T() + U())>
	{
		if (B.M == 1 && B.N == 1)
			return *this * B.mx[0][0];
		else if (M == 1 && N == 1)
			return B * mx[0][0];

		if (N != B.M)
			NumericException::throwMatrixMultDimensions();

		Matrix<decltype(T() + U())> C(M, B.N);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < B.N; j++)
			{
				ComplexNumber<T> temp(0.0);
				for (int k = 0; k < N; k++)
					temp += mx[i][k] * B.mx[k][j];
				C.mx[i][j] = std::move(temp);
			}
		}
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator * (const ComplexNumber<U> &b) const ->Matrix<decltype(T() + U())>
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] * b;
		return C;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator / (const Matrix<T> &B) const 
	{
		if (B.M == 1 && B.N == 1)
			return *this / B.mx[0][0];
		else if (M == 1 && N == 1)
			return B.ldivide(mx[0][0]);
		
		if (M != B.M || N != B.N)
			throw NumericException("/ Matrix dimensions must agree");

		return Matrix<T>::matrix_divide(*this, B);
	}

	template <class T> template <class U>
	auto Matrix<T>::operator / (const ComplexNumber<U> &b) const
		->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] / b;
		return C;
	}

	template <class T>
	ComplexNumber<T>& Matrix<T>::operator()(int i, int j)
	{
		return mx[i][j];
	}

	template <class T> template <class U>
	auto Matrix<T>::operator == (const Matrix<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		if (isScalar())
			return b == mx[0][0];
		if (b.isScalar())
			return *this == b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("== Matrix dimensions must agree");

		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] == b.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator == (const ComplexNumber<U> &b) const
		->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] == b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator != (const Matrix<U> &b) const
		->Matrix < decltype(T() + U()) >
	{
		if (isScalar())
			return b != mx[0][0];
		if (b.isScalar())
			return *this != b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("!= Matrix dimensions must agree");

		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] != b.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator != (const ComplexNumber<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] != b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator != (const U &b) const ->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] != b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator < (const Matrix<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		if (isScalar())
			return b > mx[0][0];
		if (b.isScalar())
			return *this < b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("< Matrix dimensions must agree");

		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] < b.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator < (const ComplexNumber<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] < b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator > (const Matrix<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		if (isScalar())
			return b < mx[0][0];
		if (b.isScalar())
			return *this > b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("> Matrix dimensions must agree");

		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] > b.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator >(const ComplexNumber<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] > b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator <= (const Matrix<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		if (isScalar())
			return b >= mx[0][0];
		if (b.isScalar())
			return *this <= b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("<= Matrix dimensions must agree");

		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] == b.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator <= (const ComplexNumber<U> &b) const
		->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] <= b;
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator >= (const Matrix<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		if (isScalar())
			return b <= mx[0][0];
		if (b.isScalar())
			return *this >= b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException(">= Matrix dimensions must agree");

		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] >= b.mx[i][j];
		return C;
	}

	template <class T> template <class U>
	auto Matrix<T>::operator >= (const ComplexNumber<U> &b) const ->Matrix < decltype(T() + U()) >
	{
		Matrix<decltype(T() + U())> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] >= b;
		return C;
	}

	template <class T> 
	vector<vector<ComplexNumber<T>>>* Matrix<T>::getVector()
	{
		return &mx; 
	}

	template <class T> string Matrix<T>::toString() const
	{
		if (M == 0 && N == 0)
			return "[ ]";

		string temp = "";
		for (int i = 0; i < M; i++)
		{
			temp.append("\n");
			for (int j = 0; j < N; j++)
				temp.append("\t" + mx[i][j].toString());
		}
		return temp;
	}

	template <class T> string Matrix<T>::toHtml() const
	{
		if (M == 0 && N == 0)
			return "[ ]";
		string temp = "<table>";
		for (int i = 0; i < M; i++)
		{
			temp += "<tr>";
			for (int j = 0; j < N; j++)
				temp += "<td>" + mx[i][j].toString() + "&nbsp; &nbsp; &nbsp;</td>";
			temp += "</tr>";
		}
		temp += "</table>";
		return temp;
	}

	template <class T> bool Matrix<T>::operator == (const bool &b) const
	{
		if (b)
			return checkIfTrue();
		else
			return checkIfFalse();
	}

	template <class T> bool Matrix<T>::checkIfTrue() const
	{
		if (M == 0 || N == 0)
			return false;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				if (mx[i][j] == 0)
					return false;
		return true;
	}

	template <class T> bool Matrix<T>::checkIfFalse() const
	{
		if (M == 0 || N == 0)
			return true;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				if (mx[i][j] == 0)
					return true;
		return false;
	}

	template <>
	Matrix<double>::operator Matrix<hdouble>() const
	{
		Matrix<hdouble> out(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				out.mx[i][j] = mx[i][j];
		return out;
	}

	template <>
	Matrix<hdouble>::operator Matrix<double>() const
	{
		Matrix<double> out(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				out.mx[i][j] = mx[i][j];
		return out;
	}

	template <class T>
	Matrix<T> Matrix<T>::at(const Matrix<T> &a) const
	{
		Matrix<T> out(a.M, a.N);
		int idx_max = M*N;
		for (int i = 0; i < a.M; i++)
		{
			for (int j = 0; j < a.N; j++)
			{
				const ComplexNumber<T> &ref = a.mx[i][j];
				if (!ref.checkForPositiveInteger())
					NumericException::throwIndexMustBeReal();
				if (ref.re > idx_max)
					NumericException::throwIndexOutOfRange();
				int row, col;
				ref.computeIndex(M, row, col);
				out.mx[i][j] = mx[row][col];
			}
		}
		return out;
	}

	template <class T>
	Matrix<T> Matrix<T>::at(const Matrix<T> &first, const Matrix<T> &second) const
	{
		Matrix<T> out(first.M*first.N, second.M*second.N);
		int row = 0;
		for (int j = 0; j < first.N; j++)
		{
			for (int i = 0; i < first.M; i++)
			{
				const ComplexNumber<T> &fcell = first.mx[i][j];
				if (!fcell.checkForPositiveInteger())
					NumericException::throwIndexMustBeReal();
				int row_idx = fcell.getReInt()-1;
				int col = 0;
				if (row_idx >= M)
					NumericException::throwIndexOutOfRange();

				for (int jj = 0; jj < second.N; jj++)
				{
					for (int ii = 0; ii < second.M; ii++)
					{
						const ComplexNumber<T> &scell = second.mx[ii][jj];
						if (!scell.checkForPositiveInteger())
							NumericException::throwIndexMustBeReal();
						int col_idx = scell.getReInt()-1;
						if (col_idx >= N)
							NumericException::throwIndexOutOfRange();

						out.mx[row][col] = mx[row_idx][col_idx];

						col++;
					}
				}

				row++;
			}
		}

		return out;
	}

	template <class T>
	void Matrix<T>::assign(const Matrix<T> &cells, const ComplexNumber<T> &data)
	{
		int idx_max = M*N;
		for (int j = 0; j<cells.N; j++)
		{
			for (int i = 0; i < cells.M; i++)
			{
				const ComplexNumber<T> &ref = cells.mx[i][j];
				if (!ref.checkForPositiveInteger())
					NumericException::throwIndexMustBeReal();
				if (ref.re > idx_max)
					NumericException::throwIndexOutOfRange();
				int row, col;
				ref.computeIndex(M, row, col);
				mx[row][col] = data;
			}
		}
	}

	template <class T>
	void Matrix<T>::assign(const Matrix<T> &cells, const Matrix<T> &data)
	{
		
		if (data.isScalar())
		{
			assign(cells, data.mx[0][0]);
			return;
		}

		if (cells.M*cells.N != data.M*data.N )
			throw NumericException("In an assignment  A(I) = B, the number of elements in B and I must be the same.");

		int idx_max = M*N;
		int i_data = 0;
		int j_data = 0;
		for (int j = 0; j<cells.N; j++)
		{
			for (int i = 0; i < cells.M; i++)
			{
				const ComplexNumber<T> &ref = cells.mx[i][j];
				if (!ref.checkForPositiveInteger())
					NumericException::throwIndexMustBeReal();
				if (ref.re > idx_max)
					NumericException::throwIndexOutOfRange();
				int row, col;
				ref.computeIndex(M, row, col);

				mx[row][col] = data.mx[i_data++][j_data];
				if (i_data >= data.M)
				{
					i_data = 0;
					j_data++;
				}
			}
		}
	}


	template <class T>
	void Matrix<T>::assign(const Matrix<T> &data)
	{
		*this = data;
	}

	template class Matrix < double > ;
	template class Matrix < hdouble > ;
}