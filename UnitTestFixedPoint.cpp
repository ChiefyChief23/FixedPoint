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
		typedef FixedPoint<std::uint8_t, 4> U8F4;

		EXPECT_TRUE(std::numeric_limits<U8F4>::is_specialized);
		EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::min());
		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::max());
		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::lowest());

		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::digits);
		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::digits10);
		EXPECT_FALSE(std::numeric_limits<U8F4>::is_signed);
		EXPECT_FALSE(std::numeric_limits<U8F4>::is_integer);
		EXPECT_FALSE(std::numeric_limits<U8F4>::is_exact);

		EXPECT_EQ(2, std::numeric_limits<U8F4>::radix);

		U8F4 epsilon;
		epsilon.raw(std::uint8_t(1));
		EXPECT_EQ(epsilon, std::numeric_limits<U8F4>::epsilon());

		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::round_error());

		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::min_exponent);
		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::min_exponent10);
		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::max_exponent);
		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::max_exponent10);

		EXPECT_FALSE(std::numeric_limits<U8F4>::has_infinity);
		EXPECT_FALSE(std::numeric_limits<U8F4>::has_quiet_NaN);
		EXPECT_FALSE(std::numeric_limits<U8F4>::has_signaling_NaN);
		EXPECT_EQ(std::numeric_limits<U8F4>::has_denorm, std::denorm_absent);

		EXPECT_FALSE(std::numeric_limits<U8F4>::has_denorm_loss);
		EXPECT_EQ(0, std::numeric_limits<U8F4>::infinity());
		EXPECT_EQ(0, std::numeric_limits<U8F4>::quiet_NaN());
		EXPECT_EQ(0, std::numeric_limits<U8F4>::signaling_NaN());
		//EXPECT_EQ(U8F4(0), std::numeric_limits<U8F4>::denorm_min());

		EXPECT_FALSE(std::numeric_limits<U8F4>::is_iec559);
		EXPECT_TRUE(std::numeric_limits<U8F4>::is_bounded);
		EXPECT_FALSE(std::numeric_limits<U8F4>::is_modulo);

		EXPECT_TRUE(std::numeric_limits<U8F4>::traps);
		EXPECT_FALSE(std::numeric_limits<U8F4>::tinyness_before);
		EXPECT_EQ(std::numeric_limits<U8F4>::round_style, std::round_toward_zero);
	}

	TEST(FixedPoint, NumericLimitsMaxMin)
	{
		std::cout << "[          ] U8F4 - Max/Min" << std::endl;

		FixedPoint<std::uint8_t, 4> u8_f4_min_a = std::numeric_limits<FixedPoint<std::uint8_t, 4>>::min();
		FixedPoint<std::uint8_t, 4> u8_f4_max_a = std::numeric_limits<FixedPoint<std::uint8_t, 4>>::max();

		FixedPoint<std::uint8_t, 4> u8_f4_min_b(0);
		FixedPoint<std::uint8_t, 4> u8_f4_max_b(15.9375);

		std::cout << "[          ] " << u8_f4_min_a.rawBitSet() << "  " << u8_f4_min_a.toDouble() << " - Reference" << std::endl;
		std::cout << "[          ] " << u8_f4_min_b.rawBitSet() << "  " << u8_f4_min_b.toDouble() << " - Test" << std::endl;
		std::cout << "[          ] " << u8_f4_max_a.rawBitSet() << "  " << u8_f4_max_a.toDouble() << " - Reference" << std::endl;
		std::cout << "[          ] " << u8_f4_max_b.rawBitSet() << "  " << u8_f4_max_b.toDouble() << " - Test" << std::endl;
		std::cout << "[          ] " << std::endl;

		EXPECT_EQ(u8_f4_min_a, u8_f4_min_b);
		EXPECT_EQ(u8_f4_max_a, u8_f4_max_b);

		std::cout << "[          ] S8F4 - Max/Min" << std::endl;

		FixedPoint<std::int8_t, 4> s8_f4_min_a = std::numeric_limits<FixedPoint<std::int8_t, 4>>::min();
		FixedPoint<std::int8_t, 4> s8_f4_max_a = std::numeric_limits<FixedPoint<std::int8_t, 4>>::max();

		FixedPoint<std::int8_t, 4> s8_f4_min_b(-8);
		FixedPoint<std::int8_t, 4> s8_f4_max_b(7.9375);

		std::cout << "[          ] " << s8_f4_min_a.rawBitSet() << "  " << s8_f4_min_a.toDouble() << " - Reference" << std::endl;
		std::cout << "[          ] " << s8_f4_min_b.rawBitSet() << "  " << s8_f4_min_b.toDouble() << " - Test" << std::endl;
		std::cout << "[          ] " << s8_f4_max_a.rawBitSet() << "  " << s8_f4_max_a.toDouble() << " - Reference" << std::endl;
		std::cout << "[          ] " << s8_f4_max_b.rawBitSet() << "  " << s8_f4_max_b.toDouble() << " - Test" << std::endl;
		std::cout << "[          ] " << std::endl;

		EXPECT_EQ(s8_f4_min_a, s8_f4_min_b);
		EXPECT_EQ(s8_f4_max_a, s8_f4_max_b);

		std::cout << "[          ] U16F8 - Max/Min" << std::endl;

		FixedPoint<std::uint16_t, 8> u16_f8_min_a = std::numeric_limits<FixedPoint<std::uint16_t, 8>>::min();
		FixedPoint<std::uint16_t, 8> u16_f8_max_a = std::numeric_limits<FixedPoint<std::uint16_t, 8>>::max();

		FixedPoint<std::uint16_t, 8> u16_f8_min_b(0);
		FixedPoint<std::uint16_t, 8> u16_f8_max_b(255.9961);

		std::cout << "[          ] " << u16_f8_min_a.rawBitSet() << "  " << u16_f8_min_a.toDouble() << " - Reference" << std::endl;
		std::cout << "[          ] " << u16_f8_min_b.rawBitSet() << "  " << u16_f8_min_b.toDouble() << " - Test" << std::endl;
		std::cout << "[          ] " << u16_f8_max_a.rawBitSet() << "  " << u16_f8_max_a.toDouble() << " - Reference" << std::endl;
		std::cout << "[          ] " << u16_f8_max_b.rawBitSet() << "  " << u16_f8_max_b.toDouble() << " - Test" << std::endl;
		std::cout << "[          ] " << std::endl;

		EXPECT_EQ(u16_f8_min_a, u16_f8_min_b);
		EXPECT_EQ(u16_f8_max_a, u16_f8_max_b);

		std::cout << "[          ] S16F8 - Max/Min" << std::endl;

		FixedPoint<std::int16_t, 8> s16_f8_min_a = std::numeric_limits<FixedPoint<std::int16_t, 8>>::min();
		FixedPoint<std::int16_t, 8> s16_f8_max_a = std::numeric_limits<FixedPoint<std::int16_t, 8>>::max();

		FixedPoint<std::int16_t, 8> s16_f8_min_b(-128);
		FixedPoint<std::int16_t, 8> s16_f8_max_b(127.9961);

		std::cout << "[          ] " << s16_f8_min_a.rawBitSet() << "  " << s16_f8_min_a.toDouble() << " - Reference" << std::endl;
		std::cout << "[          ] " << s16_f8_min_b.rawBitSet() << "  " << s16_f8_min_b.toDouble() << " - Test" << std::endl;
		std::cout << "[          ] " << s16_f8_max_a.rawBitSet() << "  " << s16_f8_max_a.toDouble() << " - Reference" << std::endl;
		std::cout << "[          ] " << s16_f8_max_b.rawBitSet() << "  " << s16_f8_max_b.toDouble() << " - Test" << std::endl;

		EXPECT_EQ(s16_f8_min_a, s16_f8_min_b);
		EXPECT_EQ(s16_f8_max_a, s16_f8_max_b);
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

	TEST(FixedPoint, Addition)
	{
		std::cout << "[          ] U8F3 + U8F3 Addition Exact - 8/8 bit" << std::endl;
		FixedPoint<std::uint8_t, 3> u8_f3_a(2.625);
		FixedPoint<std::uint8_t, 3> u8_f3_b(1.625);
		FixedPoint<std::uint8_t, 3> u8_f3_c = u8_f3_a + u8_f3_b;

		std::cout << "[          ] A:  " << u8_f3_a.rawBitSet() << "  " << u8_f3_a.toDouble() << std::endl;
		std::cout << "[          ] B:  " << u8_f3_b.rawBitSet() << "  " << u8_f3_b.toDouble() << std::endl;
		std::cout << "[          ] C:  " << u8_f3_c.rawBitSet() << "  " << u8_f3_c.toDouble() << std::endl;
		std::cout << "[          ]" << std::endl;

		FixedPoint<std::uint8_t, 3> u8_f3_d(4.25);
		EXPECT_EQ(u8_f3_c, u8_f3_d);

		std::cout << "[          ] S8F3 + S8F3 Addition Exact - 8/8 bit" << std::endl;
		FixedPoint<std::int8_t, 3> s8_f3_a(3.125);
		FixedPoint<std::int8_t, 3> s8_f3_b(-1.625);
		FixedPoint<std::int8_t, 3> s8_f3_c = s8_f3_a + s8_f3_b;

		std::cout << "[          ] A:  " << s8_f3_a.rawBitSet() << "  " << s8_f3_a.toDouble() << std::endl;
		std::cout << "[          ] B:  " << s8_f3_b.rawBitSet() << " " << s8_f3_b.toDouble() << std::endl;
		std::cout << "[          ] C:  " << s8_f3_c.rawBitSet() << "  " << s8_f3_c.toDouble() << std::endl;
		std::cout << "[          ]" << std::endl;

		FixedPoint<std::int8_t, 3> s8_f3_d(1.5);
		EXPECT_EQ(s8_f3_c, s8_f3_d);

		std::cout << "[          ] S16F8 + U16F8 Addition Exact - 16/16 bit" << std::endl;
		FixedPoint<std::int16_t, 8> s16_f8_a(-13.375);
		FixedPoint<std::uint16_t, 6> u16_f6_b(10.125);
		FixedPoint<std::int16_t, 8> s16_f8_c = s16_f8_a + u16_f6_b;

		std::cout << "[          ] A:  " << s16_f8_a.rawBitSet() << " " << s16_f8_a.toDouble() << std::endl;
		std::cout << "[          ] B:  " << u16_f6_b.rawBitSet() << "  " << u16_f6_b.toDouble() << std::endl;
		std::cout << "[          ] C:  " << s16_f8_c.rawBitSet() << " " << s16_f8_c.toDouble() << std::endl;
		std::cout << "[          ]" << std::endl;

		FixedPoint<std::int16_t, 8> s16_f8_d(-3.25);
		EXPECT_EQ(s16_f8_c, s16_f8_d);

		std::cout << "[          ] U8F4 + S16F12 Addition Exact - 8/16 bit - Incompatible" << std::endl;
		FixedPoint<std::uint8_t, 4> u8_f4_a(1.125);
		FixedPoint<std::int16_t, 12> s16_f12_a(-0.125);
		FixedPoint<std::uint8_t, 4> u8_f4_b = u8_f4_a + s16_f12_a;

		std::cout << "[          ] A:          " << u8_f4_a.rawBitSet() << "  " << u8_f4_a.toDouble() << std::endl;
		std::cout << "[          ] B:  " << s16_f12_a.rawBitSet() << " " << s16_f12_a.toDouble() << std::endl;
		std::cout << "[          ] C:          " << u8_f4_b.rawBitSet() << "  " << u8_f4_b.toDouble() << std::endl;

		FixedPoint<std::uint8_t, 4> u8_f4_c(1);
		EXPECT_EQ(u8_f4_b, u8_f4_c);
	}
}