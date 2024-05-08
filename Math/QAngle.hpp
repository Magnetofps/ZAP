#pragma once
#include <cmath>

struct QAngle {
  float x;
  float y;

  QAngle() : x(0), y(0) {
  }

  QAngle(const float x, const float y) : x(x), y(y) {
  }

  QAngle operator+(const QAngle &other) const { return {x + other.x, y + other.y}; }

  QAngle operator-(const QAngle &other) const { return {x - other.x, y - other.y}; }

  QAngle operator*(const float scalar) const { return {x * scalar, y * scalar}; }

  QAngle operator/(const float scalar) const { return {x / scalar, y / scalar}; }

  QAngle &operator+=(const QAngle &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  QAngle &operator-=(const QAngle &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  QAngle &operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  QAngle &operator/=(const float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  bool operator==(const QAngle &other) const { return x == other.x && y == other.y; }

  bool operator!=(const QAngle &other) const { return !(*this == other); }

  [[nodiscard]] float dot(const QAngle &other) const { return x * other.x + y * other.y; }

  [[nodiscard]] float length() const { return std::sqrt(x * x + y * y); }

  [[nodiscard]] float distanceTo(const QAngle &other) const { return (other - *this).length(); };

  QAngle &normalize() {
    if (const float len = length(); len > 0) {
      x /= len;
      y /= len;
    }
    return *this;
  }

  QAngle &Clamp(const float minVal, const float maxVal) {
    x = std::clamp(x, minVal, maxVal);
    y = std::clamp(y, minVal, maxVal);

    return *this;
  }

  [[nodiscard]] QAngle lerp(const QAngle &other, const float t) const { return (*this) * (1.0f - t) + other * t; }

  QAngle &NormalizeAngles() {
    if (!isValid()) { return *this; }

    while (x > 89.0f)
      x -= 180.f;

    while (x < -89.0f)
      x += 180.f;

    while (y > 180.f)
      y -= 360.f;

    while (y < -180.f)
      y += 360.f;

    return *this;
  }

  [[nodiscard]] bool isValid() const {
    return !(std::isnan(x) || std::isinf(x) || std::isnan(y) || std::isinf(y));
  }

  static QAngle zero() { return {0, 0}; }
};
