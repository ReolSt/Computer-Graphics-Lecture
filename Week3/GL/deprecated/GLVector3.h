#pragma once

template <typename T>
class GLVector3
{
public:
	//static GLVector3<GLfloat> back(0.0f, 0.0f, -1.0f);
	//static GLVector3<GLfloat> down(0.0f, -1.0f, 0.0f);
public:
	GLVector3() 
		: x(0), y(0), z(0) { }

	GLVector3(const GLVector3<T>& rhs)
		: x(rhs.x), y(rhs.y), z(rhs.z) { }

	GLVector3(T rhs[3])
		: x(rhs[0]), y(rhs[1]), z(rhs[2]) { }

	GLVector3(const T& x, const T& y, const T& z)
		: x(x), y(y), z(z) { }

	inline GLVector3& operator=(const GLVector3& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;

		return *this;
	}

	template <typename U>
	inline GLVector3& operator=(const T& rhs)
	{
		this->x = rhs;
		this->y = rhs;
		this->z = rhs;

		return *this;
	}

	inline GLVector3& operator+=(const GLVector3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}

	template <typename U>
	inline GLVector3& operator+=(const T& rhs)
	{
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;

		return *this;
	}

	inline GLVector3& operator-=(const GLVector3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}

	template <typename U>
	inline GLVector3& operator-=(const T& rhs)
	{
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;

		return *this;
	}

	inline GLVector3& operator*=(const GLVector3& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;

		return *this;
	}

	template <typename U>
	inline GLVector3& operator*=(const T& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;

		return *this;
	}

	inline GLVector3& operator/=(const GLVector3& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;

		return *this;
	}

	template <typename U>
	inline GLVector3& operator/=(const T& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;

		return *this;
	}

	template <typename U>
	inline bool operator==(const GLVector3& rhs)
	{
		return this->x == rhs.x &&
			this->y == rhs.y &&
			this->z == rhs.z;
	}

	template <typename U>
	inline bool operator!=(const GLVector3& rhs)
	{
		return !(this == rhs);
	}

	T x;
	T y;
	T z;
};

template <typename T, typename U>
GLVector3<T> operator+(const GLVector3<T>& lhs, const GLVector3<U>& rhs)
{
	return GLVector3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <typename T, typename U>
GLVector3<T> operator+(const GLVector3<T>& lhs, const U& rhs)
{
	return GLVector3<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

template <typename T, typename U>
GLVector3<T> operator-(const GLVector3<T>& lhs, const GLVector3<U>& rhs)
{
	return GLVector3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <typename T, typename U>
GLVector3<T> operator-(const GLVector3<T>& lhs, const U& rhs)
{
	return GLVector3<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}

template <typename T, typename U>
GLVector3<T> operator*(const GLVector3<T>& lhs, const GLVector3<U>& rhs)
{
	return GLVector3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

template <typename T, typename U>
GLVector3<T> operator*(const GLVector3<T>& lhs, const U& rhs)
{
	return GLVector3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

template <typename T>
GLVector3<T> operator/(const GLVector3<T>& lhs, const GLVector3<T>& rhs)
{
	return GLVector3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

template <typename T, typename U>
GLVector3<T> operator/(const GLVector3<T>& lhs, const U& rhs)
{
	return GLVector3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}
