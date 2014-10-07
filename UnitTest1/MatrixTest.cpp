#include "stdafx.h"
#include "CppUnitTest.h"
#include "Calc\Matrix.h"

#include <stdlib.h>
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(MatrixTest)
	{
		PR::Matrix<float> A;
		PR::Matrix<float> B;
	public:
		

		TEST_METHOD_INITIALIZE(init)
		{
			srand((unsigned int)time(nullptr));
			float temp = 400.0;
			A = PR::Matrix<float>(10, 10);
			B = PR::Matrix<float>(10, 10);

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					A(i, j) = PR::ComplexNumber<float>(rand() / temp, rand() / temp);
					B(i, j) = PR::ComplexNumber<float>(rand() / temp, rand() / temp);
				}
			}
		}

		TEST_METHOD(MatrixAddAndSubTest)
		{
			auto C = A + B;
			auto D = A - B;

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					Assert::IsTrue(A(i, j) + B(i, j)== C(i, j));
					Assert::IsTrue(A(i, j) - B(i, j)== D(i, j));
				}
			}

			Assert::IsTrue(C.rows() == 10 && C.cols() == 10);
			Assert::IsTrue(D.rows() == 10 && D.cols() == 10);
		}

		TEST_METHOD(MatrixMult)
		{
			PR::Matrix<float> a(10, 5, PR::ComplexNumber<float>(3.0, 5.0));
			PR::Matrix<float> b(5, 10, PR::ComplexNumber<float>(-2.0, 3.0));
			auto c = a*b;
			int aM = a.rows();
			int aN = a.cols();
			int bN = b.cols();
			for (int i = 0; i < aM; i++)
			{
				for (int j = 0; j < bN; j++)
				{
					PR::ComplexNumber<float> temp(0.0, 0.0);
					for (int k = 0; k < aN; k++)
					{
						temp += a(i, k)*b(k, j);
					}
					Assert::IsTrue(temp == c(i, j));
				}
			}
			
		}

	};
}