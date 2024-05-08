#pragma once
#include <cmath>
#include "Vector3D.hpp"
#include "QAngle.hpp"

class Resolver {
public:
  static QAngle CalculateAngle(const Vector3D from, const Vector3D to) {
    Vector3D newDirection = to.Subtract(from);
    newDirection.Normalize();

    float pitch = -asinf(newDirection.z) * (180 / M_PI);
    float yaw = atan2f(newDirection.y, newDirection.x) * (180 / M_PI);

    return {pitch, yaw};
  }

  static Vector3D GetTargetPosition(const Vector3D &targetPosition, const Vector3D targetVelocity, const float time) {
    return targetPosition.Add(targetVelocity.Multiply(time));
  }

  static float GetTimeToTarget(const Vector3D startPosition, const Vector3D endPosition, const float bulletSpeed) {
    const float distance = endPosition.Subtract(startPosition).Magnitude();
    return distance / bulletSpeed;
  }

  static Vector3D GetTargetPosition(const Vector3D startPosition, const Vector3D endPosition, const Vector3D targetVelocity, const float bulletSpeed) {
    const float time = GetTimeToTarget(startPosition, endPosition, bulletSpeed);
    return GetTargetPosition(endPosition, targetVelocity, time);
  }

  // Aim at moving target without bullet drop predicion
  static bool CalculateAimRotation(const Vector3D startPosition, Vector3D endPosition, const Vector3D targetVelocity, const float bulletSpeed, QAngle &result) {
    endPosition = GetTargetPosition(startPosition, endPosition, targetVelocity, bulletSpeed);
    result = CalculateAngle(startPosition, endPosition);
    return true;
  }

  static bool CalculateAimRotationNew(const Vector3D start, Vector3D targetPosition, const Vector3D targetVelocity, const float bulletSpeed, const float bulletScale, const int steps, QAngle &result) {
    const float gravity = 750.0f / bulletScale;

    float angle = 0;
    float time = 0.0;
    const float timeStep = 1.0f / steps;

    for (int i = 0; i < steps; i++) {
      Vector3D predictedPosition = GetTargetPosition(targetPosition, targetVelocity, time);
      if (!OptimalAngle(start, predictedPosition, bulletSpeed, gravity, angle))
        continue;

      Vector3D direction = predictedPosition.Subtract(start);
      const float horizontalDistance = direction.Magnitude2D();
      if (const float travelTime = horizontalDistance / (bulletSpeed * cosf(angle)); travelTime <= time) {
        result.x = -angle * (180 / M_PI);
        result.y = atan2f(direction.y, direction.x) * (180 / M_PI); //180
        return true;
      }
      time += timeStep;
    }

    targetPosition = GetTargetPosition(start, targetPosition, targetVelocity, bulletSpeed);
    result = CalculateAngle(start, targetPosition);
    return true;
  }

  static bool OptimalAngle(const Vector3D start, const Vector3D end, const float speed, const float gravity, float &angle) {
    const float horizontalDistance = start.Distance2D(end);
    const float heightDifference = end.z - start.z;

    const float root = powf(speed, 4) - gravity * (gravity * powf(horizontalDistance, 2) + 2 * heightDifference * powf(speed, 2));
    if (root < 0.0)
      return false;

    const float term1 = powf(speed, 2) - std::sqrt(root);
    const float term2 = gravity * horizontalDistance;

    angle = atanf(term1 / term2);
    return true;
  }
};
