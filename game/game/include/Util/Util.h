#pragma once

#include <type_traits>

template <typename T>
inline bool getBit(const T &bitfield, const int flag)
{
	static_assert(std::is_integral<T>::value, "Cannot do bitwise operations on non-integral type!\n");
	return (bitfield & flag);
}

template <typename T>
inline void setBit(T &bitfield, const int &bit, bool flag)
{
	static_assert(std::is_integral<T>::value, "Cannot do bitwise operations on non-integral type!\n");
	bitfield = flag ? bitfield | bit : ~(~bitfield | bit);
}