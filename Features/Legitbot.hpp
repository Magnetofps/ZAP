// ReSharper disable CppDFAUnreachableCode CppDFAConstantConditions
#pragma once
#include <random>
#include <vector>

#include "../Core/Level.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/Player.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/Resolver.hpp"
#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputManager.hpp"
#include "../Utils/Memory.hpp"
#include "../Utils/Weapons.hpp"
#include "../Utils/XDisplay.hpp"

// Conversion
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

struct Legitbot {
  XDisplay *X11Display;
  LocalPlayer *Myself;
  std::vector<Player *> *Players;
  Level *Map;

  Player *CurrentTarget = nullptr;
  bool TargetSelected = true;
  QAngle RCSLastPunch;
  std::chrono::milliseconds LastAimTime;

  Legitbot(XDisplay *X11Display, Level *Map, LocalPlayer *Myself, std::vector<Player *> *GamePlayers): LastAimTime() {
    this->X11Display = X11Display;
    this->Myself = Myself;
    this->Players = GamePlayers;
    this->Map = Map;
  }

  static bool Save() {
    try {
      Config::Aimbot::AimbotEnabled = Features::Aimbot::AimbotEnabled;
      Config::Aimbot::BindMethod = Features::Aimbot::BindMethod;
      Config::Aimbot::InputMethod = Features::Aimbot::InputMethod;
      Config::Aimbot::ClosestHitbox = Features::Aimbot::ClosestHitbox;
      Config::Aimbot::OnFire = Features::Aimbot::OnFire;
      Config::Aimbot::OnADS = Features::Aimbot::OnADS;
      Config::Aimbot::VisCheck = Features::Aimbot::VisCheck;
      Config::Aimbot::TeamCheck = Features::Aimbot::TeamCheck;
      Config::Aimbot::TargetSwitching = Features::Aimbot::TargetSwitching;
      Config::Aimbot::Priority = Features::Aimbot::Priority;
      Config::Aimbot::PredictMovement = Features::Aimbot::PredictMovement;
      Config::Aimbot::PredictBulletDrop = Features::Aimbot::PredictBulletDrop;
      Config::Aimbot::FinalDistance = Features::Aimbot::FinalDistance;
      Config::Aimbot::Smooth = Features::Aimbot::Smooth;
      Config::Aimbot::Speed = Features::Aimbot::Speed;
      Config::Aimbot::SmoothingMethod = Features::Aimbot::SmoothingMethod;
      Config::Aimbot::HipfireSmooth = Features::Aimbot::HipfireSmooth;
      Config::Aimbot::ADSSmooth = Features::Aimbot::ADSSmooth;
      Config::Aimbot::MinHipfireSmooth = Features::Aimbot::MinHipfireSmooth;
      Config::Aimbot::MaxHipfireSmooth = Features::Aimbot::MaxHipfireSmooth;
      Config::Aimbot::MinADSSmooth = Features::Aimbot::MinADSSmooth;
      Config::Aimbot::MaxADSSmooth = Features::Aimbot::MaxADSSmooth;
      // Aimbot 3 Testing
      Config::Aimbot::MouseHipfireSmoothing = Features::Aimbot::MouseHipfireSmoothing;
      Config::Aimbot::MouseADSSmoothing = Features::Aimbot::MouseADSSmoothing;
      Config::Aimbot::MouseExtraSmoothing = Features::Aimbot::MouseExtraSmoothing;
      Config::Aimbot::MinMouseHipfireSmoothing = Features::Aimbot::MinMouseHipfireSmoothing;
      Config::Aimbot::MaxMouseHipfireSmoothing = Features::Aimbot::MaxMouseHipfireSmoothing;
      Config::Aimbot::MinMouseADSSmoothing = Features::Aimbot::MinMouseADSSmoothing;
      Config::Aimbot::MaxMouseADSSmoothing = Features::Aimbot::MaxMouseADSSmoothing;

      Config::Aimbot::Delay = Features::Aimbot::Delay;
      Config::Aimbot::FOV = Features::Aimbot::FOV;
      Config::Aimbot::ZoomScale = Features::Aimbot::ZoomScale;
      Config::Aimbot::MinDistance = Features::Aimbot::MinDistance;
      Config::Aimbot::MaxDistance = Features::Aimbot::MaxDistance;
      Config::Aimbot::HipfireDistance = Features::Aimbot::HipfireDistance;
      Config::Aimbot::ZoomDistance = Features::Aimbot::ZoomDistance;
      // AimMode 2
      Config::Aimbot::HipfireSmooth1 = Features::Aimbot::HipfireSmooth1;
      Config::Aimbot::ADSSmooth1 = Features::Aimbot::ADSSmooth1;
      Config::Aimbot::ExtraSmoothing = Features::Aimbot::ExtraSmoothing;
      Config::Aimbot::Deadzone = Features::Aimbot::Deadzone;
      Config::Aimbot::FOV1 = Features::Aimbot::FOV1;
      // Weapon Toggles
      // Light
      Config::Aimbot::P2020 = Features::Aimbot::P2020;
      Config::Aimbot::RE45 = Features::Aimbot::RE45;
      Config::Aimbot::Alternator = Features::Aimbot::Alternator;
      Config::Aimbot::R99 = Features::Aimbot::R99;
      Config::Aimbot::R301 = Features::Aimbot::R301;
      Config::Aimbot::Spitfire = Features::Aimbot::Spitfire;
      Config::Aimbot::G7 = Features::Aimbot::G7;
      // Heavy
      Config::Aimbot::Flatline = Features::Aimbot::Flatline;
      Config::Aimbot::Hemlock = Features::Aimbot::Hemlock;
      Config::Aimbot::Repeater = Features::Aimbot::Repeater;
      Config::Aimbot::Rampage = Features::Aimbot::Rampage;
      Config::Aimbot::CARSMG = Features::Aimbot::CARSMG;
      // Energy
      Config::Aimbot::Havoc = Features::Aimbot::Havoc;
      Config::Aimbot::Devotion = Features::Aimbot::Devotion;
      Config::Aimbot::LSTAR = Features::Aimbot::LSTAR;
      Config::Aimbot::TripleTake = Features::Aimbot::TripleTake;
      Config::Aimbot::Volt = Features::Aimbot::Volt;
      Config::Aimbot::Nemesis = Features::Aimbot::Nemesis;
      // Shotgun
      Config::Aimbot::Mozambique = Features::Aimbot::Mozambique;
      Config::Aimbot::EVA8 = Features::Aimbot::EVA8;
      Config::Aimbot::Peacekeeper = Features::Aimbot::Peacekeeper;
      Config::Aimbot::Mastiff = Features::Aimbot::Mastiff;
      // Snipers
      Config::Aimbot::Longbow = Features::Aimbot::Longbow;
      Config::Aimbot::ChargeRifle = Features::Aimbot::ChargeRifle;
      Config::Aimbot::Sentinel = Features::Aimbot::Sentinel;
      // Legendary
      Config::Aimbot::Wingman = Features::Aimbot::Wingman;
      Config::Aimbot::Prowler = Features::Aimbot::Prowler;
      Config::Aimbot::Bocek = Features::Aimbot::Bocek;
      Config::Aimbot::Kraber = Features::Aimbot::Kraber;
      Config::Aimbot::Knife = Features::Aimbot::Knife;

      Config::AimbotBinds::AimBind = static_cast<int>(Features::AimbotBinds::AimBind);
      Config::AimbotBinds::ExtraBind = static_cast<int>(Features::AimbotBinds::ExtraBind);

      Config::AimbotHitboxes::Hitbox = static_cast<int>(Features::AimbotHitboxes::Hitbox);

      Config::RCS::RCSEnabled = Features::RCS::RCSEnabled;
      Config::RCS::RCSMode = Features::RCS::RCSMode;
      Config::RCS::OnADS = Features::RCS::OnADS;
      Config::RCS::PitchPower = Features::RCS::PitchPower;
      Config::RCS::YawPower = Features::RCS::YawPower;
      Config::RCS::PitchReduction = Features::RCS::PitchReduction;
      Config::RCS::YawReduction = Features::RCS::YawReduction;
      // Weapon Toggles
      // Light
      Config::RCS::P2020 = Features::RCS::P2020;
      Config::RCS::RE45 = Features::RCS::RE45;
      Config::RCS::Alternator = Features::RCS::Alternator;
      Config::RCS::R99 = Features::RCS::R99;
      Config::RCS::R301 = Features::RCS::R301;
      Config::RCS::Spitfire = Features::RCS::Spitfire;
      Config::RCS::G7 = Features::RCS::G7;
      // Heavy
      Config::RCS::Flatline = Features::RCS::Flatline;
      Config::RCS::Hemlock = Features::RCS::Hemlock;
      Config::RCS::Repeater = Features::RCS::Repeater;
      Config::RCS::Rampage = Features::RCS::Rampage;
      Config::RCS::CARSMG = Features::RCS::CARSMG;
      // Energy
      Config::RCS::Havoc = Features::RCS::Havoc;
      Config::RCS::Devotion = Features::RCS::Devotion;
      Config::RCS::LSTAR = Features::RCS::LSTAR;
      Config::RCS::TripleTake = Features::RCS::TripleTake;
      Config::RCS::Volt = Features::RCS::Volt;
      Config::RCS::Nemesis = Features::RCS::Nemesis;
      // Shotgun
      Config::RCS::Mozambique = Features::RCS::Mozambique;
      Config::RCS::EVA8 = Features::RCS::EVA8;
      Config::RCS::Peacekeeper = Features::RCS::Peacekeeper;
      Config::RCS::Mastiff = Features::RCS::Mastiff;
      // Snipers
      Config::RCS::Longbow = Features::RCS::Longbow;
      Config::RCS::ChargeRifle = Features::RCS::ChargeRifle;
      Config::RCS::Sentinel = Features::RCS::Sentinel;
      // Legendary
      Config::RCS::Wingman = Features::RCS::Wingman;
      Config::RCS::Prowler = Features::RCS::Prowler;
      Config::RCS::Kraber = Features::RCS::Kraber;
      // Advanced
      Config::RCS::AdvancedRCS = Features::RCS::AdvancedRCS;
      Config::RCS::AdvancedPitchPower = Features::RCS::AdvancedPitchPower;
      Config::RCS::AdvancedYawPower = Features::RCS::AdvancedYawPower;
      Config::RCS::AdvancedPitchReduction = Features::RCS::AdvancedPitchReduction;
      Config::RCS::AdvancedYawReduction = Features::RCS::AdvancedYawReduction;
      Config::RCS::P2020Pitch = Features::RCS::P2020Pitch;
      Config::RCS::P2020Yaw = Features::RCS::P2020Yaw;
      Config::RCS::P2020PitchReduction = Features::RCS::P2020PitchReduction;
      Config::RCS::P2020YawReduction = Features::RCS::P2020YawReduction;
      Config::RCS::RE45Pitch = Features::RCS::RE45Pitch;
      Config::RCS::RE45Yaw = Features::RCS::RE45Yaw;
      Config::RCS::RE45PitchReduction = Features::RCS::RE45PitchReduction;
      Config::RCS::RE45YawReduction = Features::RCS::RE45YawReduction;
      Config::RCS::AlternatorPitch = Features::RCS::AlternatorPitch;
      Config::RCS::AlternatorYaw = Features::RCS::AlternatorYaw;
      Config::RCS::AlternatorPitchReduction = Features::RCS::AlternatorPitchReduction;
      Config::RCS::AlternatorYawReduction = Features::RCS::AlternatorYawReduction;
      Config::RCS::R99Pitch = Features::RCS::R99Pitch;
      Config::RCS::R99Yaw = Features::RCS::R99Yaw;
      Config::RCS::R99PitchReduction = Features::RCS::R99PitchReduction;
      Config::RCS::R99YawReduction = Features::RCS::R99YawReduction;
      Config::RCS::R301Pitch = Features::RCS::R301Pitch;
      Config::RCS::R301Yaw = Features::RCS::R301Yaw;
      Config::RCS::R301PitchReduction = Features::RCS::R301PitchReduction;
      Config::RCS::R301YawReduction = Features::RCS::R301YawReduction;
      Config::RCS::SpitfirePitch = Features::RCS::SpitfirePitch;
      Config::RCS::SpitfireYaw = Features::RCS::SpitfireYaw;
      Config::RCS::SpitfirePitchReduction = Features::RCS::SpitfirePitchReduction;
      Config::RCS::SpitfireYawReduction = Features::RCS::SpitfireYawReduction;
      Config::RCS::G7Pitch = Features::RCS::G7Pitch;
      Config::RCS::G7Yaw = Features::RCS::G7Yaw;
      Config::RCS::G7PitchReduction = Features::RCS::G7PitchReduction;
      Config::RCS::G7YawReduction = Features::RCS::G7YawReduction;
      Config::RCS::FlatlinePitch = Features::RCS::FlatlinePitch;
      Config::RCS::FlatlineYaw = Features::RCS::FlatlineYaw;
      Config::RCS::FlatlinePitchReduction = Features::RCS::FlatlinePitchReduction;
      Config::RCS::FlatlineYawReduction = Features::RCS::FlatlineYawReduction;
      Config::RCS::HemlockPitch = Features::RCS::HemlockPitch;
      Config::RCS::HemlockYaw = Features::RCS::HemlockYaw;
      Config::RCS::HemlockPitchReduction = Features::RCS::HemlockPitchReduction;
      Config::RCS::HemlockYawReduction = Features::RCS::HemlockYawReduction;
      Config::RCS::ProwlerPitch = Features::RCS::ProwlerPitch;
      Config::RCS::ProwlerYaw = Features::RCS::ProwlerYaw;
      Config::RCS::ProwlerPitchReduction = Features::RCS::ProwlerPitchReduction;
      Config::RCS::ProwlerYawReduction = Features::RCS::ProwlerYawReduction;
      Config::RCS::RepeaterPitch = Features::RCS::RepeaterPitch;
      Config::RCS::RepeaterYaw = Features::RCS::RepeaterYaw;
      Config::RCS::RepeaterPitchReduction = Features::RCS::RepeaterPitchReduction;
      Config::RCS::RepeaterYawReduction = Features::RCS::RepeaterYawReduction;
      Config::RCS::RampagePitch = Features::RCS::RampagePitch;
      Config::RCS::RampageYaw = Features::RCS::RampageYaw;
      Config::RCS::RampagePitchReduction = Features::RCS::RampagePitchReduction;
      Config::RCS::RampageYawReduction = Features::RCS::RampageYawReduction;
      Config::RCS::CARSMGPitch = Features::RCS::CARSMGPitch;
      Config::RCS::CARSMGYaw = Features::RCS::CARSMGYaw;
      Config::RCS::CARSMGPitchReduction = Features::RCS::CARSMGPitchReduction;
      Config::RCS::CARSMGYawReduction = Features::RCS::CARSMGYawReduction;
      Config::RCS::HavocPitch = Features::RCS::HavocPitch;
      Config::RCS::HavocYaw = Features::RCS::HavocYaw;
      Config::RCS::HavocPitchReduction = Features::RCS::HavocPitchReduction;
      Config::RCS::HavocYawReduction = Features::RCS::HavocYawReduction;
      Config::RCS::DevotionPitch = Features::RCS::DevotionPitch;
      Config::RCS::DevotionYaw = Features::RCS::DevotionYaw;
      Config::RCS::DevotionPitchReduction = Features::RCS::DevotionPitchReduction;
      Config::RCS::DevotionYawReduction = Features::RCS::DevotionYawReduction;
      Config::RCS::LSTARPitch = Features::RCS::LSTARPitch;
      Config::RCS::LSTARYaw = Features::RCS::LSTARYaw;
      Config::RCS::LSTARPitchReduction = Features::RCS::LSTARPitchReduction;
      Config::RCS::LSTARYawReduction = Features::RCS::LSTARYawReduction;
      Config::RCS::TripleTakePitch = Features::RCS::TripleTakePitch;
      Config::RCS::TripleTakeYaw = Features::RCS::TripleTakeYaw;
      Config::RCS::TripleTakePitchReduction = Features::RCS::TripleTakePitchReduction;
      Config::RCS::TripleTakeYawReduction = Features::RCS::TripleTakeYawReduction;
      Config::RCS::VoltPitch = Features::RCS::VoltPitch;
      Config::RCS::VoltYaw = Features::RCS::VoltYaw;
      Config::RCS::VoltPitchReduction = Features::RCS::VoltPitchReduction;
      Config::RCS::VoltYawReduction = Features::RCS::VoltYawReduction;
      Config::RCS::NemesisPitch = Features::RCS::NemesisPitch;
      Config::RCS::NemesisYaw = Features::RCS::NemesisYaw;
      Config::RCS::NemesisPitchReduction = Features::RCS::NemesisPitchReduction;
      Config::RCS::NemesisYawReduction = Features::RCS::NemesisYawReduction;
      Config::RCS::MozambiquePitch = Features::RCS::MozambiquePitch;
      Config::RCS::MozambiqueYaw = Features::RCS::MozambiqueYaw;
      Config::RCS::MozambiquePitchReduction = Features::RCS::MozambiquePitchReduction;
      Config::RCS::MozambiqueYawReduction = Features::RCS::MozambiqueYawReduction;
      Config::RCS::PeacekeeperPitch = Features::RCS::PeacekeeperPitch;
      Config::RCS::PeacekeeperYaw = Features::RCS::PeacekeeperYaw;
      Config::RCS::PeacekeeperPitchReduction = Features::RCS::PeacekeeperPitchReduction;
      Config::RCS::PeacekeeperYawReduction = Features::RCS::PeacekeeperYawReduction;
      Config::RCS::MastiffPitch = Features::RCS::MastiffPitch;
      Config::RCS::MastiffYaw = Features::RCS::MastiffYaw;
      Config::RCS::MastiffPitchReduction = Features::RCS::MastiffPitchReduction;
      Config::RCS::MastiffYawReduction = Features::RCS::MastiffYawReduction;
      Config::RCS::LongbowPitch = Features::RCS::LongbowPitch;
      Config::RCS::LongbowYaw = Features::RCS::LongbowYaw;
      Config::RCS::LongbowPitchReduction = Features::RCS::LongbowPitchReduction;
      Config::RCS::LongbowYawReduction = Features::RCS::LongbowYawReduction;
      Config::RCS::ChargeRiflePitch = Features::RCS::ChargeRiflePitch;
      Config::RCS::ChargeRifleYaw = Features::RCS::ChargeRifleYaw;
      Config::RCS::ChargeRiflePitchReduction = Features::RCS::ChargeRiflePitchReduction;
      Config::RCS::ChargeRifleYawReduction = Features::RCS::ChargeRifleYawReduction;
      Config::RCS::SentinelPitch = Features::RCS::SentinelPitch;
      Config::RCS::SentinelYaw = Features::RCS::SentinelYaw;
      Config::RCS::SentinelPitchReduction = Features::RCS::SentinelPitchReduction;
      Config::RCS::SentinelYawReduction = Features::RCS::SentinelYawReduction;
      Config::RCS::WingmanPitch = Features::RCS::WingmanPitch;
      Config::RCS::WingmanYaw = Features::RCS::WingmanYaw;
      Config::RCS::WingmanPitchReduction = Features::RCS::WingmanPitchReduction;
      Config::RCS::WingmanYawReduction = Features::RCS::WingmanYawReduction;
      Config::RCS::EVA8Pitch = Features::RCS::EVA8Pitch;
      Config::RCS::EVA8Yaw = Features::RCS::EVA8Yaw;
      Config::RCS::EVA8PitchReduction = Features::RCS::EVA8PitchReduction;
      Config::RCS::EVA8YawReduction = Features::RCS::EVA8YawReduction;
      Config::RCS::KraberPitch = Features::RCS::KraberPitch;
      Config::RCS::KraberYaw = Features::RCS::KraberYaw;
      Config::RCS::KraberPitchReduction = Features::RCS::KraberPitchReduction;
      Config::RCS::KraberYawReduction = Features::RCS::KraberYawReduction;

      return true;
    } catch (...) { return false; }
  }

  static auto UpdateAimList() -> void {
    Features::Aimbot::AimList.clear();
    // Light
    if (Features::Aimbot::P2020)
      Features::Aimbot::AimList.insert(WeaponIDs::P2020);
    if (Features::Aimbot::RE45)
      Features::Aimbot::AimList.insert(WeaponIDs::RE45);
    if (Features::Aimbot::Alternator)
      Features::Aimbot::AimList.insert(WeaponIDs::ALTERNATOR);
    if (Features::Aimbot::R99)
      Features::Aimbot::AimList.insert(WeaponIDs::R99);
    if (Features::Aimbot::R301)
      Features::Aimbot::AimList.insert(WeaponIDs::R301);
    if (Features::Aimbot::Spitfire)
      Features::Aimbot::AimList.insert(WeaponIDs::SPITFIRE);
    if (Features::Aimbot::G7)
      Features::Aimbot::AimList.insert(WeaponIDs::G7);
    // Heavy
    if (Features::Aimbot::Flatline)
      Features::Aimbot::AimList.insert(WeaponIDs::FLATLINE);
    if (Features::Aimbot::Hemlock)
      Features::Aimbot::AimList.insert(WeaponIDs::HEMLOCK);
    if (Features::Aimbot::Repeater)
      Features::Aimbot::AimList.insert(WeaponIDs::REPEATER);
    if (Features::Aimbot::Rampage)
      Features::Aimbot::AimList.insert(WeaponIDs::RAMPAGE);
    if (Features::Aimbot::CARSMG)
      Features::Aimbot::AimList.insert(WeaponIDs::CAR);
    // Energy
    if (Features::Aimbot::Havoc)
      Features::Aimbot::AimList.insert(WeaponIDs::HAVOC);
    if (Features::Aimbot::Devotion)
      Features::Aimbot::AimList.insert(WeaponIDs::DEVOTION);
    if (Features::Aimbot::LSTAR)
      Features::Aimbot::AimList.insert(WeaponIDs::LSTAR);
    if (Features::Aimbot::TripleTake)
      Features::Aimbot::AimList.insert(WeaponIDs::TRIPLETAKE);
    if (Features::Aimbot::Volt)
      Features::Aimbot::AimList.insert(WeaponIDs::VOLT);
    if (Features::Aimbot::Nemesis)
      Features::Aimbot::AimList.insert(WeaponIDs::NEMESIS);
    // Shotguns
    if (Features::Aimbot::Mozambique)
      Features::Aimbot::AimList.insert(WeaponIDs::MOZAMBIQUE);
    if (Features::Aimbot::EVA8)
      Features::Aimbot::AimList.insert(WeaponIDs::EVA8);
    if (Features::Aimbot::Peacekeeper)
      Features::Aimbot::AimList.insert(WeaponIDs::PEACEKEEPER);
    if (Features::Aimbot::Mastiff)
      Features::Aimbot::AimList.insert(WeaponIDs::MASTIFF);
    // Snipers
    if (Features::Aimbot::Longbow)
      Features::Aimbot::AimList.insert(WeaponIDs::LONGBOW);
    if (Features::Aimbot::ChargeRifle)
      Features::Aimbot::AimList.insert(WeaponIDs::CHARGE_RIFLE);
    if (Features::Aimbot::Sentinel)
      Features::Aimbot::AimList.insert(WeaponIDs::SENTINEL);
    // Legendary
    if (Features::Aimbot::Wingman)
      Features::Aimbot::AimList.insert(WeaponIDs::WINGMAN);
    if (Features::Aimbot::Prowler)
      Features::Aimbot::AimList.insert(WeaponIDs::PROWLER);
    if (Features::Aimbot::Bocek)
      Features::Aimbot::AimList.insert(WeaponIDs::BOCEK);
    if (Features::Aimbot::Kraber)
      Features::Aimbot::AimList.insert(WeaponIDs::KRABER);
    if (Features::Aimbot::Knife)
      Features::Aimbot::AimList.insert(WeaponIDs::KNIFE);
  }

  static auto UpdateRCSList() -> void {
    Features::RCS::RCSList.clear();
    // Light
    if (Features::RCS::P2020)
      Features::RCS::RCSList.insert(WeaponIDs::P2020);
    if (Features::RCS::RE45)
      Features::RCS::RCSList.insert(WeaponIDs::RE45);
    if (Features::RCS::Alternator)
      Features::RCS::RCSList.insert(WeaponIDs::ALTERNATOR);
    if (Features::RCS::R99)
      Features::RCS::RCSList.insert(WeaponIDs::R99);
    if (Features::RCS::R301)
      Features::RCS::RCSList.insert(WeaponIDs::R301);
    if (Features::RCS::Spitfire)
      Features::RCS::RCSList.insert(WeaponIDs::SPITFIRE);
    if (Features::RCS::G7)
      Features::RCS::RCSList.insert(WeaponIDs::G7);
    // Heavy
    if (Features::RCS::Flatline)
      Features::RCS::RCSList.insert(WeaponIDs::FLATLINE);
    if (Features::RCS::Hemlock)
      Features::RCS::RCSList.insert(WeaponIDs::HEMLOCK);
    if (Features::RCS::Repeater)
      Features::RCS::RCSList.insert(WeaponIDs::REPEATER);
    if (Features::RCS::Rampage)
      Features::RCS::RCSList.insert(WeaponIDs::RAMPAGE);
    if (Features::RCS::CARSMG)
      Features::RCS::RCSList.insert(WeaponIDs::CAR);
    // Energy
    if (Features::RCS::Havoc)
      Features::RCS::RCSList.insert(WeaponIDs::HAVOC);
    if (Features::RCS::Devotion)
      Features::RCS::RCSList.insert(WeaponIDs::DEVOTION);
    if (Features::RCS::LSTAR)
      Features::RCS::RCSList.insert(WeaponIDs::LSTAR);
    if (Features::RCS::TripleTake)
      Features::RCS::RCSList.insert(WeaponIDs::TRIPLETAKE);
    if (Features::RCS::Volt)
      Features::RCS::RCSList.insert(WeaponIDs::VOLT);
    if (Features::RCS::Nemesis)
      Features::RCS::RCSList.insert(WeaponIDs::NEMESIS);
    // Shotguns
    if (Features::RCS::Mozambique)
      Features::RCS::RCSList.insert(WeaponIDs::MOZAMBIQUE);
    if (Features::RCS::EVA8)
      Features::RCS::RCSList.insert(WeaponIDs::EVA8);
    if (Features::RCS::Peacekeeper)
      Features::RCS::RCSList.insert(WeaponIDs::PEACEKEEPER);
    if (Features::RCS::Mastiff)
      Features::RCS::RCSList.insert(WeaponIDs::MASTIFF);
    // Snipers
    if (Features::RCS::Longbow)
      Features::RCS::RCSList.insert(WeaponIDs::LONGBOW);
    if (Features::RCS::ChargeRifle)
      Features::RCS::RCSList.insert(WeaponIDs::CHARGE_RIFLE);
    if (Features::RCS::Sentinel)
      Features::RCS::RCSList.insert(WeaponIDs::SENTINEL);
    // Legendary
    if (Features::RCS::Wingman)
      Features::RCS::RCSList.insert(WeaponIDs::WINGMAN);
    if (Features::RCS::Prowler)
      Features::RCS::RCSList.insert(WeaponIDs::PROWLER);
    if (Features::RCS::Kraber)
      Features::RCS::RCSList.insert(WeaponIDs::KRABER);
  }

  auto UpdateAimbot() -> void {
    if (!Features::Aimbot::AimbotEnabled) {
      ReleaseTarget();
      return;
    }

    if (Features::Home::IsMenuOpened)
      return;

    UpdateAimList();

    if (!Myself->IsCombatReady()) {
      CurrentTarget = nullptr;
      return;
    }

    if (!Features::Aimbot::AimList.contains(Myself->WeaponIndex)) {
      ReleaseTarget();
      return;
    }

    if (Myself->IsHoldingGrenade) {
      ReleaseTarget();
      return;
    }

    if (Features::Aimbot::BindMethod == 0) { // OnFire and OnADS
      if (Features::Aimbot::OnFire) {
        if (Features::Aimbot::OnADS) {
          if (!Myself->IsInAttack && !Myself->IsZooming) {
            ReleaseTarget();
            return;
          }
        } else {
          if (!Myself->IsInAttack) {
            ReleaseTarget();
            return;
          }
        }
      } else {
        if (Features::Aimbot::OnADS) {
          if (!Myself->IsZooming) {
            ReleaseTarget();
            return;
          }
        }
      }
    } else { // Keybinds
      if (!isKeybindDown()) {
        ReleaseTarget();
        return;
      }
    }

    if (Player *Target = CurrentTarget; !IsValidTarget(Target)) {
      if (TargetSelected && !Features::Aimbot::TargetSwitching) { return; }

      Target = FindBestTarget();
      if (!IsValidTarget(Target)) {
        ReleaseTarget();
        return;
      }

      CurrentTarget = Target;
      CurrentTarget->IsLockedOn = true;
      TargetSelected = true;
    }

    if (TargetSelected && CurrentTarget) {
      if (const auto Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); Now >= LastAimTime + std::chrono::milliseconds(Features::Aimbot::Delay)) {
        StartAiming();
        LastAimTime = Now;
      }
    }
  }

  auto UpdateRCS() const -> void {
    if (!Features::RCS::RCSEnabled)
      return;
    if (!Map->IsPlayable)
      return;

    if (Features::RCS::RCSEnabled) {
      UpdateRCSSettings();

      if (Features::RCS::RCSMode == 1) // Combined Is In StartAiming() && MoveMouse()
        return;
      if (Features::Aimbot::InputMethod == 1) // Memory Input Method - Must Use Combined
        return;

      if (!Myself->IsCombatReady())
        return;
      if (!Myself->IsInAttack)
        return;
      if (Features::RCS::OnADS && !Myself->IsZooming)
        return;


      const auto PunchAnglesDiff = Myself->punchAnglesDiff;
      if (PunchAnglesDiff.isZeroVector())
        return;

      const auto PitchPower = Features::RCS::AdvancedRCS ? Features::RCS::AdvancedPitchPower : Features::RCS::PitchPower;
      const auto YawPower = Features::RCS::AdvancedRCS ? Features::RCS::AdvancedYawPower : Features::RCS::YawPower;

      const int Pitch = (PunchAnglesDiff.x > 0) ? RoundHalfEven(PunchAnglesDiff.x * static_cast<float>(PitchPower)) : 0;
      const int Yaw = RoundHalfEven(-PunchAnglesDiff.y * static_cast<float>(YawPower));
      X11Display->MoveMouse(Pitch, Yaw);
    }
  }

  static auto isKeybindDown() -> bool {
    return InputManager::isKeyDownOrPress(Features::AimbotBinds::AimBind) || InputManager::isKeyDownOrPress(Features::AimbotBinds::ExtraBind);
  }

  auto StartAiming() const -> void {
    if (Features::Aimbot::InputMethod == 0) { // Mouse movement
      // Get Target Angle
      auto DesiredAngles = QAngle(0, 0);
      if (!GetAngle(CurrentTarget, DesiredAngles))
        return;

      if (Features::RCS::RCSEnabled && Features::RCS::RCSMode == 1) {
        auto PunchAngles = Memory::Read<QAngle>(Myself->BasePointer + OFF_PUNCH_ANGLES);
        if (Features::RCS::AdvancedRCS) {
          PunchAngles.x *= Features::RCS::AdvancedPitchReduction / 100.f;
          PunchAngles.y *= Features::RCS::AdvancedYawReduction / 100.f;
        } else if (!Features::RCS::AdvancedRCS) {
          PunchAngles.x *= Features::RCS::PitchReduction / 100.f;
          PunchAngles.y *= Features::RCS::YawReduction / 100.f;
        }

        DesiredAngles -= PunchAngles;
      }

      if (DesiredAngles == QAngle(0, 0))
        return;

      DesiredAngles.NormalizeAngles();

      // Smoothing
      SmoothAngle(DesiredAngles);

      const Vector2D aimbotDelta = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles)).Multiply(Features::Aimbot::Speed);
      const int totalYawIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.x));
      const int totalPitchIncrementInt = RoundHalfEven(AL1AF0(aimbotDelta.y * -1));

      // Move Mouse
      if (totalPitchIncrementInt == 0 && totalYawIncrementInt == 0)
        return;
      X11Display->MoveMouse(totalYawIncrementInt, totalPitchIncrementInt);
    } else if (Features::Aimbot::InputMethod == 1) { // Write ViewAngles / Controller
      // Get Target Angle
      auto DesiredAngles = QAngle(0, 0);
      if (!GetAngle(CurrentTarget, DesiredAngles)) // Get Angle to target + prediction
        return;

      // Recoil Control
      if (Features::RCS::RCSEnabled) {
        auto PunchAngles = Memory::Read<Vector2D>(Myself->BasePointer + OFF_PUNCH_ANGLES); // Get punch angles
        PunchAngles.x *= Features::RCS::PitchReduction / 100.f;
        PunchAngles.y *= Features::RCS::YawReduction / 100.f;

        DesiredAngles -= QAngle(PunchAngles.x, PunchAngles.y);
      }

      if (DesiredAngles == QAngle(0, 0))
        return;

      DesiredAngles.NormalizeAngles();
      SmoothAngle(DesiredAngles); // Apply Smoothing

      // Memory Aimbot
      const auto VectorDesiredAngles = Vector2D(DesiredAngles.x, DesiredAngles.y);
      Myself->SetViewAngle(VectorDesiredAngles);
    }
  }

  auto SmoothAngle(QAngle &Angle) const -> void {
    const QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
    QAngle Delta = Angle - ViewAngles;
    Delta.NormalizeAngles();

    float SmoothValue;

    if (Features::Aimbot::SmoothingMethod == 0) // Static Smoothing
      SmoothValue = powf(Myself->IsZooming ? Features::Aimbot::ADSSmooth : Features::Aimbot::HipfireSmooth, 0.4f);
    else // Random Smoothing
      SmoothValue = RandomSmoothing(Myself->IsZooming ? Features::Aimbot::MinADSSmooth : Features::Aimbot::MinHipfireSmooth, Myself->IsZooming ? Features::Aimbot::MaxADSSmooth : Features::Aimbot::MaxHipfireSmooth);

    SmoothValue = std::min(0.999f, SmoothValue);
    const auto ToChange = Delta - Delta * SmoothValue;

    Angle = ViewAngles + ToChange;
  }

  auto GetAngle(const Player *Target, QAngle &Angle) const -> bool {
    if (const QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles(); !CurrentAngle.isValid())
      return false;

    if (!GetAngleToTarget(Target, Angle))
      return false;

    return true;
  }

  auto GetAngleToTarget(const Player *Target, QAngle &Angle) const -> bool {
    const Vector3D TargetPosition = Target->GetBonePosition(Features::Aimbot::ClosestHitbox ? static_cast<HitboxType>(GetBestBone(Target)) : Features::AimbotHitboxes::Hitbox);
    const Vector3D TargetVelocity = Target->AbsoluteVelocity;
    const Vector3D CameraPosition = Myself->CameraPosition;

    if (Myself->WeaponProjectileSpeed > 1.0f) {
      if (Features::Aimbot::PredictBulletDrop && Features::Aimbot::PredictMovement) {
        return Resolver::CalculateAimRotationNew(CameraPosition, TargetPosition, TargetVelocity, Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, 255, Angle);
      }
      if (Features::Aimbot::PredictBulletDrop) {
        return Resolver::CalculateAimRotationNew(CameraPosition, TargetPosition, Vector3D(0, 0, 0), Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, 255, Angle);
      }
      if (Features::Aimbot::PredictMovement) {
        return Resolver::CalculateAimRotation(CameraPosition, TargetPosition, TargetVelocity, Myself->WeaponProjectileSpeed, Angle);
      }
    }

    Angle = Resolver::CalculateAngle(CameraPosition, TargetPosition);
    return true;
  }

  static auto IsValidTarget(const Player *target) -> bool {
    if (target == nullptr)
      return false;

    if (target->IsAlly && !Features::Aimbot::TeamCheck)
      return false;

    if (!target->IsCombatReady())
      return false;

    if (Features::Aimbot::VisCheck && !target->IsVisible)
      return false;

    if (target->Distance2DToLocalPlayer < Conversion::ToGameUnits((Features::Aimbot::MinDistance)))
      return false;

    if (target->Distance2DToLocalPlayer > Conversion::ToGameUnits((Features::Aimbot::MaxDistance)))
      return false;

    return true;
  }

  [[nodiscard]] auto CalculateDistanceFromCrosshair(const Vector3D TargetPosition) const -> float {
    const Vector3D CameraPosition = Myself->CameraPosition;
    const QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();

    if (CameraPosition.Distance(TargetPosition) <= 0.0001f)
      return -1;

    const QAngle TargetAngle = Resolver::CalculateAngle(CameraPosition, TargetPosition);
    if (!TargetAngle.isValid())
      return -1;

    return CurrentAngle.distanceTo(TargetAngle);
  }

  auto ReleaseTarget() -> void {
    if (CurrentTarget != nullptr && CurrentTarget->IsValid())
      CurrentTarget->IsLockedOn = false;

    TargetSelected = false;
    CurrentTarget = nullptr;
  }

  [[nodiscard]] auto GetFOVScale() const -> float {
    if (Myself->IsValid()) { if (Myself->IsZooming) { if (Myself->TargetZoomFOV > 1.0 && Myself->TargetZoomFOV < 90.0) { return tanf(DEG2RAD(Myself->TargetZoomFOV) * (0.64285714285)); } } }
    return 1.0;
  }

  auto GetBestBone(const Player *Target) const -> int {
    float NearestDistance = 999;
    auto NearestBone = 2;
    for (auto i = 0; i < 6; i++) {
      const auto Bone = static_cast<HitboxType>(i);
      if (const float DistanceFromCrosshair = CalculateDistanceFromCrosshair(Target->GetBonePosition(Bone)); DistanceFromCrosshair < NearestDistance) {
        NearestBone = i;
        NearestDistance = DistanceFromCrosshair;
      }
    }
    return NearestBone;
  }

  [[nodiscard]] auto FindBestTarget() const -> Player * {
    Player *NearestTarget = nullptr;
    float BestDistance = 9999;
    const auto ScaledFOV = Features::Aimbot::FOV * (GetFOVScale() * Features::Aimbot::ZoomScale);
    const auto BestFOV = std::min(Features::Aimbot::FOV, ScaledFOV);
    float LastPov = 9999;
    const Vector3D CameraPosition = Myself->CameraPosition;
    for (const auto p : *Players) {
      if (!IsValidTarget(p))
        continue;
      if (p->DistanceToLocalPlayer > Conversion::ToGameUnits(Features::Aimbot::MinDistance) && p->DistanceToLocalPlayer < Conversion::ToGameUnits(Features::Aimbot::MaxDistance)) {
        const auto BestBone = static_cast<HitboxType>(GetBestBone(p));
        Vector3D TargetPosition = p->GetBonePosition(BestBone);

        const float Distance = CameraPosition.Distance(TargetPosition);
        const float FOV = CalculateDistanceFromCrosshair(TargetPosition);

        if (FOV > BestFOV)
          continue;

        if (Features::Aimbot::Priority == 0 && FOV > LastPov)
          continue;

        if (Features::Aimbot::Priority == 1 && Distance > BestDistance)
          continue;

        if (Features::Aimbot::Priority == 2 && FOV > LastPov && Distance > BestDistance)
          continue;

        NearestTarget = p;
        BestDistance = Distance;
        LastPov = FOV;
      }
    }
    return NearestTarget;
  }

  // Math
  static auto RandomSmoothing(const auto a, const auto b) -> float {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution dis(0.0, 1.0);

    const auto random = dis(gen);
    return a + random * (b - a);
  }

  [[nodiscard]] auto CalculatePitchIncrement(const QAngle AimbotDesiredAngles) const -> float {
    const float wayA = AimbotDesiredAngles.x - Myself->ViewAngles.x;
    float wayB = 180.0f - fabsf(wayA);
    if (wayA > 0 && wayB > 0)
      wayB *= -1;
    if (fabsf(wayA) < fabsf(wayB))
      return wayA;
    return wayB;
  }

  [[nodiscard]] auto CalculateYawIncrement(const QAngle AimbotDesiredAngles) const -> float {
    const auto wayA = AimbotDesiredAngles.y - Myself->ViewAngles.y;
    auto wayB = 360.0f - fabsf(wayA);
    if (wayA > 0 && wayB > 0)
      wayB *= -1;
    if (fabs(wayA) < fabs(wayB))
      return wayA;
    return wayB;
  }

  static auto RoundHalfEven(const float x) -> int { return (x >= 0.0) ? static_cast<int>(std::round(x)) : static_cast<int>(std::round(-x)) * -1; }

  static auto AL1AF0(const float num) -> float {
    if (num > 0)
      return std::max(num, 1.0f);
    return std::min(num, -1.0f);
  }

  auto UpdateRCSSettings() const -> void {
    if (!Features::RCS::AdvancedRCS) { return; }

    const int weaponHeld = Myself->WeaponIndex;

    if (Features::RCS::AdvancedRCS) {
      if (weaponHeld == WeaponIDs::P2020) { // P2020
        Features::RCS::AdvancedPitchPower = Features::RCS::P2020Pitch;
        Features::RCS::AdvancedYawPower = Features::RCS::P2020Yaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::P2020PitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::P2020YawReduction;
      }
      if (weaponHeld == WeaponIDs::RE45) { // RE-45
        Features::RCS::AdvancedPitchPower = Features::RCS::RE45Pitch;
        Features::RCS::AdvancedYawPower = Features::RCS::RE45Yaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::RE45PitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::RE45YawReduction;
      }
      if (weaponHeld == WeaponIDs::ALTERNATOR) { // Alternator
        Features::RCS::AdvancedPitchPower = Features::RCS::AlternatorPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::AlternatorYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::AlternatorPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::AlternatorYawReduction;
      }
      if (weaponHeld == WeaponIDs::R99) { // R-99
        Features::RCS::AdvancedPitchPower = Features::RCS::R99Pitch;
        Features::RCS::AdvancedYawPower = Features::RCS::R99Yaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::R99PitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::R99YawReduction;
      }
      if (weaponHeld == WeaponIDs::R301) { // R-301
        Features::RCS::AdvancedPitchPower = Features::RCS::R301Pitch;
        Features::RCS::AdvancedYawPower = Features::RCS::R301Yaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::R301PitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::R301YawReduction;
      }
      if (weaponHeld == WeaponIDs::SPITFIRE) { // Spitfire
        Features::RCS::AdvancedPitchPower = Features::RCS::SpitfirePitch;
        Features::RCS::AdvancedYawPower = Features::RCS::SpitfireYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::SpitfirePitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::SpitfireYawReduction;
      }
      if (weaponHeld == WeaponIDs::G7) { // G7
        Features::RCS::AdvancedPitchPower = Features::RCS::G7Pitch;
        Features::RCS::AdvancedYawPower = Features::RCS::G7Yaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::G7PitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::G7YawReduction;
      }
      // Heavy Weapons
      if (weaponHeld == WeaponIDs::CAR) { // CARSMG
        Features::RCS::AdvancedPitchPower = Features::RCS::CARSMGPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::CARSMGYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::CARSMGPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::CARSMGYawReduction;
      }
      if (weaponHeld == WeaponIDs::RAMPAGE) { // Rampage
        Features::RCS::AdvancedPitchPower = Features::RCS::RampagePitch;
        Features::RCS::AdvancedYawPower = Features::RCS::RampageYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::RampagePitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::RampageYawReduction;
      }
      if (weaponHeld == WeaponIDs::REPEATER) { // Repeater
        Features::RCS::AdvancedPitchPower = Features::RCS::RepeaterPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::RepeaterYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::RepeaterPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::RepeaterYawReduction;
      }
      if (weaponHeld == WeaponIDs::HEMLOCK) { // Hemlock
        Features::RCS::AdvancedPitchPower = Features::RCS::HemlockPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::HemlockYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::HemlockPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::HemlockYawReduction;
      }
      if (weaponHeld == WeaponIDs::FLATLINE) { // Flatline
        Features::RCS::AdvancedPitchPower = Features::RCS::FlatlinePitch;
        Features::RCS::AdvancedYawPower = Features::RCS::FlatlineYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::FlatlinePitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::FlatlineYawReduction;
      }
      // Energy Weapons
      if (weaponHeld == WeaponIDs::NEMESIS) { // Nemesis
        Features::RCS::AdvancedPitchPower = Features::RCS::NemesisPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::NemesisYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::NemesisPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::NemesisYawReduction;
      }
      if (weaponHeld == WeaponIDs::VOLT) { // Volt
        Features::RCS::AdvancedPitchPower = Features::RCS::VoltPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::VoltYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::VoltPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::VoltYawReduction;
      }
      if (weaponHeld == WeaponIDs::TRIPLETAKE) { // TripleTake
        Features::RCS::AdvancedPitchPower = Features::RCS::TripleTakePitch;
        Features::RCS::AdvancedYawPower = Features::RCS::TripleTakeYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::TripleTakePitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::TripleTakeYawReduction;
      }
      if (weaponHeld == WeaponIDs::LSTAR) { // LSTAR
        Features::RCS::AdvancedPitchPower = Features::RCS::LSTARPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::LSTARYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::LSTARPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::LSTARYawReduction;
      }
      if (weaponHeld == WeaponIDs::DEVOTION) { // Devotion
        Features::RCS::AdvancedPitchPower = Features::RCS::DevotionPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::DevotionYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::DevotionPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::DevotionYawReduction;
      }
      if (weaponHeld == WeaponIDs::HAVOC) { // Havoc
        Features::RCS::AdvancedPitchPower = Features::RCS::HavocPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::HavocYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::HavocPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::HavocYawReduction;
      }
      // Shotguns
      if (weaponHeld == WeaponIDs::MOZAMBIQUE) { // Mozambique
        Features::RCS::AdvancedPitchPower = Features::RCS::MozambiquePitch;
        Features::RCS::AdvancedYawPower = Features::RCS::MozambiqueYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::MozambiquePitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::MozambiqueYawReduction;
      }
      if (weaponHeld == WeaponIDs::EVA8) { // EVA8
        Features::RCS::AdvancedPitchPower = Features::RCS::EVA8Pitch;
        Features::RCS::AdvancedYawPower = Features::RCS::EVA8Yaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::EVA8PitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::EVA8YawReduction;
      }
      if (weaponHeld == WeaponIDs::PEACEKEEPER) { // Peacekeeper
        Features::RCS::AdvancedPitchPower = Features::RCS::PeacekeeperPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::PeacekeeperYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::PeacekeeperPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::PeacekeeperYawReduction;
      }
      if (weaponHeld == WeaponIDs::MASTIFF) { // Mastiff
        Features::RCS::AdvancedPitchPower = Features::RCS::MastiffPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::MastiffYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::MastiffPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::MastiffYawReduction;
      }
      // Snipers
      if (weaponHeld == WeaponIDs::SENTINEL) { // Sentinel
        Features::RCS::AdvancedPitchPower = Features::RCS::SentinelPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::SentinelYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::SentinelPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::SentinelYawReduction;
      }
      if (weaponHeld == WeaponIDs::CHARGE_RIFLE) { // ChargeRifle
        Features::RCS::AdvancedPitchPower = Features::RCS::ChargeRiflePitch;
        Features::RCS::AdvancedYawPower = Features::RCS::ChargeRifleYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::ChargeRiflePitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::ChargeRifleYawReduction;
      }
      if (weaponHeld == WeaponIDs::LONGBOW) { // Longbow
        Features::RCS::AdvancedPitchPower = Features::RCS::LongbowPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::LongbowYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::LongbowPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::LongbowYawReduction;
      }
      // Legendary Weapons
      if (weaponHeld == WeaponIDs::WINGMAN) { // Wingman
        Features::RCS::AdvancedPitchPower = Features::RCS::WingmanPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::WingmanYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::WingmanPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::WingmanYawReduction;
      }
      if (weaponHeld == WeaponIDs::PROWLER) { // Prowler
        Features::RCS::AdvancedPitchPower = Features::RCS::ProwlerPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::ProwlerYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::ProwlerPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::ProwlerYawReduction;
      }
      if (weaponHeld == WeaponIDs::KRABER) { // Kraber
        Features::RCS::AdvancedPitchPower = Features::RCS::KraberPitch;
        Features::RCS::AdvancedYawPower = Features::RCS::KraberYaw;
        Features::RCS::AdvancedPitchReduction = Features::RCS::KraberPitchReduction;
        Features::RCS::AdvancedYawReduction = Features::RCS::KraberYawReduction;
      }
    }
  }
};
