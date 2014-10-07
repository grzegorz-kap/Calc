#include "stdafx.h"
#include "CppUnitTest.h"
#include "Calc\ComplexNumber.h"

#include <stdlib.h>
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(ComplexNumberTest)
	{
		
	public:
		PR::ComplexNumber<float> a;
		PR::ComplexNumber<float> b;

		TEST_METHOD_INITIALIZE(init)
		{
			srand((unsigned int)time(nullptr));
			float temp = 400.0;
			a.setRe(rand() / temp);
			a.setIm(rand() / temp);
			b.setRe(rand() / temp);
			b.setIm(rand() / temp);
		}

		TEST_METHOD(ComplexNumberSimpleOperations)
		{
			auto c = a + b;
			Assert::AreEqual(a.getRe() + b.getRe(), c.getRe());
			Assert::AreEqual(a.getIm() + b.getIm(), c.getIm());

			c = a - b;
			Assert::AreEqual(a.getRe() - b.getRe(), c.getRe());
			Assert::AreEqual(a.getIm() - b.getIm(), c.getIm());

			c = a * b;
			Assert::AreEqual(a.getRe() * b.getRe() - a.getIm()*b.getIm(), c.getRe());
			Assert::AreEqual(a.getRe()*b.getIm() + a.getIm()*b.getRe(), c.getIm());

			c = a / b;
			auto ere = (a.getRe()*b.getRe() + a.getIm()*b.getIm()) / (b.getRe()*b.getRe() + b.getIm()*b.getIm());
			auto eim = (a.getIm()*b.getRe() - a.getRe()*b.getIm()) / (b.getRe()*b.getRe() + b.getIm()*b.getIm());
			Assert::AreEqual(ere, c.getRe());
			Assert::AreEqual(eim, c.getIm());
		}

	};
}