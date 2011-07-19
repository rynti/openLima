#ifndef OPENLIMA_UTIL_VECTOR3F_HPP
#define OPENLIMA_UTIL_VECTOR3F_HPP

#include "Vector3.hpp"


class Vector3f : public Vector3<float> {
public:
	Vector3f(float x, float y, float z) : Vector3<float>(x, y, z) {}
	Vector3f() : Vector3(0.0f, 0.0f, 0.0f) {}
};

#endif /* OPENLIMA_UTIL_VECTOR3F_HPP */