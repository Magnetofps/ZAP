#pragma once
struct FloatVector3D {
  float x, y, z;

  FloatVector3D() : x(0), y(0), z(0) {
  }

  FloatVector3D(const float x_val, const float y_val, const float z_val) : x(x_val), y(y_val), z(z_val) {
  }

  [[nodiscard]] FloatVector3D subtract(const FloatVector3D &other) const { return {x - other.x, y - other.y, z - other.z}; }

  [[nodiscard]] FloatVector3D add(const FloatVector3D &other) const { return {x + other.x, y + other.y, z + other.z}; }

  [[nodiscard]] float dotProduct(const FloatVector3D &other) const { return x * other.x + y * other.y + z * other.z; }

  [[nodiscard]] float magnitude() const { return std::sqrt(x * x + y * y + z * z); }

  [[nodiscard]] float distance(const FloatVector3D &other) const {
    const FloatVector3D diff = subtract(other);
    return diff.magnitude();
  }

  [[nodiscard]] bool isZeroVector() const { return x == 0 && y == 0 && z == 0; }

  [[nodiscard]] FloatVector3D normalize() const {
    if (const float mag = magnitude(); mag != 0)
      return {x / mag, y / mag, z / mag};
    return {};
  }

  [[nodiscard]] FloatVector3D multiply(const float scalar) const { return {x * scalar, y * scalar, z * scalar}; }

  [[nodiscard]] std::string toString() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")"; }

  void print() const { std::cout << toString() << "\n"; }

  [[nodiscard]] FloatVector2D to2D() const { return {x, y}; }

  bool operator==(const FloatVector3D &other) const {
    float epsilon = 1e-5;
    return std::abs(x - other.x) < epsilon && std::abs(y - other.y) < epsilon && std::abs(z - other.z < epsilon);
  }

  bool operator!=(const FloatVector3D &other) const { return !(*this == other); }
};
