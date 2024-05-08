#pragma once
struct Vector2D {
  float x, y;

  Vector2D() : x(0), y(0) {
  }

  Vector2D(const float x_val, const float y_val) : x(x_val), y(y_val) {
  }

  float operator[](int i) const;

  float &operator[](int i);

  [[nodiscard]] Vector2D Subtract(const Vector2D &other) const { return {x - other.x, y - other.y}; }

  [[nodiscard]] Vector2D Add(const Vector2D &other) const { return {x + other.x, y + other.y}; }

  [[nodiscard]] Vector2D Divide(const Vector2D &other) const { return {x / other.x, y / other.y}; }

  [[nodiscard]] Vector2D Divide(const float scalar) const { return {x / scalar, y / scalar}; }

  [[nodiscard]] float DotProduct(const Vector2D &other) const { return x * other.x + y * other.y; }

  [[nodiscard]] float Magnitude() const { return std::sqrt(x * x + y * y); }

  [[nodiscard]] float Distance(const Vector2D &other) const {
    const Vector2D diff = Subtract(other);
    return diff.Magnitude();
  }

  [[nodiscard]] Vector2D Multiply(const float scalar) const { return {x * scalar, y * scalar}; }

  [[nodiscard]] Vector2D Normalized() const {
    float length = std::sqrt(x * x + y * y);
    return length != 0 ? Vector2D{x / length, y / length} : Vector2D{0, 0};
  }

  [[nodiscard]] Vector2D MultipliedByScalar(const float scalar) const {
    return {x * scalar, y * scalar};
  }

  [[nodiscard]] Vector2D Clamp() const {
    float clampedX = std::clamp(x, -89.0f, 89.0f);
    float clampedY = std::fmod(y + 180.0f, 360.0f) - 180.0f;

    return {clampedX, clampedY};
  }

  [[nodiscard]] bool IsZeroVector() const { return x == 0 && y == 0; }

  bool operator==(const Vector2D &other) const {
    float epsilon = 1e-5;
    return std::abs(x - other.x) < epsilon && std::abs(y - other.y) < epsilon;
  }

  bool operator!=(const Vector2D &other) const { return !(*this == other); }
};
