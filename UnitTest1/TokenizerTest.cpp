#include "stdafx.h"
#include "CppUnitTest.h"

#include "Calc\LexicalAnalyzer.h"

#include <string>
#include <vector>
#include <cwchar>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	using PR::Tokenizer;
	using PR::Token;
	using std::string;
	using std::vector;

	TEST_CLASS(TokenizerTest)
	{
		vector<string> in;
		vector<vector<Token>> output;
		TEST_METHOD_INITIALIZE(init)
		{
			in =
			{
				"2*2i+2e-10",
				"2+ada ==\t\n10",
				"2+/*10i*/,(-2.1)",
				"10.10e-3-1i*10",
				"[1+3,12;\n    \n1:-2]"
			};

			output = 
			{
				{
					Token("2", PR::TOKEN_CLASS::NUMBER),
					Token("*", PR::TOKEN_CLASS::OPERATOR),
					Token("2i", PR::TOKEN_CLASS::NUMBER),
					Token("+", PR::TOKEN_CLASS::OPERATOR),
					Token("2e-10", PR::TOKEN_CLASS::NUMBER)
				},
				{
					Token("2", PR::TOKEN_CLASS::NUMBER),
					Token("+", PR::TOKEN_CLASS::OPERATOR),
					Token("ada", PR::TOKEN_CLASS::ID),
					Token("==", PR::TOKEN_CLASS::OPERATOR),
					Token("\n", PR::TOKEN_CLASS::NEW_LINE),
					Token("10", PR::TOKEN_CLASS::NUMBER)
				},
				{
					Token("2", PR::TOKEN_CLASS::NUMBER),
					Token("+", PR::TOKEN_CLASS::OPERATOR),
					Token(",", PR::TOKEN_CLASS::COMMA),
					Token("(", PR::TOKEN_CLASS::OPEN_PARENTHESIS),
					Token("-", PR::TOKEN_CLASS::OPERATOR),
					Token("2.1",PR::TOKEN_CLASS::NUMBER),
					Token(")", PR::TOKEN_CLASS::CLOSE_PARENTHESIS),
				},
				{
					Token("10.10e-3",PR::TOKEN_CLASS::NUMBER),
					Token("-", PR::TOKEN_CLASS::OPERATOR),
					Token("1i",PR::TOKEN_CLASS::NUMBER),
					Token("*", PR::TOKEN_CLASS::OPERATOR),
					Token("10",PR::TOKEN_CLASS::NUMBER)
				},
				{
					Token("[", PR::TOKEN_CLASS::MATRIX_START),
					Token("1", PR::TOKEN_CLASS::NUMBER),
					Token("+", PR::TOKEN_CLASS::OPERATOR),
					Token("3", PR::TOKEN_CLASS::NUMBER),
					Token(",", PR::TOKEN_CLASS::COMMA),
					Token("12",PR::TOKEN_CLASS::NUMBER),
					Token(";", PR::TOKEN_CLASS::SEMICOLON),
					Token("\n",PR::TOKEN_CLASS::NEW_LINE),
					Token("1", PR::TOKEN_CLASS::NUMBER),
					Token(":", PR::TOKEN_CLASS::COLON),
					Token("-", PR::TOKEN_CLASS::OPERATOR),
					Token("2", PR::TOKEN_CLASS::NUMBER),
					Token("]", PR::TOKEN_CLASS::MATRIX_END)
				}
			};
		}

		
	public:
		
		TEST_METHOD(TokenizeInputTest)
		{
			for (int i = in.size() - 1; i >= 0; i--)
			{
				PR::LexicalAnalyzer lexicalAnalyzer;
				lexicalAnalyzer.analyze(in[i]);
				if (lexicalAnalyzer.getTokens() != output[i])
				{
					Assert::Fail(std::to_wstring(i).c_str());
				}
			}
		}

	};
}