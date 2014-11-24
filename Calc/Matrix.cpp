#include "stdafx.h"
#include "Matrix.h"

namespace PR
{
	extern template class ComplexNumber < double > ;
	extern template class ComplexNumber < hdouble > ;

	extern template class Numeric < Matrix<double> > ;
	extern template class Numeric < Matrix<hdouble> > ;
	extern template class Numeric < ComplexNumber<double> > ;
	extern template class Numeric < ComplexNumber<hdouble> > ;

	template <class T> Matrix<T>::Matrix()
		:M(0), N(0)
	{
		setDataType();
	};


	template <class T> Matrix<T>::Matrix(const ComplexNumber<T> &b)
		:Matrix(1, 1, b)
	{
		setDataType();
	}

	template <class T> Matrix<T>::Matrix(Matrix<T> &&other)
		: M(0), N(0)
	{
		*this = std::move(other);
		setDataType();
	}

	template <class T> Matrix<T>::Matrix(const Matrix<T> &b)
		:mx(b.mx), M(b.M), N(b.N)
	{
		setDataType();
	}

	template <class T> Matrix<T>::Matrix(string &&scalar)
		: Matrix(1,1)
	{
		mx[0][0] = ComplexNumber<T>(std::move(scalar));
	}

	template <class T> Matrix<T>::Matrix(int m, int n)
		: M(m), N(n)
	{
		setDataType();
		mx.assign(m, vector<ComplexNumber<T>>(n));
	}

	template <class T> Matrix<T>::Matrix(int m, int n, const ComplexNumber<T> &value)
		:M(m), N(n)
	{
		setDataType();
		mx.assign(m, vector<ComplexNumber<T>>(n, value));
	}

	template <class T> Matrix<T>::~Matrix()
	{

	}

	template <> void Matrix<double>::setDataType()
	{
		_type = TYPE::M_DOUBLE;
	}

	template<> void Matrix<hdouble>::setDataType()
	{
		_type = TYPE::RM_DOUBLE;
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

	template <class T> Matrix<T> Matrix<T>::rdivide(const Matrix<T> &b) const
	{
		if (b.M == 1 && b.N == 1)
			return *this / b.mx[0][0];
		else if (M == 1 && N == 1)
			return b.ldivide(mx[0][0]);

		if (M != b.M || N != b.N)
			throw NumericException("/ Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] / b.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::rdivide(const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] / b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::ldivide(const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = b / mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::times(const Matrix<T> &b) const 
	{
		if (b.M == 1 && b.N == 1)
			return *this * b.mx[0][0];
		else if (M == 1 && N == 1)
			return b * mx[0][0];

		if (b.N != N || b.M != M)
			throw CalcException("Incompatibile matrix m x n");
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] * b.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::transpose() const
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

	template <class T> Matrix<T> Matrix<T>::operator + (const Matrix<T> &B) const
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

	template <class T> Matrix<T> Matrix<T>::operator + (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] + b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator - (const Matrix<T> &B) const
	{
		if (B.M == 1 && B.N == 1)
			return *this - B.mx[0][0];
		else if (M == 1 && N == 1)
			return B.sub(mx[0][0]);

		if (M != B.M || N != B.N)
			throw NumericException("- Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] - B.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::sub(const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = b - mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator - (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] - b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator * (const Matrix<T> &B) const
	{
		if (B.M == 1 && B.N == 1)
			return *this * B.mx[0][0];
		else if (M == 1 && N == 1)
			return B * mx[0][0];

		if (N != B.M)
			NumericException::throwMatrixMultDimensions();

		Matrix<T> C(M, B.N);
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

	template <class T> Matrix<T> Matrix<T>::operator * (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] * b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator / (const Matrix<T> &B) const 
	{
		if (B.M == 1 && B.N == 1)
			return *this / B.mx[0][0];
		else if (M == 1 && N == 1)
			return B.ldivide(mx[0][0]);
		
		if (M != B.M || N != B.N)
			throw NumericException("/ Matrix dimensions must agree");

		return Matrix<T>::matrix_divide(*this, B);
	}

	template <class T> Matrix<T> Matrix<T>::operator / (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] / b;
		return C;
	}

	template <class T> ComplexNumber<T>& Matrix<T>::operator()(int i, int j)
	{
		return mx[i][j];
	}

	template <class T> Matrix<T> Matrix<T>::operator == (const Matrix<T> &b) const
	{
		if (isScalar())
			return b == mx[0][0];
		if (b.isScalar())
			return *this == b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("== Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] == b.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator == (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] == b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator != (const Matrix<T> &b) const
	{
		if (isScalar())
			return b != mx[0][0];
		if (b.isScalar())
			return *this != b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("!= Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] != b.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator != (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] != b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator != (const T &b) const 
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] != b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator < (const Matrix<T> &b) const
	{
		if (isScalar())
			return b > mx[0][0];
		if (b.isScalar())
			return *this < b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("< Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] < b.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator < (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] < b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator > (const Matrix<T> &b) const
	{
		if (isScalar())
			return b < mx[0][0];
		if (b.isScalar())
			return *this > b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("> Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] > b.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator >(const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] > b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator <= (const Matrix<T> &b) const
	{
		if (isScalar())
			return b >= mx[0][0];
		if (b.isScalar())
			return *this <= b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException("<= Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] == b.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator <= (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] <= b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator >= (const Matrix<T> &b) const
	{
		if (isScalar())
			return b <= mx[0][0];
		if (b.isScalar())
			return *this >= b.mx[0][0];

		if (M != b.M || N != b.N)
			throw NumericException(">= Matrix dimensions must agree");

		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] >= b.mx[i][j];
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator >= (const ComplexNumber<T> &b) const
	{
		Matrix<T> C(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				C.mx[i][j] = mx[i][j] >= b;
		return C;
	}

	template <class T> Matrix<T> Matrix<T>::operator | (const Matrix<T> &b) const
	{
		if (M != b.M || N != b.N)
			throw NumericException("Error using | . Matrix sizes must agree");
		Matrix<T> c(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				c.mx[i][j] = mx[i][j] | b.mx[i][j];
		return c;
	}

	template <class T> Matrix<T> Matrix<T>::operator & (const Matrix<T> &b) const
	{
		if (M != b.M || N != b.N)
			throw NumericException("Error using & . Matrix sizes must agree");
		Matrix<T> c(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				c.mx[i][j] = mx[i][j] & b.mx[i][j];
		return c;
	}

	template <class T> Matrix<T> Matrix<T>::logical_not() const
	{
		if (M == 0 || N == 0)
			return Matrix<T>(1, 1, ComplexNumber<T>(0));

		Matrix<T> c(M, N);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				c.mx[i][j] = mx[i][j].logical_not();
		return c;
	}
	
	template <class T>
	ComplexNumber<T> Matrix<T>::maxValue() const
	{
		if (M == 0 || N == 0)
			return ComplexNumber<T>(0);

		ComplexNumber<T> max_value(mx[0][0]);
		for (const vector<ComplexNumber<T>> &row : mx)
		{
			auto row_max = std::max_element(row.begin(), row.end(),
				[](const ComplexNumber<T> &a, const ComplexNumber<T> &b){
				return a.getRe() < b.getRe();
			});
			if ((*row_max > max_value)==true)
				max_value = *row_max;
		}
		return max_value;
	}

	template <class T>
	ComplexNumber<T> Matrix<T>::minValue() const
	{
		if (M == 0 || N == 0)
			return ComplexNumber<T>(0);

		ComplexNumber<T> min_value(mx[0][0]);
		for (const vector<ComplexNumber<T>> &row : mx)
		{
			auto row_min = std::min_element(row.begin(), row.end(),
				[](const ComplexNumber<T> &a, const ComplexNumber<T> &b){
				return a.getRe() > b.getRe();
			});
			if ((*row_min < min_value)==true)
				min_value = *row_min;
		}
		return min_value;
	}

	template <class T>
	string Matrix<T>::maxValueString() const
	{
		return maxValue().toString();
	}

	template <class T>
	string Matrix<T>::minValueString() const
	{
		return minValue().toString();
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
	Matrix<T> Matrix<T>::getLastIndexOfCol() const
	{
		return Matrix<T>(1, 1, ComplexNumber<T>(N));
	}

	template <class T>
	Matrix<T> Matrix<T>::getLastIndexOfRow() const
	{
		return Matrix<T>(1, 1, ComplexNumber<T>(M));
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
	Matrix<T> Matrix<T>::atColumn(int idx) const
	{
		if (idx < 0)
			NumericException::throwIndexMustBeReal();
		if (idx >= N)
			NumericException::throwIndexOutOfRange();

		Matrix<T> out(M, 1);
		for (int i = 0; i < M; i++)
			out.mx[i][0] = mx[i][idx];
		return out;
	}

	template <class T>
	void Matrix<T>::assign(const Matrix<T> &data)
	{
		*this = data;
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

		if (cells.M*cells.N != data.M*data.N)
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
	void Matrix<T>::assign(const Matrix<T> &row, const Matrix<T> &col, const Matrix<T> &data)
	{
		/*
		a(I,J) = b assigns the values of b into the elements of the rectangular 
		submatrix of a specified by the subscript vectors I and J. 
		b must have LENGTH(I) rows and LENGTH(J) columns.
		*/

		if (data.isScalar())
		{
			assign(row, col, data.mx[0][0]);
			return;
		}

		int length_row = row.M*row.N;
		int length_col = col.M*col.N;
		
		if (length_row != data.M || length_col != data.N)
		{
			if (length_col == 1 == data.M && length_row == data.N ||
				length_row == 1 == data.N && length_col == data.M)
			{
				assign(row, col, data.transpose());
				return;
			}
			throw NumericException("Subscripted assignment dimension mismatch.");
		}

		row.checkForPositiveInteger();
		col.checkForPositiveInteger();
		

		int i_data = 0;
		int j_data = 0;

		for (int j_row = 0; j_row < row.N; j_row++)
		{
			for (int i_row = 0; i_row < row.M; i_row++ , j_data=0,i_data++)
			{
				int row_idx = row.mx[i_row][j_row].getReInt() - 1;
				if (row_idx >= M)
					expandRowsTo(row_idx, ComplexNumber<T>(0));
				for (int j_col = 0; j_col < col.N; j_col++)
				{
					for (int i_col = 0; i_col < col.M; i_col++)
					{
						int col_idx = col.mx[i_col][j_col].getReInt() - 1;
						if (col_idx >= N)
							expandColsTo(col_idx, ComplexNumber<T>(0));

						mx[row_idx][col_idx] = data.mx[i_data][j_data++];
					}
				}
			}
		}
	}

	template <class T>
	void Matrix<T>::assign(const Matrix<T> &row, const Matrix<T> &col, const ComplexNumber<T> &data)
	{
		row.checkForPositiveInteger();
		col.checkForPositiveInteger();

		for (int j_row = 0; j_row < row.N; j_row++)
		{
			for (int i_row = 0; i_row < row.M; i_row++)
			{
				int row_idx = row.mx[i_row][j_row].getReInt() - 1;
				if (row_idx >= M)
					expandRowsTo(row_idx, ComplexNumber<T>(0));
				for (int j_col = 0; j_col < col.N; j_col++)
				{
					for (int i_col = 0; i_col < col.M; i_col++)
					{
						int col_idx = col.mx[i_col][j_col].getReInt() - 1;
						if (col_idx >= N)
							expandColsTo(col_idx, ComplexNumber<T>(0));

						mx[row_idx][col_idx] = data;
					}
				}
			}
		}
	}

	template <class T>
	Matrix<T> Matrix<T>::getIndex(int num) const
	{
		Matrix<T> out(1, num);

		if (num==0)
		{
			out.N = -1;
			return out;
		}

		vector<ComplexNumber<T>> &ref = out.mx[0];
		int i = 1;
		for (ComplexNumber<T> &ref : ref)
		{
			ref = ComplexNumber<T>(i++);
		}
		return out;
	}

	template <class T>
	string Matrix<T>::get_cell_string(int i, int j) const
	{
		if (i >= M || j >= N)
			return "Out of range";
		return mx[i][j].toString();
	}

	template <class T>
	Matrix<T> Matrix<T>::getIndexAll() const
	{
		Matrix<T> out(M*N, 1);
		int ii = 1;
		for (int i = 0;i< out.M; i++)
			out.mx[i][0] = ComplexNumber<T>(ii++);
		return out;
	}

	template <class T>
	int Matrix<T>::getRowsCountForEmptyMatrixAssignment() const
	{
		if (M == 1 && N>1)
			return N;
		else
			return M;
	}

	template <class T>
	int Matrix<T>::getColsCountForEmptyMatrixAssignment() const
	{
		if (N == 1 && M>1)
			return M;
		else
			return N;
	}

	template <class T>
	void Matrix<T>::expandRowsTo(int idx, const ComplexNumber<T> &value)
	{
		int count = idx - M + 1;
		if (count <= 0)
			return;

		mx.insert(mx.end(), count, vector<ComplexNumber<T>>(N, value));
		M += count;
	}

	template <class T>
	void Matrix<T>::expandColsTo(int idx, const ComplexNumber<T> &value)
	{
		int count = idx - N + 1;
		if (count <= 0)
			return;

		for (auto &vec : mx)
		{
			vec.insert(vec.end(), count, value);
		}

		N += count;
	}

	template <class T>
	void Matrix<T>::checkForPositiveInteger() const
	{
		std::for_each(mx.cbegin(), mx.cend(), [](const vector<ComplexNumber<T>> &vec){
			std::for_each(vec.cbegin(), vec.cend(), [](const ComplexNumber<T> &cell){
				if (!cell.checkForPositiveInteger())
					NumericException::throwIndexMustBeReal();
			});
		});
	}

	template <class T>
	string Matrix<T>::getValueInfoString() const
	{
		if (isScalar())
			return mx[0][0].toString();
		
		return "Size: " + std::to_string(M) + "x" + std::to_string(N);
	}

	template <class T> void Matrix<T>::rows(int arg)
	{
		M = arg; 
	}

	template <class T> void Matrix<T>::cols(int arg)
	{ 
		N = arg; 
	}

	template <class T> int Matrix<T>::get_cols_int() const  
	{ 
		return N;
	}

	template <class T> int Matrix<T>::get_rows_int() const  
	{ 
		return M; 
	}

	template <class T> int * Matrix<T>::getM_P()
	{
		return &M;
	}

	template <class T> int * Matrix<T>::getN_P()
	{
		return &N;
	}

	template <class T> bool Matrix<T>::isScalar() const
	{
		return M == 1 && N == 1;
	}

	template <class T> bool Matrix<T>::isInteger() const
	{
		return isScalar() && mx[0][0].isInteger();
	}

	template <class T> bool Matrix<T>::isReal() const
	{
		for (const auto &row : mx)
			for (const auto &element : row)
				if (!element.isReal())
					return false;
		return true;
	}

	template <class T> bool Matrix<T>::isMatrix() const 
	{ 
		return true; 
	}

	template <class T> bool Matrix<T>::isEmpty() const 
	{ 
		return M <= 0 && N <= 0; 
	}

	template <class T> int Matrix<T>::toInteger() const
	{
		return mx[0][0].toInteger();
	}

	template<class T> Matrix<T> Matrix<T>::getRowIndex() const 
	{ 
		return getIndex(M);
	}

	template<class T> Matrix<T> Matrix<T>::getColIndex() const 
	{ 
		return getIndex(N); 
	}

	

	template <class T> shared_ptr<Data> Matrix<T>::copy() const
	{
		return make_shared<Matrix<T>>(*this);
	}

	template <class T> vector<double> Matrix<T>::toDoubleVector() const
	{
		if (!M)
			return vector<double>();
		vector<double> out;
		out.reserve(N);
		for (const ComplexNumber<T> &element : mx[0])
			out.push_back(element.toDouble());
		return out;
	}

	template <class T> vector<double> Matrix<T>::toDoubleVectorAll() const
	{
		vector<double> out;
		out.reserve(M*N);
		for (const auto &row : mx)
			for (const auto &cell : row)
				out.push_back(cell.toDouble());
		return out;
	}

	template <class T>
	Matrix<T>::operator ComplexNumber<double>() const
	{
		if (M&&N)
			return ComplexNumber<double>(mx[0][0]);
		else
			throw CalcException("Cannot convert empty matrix to scalar value.");
	}

	template <class T>
	Matrix<T>::operator ComplexNumber<hdouble>() const
	{
		if (M&&N)
			return ComplexNumber<hdouble>(mx[0][0]);
		else
			throw CalcException("Cannot convert empty matrix to scalar value.");
	}


	template class Matrix < double > ;
	template class Matrix < hdouble > ;
}