#pragma once

template <typename T>
class GLVector2
{
public:
	GLVector2()
		: x(0), y(0) { }

	GLVector2(const GLVector2& rhs)
		: x(rhs.x), y(rhs.y) { }

	GLVector2(const T& x, const T& y)
		: x(x), y(y) { }

	inline GLVector2& operator=(const GLVector2& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;

		return *this;
	}

	template <typename U>
	inline GLVector2& operator=(const U& rhs)
	{
		this->x = rhs;
		this->y = rhs;

		return *this;
	}

	inline GLVector2& operator+=(const GLVector2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}

	template <typename U>
	inline GLVector2& operator+=(const U& rhs)
	{
		this->x += rhs;
		this->y += rhs;

		return *this;
	}

	inline GLVector2& operator-=(const GLVector2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}

	template <typename U>
	inline GLVector2& operator-=(const U& rhs)
	{
		this->x -= rhs;
		this->y -= rhs;

		return *this;
	}

	inline GLVector2& operator*=(const GLVector2& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;

		return *this;
	}

	template <typename U>
	inline GLVector2& operator*=(const U& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;

		return *this;
	}

	inline GLVector2& operator/=(const GLVector2& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;

		return *this;
	}

	template <typename U>
	inline GLVector2& operator/=(const U& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;

		return *this;
	}

	T x;
	T y;
};

template <typename T, typename U>
inline const GLVector2<T>& operator+(const GLVector2<T>& lhs, const GLVector2<U>& rhs)
{
	return GLVector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T, typename U>
inline const GLVector2<T>& operator+(const GLVector2<T>& lhs, const U& rhs)
{
	return GLVector2<T>(lhs.x + rhs, lhs.y + rhs);
}

template <typename T, typename U>
inline GLVector2<T> operator-(const GLVector2<T>& lhs, const GLVector2<U>& rhs)
{
	return GLVector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T, typename U>
inline const GLVector2<T>& operator-(const GLVector2<T>& lhs, const U& rhs)
{
	return GLVector2<T>(lhs.x - rhs, lhs.y - rhs);
}

template <typename T, typename U>
inline GLVector2<T> operator*(const GLVector2<T>& lhs, const GLVector2<U>& rhs)
{
	return GLVector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <typename T, typename U>
inline const GLVector2<T>& operator*(const GLVector2<T>& lhs, const U& rhs)
{
	return GLVector2<T>(lhs.x * rhs, lhs.y * rhs);
}

template <typename T, typename U>
inline GLVector2<T> operator/(const GLVector2<T>& lhs, const GLVector2<U>& rhs)
{
	return GLVector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

template <typename T, typename U>
inline const GLVector2<T>& operator/(const GLVector2<T>& lhs, const U& rhs)
{
	return GLVector2<T>(lhs.x / rhs, lhs.y / rhs);
}
