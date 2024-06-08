#pragma once
#include <sstream>
#include <string>
#include <vector>

#include "../Core/Camera.hpp"
#include "../Core/Level.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/Player.hpp"
#include "../Features/Legitbot.hpp"
#include "../imgui/imgui.h"
#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/Memory.hpp"
#include "../Utils/XDisplay.hpp"

// Geometry
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))
#define ABS(x) ((x < 0) ? (-x) : (x))

struct Sense {
  // Variables
  XDisplay *X11Display;
  Camera *GameCamera;
  LocalPlayer *Myself;
  std::vector<Player *> *Players;
  std::chrono::milliseconds LastSpectatorUpdateTime{};
  int TotalSpectators = 0;
  std::vector<std::string> Spectators;

  std::chrono::milliseconds ProcessingLastUpdatae{};
  std::vector<double> ProcessingTimes;
  double ProcessingTime = 0;

  std::chrono::milliseconds FpsUpdate{};
  int FpsLastFrame = 0;
  int Fps = 0;

  Level *Map;

  Sense(Level *Map, std::vector<Player *> *Players, Camera *GameCamera, LocalPlayer *Myself, XDisplay *X11Display) {
    this->Players = Players;
    this->GameCamera = GameCamera;
    this->Map = Map;
    this->Myself = Myself;
    this->X11Display = X11Display;
  }

  static bool Save() {
    try {
      Config::Sense::Enabled = Features::Sense::Enabled;
      Config::Sense::DrawFOVCircle = Features::Sense::DrawFOVCircle;
      Config::Sense::DrawFilledFOVCircle = Features::Sense::DrawFilledFOVCircle;
      Config::Sense::FOVThickness = Features::Sense::FOVThickness;
      Config::Sense::GameFOV = Features::Sense::GameFOV;
      Config::Sense::DrawCrosshair = Features::Sense::DrawCrosshair;
      Config::Sense::CrosshairSize = Features::Sense::CrosshairSize;
      Config::Sense::CrosshairThickness = Features::Sense::CrosshairThickness;
      Config::Sense::ShowSpectators = Features::Sense::ShowSpectators;
      Config::Sense::DrawSpectatorWarning = Features::Sense::DrawSpectatorWarning;
      Config::Sense::DrawVisibleWarning = Features::Sense::DrawVisibleWarning;
      Config::Sense::WarningTextOutline = Features::Sense::WarningTextOutline;
      Config::Sense::WarningTextX = Features::Sense::WarningTextX;
      Config::Sense::WarningTextY = Features::Sense::WarningTextY;
      Config::Sense::TextOutline = Features::Sense::TextOutline;
      Config::Sense::VisibilityCheck = Features::Sense::VisibilityCheck;
      Config::Sense::ESPMaxDistance = Features::Sense::ESPMaxDistance;

      Config::SenseEnemy::DrawEnemy = Features::Sense::Enemy::DrawEnemy;
      Config::SenseEnemy::DrawBoxes = Features::Sense::Enemy::DrawBoxes;
      Config::SenseEnemy::BoxType = Features::Sense::Enemy::BoxType;
      Config::SenseEnemy::BoxStyle = Features::Sense::Enemy::BoxStyle;
      Config::SenseEnemy::BoxThickness = Features::Sense::Enemy::BoxThickness;
      Config::SenseEnemy::DrawSkeleton = Features::Sense::Enemy::DrawSkeleton;
      Config::SenseEnemy::SkeletonThickness = Features::Sense::Enemy::SkeletonThickness;
      Config::SenseEnemy::DrawHeadCircle = Features::Sense::Enemy::DrawHeadCircle;
      Config::SenseEnemy::HeadCircleThickness = Features::Sense::Enemy::HeadCircleThickness;
      Config::SenseEnemy::DrawBars = Features::Sense::Enemy::DrawBars;
      Config::SenseEnemy::HealthBar = Features::Sense::Enemy::HealthBar;
      Config::SenseEnemy::ShieldBar = Features::Sense::Enemy::ShieldBar;
      Config::SenseEnemy::BarMode = Features::Sense::Enemy::BarMode;
      Config::SenseEnemy::BarStyle = Features::Sense::Enemy::BarStyle;
      Config::SenseEnemy::BarThickness = Features::Sense::Enemy::BarThickness;
      Config::SenseEnemy::BarThickness2 = Features::Sense::Enemy::BarThickness2;
      Config::SenseEnemy::BarHeight = Features::Sense::Enemy::BarHeight;
      Config::SenseEnemy::BarWidth = Features::Sense::Enemy::BarWidth;
      Config::SenseEnemy::BarColorMode = Features::Sense::Enemy::BarColorMode;
      Config::SenseEnemy::WeaponColorType = Features::Sense::Enemy::WeaponColorType;
      Config::SenseEnemy::DrawDistance = Features::Sense::Enemy::DrawDistance;
      Config::SenseEnemy::TracerPosition = Features::Sense::Enemy::TracerPosition;
      Config::SenseEnemy::TracerBone = Features::Sense::Enemy::TracerBone;
      Config::SenseEnemy::DrawTracers = Features::Sense::Enemy::DrawTracers;
      Config::SenseEnemy::TracerThickness = Features::Sense::Enemy::TracerThickness;
      Config::SenseEnemy::DrawNames = Features::Sense::Enemy::DrawNames;
      Config::SenseEnemy::DrawStatus = Features::Sense::Enemy::DrawStatus;
      Config::SenseEnemy::ShowMaxStatusValues = Features::Sense::Enemy::ShowMaxStatusValues;
      Config::SenseEnemy::DrawWeapon = Features::Sense::Enemy::DrawWeapon;
      Config::SenseEnemy::DrawLegend = Features::Sense::Enemy::DrawLegend;

      Config::SenseTeammate::DrawTeam = Features::Sense::Teammate::DrawTeam;
      Config::SenseTeammate::DrawBoxes = Features::Sense::Teammate::DrawBoxes;
      Config::SenseTeammate::BoxType = Features::Sense::Teammate::BoxType;
      Config::SenseTeammate::BoxStyle = Features::Sense::Teammate::BoxStyle;
      Config::SenseTeammate::BoxThickness = Features::Sense::Teammate::BoxThickness;
      Config::SenseTeammate::DrawSkeleton = Features::Sense::Teammate::DrawSkeleton;
      Config::SenseTeammate::SkeletonThickness = Features::Sense::Teammate::SkeletonThickness;
      Config::SenseTeammate::DrawHeadCircle = Features::Sense::Teammate::DrawHeadCircle;
      Config::SenseTeammate::HeadCircleThickness = Features::Sense::Teammate::HeadCircleThickness;
      Config::SenseTeammate::DrawBars = Features::Sense::Teammate::DrawBars;
      Config::SenseTeammate::HealthBar = Features::Sense::Teammate::HealthBar;
      Config::SenseTeammate::ShieldBar = Features::Sense::Teammate::ShieldBar;
      Config::SenseTeammate::BarMode = Features::Sense::Teammate::BarMode;
      Config::SenseTeammate::BarStyle = Features::Sense::Teammate::BarStyle;
      Config::SenseTeammate::BarThickness = Features::Sense::Teammate::BarThickness;
      Config::SenseTeammate::BarThickness2 = Features::Sense::Teammate::BarThickness2;
      Config::SenseTeammate::BarHeight = Features::Sense::Teammate::BarHeight;
      Config::SenseTeammate::BarWidth = Features::Sense::Teammate::BarWidth;
      Config::SenseTeammate::BarColorMode = Features::Sense::Teammate::BarColorMode;
      Config::SenseTeammate::WeaponColorType = Features::Sense::Teammate::WeaponColorType;
      Config::SenseTeammate::DrawDistance = Features::Sense::Teammate::DrawDistance;
      Config::SenseTeammate::TracerPosition = Features::Sense::Teammate::TracerPosition;
      Config::SenseTeammate::TracerBone = Features::Sense::Teammate::TracerBone;
      Config::SenseTeammate::DrawTracers = Features::Sense::Teammate::DrawTracers;
      Config::SenseTeammate::TracerThickness = Features::Sense::Teammate::TracerThickness;
      Config::SenseTeammate::DrawNames = Features::Sense::Teammate::DrawNames;
      Config::SenseTeammate::DrawStatus = Features::Sense::Teammate::DrawStatus;
      Config::SenseTeammate::ShowMaxStatusValues = Features::Sense::Teammate::ShowMaxStatusValues;
      Config::SenseTeammate::DrawWeapon = Features::Sense::Teammate::DrawWeapon;
      Config::SenseTeammate::DrawLegend = Features::Sense::Teammate::DrawLegend;

      Config::SensePositions::NamePosition = Features::Sense::Positions::NamePosition;
      Config::SensePositions::DistancePosition = Features::Sense::Positions::DistancePosition;
      Config::SensePositions::LegendPosition = Features::Sense::Positions::LegendPosition;
      Config::SensePositions::WeaponPosition = Features::Sense::Positions::WeaponPosition;
      Config::SensePositions::StatusPosition = Features::Sense::Positions::StatusPosition;

      // Colors
      Config::SenseEnemy::WeaponColorType = Features::Sense::Enemy::WeaponColorType;
      Config::EnemyColors::InvisibleBoxColorR = Features::Colors::Enemy::InvisibleBoxColor[0];
      Config::EnemyColors::InvisibleBoxColorG = Features::Colors::Enemy::InvisibleBoxColor[1];
      Config::EnemyColors::InvisibleBoxColorB = Features::Colors::Enemy::InvisibleBoxColor[2];
      Config::EnemyColors::InvisibleBoxColorA = Features::Colors::Enemy::InvisibleBoxColor[3];
      Config::EnemyColors::VisibleBoxColorR = Features::Colors::Enemy::VisibleBoxColor[0];
      Config::EnemyColors::VisibleBoxColorG = Features::Colors::Enemy::VisibleBoxColor[1];
      Config::EnemyColors::VisibleBoxColorB = Features::Colors::Enemy::VisibleBoxColor[2];
      Config::EnemyColors::VisibleBoxColorA = Features::Colors::Enemy::VisibleBoxColor[3];
      Config::EnemyColors::InvisibleFilledBoxColorR = Features::Colors::Enemy::InvisibleFilledBoxColor[0];
      Config::EnemyColors::InvisibleFilledBoxColorG = Features::Colors::Enemy::InvisibleFilledBoxColor[1];
      Config::EnemyColors::InvisibleFilledBoxColorB = Features::Colors::Enemy::InvisibleFilledBoxColor[2];
      Config::EnemyColors::InvisibleFilledBoxColorA = Features::Colors::Enemy::InvisibleFilledBoxColor[3];
      Config::EnemyColors::VisibleFilledBoxColorR = Features::Colors::Enemy::VisibleFilledBoxColor[0];
      Config::EnemyColors::VisibleFilledBoxColorG = Features::Colors::Enemy::VisibleFilledBoxColor[1];
      Config::EnemyColors::VisibleFilledBoxColorB = Features::Colors::Enemy::VisibleFilledBoxColor[2];
      Config::EnemyColors::VisibleFilledBoxColorA = Features::Colors::Enemy::VisibleFilledBoxColor[3];
      Config::EnemyColors::InvisibleTracerColorR = Features::Colors::Enemy::InvisibleTracerColor[0];
      Config::EnemyColors::InvisibleTracerColorG = Features::Colors::Enemy::InvisibleTracerColor[1];
      Config::EnemyColors::InvisibleTracerColorB = Features::Colors::Enemy::InvisibleTracerColor[2];
      Config::EnemyColors::InvisibleTracerColorA = Features::Colors::Enemy::InvisibleTracerColor[3];
      Config::EnemyColors::VisibleTracerColorR = Features::Colors::Enemy::VisibleTracerColor[0];
      Config::EnemyColors::VisibleTracerColorG = Features::Colors::Enemy::VisibleTracerColor[1];
      Config::EnemyColors::VisibleTracerColorB = Features::Colors::Enemy::VisibleTracerColor[2];
      Config::EnemyColors::VisibleTracerColorA = Features::Colors::Enemy::VisibleTracerColor[3];
      Config::EnemyColors::InvisibleSkeletonColorR = Features::Colors::Enemy::InvisibleSkeletonColor[0];
      Config::EnemyColors::InvisibleSkeletonColorG = Features::Colors::Enemy::InvisibleSkeletonColor[1];
      Config::EnemyColors::InvisibleSkeletonColorB = Features::Colors::Enemy::InvisibleSkeletonColor[2];
      Config::EnemyColors::InvisibleSkeletonColorA = Features::Colors::Enemy::InvisibleSkeletonColor[3];
      Config::EnemyColors::VisibleSkeletonColorR = Features::Colors::Enemy::VisibleSkeletonColor[0];
      Config::EnemyColors::VisibleSkeletonColorG = Features::Colors::Enemy::VisibleSkeletonColor[1];
      Config::EnemyColors::VisibleSkeletonColorB = Features::Colors::Enemy::VisibleSkeletonColor[2];
      Config::EnemyColors::VisibleSkeletonColorA = Features::Colors::Enemy::VisibleSkeletonColor[3];
      Config::EnemyColors::InvisibleNameColorR = Features::Colors::Enemy::InvisibleNameColor[0];
      Config::EnemyColors::InvisibleNameColorG = Features::Colors::Enemy::InvisibleNameColor[1];
      Config::EnemyColors::InvisibleNameColorB = Features::Colors::Enemy::InvisibleNameColor[2];
      Config::EnemyColors::InvisibleNameColorA = Features::Colors::Enemy::InvisibleNameColor[3];
      Config::EnemyColors::VisibleNameColorR = Features::Colors::Enemy::VisibleNameColor[0];
      Config::EnemyColors::VisibleNameColorG = Features::Colors::Enemy::VisibleNameColor[1];
      Config::EnemyColors::VisibleNameColorB = Features::Colors::Enemy::VisibleNameColor[2];
      Config::EnemyColors::VisibleNameColorA = Features::Colors::Enemy::VisibleNameColor[3];
      Config::EnemyColors::InvisibleDistanceColorR = Features::Colors::Enemy::InvisibleDistanceColor[0];
      Config::EnemyColors::InvisibleDistanceColorG = Features::Colors::Enemy::InvisibleDistanceColor[1];
      Config::EnemyColors::InvisibleDistanceColorB = Features::Colors::Enemy::InvisibleDistanceColor[2];
      Config::EnemyColors::InvisibleDistanceColorA = Features::Colors::Enemy::InvisibleDistanceColor[3];
      Config::EnemyColors::VisibleDistanceColorR = Features::Colors::Enemy::VisibleDistanceColor[0];
      Config::EnemyColors::VisibleDistanceColorG = Features::Colors::Enemy::VisibleDistanceColor[1];
      Config::EnemyColors::VisibleDistanceColorB = Features::Colors::Enemy::VisibleDistanceColor[2];
      Config::EnemyColors::VisibleDistanceColorA = Features::Colors::Enemy::VisibleDistanceColor[3];
      Config::EnemyColors::InvisibleLegendColorR = Features::Colors::Enemy::InvisibleLegendColor[0];
      Config::EnemyColors::InvisibleLegendColorG = Features::Colors::Enemy::InvisibleLegendColor[1];
      Config::EnemyColors::InvisibleLegendColorB = Features::Colors::Enemy::InvisibleLegendColor[2];
      Config::EnemyColors::InvisibleLegendColorA = Features::Colors::Enemy::InvisibleLegendColor[3];
      Config::EnemyColors::VisibleLegendColorR = Features::Colors::Enemy::VisibleLegendColor[0];
      Config::EnemyColors::VisibleLegendColorG = Features::Colors::Enemy::VisibleLegendColor[1];
      Config::EnemyColors::VisibleLegendColorB = Features::Colors::Enemy::VisibleLegendColor[2];
      Config::EnemyColors::VisibleLegendColorA = Features::Colors::Enemy::VisibleLegendColor[3];
      Config::EnemyColors::InvisibleWeaponColorR = Features::Colors::Enemy::InvisibleWeaponColor[0];
      Config::EnemyColors::InvisibleWeaponColorG = Features::Colors::Enemy::InvisibleWeaponColor[1];
      Config::EnemyColors::InvisibleWeaponColorB = Features::Colors::Enemy::InvisibleWeaponColor[2];
      Config::EnemyColors::InvisibleWeaponColorA = Features::Colors::Enemy::InvisibleWeaponColor[3];
      Config::EnemyColors::VisibleWeaponColorR = Features::Colors::Enemy::VisibleWeaponColor[0];
      Config::EnemyColors::VisibleWeaponColorG = Features::Colors::Enemy::VisibleWeaponColor[1];
      Config::EnemyColors::VisibleWeaponColorB = Features::Colors::Enemy::VisibleWeaponColor[2];
      Config::EnemyColors::VisibleWeaponColorA = Features::Colors::Enemy::VisibleWeaponColor[3];
      Config::Colors::FOVColorR = Features::Colors::FOVColor[0];
      Config::Colors::FOVColorG = Features::Colors::FOVColor[1];
      Config::Colors::FOVColorB = Features::Colors::FOVColor[2];
      Config::Colors::FOVColorA = Features::Colors::FOVColor[3];
      Config::Colors::FilledFOVColorR = Features::Colors::FilledFOVColor[0];
      Config::Colors::FilledFOVColorG = Features::Colors::FilledFOVColor[1];
      Config::Colors::FilledFOVColorB = Features::Colors::FilledFOVColor[2];
      Config::Colors::FilledFOVColorA = Features::Colors::FilledFOVColor[3];
      Config::Colors::CrosshairColorR = Features::Colors::CrosshairColor[0];
      Config::Colors::CrosshairColorG = Features::Colors::CrosshairColor[1];
      Config::Colors::CrosshairColorB = Features::Colors::CrosshairColor[2];
      Config::Colors::CrosshairColorA = Features::Colors::CrosshairColor[3];

      // Weapon Colors
      Config::EnemyColors::LightWeaponColorR = Features::Colors::Enemy::LightWeaponColor[0];
      Config::EnemyColors::LightWeaponColorG = Features::Colors::Enemy::LightWeaponColor[1];
      Config::EnemyColors::LightWeaponColorB = Features::Colors::Enemy::LightWeaponColor[2];
      Config::EnemyColors::LightWeaponColorA = Features::Colors::Enemy::LightWeaponColor[3];
      Config::EnemyColors::HeavyWeaponColorR = Features::Colors::Enemy::HeavyWeaponColor[0];
      Config::EnemyColors::HeavyWeaponColorG = Features::Colors::Enemy::HeavyWeaponColor[1];
      Config::EnemyColors::HeavyWeaponColorB = Features::Colors::Enemy::HeavyWeaponColor[2];
      Config::EnemyColors::HeavyWeaponColorA = Features::Colors::Enemy::HeavyWeaponColor[3];
      Config::EnemyColors::EnergyWeaponColorR = Features::Colors::Enemy::EnergyWeaponColor[0];
      Config::EnemyColors::EnergyWeaponColorG = Features::Colors::Enemy::EnergyWeaponColor[1];
      Config::EnemyColors::EnergyWeaponColorB = Features::Colors::Enemy::EnergyWeaponColor[2];
      Config::EnemyColors::EnergyWeaponColorA = Features::Colors::Enemy::EnergyWeaponColor[3];
      Config::EnemyColors::ShotgunWeaponColorR = Features::Colors::Enemy::ShotgunWeaponColor[0];
      Config::EnemyColors::ShotgunWeaponColorG = Features::Colors::Enemy::ShotgunWeaponColor[1];
      Config::EnemyColors::ShotgunWeaponColorB = Features::Colors::Enemy::ShotgunWeaponColor[2];
      Config::EnemyColors::ShotgunWeaponColorA = Features::Colors::Enemy::ShotgunWeaponColor[3];
      Config::EnemyColors::SniperWeaponColorR = Features::Colors::Enemy::SniperWeaponColor[0];
      Config::EnemyColors::SniperWeaponColorG = Features::Colors::Enemy::SniperWeaponColor[1];
      Config::EnemyColors::SniperWeaponColorB = Features::Colors::Enemy::SniperWeaponColor[2];
      Config::EnemyColors::SniperWeaponColorA = Features::Colors::Enemy::SniperWeaponColor[3];
      Config::EnemyColors::LegendaryWeaponColorR = Features::Colors::Enemy::LegendaryWeaponColor[0];
      Config::EnemyColors::LegendaryWeaponColorG = Features::Colors::Enemy::LegendaryWeaponColor[1];
      Config::EnemyColors::LegendaryWeaponColorB = Features::Colors::Enemy::LegendaryWeaponColor[2];
      Config::EnemyColors::LegendaryWeaponColorA = Features::Colors::Enemy::LegendaryWeaponColor[3];
      Config::EnemyColors::MeleeWeaponColorR = Features::Colors::Enemy::MeleeWeaponColor[0];
      Config::EnemyColors::MeleeWeaponColorG = Features::Colors::Enemy::MeleeWeaponColor[1];
      Config::EnemyColors::MeleeWeaponColorB = Features::Colors::Enemy::MeleeWeaponColor[2];
      Config::EnemyColors::MeleeWeaponColorA = Features::Colors::Enemy::MeleeWeaponColor[3];
      Config::EnemyColors::ThrowableWeaponColorR = Features::Colors::Enemy::ThrowableWeaponColor[0];
      Config::EnemyColors::ThrowableWeaponColorG = Features::Colors::Enemy::ThrowableWeaponColor[1];
      Config::EnemyColors::ThrowableWeaponColorB = Features::Colors::Enemy::ThrowableWeaponColor[2];
      Config::EnemyColors::ThrowableWeaponColorA = Features::Colors::Enemy::ThrowableWeaponColor[3];

      // Colors
      Config::SenseTeammate::WeaponColorType = Features::Sense::Teammate::WeaponColorType;
      Config::TeammateColors::InvisibleBoxColorR = Features::Colors::Teammate::InvisibleBoxColor[0];
      Config::TeammateColors::InvisibleBoxColorG = Features::Colors::Teammate::InvisibleBoxColor[1];
      Config::TeammateColors::InvisibleBoxColorB = Features::Colors::Teammate::InvisibleBoxColor[2];
      Config::TeammateColors::InvisibleBoxColorA = Features::Colors::Teammate::InvisibleBoxColor[3];
      Config::TeammateColors::VisibleBoxColorR = Features::Colors::Teammate::VisibleBoxColor[0];
      Config::TeammateColors::VisibleBoxColorG = Features::Colors::Teammate::VisibleBoxColor[1];
      Config::TeammateColors::VisibleBoxColorB = Features::Colors::Teammate::VisibleBoxColor[2];
      Config::TeammateColors::VisibleBoxColorA = Features::Colors::Teammate::VisibleBoxColor[3];
      Config::TeammateColors::InvisibleFilledBoxColorR = Features::Colors::Teammate::InvisibleFilledBoxColor[0];
      Config::TeammateColors::InvisibleFilledBoxColorG = Features::Colors::Teammate::InvisibleFilledBoxColor[1];
      Config::TeammateColors::InvisibleFilledBoxColorB = Features::Colors::Teammate::InvisibleFilledBoxColor[2];
      Config::TeammateColors::InvisibleFilledBoxColorA = Features::Colors::Teammate::InvisibleFilledBoxColor[3];
      Config::TeammateColors::VisibleFilledBoxColorR = Features::Colors::Teammate::VisibleFilledBoxColor[0];
      Config::TeammateColors::VisibleFilledBoxColorG = Features::Colors::Teammate::VisibleFilledBoxColor[1];
      Config::TeammateColors::VisibleFilledBoxColorB = Features::Colors::Teammate::VisibleFilledBoxColor[2];
      Config::TeammateColors::VisibleFilledBoxColorA = Features::Colors::Teammate::VisibleFilledBoxColor[3];
      Config::TeammateColors::InvisibleTracerColorR = Features::Colors::Teammate::InvisibleTracerColor[0];
      Config::TeammateColors::InvisibleTracerColorG = Features::Colors::Teammate::InvisibleTracerColor[1];
      Config::TeammateColors::InvisibleTracerColorB = Features::Colors::Teammate::InvisibleTracerColor[2];
      Config::TeammateColors::InvisibleTracerColorA = Features::Colors::Teammate::InvisibleTracerColor[3];
      Config::TeammateColors::VisibleTracerColorR = Features::Colors::Teammate::VisibleTracerColor[0];
      Config::TeammateColors::VisibleTracerColorG = Features::Colors::Teammate::VisibleTracerColor[1];
      Config::TeammateColors::VisibleTracerColorB = Features::Colors::Teammate::VisibleTracerColor[2];
      Config::TeammateColors::VisibleTracerColorA = Features::Colors::Teammate::VisibleTracerColor[3];
      Config::TeammateColors::InvisibleSkeletonColorR = Features::Colors::Teammate::InvisibleSkeletonColor[0];
      Config::TeammateColors::InvisibleSkeletonColorG = Features::Colors::Teammate::InvisibleSkeletonColor[1];
      Config::TeammateColors::InvisibleSkeletonColorB = Features::Colors::Teammate::InvisibleSkeletonColor[2];
      Config::TeammateColors::InvisibleSkeletonColorA = Features::Colors::Teammate::InvisibleSkeletonColor[3];
      Config::TeammateColors::VisibleSkeletonColorR = Features::Colors::Teammate::VisibleSkeletonColor[0];
      Config::TeammateColors::VisibleSkeletonColorG = Features::Colors::Teammate::VisibleSkeletonColor[1];
      Config::TeammateColors::VisibleSkeletonColorB = Features::Colors::Teammate::VisibleSkeletonColor[2];
      Config::TeammateColors::VisibleSkeletonColorA = Features::Colors::Teammate::VisibleSkeletonColor[3];
      Config::TeammateColors::InvisibleNameColorR = Features::Colors::Teammate::InvisibleNameColor[0];
      Config::TeammateColors::InvisibleNameColorG = Features::Colors::Teammate::InvisibleNameColor[1];
      Config::TeammateColors::InvisibleNameColorB = Features::Colors::Teammate::InvisibleNameColor[2];
      Config::TeammateColors::InvisibleNameColorA = Features::Colors::Teammate::InvisibleNameColor[3];
      Config::TeammateColors::VisibleNameColorR = Features::Colors::Teammate::VisibleNameColor[0];
      Config::TeammateColors::VisibleNameColorG = Features::Colors::Teammate::VisibleNameColor[1];
      Config::TeammateColors::VisibleNameColorB = Features::Colors::Teammate::VisibleNameColor[2];
      Config::TeammateColors::VisibleNameColorA = Features::Colors::Teammate::VisibleNameColor[3];
      Config::TeammateColors::InvisibleDistanceColorR = Features::Colors::Teammate::InvisibleDistanceColor[0];
      Config::TeammateColors::InvisibleDistanceColorG = Features::Colors::Teammate::InvisibleDistanceColor[1];
      Config::TeammateColors::InvisibleDistanceColorB = Features::Colors::Teammate::InvisibleDistanceColor[2];
      Config::TeammateColors::InvisibleDistanceColorA = Features::Colors::Teammate::InvisibleDistanceColor[3];
      Config::TeammateColors::VisibleDistanceColorR = Features::Colors::Teammate::VisibleDistanceColor[0];
      Config::TeammateColors::VisibleDistanceColorG = Features::Colors::Teammate::VisibleDistanceColor[1];
      Config::TeammateColors::VisibleDistanceColorB = Features::Colors::Teammate::VisibleDistanceColor[2];
      Config::TeammateColors::VisibleDistanceColorA = Features::Colors::Teammate::VisibleDistanceColor[3];
      Config::TeammateColors::InvisibleLegendColorR = Features::Colors::Teammate::InvisibleLegendColor[0];
      Config::TeammateColors::InvisibleLegendColorG = Features::Colors::Teammate::InvisibleLegendColor[1];
      Config::TeammateColors::InvisibleLegendColorB = Features::Colors::Teammate::InvisibleLegendColor[2];
      Config::TeammateColors::InvisibleLegendColorA = Features::Colors::Teammate::InvisibleLegendColor[3];
      Config::TeammateColors::VisibleLegendColorR = Features::Colors::Teammate::VisibleLegendColor[0];
      Config::TeammateColors::VisibleLegendColorG = Features::Colors::Teammate::VisibleLegendColor[1];
      Config::TeammateColors::VisibleLegendColorB = Features::Colors::Teammate::VisibleLegendColor[2];
      Config::TeammateColors::VisibleLegendColorA = Features::Colors::Teammate::VisibleLegendColor[3];
      Config::TeammateColors::InvisibleWeaponColorR = Features::Colors::Teammate::InvisibleWeaponColor[0];
      Config::TeammateColors::InvisibleWeaponColorG = Features::Colors::Teammate::InvisibleWeaponColor[1];
      Config::TeammateColors::InvisibleWeaponColorB = Features::Colors::Teammate::InvisibleWeaponColor[2];
      Config::TeammateColors::InvisibleWeaponColorA = Features::Colors::Teammate::InvisibleWeaponColor[3];
      Config::TeammateColors::VisibleWeaponColorR = Features::Colors::Teammate::VisibleWeaponColor[0];
      Config::TeammateColors::VisibleWeaponColorG = Features::Colors::Teammate::VisibleWeaponColor[1];
      Config::TeammateColors::VisibleWeaponColorB = Features::Colors::Teammate::VisibleWeaponColor[2];
      Config::TeammateColors::VisibleWeaponColorA = Features::Colors::Teammate::VisibleWeaponColor[3];
      Config::Colors::FOVColorR = Features::Colors::FOVColor[0];
      Config::Colors::FOVColorG = Features::Colors::FOVColor[1];
      Config::Colors::FOVColorB = Features::Colors::FOVColor[2];
      Config::Colors::FOVColorA = Features::Colors::FOVColor[3];
      Config::Colors::FilledFOVColorR = Features::Colors::FilledFOVColor[0];
      Config::Colors::FilledFOVColorG = Features::Colors::FilledFOVColor[1];
      Config::Colors::FilledFOVColorB = Features::Colors::FilledFOVColor[2];
      Config::Colors::FilledFOVColorA = Features::Colors::FilledFOVColor[3];
      Config::Colors::CrosshairColorR = Features::Colors::CrosshairColor[0];
      Config::Colors::CrosshairColorG = Features::Colors::CrosshairColor[1];
      Config::Colors::CrosshairColorB = Features::Colors::CrosshairColor[2];
      Config::Colors::CrosshairColorA = Features::Colors::CrosshairColor[3];

      // Weapon Colors
      Config::TeammateColors::LightWeaponColorR = Features::Colors::Teammate::LightWeaponColor[0];
      Config::TeammateColors::LightWeaponColorG = Features::Colors::Teammate::LightWeaponColor[1];
      Config::TeammateColors::LightWeaponColorB = Features::Colors::Teammate::LightWeaponColor[2];
      Config::TeammateColors::LightWeaponColorA = Features::Colors::Teammate::LightWeaponColor[3];
      Config::TeammateColors::HeavyWeaponColorR = Features::Colors::Teammate::HeavyWeaponColor[0];
      Config::TeammateColors::HeavyWeaponColorG = Features::Colors::Teammate::HeavyWeaponColor[1];
      Config::TeammateColors::HeavyWeaponColorB = Features::Colors::Teammate::HeavyWeaponColor[2];
      Config::TeammateColors::HeavyWeaponColorA = Features::Colors::Teammate::HeavyWeaponColor[3];
      Config::TeammateColors::EnergyWeaponColorR = Features::Colors::Teammate::EnergyWeaponColor[0];
      Config::TeammateColors::EnergyWeaponColorG = Features::Colors::Teammate::EnergyWeaponColor[1];
      Config::TeammateColors::EnergyWeaponColorB = Features::Colors::Teammate::EnergyWeaponColor[2];
      Config::TeammateColors::EnergyWeaponColorA = Features::Colors::Teammate::EnergyWeaponColor[3];
      Config::TeammateColors::ShotgunWeaponColorR = Features::Colors::Teammate::ShotgunWeaponColor[0];
      Config::TeammateColors::ShotgunWeaponColorG = Features::Colors::Teammate::ShotgunWeaponColor[1];
      Config::TeammateColors::ShotgunWeaponColorB = Features::Colors::Teammate::ShotgunWeaponColor[2];
      Config::TeammateColors::ShotgunWeaponColorA = Features::Colors::Teammate::ShotgunWeaponColor[3];
      Config::TeammateColors::SniperWeaponColorR = Features::Colors::Teammate::SniperWeaponColor[0];
      Config::TeammateColors::SniperWeaponColorG = Features::Colors::Teammate::SniperWeaponColor[1];
      Config::TeammateColors::SniperWeaponColorB = Features::Colors::Teammate::SniperWeaponColor[2];
      Config::TeammateColors::SniperWeaponColorA = Features::Colors::Teammate::SniperWeaponColor[3];
      Config::TeammateColors::LegendaryWeaponColorR = Features::Colors::Teammate::LegendaryWeaponColor[0];
      Config::TeammateColors::LegendaryWeaponColorG = Features::Colors::Teammate::LegendaryWeaponColor[1];
      Config::TeammateColors::LegendaryWeaponColorB = Features::Colors::Teammate::LegendaryWeaponColor[2];
      Config::TeammateColors::LegendaryWeaponColorA = Features::Colors::Teammate::LegendaryWeaponColor[3];
      Config::TeammateColors::MeleeWeaponColorR = Features::Colors::Teammate::MeleeWeaponColor[0];
      Config::TeammateColors::MeleeWeaponColorG = Features::Colors::Teammate::MeleeWeaponColor[1];
      Config::TeammateColors::MeleeWeaponColorB = Features::Colors::Teammate::MeleeWeaponColor[2];
      Config::TeammateColors::MeleeWeaponColorA = Features::Colors::Teammate::MeleeWeaponColor[3];
      Config::TeammateColors::ThrowableWeaponColorR = Features::Colors::Teammate::ThrowableWeaponColor[0];
      Config::TeammateColors::ThrowableWeaponColorG = Features::Colors::Teammate::ThrowableWeaponColor[1];
      Config::TeammateColors::ThrowableWeaponColorB = Features::Colors::Teammate::ThrowableWeaponColor[2];
      Config::TeammateColors::ThrowableWeaponColorA = Features::Colors::Teammate::ThrowableWeaponColor[3];

      Config::Colors::SpectatorWarningColorR = Features::Colors::SpectatorWarningColor[0];
      Config::Colors::SpectatorWarningColorG = Features::Colors::SpectatorWarningColor[1];
      Config::Colors::SpectatorWarningColorB = Features::Colors::SpectatorWarningColor[2];
      Config::Colors::SpectatorWarningColorA = Features::Colors::SpectatorWarningColor[3];
      Config::Colors::VisibleWarningColorR = Features::Colors::VisibleWarningColor[0];;
      Config::Colors::VisibleWarningColorG = Features::Colors::VisibleWarningColor[1];
      Config::Colors::VisibleWarningColorB = Features::Colors::VisibleWarningColor[2];
      Config::Colors::VisibleWarningColorA = Features::Colors::VisibleWarningColor[3];

      return true;
    } catch (...) { return false; }
  }

  void RenderWatermark(ImDrawList *Canvas, LocalPlayer *Myself, const Overlay &OverlayWindow) {
    int ScreenWidth;
    int ScreenHeight;
    OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);

    if (Features::Watermark::Enabled) {
      ImGui::SetNextWindowPos(ImVec2(10.0f, 22.0f), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
      ImGui::SetNextWindowBgAlpha(0.75f);

      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10.0f, 8.0f });
      ImGui::PushStyleColor(ImGuiCol_Border, { 1.00f, 0.65f, 0.00f, 1.00f });
      ImGui::Begin("Watermark", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

      if (Features::Watermark::Name) {
        ImGui::TextColored(ImVec4(1, 0.75, 0, 1), "ZAP");

        if (Features::Watermark::Spectators || Features::Watermark::ProcessingSpeed || Features::Watermark::GameFPS) {
          ImGui::SameLine();
          ImGui::TextColored({ 0.5, 0.5, 0.5, 1 }, " | ");
          ImGui::SameLine();
        }
      }

      if (Features::Watermark::Spectators) {
        if (const std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); now >= LastSpectatorUpdateTime + std::chrono::milliseconds(1500)) {
          auto TempTotalSpectators = 0;
          std::vector<std::string> TempSpectators;

          for (const auto p: *Players) {
            printf("Name: %s - PlayerName: %s\n", p->Name.c_str(), p->PlayerName.c_str());
            if (p->IsSpectating()) {
              TempTotalSpectators++;
              TempSpectators.push_back(p->GetPlayerName());
            }
          }

          TotalSpectators = TempTotalSpectators;
          Spectators = TempSpectators;
          LastSpectatorUpdateTime = now;
        }
        ImGui::Text("spectators: ");
        ImGui::SameLine();
        ImGui::TextColored(TotalSpectators > 0 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1), "%d", TotalSpectators);

        if (Features::Watermark::ProcessingSpeed || Features::Watermark::GameFPS) {
          ImGui::SameLine();
          ImGui::TextColored({ 0.5, 0.5, 0.5, 1 }, " | ");
          ImGui::SameLine();
        }
      }

      if (Features::Watermark::ProcessingSpeed) {
        if (const std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); now >= ProcessingLastUpdatae + std::chrono::milliseconds(600)) {
          const double averageProcessingTime = std::accumulate(ProcessingTimes.begin(), ProcessingTimes.end(), 0.0) / static_cast<double>(ProcessingTimes.size());
          ProcessingTime = averageProcessingTime;
          ProcessingLastUpdatae = now;
        }

        if (ProcessingTimes.size() >= 10)
          ProcessingTimes.erase(ProcessingTimes.begin());

        ProcessingTimes.push_back(OverlayWindow.ProcessingTime);

        const ImVec4 ProcessingTimeColor = ProcessingTime > 20 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1);
        ImGui::Text("performance: ");
        ImGui::SameLine();
        ImGui::TextColored(ProcessingTimeColor, "%.2fms", ProcessingTime);

        if (Features::Watermark::GameFPS) {
          ImGui::SameLine();
          ImGui::TextColored({ 0.5, 0.5, 0.5, 1 }, " | ");
          ImGui::SameLine();
        }
      }

      if (Features::Watermark::GameFPS) {
        const auto FrameNumber = Memory::Read<int>(OFF_REGION + OFF_GLOBAL_VARS + 0x0008);;

        if (const std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); now >= FpsUpdate + std::chrono::milliseconds(300)) {
          const int FramesSince = FrameNumber - FpsLastFrame;
          const auto Duration = now - FpsUpdate;
          Fps = static_cast<int>(FramesSince * 1000 / Duration.count());

          FpsLastFrame = FrameNumber;
          FpsUpdate = now;
        }

        const ImVec4 FpsColor = Fps < 60 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1);
        ImGui::Text("fps: ");
        ImGui::SameLine();
        ImGui::TextColored(FpsColor, "%i", Fps);
      }

      ImGui::PopStyleVar();
      ImGui::PopStyleColor();
      ImGui::End();
    }
  }

  void RenderDrawings(ImDrawList *Canvas, Legitbot *AimAssistState, LocalPlayer *Myself, Overlay OverlayWindow) {
    int ScreenWidth;
    int ScreenHeight;
    OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);

    if (Features::Sense::ShowSpectators) {
      ImVec2 Center = ImGui::GetMainViewport()->GetCenter();
      ImGui::SetNextWindowPos(ImVec2(0.0f, Center.y), ImGuiCond_Once, ImVec2(0.02f, 0.5f));
      ImGui::SetNextWindowBgAlpha(0.3f);
      ImGui::Begin("Spectators", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

      if (auto Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); Now >= LastSpectatorUpdateTime + std::chrono::milliseconds(1500)) {
        auto TempTotalSpectators = 0;
        std::vector<std::string> TempSpectators;
        for (auto p: *Players) {
          if (p->IsSpectating()) {
            TempTotalSpectators++;
            TempSpectators.push_back(p->GetPlayerName());
          }
        }

        TotalSpectators = TempTotalSpectators;
        Spectators = TempSpectators;
        LastSpectatorUpdateTime = Now;
      }

      ImGui::Text("Spectators: ");
      ImGui::SameLine();
      ImGui::TextColored(TotalSpectators > 0 ? ImVec4(1, 0.343, 0.475, 1) : ImVec4(0.4, 1, 0.343, 1), "%d", TotalSpectators);
      if (static_cast<int>(Spectators.size()) > 0) {
        ImGui::Separator();
        for (const auto &Spectator: Spectators) { ImGui::TextColored(ImVec4(1, 0.343, 0.475, 1), "> %s", Spectator.c_str()); }
      }
      ImGui::End();
    }

    // Draw Crosshair
    if (Features::Sense::DrawCrosshair) {
      auto x = static_cast<float>(ScreenWidth) * 0.5f;
      auto y = static_cast<float>(ScreenHeight) * 0.5f;
      Renderer::DrawLine(Canvas, Vector2D(x - Features::Sense::CrosshairSize, y), Vector2D(x + Features::Sense::CrosshairSize, y), Features::Sense::CrosshairThickness, ImColor(Features::Colors::CrosshairColor[0], Features::Colors::CrosshairColor[1], Features::Colors::CrosshairColor[2], Features::Colors::CrosshairColor[3])); // Left - right
      Renderer::DrawLine(Canvas, Vector2D(x, y - Features::Sense::CrosshairSize), Vector2D(x, y + Features::Sense::CrosshairSize), Features::Sense::CrosshairThickness, ImColor(Features::Colors::CrosshairColor[0], Features::Colors::CrosshairColor[1], Features::Colors::CrosshairColor[2], Features::Colors::CrosshairColor[3])); // Top - bottom
    }

    // Draw lot of things
    if (Features::Settings::ESPEnabled) {
      ImGui::PushFont(OverlayWindow.SenseFont);
      if (Features::Sense::DrawSpectatorWarning && TotalSpectators >= 1) {
        std::stringstream WarningTextStart, Space1, Amount, Space2;
        WarningTextStart << "SPECTATOR WARNING";
        Space1 << " [";
        Amount << TotalSpectators;
        Space2 << "]";
        std::string combined = WarningTextStart.str() + Space1.str() + Amount.str() + Space2.str();
        const char *CombinedText = combined.c_str();

        auto TextPos = Vector2D(static_cast<float>(Features::Sense::WarningTextX), static_cast<float>(Features::Sense::WarningTextY) - 12);
        Renderer::DrawText(Canvas, TextPos, CombinedText, ImColor(Features::Colors::SpectatorWarningColor[0], Features::Colors::SpectatorWarningColor[1], Features::Colors::SpectatorWarningColor[2], Features::Colors::SpectatorWarningColor[3]), Features::Sense::WarningTextOutline ? true : false, true, false);
      }

      for (auto p: *Players) {
        if (p->IsLocal)
          continue;

        if (!p->IsCombatReady())
          continue;

        if (p->DistanceToLocalPlayer > Conversion::ToGameUnits(Features::Sense::ESPMaxDistance))
          continue;

        if (Features::Sense::VisibilityCheck && !p->IsVisible)
          continue;

        if (!Features::Sense::Teammate::DrawTeam && p->IsAlly)
          continue;

        auto LocalOrigin3D = p->LocalOrigin;
        auto Head3D = p->GetBonePosition(HitboxType::Head);
        auto AboveHead3D = Head3D;
        AboveHead3D.z += 10.f; // Y Offset

        Vector2D LocalOriginW2S, HeadW2S, AboveHeadW2S;
        bool LocalOriginW2SValid = GameCamera->WorldToScreen(LocalOrigin3D, LocalOriginW2S);
        bool HeadW2SValid = GameCamera->WorldToScreen(Head3D, HeadW2S);
        GameCamera->WorldToScreen(AboveHead3D, AboveHeadW2S);

        auto getColor = [p](const float *VisibleColor_ALLY, const float *InvisibleColor_ALLY, const float *VisibleColor_ENEMY, const float *InvisibleColor_ENEMY) {
          const float *ChosenColor_ALLY = p->IsVisible ? VisibleColor_ALLY : InvisibleColor_ALLY;
          const float *ChosenColor_ENEMY = p->IsVisible ? VisibleColor_ENEMY : InvisibleColor_ENEMY;
          const float *ChosenColor = p->IsAlly ? ChosenColor_ALLY : ChosenColor_ENEMY;
          return ImVec4(ChosenColor[0], ChosenColor[1], ChosenColor[2], ChosenColor[3]);
        };

        auto BoxColor = getColor(Features::Colors::Teammate::VisibleBoxColor, Features::Colors::Teammate::InvisibleBoxColor, Features::Colors::Enemy::VisibleBoxColor, Features::Colors::Enemy::InvisibleBoxColor);
        auto FilledBoxColor = getColor(Features::Colors::Teammate::VisibleFilledBoxColor, Features::Colors::Teammate::InvisibleFilledBoxColor, Features::Colors::Enemy::VisibleFilledBoxColor, Features::Colors::Enemy::InvisibleFilledBoxColor);
        auto TracerColor = getColor(Features::Colors::Teammate::VisibleTracerColor, Features::Colors::Teammate::InvisibleTracerColor, Features::Colors::Enemy::VisibleTracerColor, Features::Colors::Enemy::InvisibleTracerColor);
        auto SkeletonColor = getColor(Features::Colors::Teammate::VisibleSkeletonColor, Features::Colors::Teammate::InvisibleSkeletonColor, Features::Colors::Enemy::VisibleSkeletonColor, Features::Colors::Enemy::InvisibleSkeletonColor);
        auto HeadCircleColor = getColor(Features::Colors::Teammate::VisibleHeadCircleColor, Features::Colors::Teammate::InvisibleHeadCircleColor, Features::Colors::Enemy::VisibleHeadCircleColor, Features::Colors::Enemy::InvisibleHeadCircleColor);
        auto NameColor = getColor(Features::Colors::Teammate::VisibleNameColor, Features::Colors::Teammate::InvisibleNameColor, Features::Colors::Enemy::VisibleNameColor, Features::Colors::Enemy::InvisibleNameColor);
        auto DistanceColor = getColor(Features::Colors::Teammate::VisibleLegendColor, Features::Colors::Teammate::InvisibleLegendColor, Features::Colors::Enemy::VisibleDistanceColor, Features::Colors::Enemy::InvisibleDistanceColor);
        auto LegendColor = getColor(Features::Colors::Teammate::VisibleWeaponColor, Features::Colors::Teammate::InvisibleWeaponColor, Features::Colors::Enemy::VisibleLegendColor, Features::Colors::Enemy::InvisibleLegendColor);
        auto WeaponColor = getColor(Features::Colors::Enemy::VisibleWeaponColor, Features::Colors::Enemy::InvisibleWeaponColor, Features::Colors::Enemy::VisibleWeaponColor, Features::Colors::Enemy::InvisibleWeaponColor);

        auto calculatePosition = [](const int PositionIndex, const Vector2D &AboveHeadPosition, const Vector2D &LocalOriginPosition) {
          switch (PositionIndex) {
            case 0: // Top 1
              return AboveHeadPosition.Subtract({ 0, 15 });
            case 1: // Top 2
              return AboveHeadPosition.Subtract({ 0, 30 });
            case 2: // Bottom 1
              return LocalOriginPosition;
            case 3: // Bottom 2
              return LocalOriginPosition.Add({ 0, 10 });
            case 4: // Bottom 3
              return LocalOriginPosition.Add({ 0, 20 });
            default:
              return Vector2D();
          }
        };

        Vector2D NamePosition = calculatePosition(Features::Sense::Positions::NamePosition, AboveHeadW2S, LocalOriginW2S);
        Vector2D DistancePosition = calculatePosition(Features::Sense::Positions::DistancePosition, AboveHeadW2S, LocalOriginW2S);
        Vector2D LegendPosition = calculatePosition(Features::Sense::Positions::LegendPosition, AboveHeadW2S, LocalOriginW2S);
        Vector2D WeaponPosition = calculatePosition(Features::Sense::Positions::WeaponPosition, AboveHeadW2S, LocalOriginW2S);
        Vector2D StatusPosition = calculatePosition(Features::Sense::Positions::StatusPosition, AboveHeadW2S, LocalOriginW2S);

        bool DrawTracers = p->IsAlly ? Features::Sense::Teammate::DrawTracers : Features::Sense::Enemy::DrawTracers;
        bool DrawStatus = p->IsAlly ? Features::Sense::Teammate::DrawStatus : Features::Sense::Enemy::DrawStatus;
        bool DrawBars = p->IsAlly ? Features::Sense::Teammate::DrawBars : Features::Sense::Enemy::DrawBars;
        bool DrawDistance = p->IsAlly ? Features::Sense::Teammate::DrawDistance : Features::Sense::Enemy::DrawDistance;
        bool DrawNames = p->IsAlly ? Features::Sense::Teammate::DrawNames : Features::Sense::Enemy::DrawNames;
        bool DrawLegend = p->IsAlly ? Features::Sense::Teammate::DrawLegend : Features::Sense::Enemy::DrawLegend;
        bool DrawWeapon = p->IsAlly ? Features::Sense::Teammate::DrawWeapon : Features::Sense::Enemy::DrawWeapon;
        bool DrawBoxes = p->IsAlly ? Features::Sense::Teammate::DrawBoxes : Features::Sense::Enemy::DrawBoxes;
        bool DrawSkeleton = p->IsAlly ? Features::Sense::Teammate::DrawSkeleton : Features::Sense::Enemy::DrawSkeleton;
        bool DrawHeadCircle = p->IsAlly ? Features::Sense::Teammate::DrawHeadCircle : Features::Sense::Enemy::DrawHeadCircle;

        if (DrawTracers) {
          Vector2D ChestScreenPosition;
          auto TracerBone = p->IsAlly ? Features::Sense::Teammate::TracerBone : Features::Sense::Enemy::TracerBone;
          auto TracerPosition = p->IsAlly ? Features::Sense::Teammate::TracerPosition : Features::Sense::Enemy::TracerPosition;
          auto TracerThickness = p->IsAlly ? Features::Sense::Teammate::TracerThickness : Features::Sense::Enemy::TracerThickness;
          GameCamera->WorldToScreen(p->LocalOrigin.Add(Vector3D(0, 0, TracerBone == 0 ? 66 : 0)), ChestScreenPosition);

          auto Position = Vector2D(static_cast<float>(ScreenWidth) * 0.5f, TracerPosition == 0 ? 0 : TracerPosition == 1 ? static_cast<float>(ScreenHeight) / 2 : static_cast<float>(ScreenHeight));

          if (!ChestScreenPosition.IsZeroVector())
            Renderer::DrawLine(Canvas, Position, ChestScreenPosition, TracerThickness, ImColor(TracerColor));
        }

        if (!LocalOriginW2SValid)
          continue;

        if (DrawStatus) {
          std::stringstream healthValue, shieldValue, maxHealthValue, maxShieldValue;
          healthValue << p->Health;
          shieldValue << p->Shield;
          maxHealthValue << p->MaxHealth;
          maxShieldValue << p->MaxShield;
          std::string healthInt = healthValue.str() + " HP";
          std::string shieldInt = shieldValue.str() + " AP";
          const char *healthText = const_cast<char *>(healthInt.c_str());
          const char *shieldText = const_cast<char *>(shieldInt.c_str());
          std::string combinedHealth = healthValue.str() + " / " + maxHealthValue.str() + " HP";
          const char *combinedHealthText = combinedHealth.c_str();
          std::string combinedShield = shieldValue.str() + " / " + maxShieldValue.str() + " AP";
          const char *combinedShieldText = combinedShield.c_str();

          ImColor ShieldColor;
          switch (p->MaxShield) {
            case 75:
              ShieldColor = ImColor(39, 178, 255); // Blue
              break;
            case 100:
              ShieldColor = ImColor(206, 59, 255); // Purple
              break;
            case 125:
              ShieldColor = ImColor(219, 2, 2); // Red
              break;
            default:
              ShieldColor = ImColor(247, 247, 247); // White
              break;
          }

          auto ShowMaxStatusValues = p->IsAlly ? Features::Sense::Teammate::ShowMaxStatusValues : Features::Sense::Enemy::ShowMaxStatusValues;
          Renderer::DrawText(Canvas, StatusPosition, ShowMaxStatusValues ? combinedHealthText : healthText, ImColor(0, 255, 0), Features::Sense::TextOutline, true, false);
          Renderer::DrawText(Canvas, StatusPosition.Add(Vector2D(0, 0 + 10)), ShowMaxStatusValues ? combinedShieldText : shieldText, ShieldColor, Features::Sense::TextOutline, true, false);
        }

        if (!HeadW2SValid)
          continue;

        if (DrawBars) {
          int health = p->Health;
          int maxHealth = p->MaxHealth;
          int shield = p->Shield;
          int maxShield = p->MaxShield;

          auto BarMode = p->IsAlly ? Features::Sense::Teammate::BarMode : Features::Sense::Enemy::BarMode;
          auto BarStyle = p->IsAlly ? Features::Sense::Teammate::BarStyle : Features::Sense::Enemy::BarStyle;
          auto BarColorMode = p->IsAlly ? Features::Sense::Teammate::BarColorMode : Features::Sense::Enemy::BarColorMode;
          auto BarThickness = p->IsAlly ? Features::Sense::Teammate::BarThickness : Features::Sense::Enemy::BarThickness;
          auto BarThickness2 = p->IsAlly ? Features::Sense::Teammate::BarThickness2 : Features::Sense::Enemy::BarThickness2;
          auto BarWidth = p->IsAlly ? Features::Sense::Teammate::BarWidth : Features::Sense::Enemy::BarWidth;
          auto BarHeight = p->IsAlly ? Features::Sense::Teammate::BarHeight : Features::Sense::Enemy::BarHeight;

          Renderer::Draw2DBar(Canvas, BarMode, BarStyle, BarColorMode, LocalOriginW2S, HeadW2S, AboveHeadW2S, health, maxHealth, shield, maxShield, BarThickness, BarThickness2, BarWidth, BarHeight);
        }

        if (DrawDistance && !DrawNames) {
          std::string DistanceStr = std::to_string(static_cast<int>(Conversion::ToMeters(p->DistanceToLocalPlayer)));
          std::string Buffer = "[" + DistanceStr + " M]";

          if (!LocalOriginW2S.IsZeroVector())
            Renderer::DrawText(Canvas, DistancePosition, Buffer.c_str(), ImColor(DistanceColor), Features::Sense::TextOutline, true, false);
        }

        if (!DrawDistance && DrawNames)
          Renderer::DrawText(Canvas, AboveHeadW2S.Subtract(Vector2D(0, 16)), p->GetPlayerName().c_str(), ImColor(NameColor), Features::Sense::TextOutline, true, false);

        if (DrawDistance && DrawNames) {
          std::ostringstream TextStream;
          TextStream << p->GetPlayerName() << " [" << static_cast<int>(Conversion::ToMeters(p->DistanceToLocalPlayer)) << " M]";
          std::string Combined = TextStream.str();

          Renderer::DrawText(Canvas, NamePosition, Combined.c_str(), ImColor(NameColor), Features::Sense::TextOutline, true, false);
        }

        if (DrawLegend)
          Renderer::DrawText(Canvas, LegendPosition, p->GetPlayerModelName().c_str(), ImColor(LegendColor), Features::Sense::TextOutline, true, false);

        if (DrawWeapon)
          Renderer::DrawText(Canvas, WeaponPosition, p->GetWeaponHeldName().c_str(), Features::Colors::WeaponColorMode == 1 ? p->GetWeaponHeldColor() : ImColor(WeaponColor), Features::Sense::TextOutline, true, false);

        if (DrawBoxes) {
          auto BoxType = p->IsAlly ? Features::Sense::Teammate::BoxType : Features::Sense::Enemy::BoxType;
          auto BoxStyle = p->IsAlly ? Features::Sense::Teammate::BoxStyle : Features::Sense::Enemy::BoxStyle;
          auto BoxThickness = p->IsAlly ? Features::Sense::Teammate::BoxThickness : Features::Sense::Enemy::BoxThickness;
          Renderer::Draw2DBox(Canvas, BoxType, BoxStyle, LocalOriginW2S, HeadW2S, ImColor(BoxColor), ImColor(FilledBoxColor), BoxThickness);
        }

        if (DrawSkeleton) {
          Vector2D Neck, UpperChest, LowerChest, Stomach, Leftshoulder, Leftelbow, LeftHand, Rightshoulder, RightelbowBone, RightHand, LeftThighs, Leftknees, Leftleg, RightThighs, Rightknees, Rightleg;

          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Neck), Neck);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::UpperChest), UpperChest);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LowerChest), LowerChest);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Stomach), Stomach);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftshoulder), Leftshoulder);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftelbow), Leftelbow);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftHand), LeftHand);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightshoulder), Rightshoulder);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightelbowBone), RightelbowBone);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightHand), RightHand);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::LeftThighs), LeftThighs);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftknees), Leftknees);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Leftleg), Leftleg);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::RightThighs), RightThighs);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightknees), Rightknees);
          GameCamera->WorldToScreen(p->GetBonePosition(HitboxType::Rightleg), Rightleg);

          auto SkeletonThickness = p->IsAlly ? Features::Sense::Teammate::SkeletonThickness : Features::Sense::Enemy::SkeletonThickness;
          Renderer::DrawLine(Canvas, HeadW2S, Neck, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Neck, UpperChest, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, UpperChest, LowerChest, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, LowerChest, Stomach, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Neck, Leftshoulder, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Leftshoulder, Leftelbow, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Leftelbow, LeftHand, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Neck, Rightshoulder, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Rightshoulder, RightelbowBone, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, RightelbowBone, RightHand, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Stomach, LeftThighs, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, LeftThighs, Leftknees, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Leftknees, Leftleg, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Stomach, RightThighs, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, RightThighs, Rightknees, SkeletonThickness, SkeletonColor);
          Renderer::DrawLine(Canvas, Rightknees, Rightleg, SkeletonThickness, SkeletonColor);
        }

        if (DrawHeadCircle) {
          Vector2D HeadPos2D;
          Vector3D HeadPos3D = p->GetBonePosition(HitboxType::Head);
          HeadPos3D.z += 3.f;

          GameCamera->WorldToScreen(HeadPos3D, HeadPos2D);
          Renderer::DrawCircle(Canvas, HeadPos2D, 3650 / p->DistanceToLocalPlayer, 255, ImColor(HeadCircleColor), p->IsAlly ? Features::Sense::Teammate::HeadCircleThickness : Features::Sense::Enemy::HeadCircleThickness);
        }
      }

      ImGui::PopFont();
    }
  }
};
