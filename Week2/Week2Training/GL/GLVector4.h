#pragma once


template <typename  T>
class GLVector4
{
public:
	GLVector4()
		: x(0), y(0), z(0), w(0) { }

	GLVector4(const GLVector4<T>& rhs)
		: x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) { }

	GLVector4(const T& x, const T& y, const T& z, const T& w)
		:x(x), y(y), z(z), w(w) { }

	inline GLVector4& operator=(const GLVector4& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		this->w = rhs.w;

		return *this;
	}

	template <typename U>
	inline GLVector4& operator=(const T& rhs)
	{
		this->x = rhs;
		this->y = rhs;
		this->z = rhs;
		this->w = rhs;

		return *this;
	}

	inline GLVector4& operator+=(const GLVector4& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->w += rhs.w;

		return *this;
	}

	template <typename U>
	inline GLVector4& operator+=(const T& rhs)
	{
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;
		this->w += rhs;

		return *this;
	}

	inline GLVector4& operator-=(const GLVector4& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->w -= rhs.w;

		return *this;
	}

	template <typename U>
	inline GLVector4& operator-=(const T& rhs)
	{
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;
		this->w -= rhs;

		return *this;
	}

	inline GLVector4& operator*=(const GLVector4& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		this->w *= rhs.w;

		return *this;
	}

	template <typename U>
	inline GLVector4& operator*=(const T& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		this->w *= rhs;

		return *this;
	}

	inline GLVector4& operator/=(const GLVector4& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		this->w /= rhs.w;

		return *this;
	}

	template <typename U>
	inline GLVector4& operator/=(const T& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		this->w /= rhs;

		return *this;
	}

	T x;
	T y;
	T z;
	T w;
};

template <typename T, typename U>
const GLVector4<T>& operator+(const GLVector4<T>& lhs, const GLVector4<U>& rhs)
{
	return GLVector4<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

template <typename T, typename U>
const GLVector4<T>& operator+(const GLVector4<T>& lhs, const U& rhs)
{
	return GLVector4<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
}

template <typename T, typename U>
const GLVector4<T>& operator-(const GLVector4<T>& lhs, const GLVector4<U>& rhs)
{
	return GLVector4<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

template <typename T, typename U>
const GLVector4<T>& operator-(const GLVector4<T>& lhs, const U& rhs)
{
	return GLVector4<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
}

template <typename T, typename U>
const GLVector4<T>& operator*(const GLVector4<T>& lhs, const GLVector4<U>& rhs)
{
	return GLVector4<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
}

template <typename T, typename U>
const GLVector4<T>& operator*(const GLVector4<T>& lhs, const U& rhs)
{
	return GLVector4<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
}

template <typename T, typename U>
const GLVector4<T>& operator/(const GLVector4<T>& lhs, const GLVector4<U>& rhs)
{
	return GLVector4<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
}

template <typename T, typename U>
const GLVector4<T>& operator/(const GLVector4<T>& lhs, const U& rhs)
{
	return GLVector4<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
}