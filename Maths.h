#pragma once
#include "raylib.h"

namespace Maths {

Vector3 cross(const Vector3 &a, const Vector3 &b) {
  return {a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x};
}

float dot(const Vector3 &a, const Vector3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 operator+(Vector3 a, Vector3 b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 operator*(float k, Vector3 &a) { // scalar * vector
  return {k * a.x, k * a.y, k * a.z};
}

Vector3 rotatePlus90AroundGivenAxis(Vector3 &v, Vector3 &axis) {
  // axis has to be unit
  return cross(axis, v) + dot(axis, v) * axis;
}

} // namespace Maths
