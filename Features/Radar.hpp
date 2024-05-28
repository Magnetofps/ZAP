#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <vector>

#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"

#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/InputTypes.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

// Geometry
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

struct Radar {
  Camera *GameCamera;
  Level *m_level;
  LocalPlayer *Myself;
  std::vector<Player *> *Players;
  std::chrono::milliseconds LastUpdateTime;

  Radar(std::vector<Player *> *Players, Camera *GameCamera, Level *level, LocalPlayer *localplayer) {
    this->Players = Players;
    this->GameCamera = GameCamera;
    this->m_level = level;
    this->Myself = localplayer;
  }

  void ActivateBigMap() {
    if (!Features::Radar::BigMap)
      return;

    if (InputManager::isKeyDownOrPress(Features::Radar::BigMapBind)) {
      if (const int localPlayerTeamID = Myself->Team; localPlayerTeamID != 1) {
        float curTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
        constexpr double continueTime = 0.2;
        float endTime = curTime + continueTime;
        while (curTime < endTime) {
          Memory::Write<int>(Myself->BasePointer + OFF_TEAM_NUMBER, 1);
          curTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
        }
        curTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
        endTime = curTime + continueTime;
        while (curTime < endTime) {
          Memory::Write<int>(Myself->BasePointer + OFF_TEAM_NUMBER, localPlayerTeamID);
          curTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
        }
      }
    }
  }

  static bool Save() {
    try {
      Config::Radar::MiniMap = Features::Radar::MiniMap;
      Config::Radar::MiniMapRange = Features::Radar::MiniMapRange;
      Config::Radar::MiniMapScaleX = Features::Radar::MiniMapScaleX;
      Config::Radar::MiniMapScaleY = Features::Radar::MiniMapScaleY;
      Config::Radar::MiniMapDotSize = Features::Radar::MiniMapDotSize;
      Config::Radar::MiniMapBlackBGSize = Features::Radar::MiniMapBlackBGSize;
      Config::Radar::MiniMapGuides = Features::Radar::MiniMapGuides;
      Config::Radar::BigMap = Features::Radar::BigMap;
      Config::Radar::BigMapBind = static_cast<int>(Features::Radar::BigMapBind);
      Config::Radar::CircleColorR = Features::Radar::CircleColor[0];
      Config::Radar::CircleColorG = Features::Radar::CircleColor[0];
      Config::Radar::CircleColorB = Features::Radar::CircleColor[0];
      Config::Radar::CircleColorA = Features::Radar::CircleColor[0];

      return true;
    } catch (...) { return false; }
  }

  void RenderDrawings(LocalPlayer *Myself, const Overlay &OverlayWindow) {
    int ScreenWidth;
    int ScreenHeight;
    OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
    if (!m_level->IsPlayable)
      return;

    if (Features::Radar::MiniMap) {
      const ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
      ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));

      ImGui::Begin("Radar", (bool *) true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);

      for (const auto p : *Players) {
        if (!p->IsHostile || !p->IsValid() || Myself->BasePointer == p->BasePointer)
          continue;

        const float radardistance = static_cast<int>((Myself->LocalOrigin, p->Distance2DToLocalPlayer) / 39.62);

        MiniMapRadar(p->LocalOrigin, Myself->LocalOrigin, p->ViewAngles.y, radardistance, p->Team, p->ViewYaw);
      }
      ImGui::End();
    }
  }

  // DRAW RADAR POINT mini Map
  void DrawRadarPointMiniMap(const Vector3D EnemyPos, const Vector3D LocalPos, const float targetY, const float enemyDist, const int TeamID, const int xAxis, const int yAxis, const int width, const int height, const float targetyaw) {
    bool out = false;
    Vector3D siz;
    siz.x = width;
    siz.y = height;
    Vector3D pos;
    pos.x = xAxis;
    pos.y = yAxis;
    bool ck = false;

    const Vector3D single = Renderer::RotatePoint(EnemyPos, LocalPos, pos.x, pos.y, siz.x, siz.y, targetY, 0.3f, &ck);
    if (enemyDist >= 0.f && enemyDist < Features::Radar::MiniMapRange) {
      for (int i = 1; i <= 30; i++) {
        Renderer::TeamMiniMap(single.x, single.y, Features::Radar::MiniMapDotSize, TeamID, targetyaw, Features::Radar::MiniMapDotSize, Features::Radar::MiniMapBlackBGSize, ImColor(Features::Radar::CircleColor[0], Features::Radar::CircleColor[1], Features::Radar::CircleColor[2], Features::Radar::CircleColor[3]));
      }
    }
  }

  // MINI MAP RADAR IMPLEMENTATION
  void MiniMapRadar(const Vector3D EnemyPos, const Vector3D LocalPos, const float targetY, const float enemyDist, const int TeamId, const float targetyaw) {
    constexpr ImGuiWindowFlags TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar;
    if (Features::Radar::MiniMap) {
      // 1920*1080: 215 x 215
      // 2560*1440: 335 x 335
      ImGui::SetNextWindowSize({static_cast<float>(Features::Radar::MiniMapScaleX), static_cast<float>(Features::Radar::MiniMapScaleY)});
      ImGui::Begin(("##Radar"), nullptr, TargetFlags); {
        const ImVec2 DrawPos = ImGui::GetCursorScreenPos();
        const ImVec2 DrawSize = ImGui::GetContentRegionAvail();
        const ImVec2 midRadar = ImVec2(DrawPos.x + (DrawSize.x / 2), DrawPos.y + (DrawSize.y / 2));
        if (Features::Radar::MiniMapGuides) {
          const ImVec2 startHorizontal(midRadar.x - DrawSize.x / 2.f, midRadar.y);
          const ImVec2 endHorizontal(midRadar.x + DrawSize.x / 2.f, midRadar.y);
          const ImVec2 startVertical(midRadar.x, midRadar.y - DrawSize.y / 2.f);
          const ImVec2 endVertical(midRadar.x, midRadar.y + DrawSize.y / 2.f);
          constexpr float extension = -500000.f;

          ImGui::GetWindowDrawList()->AddLine(startHorizontal, ImVec2(startHorizontal.x - extension, endHorizontal.y), IM_COL32(255, 255, 255, 255));
          ImGui::GetWindowDrawList()->AddLine(endHorizontal, ImVec2(endHorizontal.x + extension, endHorizontal.y), IM_COL32(255, 255, 255, 255));

          ImGui::GetWindowDrawList()->AddLine(startVertical, ImVec2(startVertical.x, startVertical.y - extension), IM_COL32(255, 255, 255, 255));
          ImGui::GetWindowDrawList()->AddLine(endVertical, ImVec2(endVertical.x, endVertical.y + extension), IM_COL32(255, 255, 255, 255));
        }

        DrawRadarPointMiniMap(EnemyPos, LocalPos, targetY, enemyDist, TeamId, DrawPos.x, DrawPos.y, DrawSize.x, DrawSize.y, targetyaw);
      }
      ImGui::End();
    }
  }
};
