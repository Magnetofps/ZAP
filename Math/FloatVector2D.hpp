#pragma once
struct FloatVector2D {
  float x, y;

  FloatVector2D() : x(0), y(0) {
  }

  FloatVector2D(const float x_val, const float y_val) : x(x_val), y(y_val) {
  }

  [[nodiscard]] FloatVector2D subtract(const FloatVector2D &other) const { return {x - other.x, y - other.y}; }

  [[nodiscard]] FloatVector2D add(const FloatVector2D &other) const { return {x + other.x, y + other.y}; }

  [[nodiscard]] FloatVector2D divide(const FloatVector2D &other) const { return {x / other.x, y / other.y}; }

  [[nodiscard]] FloatVector2D divide(const float scalar) const { return {x / scalar, y / scalar}; }

  [[nodiscard]] float dotProduct(const FloatVector2D &other) const { return x * other.x + y * other.y; }

  [[nodiscard]] float magnitude() const { return std::sqrt(x * x + y * y); }

  [[nodiscard]] float distance(const FloatVector2D &other) const {
    const FloatVector2D diff = subtract(other);
    return diff.magnitude();
  }

  [[nodiscard]] FloatVector2D multiply(const float scalar) const { return {x * scalar, y * scalar}; }

  [[nodiscard]] FloatVector2D normalized() const {
    FloatVector2D result;
    if (float length = std::sqrt(x * x + y * y); length != 0) {
      result.x = x / length;
      result.y = y / length;
    }
    return result;
  }

  [[nodiscard]] FloatVector2D multipliedByScalar(const float scalar) const {
    FloatVector2D result;
    result.x = x * scalar;
    result.y = y * scalar;
    return result;
  }

  [[nodiscard]] FloatVector2D clamp() const {
    //pitch doesnt have a full rotation so just set it to max value if its more than that
    float clampedX = x;
    if (clampedX < -89)
      clampedX = -89;
    if (clampedX > 89)
      clampedX = 89;
    //yaw has a full rotation so we might want to move it to the oposite side from negative to positive or vice versa
    float clampedY = y;
    if (clampedY < -180)
      clampedY += 360;
    if (clampedY > 180)
      clampedY -= 360;
    //create the vector
    if (clampedX > 89 || clampedX < -89)
      throw std::invalid_argument("SHIT CLAMPING OF PITCH. CHECK YOUR CODE");
    if (clampedY > 180 || clampedY < -180)
      throw std::invalid_argument("SHIT CLAMPING OF YAW. CHECK YOUR CODE");
    return {clampedX, clampedY};
  }

  [[nodiscard]] bool isZeroVector() const { return x == 0 && y == 0; }

  [[nodiscard]] std::string toString() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }

  void print() const { std::cout << toString() << "\n"; }

  bool operator==(const FloatVector2D &other) const {
    float epsilon = 1e-5;
    return (std::abs(x - other.x) < epsilon) && (std::abs(y - other.y) < epsilon);
  }

  bool operator!=(const FloatVector2D &other) const { return !(*this == other); }
};
