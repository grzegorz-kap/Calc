#include "stdafx.h"
#include "Mathematic.h"

namespace PR
{
	extern template class Matrix < double > ;
	extern template class Matrix < hdouble > ;
	extern template class ComplexNumber < double > ;
	extern template class ComplexNumber < hdouble > ;

	template<class T>
	Matrix<T> Mathematic::power(const Matrix<T> &a, const Matrix<T> &b)
	{
		if (b.isScalar())
			return Mathematic::power(a, b.mx[0][0]);

		if (a.isScalar())
		{
			Matrix<T> C(b.M, b.N);
			for (int i = 0; i < C.M; i++)
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = Mathematic::power(a.mx[0][0], b.mx[i][j]);
			return C;
		}

		if (a.M != b.M || a.N != b.N)
			throw NumericException("Error in A.^B: matrix dimensions must agree.");

		Matrix<T> C(a.M, a.N);
		for (int i = 0; i < C.M; i++)
			for (int j = 0; j < C.N; j++)
				C.mx[i][j] = Mathematic::power(a.mx[i][j], b.mx[i][j]);
		return C;
	}

	template<class T>
	ComplexNumber<T> Mathematic::power(const ComplexNumber<T> &a, const ComplexNumber<T> &b)
	{
		if (a.im == 0 && b.im == 0 && (a.re >= 0 || fmod(b.re, 1) == 0.0))
			return ComplexNumber<T>(pow(a.re, b.re));

		if (b.im != 0)
		{
			ComplexNumber<T> E(e<T>());
			auto y = b*logarithm(E, a);
			ComplexNumber<T> out;
			out.re = out.im = pow(E.re, y.re);
			out.re *= cos(y.im);
			out.im *= sin(y.im);
			return out;
		}
		else
		{
			T arg = argument(a);
			T mod = module(a);
			ComplexNumber<T> out;
			out.re = out.im = pow(mod, b.re);
			T chck = arg*b.re;
			if (chck == pi<T>() / 2.0 || chck == 3 * pi<T>() / 2.0)
				out.re = 0;
			else
				out.re *= cos(arg*b.re);
			out.im *= sin(arg*b.re);
			return out;
		}
	}

	template <class T>
	static Matrix<T> Mathematic::power(const Matrix<T> &a, const ComplexNumber<T> &b)
	{
		Matrix<T> C(a.M, a.N);
		for (int i = 0; i < a.M; i++)
			for (int j = 0; j < a.N; j++)
				C.mx[i][j] = Mathematic::power(a.mx[i][j], b);
		return C;
	}

	template<class T>
	static Matrix<T> Mathematic::mpower(const Matrix<T> &a, const Matrix<T> &b)
	{
		if (a.isScalar() && b.isScalar())
			return Mathematic::power(a.mx[0][0], b.mx[0][0]);

		if (a.isMatrix() && (!b.isScalar() || !b.isInteger() || b.mx[0][0].re < 0 || b.mx[0][0].im != 0))
			throw NumericException("A^B. Second argument must be non-negative integer.");

		if (a.M != a.N)
			throw NumericException("A^B. First argument must be scalar or square matrix.");

		int bb = b.mx[0][0].toInteger();
		if (bb == 0)
			return MatrixBuilder<T>::buildEye(a.M, a.N);

		Matrix<T> out(a);
		for (int i = 2; i <= bb; i++)
			out = out*a;
		return out;
	}

	template<class T>
	static ComplexNumber<T> Mathematic::mpower(const ComplexNumber<T> &a, const ComplexNumber<T> &b)
	{
		return power(a, b);
	}

	template<class T>
	static Matrix<T> Mathematic::logarithm(const Matrix<T> &a, const Matrix<T> &b)
	{
		if (!a.isScalar())
			NumericException::throwMatrixLogDimensions();

		const ComplexNumber<T> &ref = a.mx[0][0];

		Matrix<T> C(b.M, b.N);
		for (int i = 0; i < b.M; i++)
			for (int j = 0; j < b.N; j++)
				C.mx[i][j] = logarithm(ref, b.mx[i][j]);
		return C;
	}

	template<class T>
	static Matrix<T> Mathematic::logarithm(const Matrix<T> &a)
	{
		Matrix<T> C(a.M, a.N);
		for (int i = 0; i < a.M; i++)
			for (int j = 0; j < a.N; j++)
				C.mx[i][j] = logarithm(a.mx[i][j]);
		return C;
	}

	template <class T>
	static ComplexNumber<T> Mathematic::logarithm(const ComplexNumber<T> &a, const ComplexNumber<T> &b)
	{
		if (a.re == 0 && a.im == 0)
			NumericException::throwLogarithmZeroBase();
		if (b.re == 0 && b.im == 0)
			NumericException::throwLogarithmFromZero();
		if (a.re == 1 && b.re == 0)
			throw NumericException("Logarithm base equals zero");
		if (a.im == 0 && b.im == 0 && a.re>0 && b.re>0)
			return ComplexNumber<T>(log(b.re) / log(a.re));

		return ComplexNumber<T>(log(module(b)), argument(b)) / ComplexNumber<T>(log(module(a)), argument(a));
	}

	template <class T>
	static ComplexNumber<T> Mathematic::logarithm(const ComplexNumber<T> &b)
	{
		return logarithm(ComplexNumber<T>(boost::math::constants::e<T>()), b);
	}

	template <class T>
	static Matrix<T> Mathematic::logarithm10(const Matrix<T> &b)
	{
		Matrix<T> C(b.M, b.N);
		for (int i = 0; i < b.M; i++)
			for (int j = 0; j < b.N; j++)
				C.mx[i][j] = logarithm10(b.mx[i][j]);
		return C;
	}

	template <class T>
	static ComplexNumber<T> Mathematic::logarithm10(const ComplexNumber<T> &b)
	{
		return logarithm(ComplexNumber<T>(10), b);
	}

	template <class T>
	static Matrix<T> Mathematic::logarithm2(const Matrix<T> &b)
	{
		Matrix<T> C(b.M, b.N);
		for (int i = 0; i < b.M; i++)
			for (int j = 0; j < b.N; j++)
				C.mx[i][j] = logarithm2(b.mx[i][j]);
		return C;
	}

	template <class T>
	static ComplexNumber<T> Mathematic::logarithm2(const ComplexNumber<T> &b)
	{
		return logarithm(ComplexNumber<T>(2), b);
	}

	template <class T>
	static T Mathematic::argument(const ComplexNumber<T> &z)
	{
		if (z.re > 0)
			return atan(z.im / z.re);
		if (z.re < 0)
			return atan(z.im / z.re) + pi<T>();
		if (z.im>0)
			return 0.5*pi<T>();
		if (z.im < 0)
			return -0.5*pi<T>();
		return 0;
	}

	template <class T>
	static T Mathematic::module(const ComplexNumber<T> &z)
	{
		if (z.im == 0)
			return(abs(z.re));
		return sqrt(z.re*z.re + z.im*z.im);
	}

	template <class T>
	static ComplexNumber<T> Mathematic::sinus(const ComplexNumber<T> &z)
	{
		if (z.im == 0)
			return ComplexNumber<T>(sin(z.re));
		return ComplexNumber<T>(sin(z.re)*cosh(z.im), cos(z.re)*sinh(z.im));
	}

	template <class T>
	static Matrix<T> Mathematic::sinus(const Matrix<T> &m)
	{
		Matrix<T> out(m.M, m.N);
		for (int i = 0; i < m.M; i++)
			for (int j = 0; j < m.N; j++)
				out.mx[i][j] = sinus(m.mx[i][j]);
		return out;
	}

	template <class T>
	static ComplexNumber<T> Mathematic::cosinus(const ComplexNumber<T> &a)
	{
		if (a.im == 0)
			return ComplexNumber<T>(cos(a.re));
		int m = a.im>0 ? 1 : -1;
		return ComplexNumber<T>(cos(a.re)*cosh(a.im), sin(a.re)*sinh(a.im)*m);
	}

	template <class T>
	static Matrix<T> Mathematic::cosinus(const Matrix<T> &a)
	{
		Matrix<T> c(a.M, a.N);
		for (int i = 0; i < a.M; i++)
			for (int j = 0; j < a.N; j++)
				c.mx[i][j] = cosinus(a.mx[i][j]);
		return c;
	}

	template <class T>
	static ComplexNumber<T> Mathematic::tangens(const ComplexNumber<T> &a)
	{
		if (a.im == 0)
			return ComplexNumber<T>(tan(a.re));
		int m = a.im>0 ? 1 : -1;
		ComplexNumber<T> out;
		out.re = out.im = 1 / (cos(2 * a.re) + cosh(2 * a.im));
		out.re *= sin(2 * a.re);
		out.im *= sinh(2 * a.im);
		return out;
	}

	template <class T>
	static Matrix<T> Mathematic::tangens(const Matrix<T> &a)
	{
		Matrix<T> c(a.M, a.N);
		for (int i = 0; i < a.M; i++)
			for (int j = 0; j < a.N; j++)
				c.mx[i][j] = tangens(a.mx[i][j]);
		return c;
	}

	template <class T>
	static Matrix<T> Mathematic::cotangens(const Matrix<T> &b)
	{
		Matrix<T> C(b.M, b.N);
		for (int i = 0; i < C.M; i++)
			for (int j = 0; j < C.N; j++)
				C.mx[i][j] = cotangens(b.mx[i][j]);
		return C;
	}

	template <class T>
	static ComplexNumber<T> Mathematic::cotangens(const ComplexNumber<T> &b)
	{
		return cosinus(b) / sinus(b);
	}

	template <class T>
	static T Mathematic::fix(const T &value)
	{
		if (value < 0)
			return ceil(value);
		else
			return floor(value);
	}

	template <class T>
	static ComplexNumber<T> Mathematic::fix(const ComplexNumber<T> &val)
	{
		return ComplexNumber<T>(fix(val.re), fix(val.im));
	}

	template <class T>
	static Matrix<T> Mathematic::fix(const Matrix<T> &matrix)
	{
		Matrix<T> out(matrix.M, matrix.N);
		for (int i = 0; i < out.M; i++)
		{
			auto &o = out.mx[i];
			const auto &m = matrix.mx[i];
			for (int j = 0; j < out.N; j++)
				o[j] = fix(m[j]);
		}
		return out;
	}

	template <class T>  ComplexNumber<T> Mathematic::cfloor(const ComplexNumber<T> &a)
	{
		return ComplexNumber<T>(floor(a.re), floor(a.im));
	}

	template <class T>  Matrix<T> Mathematic::cfloor(const Matrix<T> &A)
	{
		Matrix<T> out(A.M, A.N);
		for (int i = 0; i < A.M; i++)
			for (int j = 0; j < A.N; j++)
				out.mx[i][j] = cfloor(A.mx[i][j]);
		return out;
	}

	template <class T> ComplexNumber<T> Mathematic::cceil(const ComplexNumber<T> &a)
	{
		return ComplexNumber<T>(ceil(a.re), ceil(a.im));
	}

	template <class T> Matrix<T> Mathematic::cceil(const Matrix<T> &A)
	{
		Matrix<T> out(A.M, A.N);
		for (int i = 0; i < A.M; i++)
			for (int j = 0; j < A.N; j++)
				out.mx[i][j] = cceil(A.mx[i][j]);
		return out;
	}

	template <class T> ComplexNumber<T> Mathematic::cmod(const ComplexNumber<T> &a, const ComplexNumber<T> &b)
	{
		if (!a.isReal() || !b.isReal())
			throw NumericException("Error using mod. Arguments must be real.");
		T val = fmod(a.re, b.re);
		if (val != 0 && (a.re < 0 && b.re>0 || a.re > 0 && b.re < 0))
			val += b.re;
		return ComplexNumber<T>(val);
	}

	template <class T> Matrix<T> Mathematic::cmod(const Matrix<T> &A, const ComplexNumber<T> &b)
	{
		Matrix<T> C(A.M, A.N);
		for (int i = 0; i < A.M; i++)
			for (int j = 0; j < A.N; j++)
				C.mx[i][j] = cmod(A.mx[i][j], b);
		return C;
	}

	template <class T> Matrix<T> Mathematic::cmod(const Matrix<T> &A, const Matrix<T> &B)
	{
		if (B.isScalar())
			return cmod(A, B.mx[0][0]);

		if (A.M != B.M || A.N != B.N)
			throw NumericException("Error using mod. Matrix sizes must agree!");

		Matrix<T> C(A.M, A.N);
		for (int i = 0; i < A.M; i++)
			for (int j = 0; j < A.N; j++)
				C.mx[i][j] = cmod(A.mx[i][j], B.mx[i][j]);
		return C;
	}

	template <class T> ComplexNumber<T> Mathematic::cround(const ComplexNumber<T> &a)
	{
		return ComplexNumber<T>(round(a.re), round(a.im));
	}

	template <class T> Matrix<T> Mathematic::cround(const Matrix<T> &A)
	{
		Matrix<T> out(A.M, A.N);
		for (int i = 0; i < A.M; i++)
			for (int j = 0; j < A.N; j++)
				out.mx[i][j] = cround(A.mx[i][j]);
		return out;
	}

	template Matrix<double> Mathematic::cround(const Matrix<double> &);
	template Matrix<hdouble> Mathematic::cround(const Matrix<hdouble> &);
	template ComplexNumber<double> Mathematic::cround(const ComplexNumber<double> &);
	template ComplexNumber<hdouble> Mathematic::cround(const ComplexNumber<hdouble> &);

	template Matrix<double> Mathematic::cmod(const Matrix<double> &, const Matrix<double> &);
	template Matrix<hdouble> Mathematic::cmod(const Matrix<hdouble> &, const Matrix<hdouble> &);
	template Matrix<double> Mathematic::cmod(const Matrix<double> &, const ComplexNumber<double> &);
	template Matrix<hdouble> Mathematic::cmod(const Matrix<hdouble> &, const ComplexNumber<hdouble> &);
	template ComplexNumber<double> Mathematic::cmod(const ComplexNumber<double> &, const ComplexNumber<double> &);
	template ComplexNumber<hdouble> Mathematic::cmod(const ComplexNumber<hdouble> &, const ComplexNumber<hdouble> &);

	template ComplexNumber<double> Mathematic::cceil(const ComplexNumber<double> &);
	template ComplexNumber<hdouble> Mathematic::cceil(const ComplexNumber<hdouble> &);
	template Matrix<double> Mathematic::cceil(const Matrix<double> &);
	template Matrix<hdouble> Mathematic::cceil(const Matrix<hdouble> &);

	template ComplexNumber<double> Mathematic::cfloor(const ComplexNumber<double> &);
	template ComplexNumber<hdouble> Mathematic::cfloor(const ComplexNumber<hdouble> &);
	template Matrix<double> Mathematic::cfloor(const Matrix<double> &);
	template Matrix<hdouble> Mathematic::cfloor(const Matrix<hdouble> &);

	template double Mathematic::fix(const double &);
	template hdouble Mathematic::fix(const hdouble &);
	template Matrix<double> Mathematic::fix(const Matrix<double>&);
	template Matrix<hdouble> Mathematic::fix(const Matrix<hdouble>&);
	template ComplexNumber<double> Mathematic::fix(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::fix(const ComplexNumber<hdouble>&);

	template double Mathematic::argument(const ComplexNumber<double> &);
	template hdouble Mathematic::argument(const ComplexNumber<hdouble> &);
	template double Mathematic::module(const ComplexNumber<double> &);
	template hdouble Mathematic::module(const ComplexNumber<hdouble> &);

	template Matrix<double> Mathematic::sinus(const Matrix<double>&);
	template Matrix<hdouble> Mathematic::sinus(const Matrix<hdouble>&);
	template Matrix<double> Mathematic::cosinus(const Matrix<double>&);
	template Matrix<hdouble> Mathematic::cosinus(const Matrix<hdouble>&);
	template Matrix<double> Mathematic::tangens(const Matrix<double>&);
	template Matrix<hdouble> Mathematic::tangens(const Matrix<hdouble>&);
	template Matrix<double> Mathematic::cotangens(const Matrix<double>&);
	template Matrix<hdouble> Mathematic::cotangens(const Matrix<hdouble>&);

	template ComplexNumber<double> Mathematic::sinus(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::sinus(const ComplexNumber<hdouble>&);
	template ComplexNumber<double> Mathematic::cosinus(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::cosinus(const ComplexNumber<hdouble>&);
	template ComplexNumber<double> Mathematic::tangens(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::tangens(const ComplexNumber<hdouble>&);
	template ComplexNumber<double> Mathematic::cotangens(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::cotangens(const ComplexNumber<hdouble>&);

	template Matrix<double> Mathematic::power(const Matrix<double>&, const Matrix<double>&);
	template Matrix<hdouble> Mathematic::power(const Matrix<hdouble>&, const Matrix<hdouble>&);
	template ComplexNumber<double> Mathematic::power(const ComplexNumber<double>&, const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::power(const ComplexNumber<hdouble>&, const ComplexNumber<hdouble>&);
	template Matrix<double> Mathematic::power(const Matrix<double>&, const ComplexNumber<double>&);
	template Matrix<hdouble> Mathematic::power(const Matrix<hdouble>&, const ComplexNumber<hdouble>&);

	template Matrix<double> Mathematic::mpower(const Matrix<double>&, const Matrix<double>&);
	template Matrix<hdouble> Mathematic::mpower(const Matrix<hdouble>&, const Matrix<hdouble>&);
	template ComplexNumber<double> Mathematic::mpower(const ComplexNumber<double>&, const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::mpower(const ComplexNumber<hdouble>&, const ComplexNumber<hdouble>&);

	template Matrix<double> Mathematic::logarithm(const Matrix<double>&, const Matrix<double>&);
	template Matrix<hdouble> Mathematic::logarithm(const Matrix<hdouble>&, const Matrix<hdouble>&);
	template Matrix<double> Mathematic::logarithm(const Matrix<double>&);
	template Matrix<hdouble> Mathematic::logarithm(const Matrix<hdouble>&);
	template ComplexNumber<double> Mathematic::logarithm(const ComplexNumber<double>&, const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::logarithm(const ComplexNumber<hdouble>&, const ComplexNumber<hdouble>&);
	template ComplexNumber<double> Mathematic::logarithm(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::logarithm(const ComplexNumber<hdouble>&);

	template Matrix<double> Mathematic::logarithm10(const Matrix<double>&);
	template Matrix<hdouble> Mathematic::logarithm10(const Matrix<hdouble>&);
	template ComplexNumber<double> Mathematic::logarithm10(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::logarithm10(const ComplexNumber<hdouble>&);
	template Matrix<double> Mathematic::logarithm2(const Matrix<double>&);
	template Matrix<hdouble> Mathematic::logarithm2(const Matrix<hdouble>&);
	template ComplexNumber<double> Mathematic::logarithm2(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> Mathematic::logarithm2(const ComplexNumber<hdouble>&);
}