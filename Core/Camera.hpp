#pragma once
#include "Offsets.hpp"
#include "../Math/Matrix.hpp"
#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Utils/Memory.hpp"

struct Camera {
  Vector2D ScreenSize;
  ViewMatrix GameViewMatrix{};

  void Initialize(const int Width, const int Height) { ScreenSize = Vector2D(static_cast<float>(Width), static_cast<float>(Height)); }

  [[nodiscard]] const Vector2D &GetResolution() const { return ScreenSize; }

  void Update() {
    const auto RenderPtr = Memory::Read<long>(OFF_REGION + OFF_VIEWRENDER);
    const auto MatrixPtr = Memory::Read<long>(RenderPtr + OFF_VIEWMATRIX);
    GameViewMatrix = Memory::Read<ViewMatrix>(MatrixPtr);
  }

  bool WorldToScreen(Vector3D WorldPosition, Vector2D &ScreenPosition) const {
    Vector3D transformed = GameViewMatrix.Transform(WorldPosition);

    if (transformed.z < 0.001) { return false; }

    transformed.x *= 1.0f / transformed.z;
    transformed.y *= 1.0f / transformed.z;

    ScreenPosition = Vector2D(ScreenSize.x / 2.0f + transformed.x * (ScreenSize.x / 2.0f), ScreenSize.y / 2.0f - transformed.y * (ScreenSize.y / 2.0f));

    return true;
  }
};
