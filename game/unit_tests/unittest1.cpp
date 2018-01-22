#include "stdafx.h"
#include "CppUnitTest.h"

#include "../game/include/Util/Util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestBitSet)
		{
			int bitfield = 0;
			int expected = 0b0010;

			axe::setBit(bitfield, 0b0010, true);

			Assert::AreEqual(expected, bitfield);
		}

		TEST_METHOD(TestBitGet)
		{
			int bitfield = 0b0100;
			bool expected = true;

			bool result = axe::getBit(bitfield, 0b0100);

			Assert::AreEqual(expected, result);
		}

	};
}