#pragma once

#include "NumericException.h"
#include "Matrix.h"
#include "ComplexNumber.h"

#include <boost\math\constants\constants.hpp>

using namespace boost::math::constants;



namespace PR
{
	template <class X> class Matrix;
	template <class X> class ComplexNumber;

	class Mathematic
	{
	public:
		Mathematic() = delete;
		~Mathematic() = delete;

		template<class T> static Matrix<T> power(const Matrix<T> &a, const Matrix<T> &b)
		{
			if (b.isScalar())
				return Mathematic::power(a, b.mx[0][0]);

			Matrix<T> C(a.M, a.N);
			for (int i = 0; i < C.M; i++)
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = Mathematic::power(a.mx[i][j], b.mx[i][j]);
			return C;
		}

		template<class T> static ComplexNumber<T> power(const ComplexNumber<T> &a, const ComplexNumber<T> &b)
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

		template<class T> static Matrix<T> power(const Matrix<T> &a, const ComplexNumber<T> &b)
		{
			{
				Matrix<T> C(a.M, a.N);
				for (int i = 0; i < a.M; i++)
					for (int j = 0; j < a.N; j++)
						C.mx[i][j] = Mathematic::power(a.mx[i][j], b);
				return C;
			}
		}
		
		template<class T> static Matrix<T>  mpower(const Matrix<T> &a, const Matrix<T> &b)
		{
			if (a.isScalar() && b.isScalar())
				return Mathematic::power(a.mx[0][0], b.mx[0][0]);

			throw CalcException("Matrix ^ Matrix to be implemented in the feature!");
		}

		template<class T> static ComplexNumber<T> mpower(const ComplexNumber<T> &a, const ComplexNumber<T> &b)
		{
			return power(a, b);
		}

		template<class T> static Matrix<T> logarithm(const Matrix<T> &a, const Matrix<T> &b)
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

		template<class T> static Matrix<T> logarithm(const Matrix<T> &a)
		{
			{
				Matrix<T> C(a.M, a.N);
				for (int i = 0; i < a.M; i++)
					for (int j = 0; j < a.N; j++)
						C.mx[i][j] = logarithm(a.mx[i][j]);
				return C;
			}
		}

		template<class T> static ComplexNumber<T> logarithm(const ComplexNumber<T> &a, const ComplexNumber<T> &b)
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

		template<class T> static ComplexNumber<T> logarithm(const ComplexNumber<T> &b)
		{
			return logarithm(ComplexNumber<T>(boost::math::constants::e<T>()), b);
		}

		template<class T> static Matrix<T> logarithm10(const Matrix<T> &b)
		{
			{
				Matrix<T> C(b.M, b.N);
				for (int i = 0; i < b.M; i++)
					for (int j = 0; j < b.N; j++)
						C.mx[i][j] = logarithm10(b.mx[i][j]);
				return C;
			}
		}

		template<class T> static ComplexNumber<T> logarithm10(const ComplexNumber<T> &b)
		{
			return logarithm(ComplexNumber<T>(10), b);
		}

		template<class T> static Matrix<T> logarithm2(const Matrix<T> &b)
		{
			Matrix<T> C(b.M, b.N);
			for (int i = 0; i < b.M; i++)
				for (int j = 0; j < b.N; j++)
					C.mx[i][j] = logarithm2(b.mx[i][j]);
			return C;
		}

		template<class T> static ComplexNumber<T> logarithm2(const ComplexNumber<T> &b)
		{
			return logarithm(ComplexNumber<T>(2), b);
		}
		
		template <class T> static T argument(const ComplexNumber<T> &z)
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

		template <class T> static T module(const ComplexNumber<T> &z)
		{
			if (z.im == 0)
				return(abs(z.re));
			return sqrt(z.re*z.re + z.im*z.im);
		}

		template <class T> static ComplexNumber<T> sinus(const ComplexNumber<T> &z)
		{
			if (z.im == 0)
				return ComplexNumber<T>(sin(z.re));
			return ComplexNumber<T>(sin(z.re)*cosh(z.im), cos(z.re)*sinh(z.im));
		}

		template <class T> static Matrix<T> sinus(const Matrix<T> &m)
		{
			Matrix<T> out(m.M, m.N);
			for (int i = 0; i < m.M; i++)
				for (int j = 0; j < m.N; j++)
					out.mx[i][j] = sinus(m.mx[i][j]);
			return out;
		}

		template <class T> static ComplexNumber<T> cosinus(const ComplexNumber<T> &a)
		{
			if (a.im == 0)
				return ComplexNumber<T>(cos(a.re));
			int m = a.im>0 ? 1 : -1;
			return ComplexNumber<T>(cos(a.re)*cosh(a.im), sin(a.re)*sinh(a.im)*m);
		}

		template <class T> static Matrix<T> cosinus(const Matrix<T> &a)
		{
			Matrix<T> c(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					c.mx[i][j] = cosinus(a.mx[i][j]);
			return c;
		}

		template <class T> static ComplexNumber<T> tangens(const ComplexNumber<T> &a)
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

		template <class T> static Matrix<T> tangens(const Matrix<T> &a)
		{
			Matrix<T> c(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					c.mx[i][j] = tangens(a.mx[i][j]);
			return c;
		}

		template <class T> static T fix(const T &value)
		{
			if (value < 0)
				return ceil(value);
			else
				return floor(value);
		}

		template <class T> static ComplexNumber<T> fix(const ComplexNumber<T> &value)
		{
			return ComplexNumber<T>(fix(value.re), fix(value.im));
		}

		template <class T> static Matrix<T> fix(const Matrix<T> &value)
		{
			Matrix<T> out(matrix.M, matrix.N);
			for (int i = 0; i<out.M; i++)
			{
				auto &o = out.mx[i];
				const auto &m = matrix.mx[i];
				for (int j = 0; j < out.N; j++)
					o[j] = fix(m[j]);
			}
			return out;
		}
	};
}

