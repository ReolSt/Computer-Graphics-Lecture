#pragma once

#include <array>

class GLIndex
{
public:
	GLIndex()
		: v1(0), v2(0), v3(0) { }

	GLIndex(const unsigned int& v1, const unsigned int& v2, const unsigned int& v3)
		: v1(v1), v2(v2), v3(v3) { }

	GLIndex(const std::array<unsigned int, 3>& indices)
		: v1(indices[0]),
		  v2(indices[1]),
		  v3(indices[2]) { }

	unsigned int v1;
	unsigned int v2;
	unsigned int v3;
};
