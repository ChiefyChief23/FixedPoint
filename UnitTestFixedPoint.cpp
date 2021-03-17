/*!
    \file UnitTestFixedPoint.cpp
*/

#include <FixedPoint.h>

#include <gtest/gtest.h>

namespace Lambda
{
	/*
		U8F4
		U = Unsigned
		8 = Total Number of Bits
		-> std::uint8_t
		F4 = Number of Fractional Bits
		-> 0000.0000

		S16F3
		S = Signed
		16 = Total Number of Bits
		-> std::int16_t
		F3 = Number of Fractional Bits
		-> 0000 0000 0000 0.000
	*/

	TEST(FixedPoint, NumericLimitsGeneral)
	{
		typedef FixedPoint<std::uint8_t, 4> FixedPoint;

		EXPECT_TRUE(std::numeric_limits<FixedPoint>::is_specialized);
		EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::min());
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::max());
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::lowest());

		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::digits);
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::digits10);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_signed);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_integer);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_exact);

		EXPECT_EQ(2, std::numeric_limits<FixedPoint>::radix);

		FixedPoint epsilon;
		epsilon.raw(std::uint8_t(1));
		EXPECT_EQ(epsilon, std::numeric_limits<FixedPoint>::epsilon());

		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::round_error());

		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::min_exponent);
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::min_exponent10);
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::max_exponent);
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::max_exponent10);

		EXPECT_FALSE(std::numeric_limits<FixedPoint>::has_infinity);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::has_quiet_NaN);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::has_signaling_NaN);
		EXPECT_EQ(std::numeric_limits<FixedPoint>::has_denorm, std::denorm_absent);

		EXPECT_FALSE(std::numeric_limits<FixedPoint>::has_denorm_loss);
		EXPECT_EQ(0, std::numeric_limits<FixedPoint>::infinity());
		EXPECT_EQ(0, std::numeric_limits<FixedPoint>::quiet_NaN());
		EXPECT_EQ(0, std::numeric_limits<FixedPoint>::signaling_NaN());
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::denorm_min());

		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_iec559);
		EXPECT_TRUE(std::numeric_limits<FixedPoint>::is_bounded);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_modulo);

		EXPECT_TRUE(std::numeric_limits<FixedPoint>::traps);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::tinyness_before);
		EXPECT_EQ(std::numeric_limits<FixedPoint>::round_style, std::round_toward_zero);
	}

	TEST(FixedPoint, StreamOperators)
	{

	}

	TEST(FixedPoint, Comparisons)
	{
		/*
		 * All of the comparator functions need to be tested for obvious reasons. Below are the basic
		 * however, this also need to extend to comparing between two different FixedPoint types.
		 *
		 * Here is the comparison between the same fixed point numbers
		 */
		FixedPoint<std::uint8_t, 4> u8_f4_a(std::uint8_t(8));
		FixedPoint<std::uint8_t, 4> u8_f4_b(std::uint8_t(8));
		FixedPoint<std::uint8_t, 4> u8_f4_c(std::uint8_t(4));
		FixedPoint<std::uint8_t, 4> u8_f4_d(std::uint8_t(2));
		FixedPoint<std::uint8_t, 4> u8_f4_e(std::uint8_t(10));

		EXPECT_TRUE(u8_f4_a == u8_f4_b);
		EXPECT_FALSE(u8_f4_a == u8_f4_c);
		EXPECT_FALSE(u8_f4_a == u8_f4_e);

		EXPECT_FALSE(u8_f4_a != u8_f4_b);
		EXPECT_TRUE(u8_f4_a != u8_f4_c);
		EXPECT_TRUE(u8_f4_a != u8_f4_e);

		EXPECT_TRUE(u8_f4_a > u8_f4_c);
		EXPECT_FALSE(u8_f4_a > u8_f4_b);
		EXPECT_FALSE(u8_f4_a > u8_f4_e);

		EXPECT_TRUE(u8_f4_a >= u8_f4_b);
		EXPECT_TRUE(u8_f4_a >= u8_f4_c);
		EXPECT_FALSE(u8_f4_a >= u8_f4_e);

		EXPECT_FALSE(u8_f4_a < u8_f4_c);
		EXPECT_FALSE(u8_f4_a < u8_f4_b);
		EXPECT_TRUE(u8_f4_a < u8_f4_e);

		EXPECT_FALSE(u8_f4_a <= u8_f4_c);
		EXPECT_FALSE(u8_f4_a <= u8_f4_d);
		EXPECT_TRUE(u8_f4_a <= u8_f4_e);

		/*
		 * Now to compare against different fixed point types we will just do 8 bit and 16 bit comparisons
		 * for now but maybe increase this to other variants too
		 */

		FixedPoint<std::int8_t, 4> s8_f4(2.5);
		FixedPoint<std::int16_t, 8> s16_f8_a(3.5);
		FixedPoint<std::int16_t, 8> s16_f8_b(2.5);
		FixedPoint<std::int16_t, 8> s16_f8_c(1.5);

		std::cout << "[          ] Double Representations" << std::endl;
		std::cout << "[          ] S8F4:    " << s8_f4.toDouble() << std::endl;
		std::cout << "[          ] S16F4 A: " << s16_f8_a.toDouble() << std::endl;
		std::cout << "[          ] S16F4 B: " << s16_f8_b.toDouble() << std::endl;
		std::cout << "[          ] S16F4 C: " << s16_f8_c.toDouble() << std::endl;
		std::cout << "[          ]" << std::endl;

		EXPECT_FALSE(s8_f4 == s16_f8_a);
		EXPECT_TRUE(s8_f4 == s16_f8_b);
		EXPECT_FALSE(s8_f4 == s16_f8_c);

		EXPECT_TRUE(s8_f4 != s16_f8_a);
		EXPECT_FALSE(s8_f4 != s16_f8_b);
		EXPECT_TRUE(s8_f4 != s16_f8_c);

		EXPECT_TRUE(s8_f4 < s16_f8_a);
		EXPECT_FALSE(s8_f4 < s16_f8_b);
		EXPECT_FALSE(s8_f4 < s16_f8_c);

		EXPECT_FALSE(s8_f4 > s16_f8_a);
		EXPECT_FALSE(s8_f4 > s16_f8_b);
		EXPECT_TRUE(s8_f4 > s16_f8_c);

		EXPECT_TRUE(s8_f4 <= s16_f8_a);
		EXPECT_TRUE(s8_f4 <= s16_f8_b);
		EXPECT_FALSE(s8_f4 <= s16_f8_c);

		EXPECT_FALSE(s8_f4 >= s16_f8_a);
		EXPECT_TRUE(s8_f4 >= s16_f8_b);
		EXPECT_TRUE(s8_f4 >= s16_f8_c);
	}

	TEST(FixedPoint, FixedPointCreation)
	{
		/*
		 * The createFixedPoint takes in a raw value due to the fixed point nature a raw value of 0x30
		 * corresponds to a value of 3
		 */
		FixedPoint<std::uint8_t, 4> u8_f4_a = FixedPoint<std::uint8_t, 4>::createFixedPoint(std::uint8_t(0x30));
		std::cout << "[          ] Unsigned 8 bit - Fractional 4 bit: 3.0" << std::endl;

		std::cout << "[          ] Raw:   " << u8_f4_a.rawBitSet() << std::endl;
		std::cout << "[          ] Whole: " << u8_f4_a.wholeBitSet() << std::endl;
		std::cout << "[          ] Frac : " << u8_f4_a.fractionBitSet() << std::endl;
		std::cout << "[          ] Double : " << u8_f4_a.toDouble() << std::endl;
		std::cout << "[          ]" << std::endl;

		FixedPoint<std::uint8_t, 4> u8_f4_b(3);
		std::cout << "[          ] Raw:   " << u8_f4_b.rawBitSet() << std::endl;
		std::cout << "[          ] Whole: " << u8_f4_b.wholeBitSet() << std::endl;
		std::cout << "[          ] Frac : " << u8_f4_b.fractionBitSet() << std::endl;
		std::cout << "[          ] Double : " << u8_f4_b.toDouble() << std::endl;

		EXPECT_EQ(u8_f4_a, u8_f4_b);

		FixedPoint<std::int16_t, 4> s16_f4_a = FixedPoint<std::int16_t, 4>::createFixedPoint(std::int16_t(0xFBCA));
		std::cout << "[          ] Signed 16 bit - Fractional 4 bit: -67.375" << std::endl;

		std::cout << "[          ] Raw:   " << s16_f4_a.rawBitSet() << std::endl;
		std::cout << "[          ] Whole: " << s16_f4_a.wholeBitSet() << std::endl;
		std::cout << "[          ] Frac : " << s16_f4_a.fractionBitSet() << std::endl;
		std::cout << "[          ] Double : " << s16_f4_a.toDouble() << std::endl;
		std::cout << "[          ]" << std::endl;

		FixedPoint<std::int16_t, 4> s16_f4_b(-67.375);
		std::cout << "[          ] Raw:   " << s16_f4_b.rawBitSet() << std::endl;
		std::cout << "[          ] Whole: " << s16_f4_b.wholeBitSet() << std::endl;
		std::cout << "[          ] Frac : " << s16_f4_b.fractionBitSet() << std::endl;
		std::cout << "[          ] Double : " << s16_f4_b.toDouble() << std::endl;

		EXPECT_EQ(s16_f4_a, s16_f4_b);
	}

	TEST(FixedPoint, Conversion)
	{
		/*
		 * Check the shifting capabilities of the convertType function. This should shift all of the bits in one
		 * direction which in this case corresponds to going from 4 to 8 by shifting the bit by one place.
		 *
		 * There are several shifting tests here which just test the different possibilities and the different data
		 * types that would be using this functionality.
		 */
		std::uint8_t u8_a(4);
		std::uint8_t u8_b(8);
		auto u8_c = FixedPoint<std::uint8_t, 4>::convertType<std::uint8_t, std::uint8_t>(u8_a, 1);
		auto u8_d = FixedPoint<std::uint8_t, 4>::convertType<std::uint8_t, std::uint8_t>(u8_a, 0);
		EXPECT_EQ(u8_b, u8_c);
		EXPECT_EQ(u8_a, u8_d);

		std::int8_t s8_a = FixedPoint<std::uint8_t, 4>::convertType<std::uint8_t, std::int8_t>(u8_a, -1);
		std::int8_t s8_b(2);
		EXPECT_EQ(s8_a, s8_b);

		std::int16_t s16_a = FixedPoint<std::uint8_t, 4>::convertType<std::uint8_t, std::int16_t>(u8_a, 3);
		std::int16_t s16_b(32);
		EXPECT_EQ(s16_a, s16_b);

		/*
		 * Check the complete conversion functionality going from one version of FixedPoint to a completely different
		 * version. Here there should be no issue when converting from S16F8 to U8F4. Do the usual comparison first to
		 * confirm that the convert function is working as intended with the same Fractional amount then go to a
		 * different sign and fractional amount
		 */
		FixedPoint<std::uint8_t, 4> u8_f4_a(5.5);
		FixedPoint<std::uint16_t, 4> u16_f4_a(5.5);
		FixedPoint<std::uint16_t, 4> u16_f4_b = u8_f4_a.convert<std::uint16_t, 4>();
		EXPECT_EQ(u16_f4_a, u16_f4_b);

		FixedPoint<std::int16_t, 8> s16_f8(5.5);
		FixedPoint<std::uint8_t, 4> u8_f4_b = s16_f8.convert<std::uint8_t, 4>();
		EXPECT_EQ(u8_f4_a, u8_f4_b);
	}
}