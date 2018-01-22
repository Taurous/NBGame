#pragma once

#include <type_traits>

namespace axe
{
	template <typename T>
	inline bool getBit(const T &bitfield, const int &bit)
	{
		static_assert(std::is_integral<T>::value, "Cannot do bitwise operations on non-integral type!\n");
		return (bitfield & bit);
	}

	template <typename T>
	inline void setBit(T &bitfield, const int &bit, bool flag)
	{
		static_assert(std::is_integral<T>::value, "Cannot do bitwise operations on non-integral type!\n");
		bitfield = flag ? bitfield | bit : ~(~bitfield | bit);
	}
}