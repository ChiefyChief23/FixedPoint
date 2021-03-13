/*!
    \file UnitTestFixedPoint.cpp
    \copyright Copyright: (C) 2021 Lambda
*/

#include <FixedPoint.h>

#include <gtest/gtest.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

namespace Lambda
{
	/*
		U8Q4
		U = Unsigned
		8 = Total Number of Bits
		-> std::uint8_t

		Q4 = Number of Fractional Bits
		-> 0000.0000


		S16Q3
		S = Signed
		16 = Total Number of Bits
		-> std::int16_t

		Q3 = Number of Fractional Bits
		-> 0000 0000 0000 0.000
	*/

	TEST(FixedPoint, NumericLimitsU8Q4) /* TODO */
	{
		typedef FixedPoint<std::uint8_t, static_cast<std::int8_t>(4)> FixedPoint;

		EXPECT_TRUE(std::numeric_limits<FixedPoint>::is_specialized);
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::min());
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::max());
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::lowest());

		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::digits);
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::digits10);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_signed);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_integer);
		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_exact);

		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::radix);
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::epsilon());
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
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::infinity());
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::quiet_NaN());
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::signaling_NaN());
		//EXPECT_EQ(FixedPoint(0), std::numeric_limits<FixedPoint>::denorm_min());

		EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_iec559);
		EXPECT_TRUE(std::numeric_limits<FixedPoint>::is_bounded);
		//EXPECT_FALSE(std::numeric_limits<FixedPoint>::is_modulo);

		//EXPECT_FALSE(std::numeric_limits<FixedPoint>::traps);
		//EXPECT_FALSE(std::numeric_limits<FixedPoint>::tinyness_before);
		EXPECT_EQ(std::numeric_limits<FixedPoint>::round_style, std::round_to_nearest);
	}

	TEST(FixedPoint, Comparisons)
	{
		FixedPoint<std::uint8_t, 4> u8_a(std::int8_t(8));
		FixedPoint<std::uint8_t, 4> u8_b(std::int8_t(8));
		FixedPoint<std::uint8_t, 4> u8_c(std::int8_t(4));

		EXPECT_EQ(u8_a, u8_b);
		EXPECT_TRUE(u8_a == u8_b);
		EXPECT_TRUE(u8_b == u8_a);

		EXPECT_NE(u8_a, u8_c);
		EXPECT_FALSE(u8_a == u8_c);
		EXPECT_FALSE(u8_c == u8_a);
	}

	TEST(FixedPoint, Conversion)
	{
		std::uint8_t u8_a(4);
		std::uint8_t u8_b(8);
		std::uint8_t u8_c = FixedPoint<std::uint8_t, 4>::convertType<std::uint8_t, std::uint8_t>(u8_a, 1);
		std::uint8_t u8_d = FixedPoint<std::uint8_t, 4>::convertType<std::uint8_t, std::uint8_t>(u8_a, 0);
		EXPECT_EQ(u8_b, u8_c);
		EXPECT_EQ(u8_a, u8_d);

		std::int8_t s8_a = FixedPoint<std::uint8_t, 4>::convertType<std::uint8_t, std::int8_t>(u8_a, -1);
		std::int8_t s8_b(2);
		EXPECT_EQ(s8_a, s8_b);

		std::int16_t s16_a = FixedPoint<std::uint8_t, 4>::convertType<std::uint8_t, std::int16_t>(u8_a, 3);
		std::int16_t s16_b(32);
		EXPECT_EQ(s16_a, s16_b);

		/*
		FixedPoint<std::uint8_t, 4> u8_a(std::int8_t(4));
		FixedPoint<std::uint8_t, 6> u8_b(std::int8_t(4));
		FixedPoint<std::uint8_t, 4> u8_c = u8_b.convert<std::uint8_t, 4>();

		EXPECT_EQ(u8_a, u8_c);
		 */
	}

	TEST(FixedPoint, NumericLimits16Bit) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, NumericLimits32Bit) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, RawAllocation)
	{
		/* Unsigned 8 Bit */
		FixedPoint<std::uint8_t, 4> u8;
		u8.raw(18);
		EXPECT_EQ(18, u8.raw());
		EXPECT_EQ(0.0625, u8.resolution());

		/* Signed 8 Bit */
		FixedPoint<std::int8_t, 2> s8;
		s8.raw(4);
		EXPECT_EQ(4, s8.raw());

		/* Unsigned 16 Bit */
		FixedPoint<std::uint16_t, 8> u16;
		u16.raw(2534);
		EXPECT_EQ(2534, u16.raw());

		/* Signed 16 Bit */
		FixedPoint<std::int16_t, 12> s16;
		s16.raw(1234);
		EXPECT_EQ(1234, s16.raw());

		/* Unsigned 32 Bit */
		FixedPoint<std::uint32_t, 16> u32;
		u32.raw(18);
		EXPECT_EQ(18, u32.raw());

		/* Signed 32 Bit */
		FixedPoint<std::int32_t, 24> s32;
		s32.raw(4);
		EXPECT_EQ(4, s32.raw());
	}

	TEST(FixedPoint, FloatAllocation) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, DoubleAllocation) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, IntegerAllocation) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, ZeroAllocation) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, AdditionArithmetic) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, SubtractionArithmetic) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, MultiplicationArithmetic) /* TODO */
	{
		EXPECT_TRUE(true);
	}

	TEST(FixedPoint, DivisionArithmetic) /* TODO */
	{
		EXPECT_TRUE(true);
	}
}