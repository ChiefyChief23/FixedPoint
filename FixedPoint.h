#pragma once

#include <cstdint>
#include <limits>
#include <bitset>
#include <iostream>
#include <cmath>

// ReSharper disable CppRedundantParentheses
// ReSharper disable CppInconsistentNaming

template <typename T> struct SignedSelector { typedef std::int64_t Type; };
template <> struct SignedSelector<std::int8_t> { typedef std::uint8_t Type; };
template <> struct SignedSelector<std::int16_t> { typedef std::uint16_t Type; };
template <> struct SignedSelector<std::int32_t> { typedef std::uint32_t Type; };
template <> struct SignedSelector<std::int64_t> { typedef std::uint64_t Type; };

template <typename T, typename U> struct SizeTypeIncrement { typedef std::int64_t Type; };
template <> struct SizeTypeIncrement<std::int8_t, std::int8_t> { typedef std::int16_t Type; };
template <> struct SizeTypeIncrement<std::int16_t, std::int16_t> { typedef std::int32_t Type; };
template <> struct SizeTypeIncrement<std::int32_t, std::int32_t> { typedef std::int32_t Type; };
template <> struct SizeTypeIncrement<std::uint8_t, std::uint8_t> { typedef std::uint16_t Type; };
template <> struct SizeTypeIncrement<std::int16_t, std::uint16_t> { typedef std::uint32_t Type; };
template <> struct SizeTypeIncrement<std::uint32_t, std::uint32_t> { typedef std::uint32_t Type; };

/*!
	\class FixedPoint
	\brief Templated class to handle Fixed Point arithmetic 
	\tparam T The number of total bits to represent the Fixed Point. This is limited to the 8, 16, and 32 bit options.
				Using signed integers will result in signed fixed point and unsigned to unsigned fixed points.
	\tparam F The number of fractional bits to have within the Fixed Point number
*/
template<typename T, std::int8_t F>
class FixedPoint
{
	static_assert(std::is_integral<T>::value, "The Base T must be of an Integral type");
	static_assert(F <= 31, "Fractional F may be not be larger than 31 bits");
	static_assert(F > 0, "Fractional must be larger than zero");

	/*! Boolean indicator if the fixed point is signed or not */
	static const bool S = std::numeric_limits<T>::is_signed;
	
	/*! Numeric value of one in the templated fixed point format */
	static const T ONE = 1 << F;

public:
	/*!
		\brief Default constructor. 
	*/
	FixedPoint() = default;

	/*!
		\brief Parameterised constructor. Converts a double to the fixed point format.
		\param value The double to convert
	*/
	explicit FixedPoint(const double& value)
		: _data(static_cast<T>(value * ONE))
	{}

	/*!
		\brief Parameterised constructor. Converts a float to the fixed point format.
		\param value The float to convert
	*/
	explicit FixedPoint(const float& value)
		: _data(static_cast<T>(value * ONE))
	{}

	/*!
		\brief Parameterised constructor. Converts a signed 8 bit value to the fixed point format.
		\param value The signed 8 bit value to convert
	*/
	explicit FixedPoint(const std::int8_t& value)
		: _data(static_cast<T>(value * ONE))
	{}

	/*!
		\brief Parameterised constructor. Converts a signed 16 bit value to the fixed point format.
		\param value The signed 16 bit value to convert
	*/
	explicit FixedPoint(const std::int16_t& value)
		: _data(static_cast<T>(value * ONE))
	{}

	/*!
		\brief Parameterised constructor. Converts a signed 32 bit value to the fixed point format.
		\param value The signed 32 bit value to convert
	*/
	explicit FixedPoint(const std::int32_t& value)
		: _data(static_cast<T>(value * ONE))
	{}

	/*!
		\brief Parameterised constructor. Converts a unsigned 8 bit value to the fixed point format.
		\param value The unsigned 8 bit value to convert
	*/
	explicit FixedPoint(const std::uint8_t& value)
		: _data(static_cast<T>(value * ONE))
	{}

	/*!
		\brief Parameterised constructor. Converts a unsigned 16 bit value to the fixed point format.
		\param value The unsigned 16 bit value to convert
	*/
	explicit FixedPoint(const std::uint16_t& value)
		: _data(static_cast<T>(value * ONE))
	{}

	/*!
		\brief Parameterised constructor. Converts a unsigned 32 bit value to the fixed point format.
		\param value The unsigned 32 bit value to convert
	*/
	explicit FixedPoint(const std::uint32_t& value)
		: _data(static_cast<T>(value * ONE))
	{}

	/*!
		\brief Static function to return the minimum value of the fixed point template
		\returns A fixed point number corresponding to the minimum value 
	*/
	static FixedPoint<T, F> min();

	/*!
		\brief Static function to return the maximum value of the fixed point template
		\returns A fixed point number corresponding to the maximum value
	*/
	static FixedPoint<T, F> max();

	T raw() const { return _data; }
	void raw(const T& value) { _data = value; }

	double toFloat() const { return static_cast<float>(_data) / ONE; }
	void fromFloat(const float& value) { _data = static_cast<T>(value * ONE); }

	double toDouble() const { return static_cast<double>(_data) / ONE; }
	void fromDouble(const double& value) { _data = static_cast<T>(value * ONE); }

	/*!
		\brief 
		\return 
	*/
	float resolution() const;
	
	/*!
		\brief 
		\return 
	*/
	std::bitset<sizeof(T) * 8> wholeBitSet();
	
	/*!
		\brief 
		\return 
	*/
	std::bitset<sizeof(T) * 8> fractionBitSet();
	
	/*!
		\brief 
		\return 
	*/
	std::bitset<sizeof(T) * 8> rawBitSet();

	template<typename U, std::int8_t G>
	FixedPoint<T, F> operator*(const FixedPoint<U, G>& value) const;

	FixedPoint<T, F>& operator++() { _data += ONE; return *this; }
	FixedPoint<T, F>& operator--() { _data -= ONE; return *this; }

	template <typename U, std::int8_t G>
	FixedPoint<T, F> operator+(const FixedPoint<U, G>& value) const;
	FixedPoint<T, F> operator+(const FixedPoint<T, F>& rhs) const;
	FixedPoint<T, F>& operator+=(const FixedPoint<T, F>& rhs);

	
	/*!
		\brief 
		\tparam U 
		\tparam G 
		\return 
	*/
	template <typename U, std::int8_t G>
	FixedPoint<U, G> convert() const;

private:
	/*!
		\brief 
		\param value 
		\return 
	*/
	static FixedPoint<T, F> createFixedPoint(T value);
	
	/*!
		\brief 
		\tparam I 
		\tparam J 
		\param initial 
		\param shift 
		\return 
	*/
	template <typename I, typename J>
	J static convertType(const I& initial, std::int8_t shift);
	
	/*!
		\brief 
		\return 
	*/
	T bitMask();

	/*!
		
	*/
	T _data;
};

template <typename T, std::int8_t F>
FixedPoint<T, F> FixedPoint<T, F>::min()
{
	if (!S)
	{
		return FixedPoint<T, F>(0);
	}

	/* TODO */
	return FixedPoint<T, F>(0);
}

template <typename T, std::int8_t F>
FixedPoint<T, F> FixedPoint<T, F>::max()
{
	/* TODO */
	return FixedPoint<T, F>(0);
}

template <typename T, std::int8_t F>
float FixedPoint<T, F>::resolution() const
{
	return 1.0f / std::pow(2.0f, static_cast<float>(F));
}

template <typename T, std::int8_t F>
std::bitset<sizeof(T) * 8> FixedPoint<T, F>::wholeBitSet()
{
	T mask = -1 ^ bitMask();
	return std::bitset<sizeof(T) * 8>(mask & _data);
}

template <typename T, std::int8_t F>
std::bitset<sizeof(T) * 8> FixedPoint<T, F>::fractionBitSet()
{
	return std::bitset<sizeof(T) * 8>(bitMask() & _data);
}

template <typename T, std::int8_t F>
std::bitset<sizeof(T) * 8> FixedPoint<T, F>::rawBitSet()
{
	return std::bitset<sizeof(T) * 8>(_data);
}

template <typename T, std::int8_t F>
T FixedPoint<T, F>::bitMask()
{
	if (S)
	{
		typename SignedSelector<T>::Type mask = std::numeric_limits<T>::max();
		mask = std::numeric_limits<typename SignedSelector<T>::Type>::max();
		return mask >> ((sizeof(typename SignedSelector<T>::Type) * 8) - F);
	}

	T mask = std::numeric_limits<T>::max();
	return mask >> ((sizeof(T) * 8) - F);
}

template <typename T, std::int8_t F>
template <typename U, std::int8_t G>
FixedPoint<T, F> FixedPoint<T, F>::operator*(const FixedPoint<U, G>& value) const
{
	FixedPoint<typename SizeTypeIncrement<T, U>::Type, F + G> intermediate;
	intermediate = FixedPoint<typename SizeTypeIncrement<T, U>::Type, F + G>::createFixedPoint(_data * value.raw());
	return intermediate.template convert<T, F>();
}

template <typename T, std::int8_t F>
FixedPoint<T, F> FixedPoint<T, F>::createFixedPoint(T value)
{
	FixedPoint<T, F> fixed_point;
	fixed_point._data = value;
	return fixed_point;
}

template <typename T, std::int8_t F>
template <typename U, std::int8_t G>
FixedPoint<T, F> FixedPoint<T, F>::operator+(const FixedPoint<U, G>& value) const
{
	static const std::int8_t FRACTION = F - G > 0 ? F : G;

	typedef typename SizeTypeIncrement<T, U>::Type V;

	FixedPoint<V, FRACTION> lhs = this->convert<V, FRACTION>();
	FixedPoint<V, FRACTION> rhs = value.template convert<V, FRACTION>();

	return FixedPoint<V, FRACTION>::createFixedPoint(lhs.raw() + rhs.raw()).template convert<T, U>();
}

template <typename T, std::int8_t F>
FixedPoint<T, F> FixedPoint<T, F>::operator+(const FixedPoint<T, F>& rhs) const
{
	return FixedPoint<T, F>::createFixedPoint(this->_data + rhs._data);
}

template <typename T, std::int8_t F>
FixedPoint<T, F>& FixedPoint<T, F>::operator+=(const FixedPoint<T, F>& rhs)
{
	_data += rhs._data;
	return *this;
}

template <typename T, std::int8_t F>
template <typename U, std::int8_t G>
FixedPoint<U, G> FixedPoint<T, F>::convert() const
{
	std::int8_t fractional = G - F;
	return FixedPoint<U, G>::createFixedPoint(convertType<T, U>(_data, fractional));
}

template <typename T, std::int8_t F>
template <typename I, typename J>
J FixedPoint<T, F>::convertType(const I& initial, std::int8_t shift)
{
	if (shift > 0)
	{
		J intermediate = static_cast<J>(initial);
		intermediate <<= shift;
		return intermediate;
	}

	I intermediate = initial;
	intermediate >>= -shift;
	return static_cast<J>(intermediate);
}

namespace std
{
	template <class T, std::int8_t F>
	class numeric_limits<FixedPoint<T, F>>
	{
	public:
		static constexpr bool is_specialized = true;
		static constexpr FixedPoint<T, F> min() noexcept { return FixedPoint<T, F>::min(); }
		static constexpr T max() noexcept { return T(); }
		static constexpr T lowest() noexcept { return T(); }
		
		static constexpr int  digits = 0;
		static constexpr int  digits10 = 0;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = false;
		
		static constexpr int radix = 2;
		static constexpr T epsilon() noexcept { return T(); }
		static constexpr T round_error() noexcept { return T(); }

		static constexpr int  min_exponent = 0;
		static constexpr int  min_exponent10 = 0;
		static constexpr int  max_exponent = 0;
		static constexpr int  max_exponent10 = 0;

		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr float_denorm_style has_denorm = denorm_absent;
		
		static constexpr bool has_denorm_loss = false;
		static constexpr T infinity() noexcept { return T(); }
		static constexpr T quiet_NaN() noexcept { return T(); }
		static constexpr T signaling_NaN() noexcept { return T(); }
		static constexpr T denorm_min() noexcept { return T(); }

		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;

		static constexpr bool traps = false;
		static constexpr bool tinyness_before = false;
		static constexpr float_round_style round_style = round_to_nearest;
	};
}