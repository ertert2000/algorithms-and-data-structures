#include "pch.h"
#include "CppUnitTest.h"
#include "../lib1_1_R/Array.cpp"
#include "../lib1_1_R/List.cpp"
#include "../lib1_1_R/BitArray.cpp"
#include "../lib1_1_R/MachineWord.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test1
{
	TEST_CLASS(Test1)
	{
	public:
		
		TEST_METHOD(TestArray)
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

		TEST_METHOD(TestList)
		{
			char A[4] = { '1', '2', '3', '4' };
			char B[4] = { '1', '2', '3', '4' };
			char C[4] = { '1', '2', '3', '4' };
			char D[4] = { '1', '2', '3', '4' };

			Cat* structA = NULL;
			Cat* structB = NULL;
			Cat* structC = NULL;
			Cat* structD = NULL;
			Cat* structE = init(NULL);
			Cat* expected = NULL;

			for (int i = 0; i < 4; i++) {
				if (i == 0)
					structA = init(A[i]);
				else
					addFront(structA, A[i]);
			}

			for (int i = 0; i < 4; i++) {
				if (i == 0)
					structB = init(B[i]);
				else
					addFront(structB, B[i]);
			}

			for (int i = 0; i < 4; i++) {
				if (i == 0)
					structC = init(C[i]);
				else
					addFront(structC, C[i]);
			}

			for (int i = 0; i < 4; i++) {
				if (i == 0)
					structD = init(D[i]);
				else
					addFront(structD, D[i]);
			}

			expected = init('1');
			addFront(expected, '2');
			addFront(expected, '3');
			addFront(expected, '4');

			combineLists(structE, structA, structB, structC, structD);
			structE = structE->next;
			while (expected->next != NULL)
			{
				Assert::AreEqual(expected->value, structE->value);
				expected = expected->next;
				structE = structE->next;
			}

		}

		TEST_METHOD(TestMachineWord)
		{
			unsigned int wordA = setBit('1') | setBit('2') | setBit('3') | setBit('4');
			unsigned int wordB = setBit('1') | setBit('2') | setBit('3') | setBit('4');
			unsigned int wordC = setBit('1') | setBit('2') | setBit('3') | setBit('4');
			unsigned int wordD = setBit('1') | setBit('2') | setBit('3') | setBit('4');

			unsigned int wordE = createFifthSet(wordA, wordB, wordC, wordD);

			unsigned int expected = 30;

			Assert::AreEqual(expected, wordE);
		}

		TEST_METHOD(TestBitArr)
		{
			char A[4] = { '1', '2', '3', '4' };
			char B[4] = { '1', '2', '3', '4' };
			char C[4] = { '1', '2', '3', '4' };
			char D[4] = { '1', '2', '3', '4' };
			char EBit[2] = { 0 };

			fifthSetBitwise(A, B, C, D, 4, EBit);
			char expected[1]{'\x1e'};

			Assert::AreEqual(expected[0], EBit[0]);
		}
	};
}
