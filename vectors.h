#pragma once

#include "../../inc/types.h"
#include <limits>

// Helper function to create a vector3, since there is explicit padding we can't use the literal syntax.
constexpr Vector3 v3(float x, float y, float z)
{
	Vector3 v = {};
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

constexpr Vector3 crossProduct(Vector3 v1, Vector3 v2)
{
	return v3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

constexpr double sqrtNewtonRaphson(double x, double curr, double prev)
{
	return curr == prev
		? curr
		: sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
}

constexpr double constSqrt(double x)
{
	return x >= 0 && x < std::numeric_limits<double>::infinity()
		? sqrtNewtonRaphson(x, x, 0)
		: std::numeric_limits<double>::quiet_NaN();
}

constexpr Vector3 normalize(Vector3 v)
{
	float length = constSqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	return v3(
		v.x / length,
		v.y / length,
		v.z / length
	);
}