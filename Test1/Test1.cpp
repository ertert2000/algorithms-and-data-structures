#include "pch.h"
#include "CppUnitTest.h"
#include "../lib1_1_R/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test1
{
	TEST_CLASS(Test1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char A[4] = { '1', '2', '3', '4' };
			char B[4] = { '1', '2', '3', '4' };
			char C[4] = { '1', '2', '3', '4' };
			char D[4] = { '1', '2', '3', '4' };
			char E[11];
			int sizeOutputArr = 4;

			processInput(A, B, C, D, E, sizeOutputArr);
			char expected[11]{ '1', '2', '3', '4', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };

			for (int i = 0; i < sizeOutputArr; i++)
				Assert::AreEqual(expected[i], E[i]);
		}
	};
}
