#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "../imgui/imgui.h"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputTypes.hpp"
#include "../Utils/termcolor.hpp"
#include "Features/Glow.hpp"
#include "Features/Legitbot.hpp"
#include "Features/Misc.hpp"
#include "Features/Radar.hpp"
#include "Features/Sense.hpp"
#include "Features/Triggerbot.hpp"

namespace tc = termcolor;

#define WriteSection(key) \
	conf << "[" #key "]"  \
		 << "\n";
#define WritePair(section, key) \
	conf << #key " = " << Config::section::key << "\n";
#define WriteSectionEnd() conf << "\n";
#define WriteComment(msg) conf << "; " << msg << '\n';

#define ReadBool(section, key) \
	Config::section::key = reader.GetBoolean(#section, #key, Config::section::key);
#define ReadFloat(section, key) \
	Config::section::key = reader.GetFloat(#section, #key, Config::section::key);
#define ReadInt(section, key) \
	Config::section::key = reader.GetInteger(#section, #key, Config::section::key);

struct ConfigManager {
  std::vector<std::string> configFiles;
  char configName[64] = {0};
  int selectedConfig = 0;
  bool finishedStartup = false;

  Legitbot *Legit;
  Triggerbot *Trigger;
  Glow *GlowESP;
  Sense *ESP;
  Radar *MapRadar;
  Misc *MiscTab;

  ConfigManager(Legitbot *Legit, Triggerbot *Trigger, Glow *GlowESP, Sense *ESP, Radar *MapRadar, Misc *MiscTab) {
    this->Legit = Legit;
    this->Trigger = Trigger;
    this->GlowESP = GlowESP;
    this->ESP = ESP;
    this->MapRadar = MapRadar;
    this->MiscTab = MiscTab;
  }

  void RenderConfigs() {
    ImGui::InputText("Config", configName, 64);

    ImGui::SameLine();
    if (ImGui::Button("Save")) {
      SaveConfig();
      LoadConfigs();
    }

    ImGui::SameLine();
    if (ImGui::Button("Load"))
      LoadConfig();

    ImGui::SameLine();
    if (ImGui::Button("Startup"))
      copy_file("Configs/" + std::string(configName) + ".ini", "Configs/STARTUP.ini", std::filesystem::copy_options::overwrite_existing);
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
      ImGui::SetTooltip("Save to STARTUP slot, which gets automatically loaded on startup");


    ImGui::BeginListBox("##Configs", ImVec2(600, 300)); {
      auto n = 0;
      for (const auto& config: configFiles) {
        const bool is_selected = (selectedConfig == n);
        if (ImGui::Selectable(config.c_str(), is_selected)) {
          selectedConfig = n;
          strcpy(configName, config.c_str());
        }

        if (is_selected) { ImGui::SetItemDefaultFocus(); }
        n++;
      }

      ImGui::EndListBox();
    }
  }

  void LoadConfigs() { // List Configs For The ListBox
    const std::string configDirectory = "Configs";
    configFiles.clear();
    for (const auto &entry: std::filesystem::directory_iterator(configDirectory)) {
      if (!entry.is_regular_file() || entry.path().extension() != ".ini")
        continue;

      if (!finishedStartup && entry.path().filename().string() == "STARTUP.ini") {
        strcpy(configName, entry.path().stem().string().c_str());
        LoadConfig();
        finishedStartup = true;
      } else {
        configFiles.push_back(entry.path().stem().string());
      }
    }
  }

  void UpdateConfig() {
    const std::string ConfigName = "Configs/" + std::string(configName) + ".ini";
    if (std::ofstream conf(ConfigName); conf.is_open()) {
      WriteSection(Aimbot);
      WritePair(Aimbot, AimbotEnabled);
      WritePair(Aimbot, BindMethod);
      WritePair(Aimbot, InputMethod); // MoveMouse or Controller (Write To ViewAngles)

      WritePair(Aimbot, ClosestHitbox);

      WritePair(Aimbot, OnFire);
      WritePair(Aimbot, OnADS);
      WritePair(Aimbot, VisCheck);
      WritePair(Aimbot, TeamCheck);
      WritePair(Aimbot, TargetSwitching);
      WritePair(Aimbot, Priority);

      WritePair(Aimbot, PredictMovement);
      WritePair(Aimbot, PredictBulletDrop);

      WritePair(Aimbot, FinalDistance);
      WritePair(Aimbot, Smooth);

      WritePair(Aimbot, Speed);
      WritePair(Aimbot, SmoothingMethod);

      WritePair(Aimbot, HipfireSmooth);
      WritePair(Aimbot, ADSSmooth);
      WritePair(Aimbot, MinHipfireSmooth);
      WritePair(Aimbot, MaxHipfireSmooth);
      WritePair(Aimbot, MinADSSmooth);
      WritePair(Aimbot, MaxADSSmooth);

      WritePair(Aimbot, MouseHipfireSmoothing);
      WritePair(Aimbot, MouseADSSmoothing);
      WritePair(Aimbot, MouseExtraSmoothing);
      WritePair(Aimbot, MinMouseHipfireSmoothing);
      WritePair(Aimbot, MaxMouseHipfireSmoothing);
      WritePair(Aimbot, MinMouseADSSmoothing);
      WritePair(Aimbot, MaxMouseADSSmoothing);

      WritePair(Aimbot, Delay);
      WritePair(Aimbot, FOV);
      WritePair(Aimbot, ZoomScale);
      WritePair(Aimbot, MinDistance);
      WritePair(Aimbot, MaxDistance);
      WritePair(Aimbot, HipfireDistance);
      WritePair(Aimbot, ZoomDistance);

      // AimMode 2
      WritePair(Aimbot, HipfireSmooth1);
      WritePair(Aimbot, ADSSmooth1);
      WritePair(Aimbot, ExtraSmoothing);
      WritePair(Aimbot, Deadzone);
      WritePair(Aimbot, FOV1);

      // Weapon Toggles
      // Light
      WritePair(Aimbot, P2020);
      WritePair(Aimbot, RE45);
      WritePair(Aimbot, Alternator);
      WritePair(Aimbot, R99);
      WritePair(Aimbot, R301);
      WritePair(Aimbot, Spitfire);
      WritePair(Aimbot, G7);

      // Heavy
      WritePair(Aimbot, Flatline);
      WritePair(Aimbot, Hemlock);
      WritePair(Aimbot, Repeater);
      WritePair(Aimbot, Rampage);
      WritePair(Aimbot, CARSMG);

      // Energy
      WritePair(Aimbot, Havoc);
      WritePair(Aimbot, Devotion);
      WritePair(Aimbot, LSTAR);
      WritePair(Aimbot, TripleTake);
      WritePair(Aimbot, Volt);
      WritePair(Aimbot, Nemesis);

      // Shotgun
      WritePair(Aimbot, Mozambique);
      WritePair(Aimbot, EVA8);
      WritePair(Aimbot, Peacekeeper);
      WritePair(Aimbot, Mastiff);

      // Snipers
      WritePair(Aimbot, Longbow);
      WritePair(Aimbot, ChargeRifle);
      WritePair(Aimbot, Sentinel);

      // Legendary
      WritePair(Aimbot, Wingman);
      WritePair(Aimbot, Prowler);
      WritePair(Aimbot, Bocek);
      WritePair(Aimbot, Kraber);
      WritePair(Aimbot, Knife);
      WriteSectionEnd();

      WriteSection(AimbotBinds);
      WritePair(AimbotBinds, AimBind);
      WritePair(AimbotBinds, ExtraBind);
      WriteSectionEnd();

      WriteSection(AimbotHitboxes);
      WritePair(AimbotHitboxes, Hitbox);
      WriteSectionEnd();

      WriteSection(RCS);
      WritePair(RCS, RCSEnabled);
      WritePair(RCS, RCSMode);

      WritePair(RCS, OnADS);

      WritePair(RCS, PitchPower);
      WritePair(RCS, YawPower);
      WritePair(RCS, PitchReduction);
      WritePair(RCS, YawReduction);

      // Weapon Toggles
      // Light
      WritePair(RCS, P2020);
      WritePair(RCS, RE45);
      WritePair(RCS, Alternator);
      WritePair(RCS, R99);
      WritePair(RCS, R301);
      WritePair(RCS, Spitfire);
      WritePair(RCS, G7);

      // Heavy
      WritePair(RCS, Flatline);
      WritePair(RCS, Hemlock);
      WritePair(RCS, Repeater);
      WritePair(RCS, Rampage);
      WritePair(RCS, CARSMG);

      // Energy
      WritePair(RCS, Havoc);
      WritePair(RCS, Devotion);
      WritePair(RCS, LSTAR);
      WritePair(RCS, TripleTake);
      WritePair(RCS, Volt);
      WritePair(RCS, Nemesis);

      // Shotgun
      WritePair(RCS, Mozambique);
      WritePair(RCS, EVA8);
      WritePair(RCS, Peacekeeper);
      WritePair(RCS, Mastiff);

      // Snipers
      WritePair(RCS, Longbow);
      WritePair(RCS, ChargeRifle);
      WritePair(RCS, Sentinel);

      // Legendary
      WritePair(RCS, Wingman); // Emotional damage!
      WritePair(RCS, Prowler);
      WritePair(RCS, Kraber);

      //---------------Advanced---------------//
      WritePair(RCS, AdvancedRCS);
      WritePair(RCS, AdvancedPitchPower);
      WritePair(RCS, AdvancedYawPower);
      WritePair(RCS, AdvancedPitchReduction);
      WritePair(RCS, AdvancedYawReduction);

      // Weapons
      // Light
      WritePair(RCS, P2020Pitch);
      WritePair(RCS, P2020Yaw);
      WritePair(RCS, P2020PitchReduction);
      WritePair(RCS, P2020YawReduction);
      WritePair(RCS, RE45Pitch);
      WritePair(RCS, RE45Yaw);
      WritePair(RCS, RE45PitchReduction);
      WritePair(RCS, RE45YawReduction);
      WritePair(RCS, AlternatorPitch);
      WritePair(RCS, AlternatorYaw);
      WritePair(RCS, AlternatorPitchReduction);
      WritePair(RCS, AlternatorYawReduction);
      WritePair(RCS, R99Pitch);
      WritePair(RCS, R99Yaw);
      WritePair(RCS, R99PitchReduction);
      WritePair(RCS, R99YawReduction);
      WritePair(RCS, R301Pitch);
      WritePair(RCS, R301Yaw);
      WritePair(RCS, R301PitchReduction);
      WritePair(RCS, R301YawReduction);
      WritePair(RCS, SpitfirePitch);
      WritePair(RCS, SpitfireYaw);
      WritePair(RCS, SpitfirePitchReduction);
      WritePair(RCS, SpitfireYawReduction);
      WritePair(RCS, G7Pitch);
      WritePair(RCS, G7Yaw);
      WritePair(RCS, G7PitchReduction);
      WritePair(RCS, G7YawReduction);
      // Heavy
      WritePair(RCS, FlatlinePitch);
      WritePair(RCS, FlatlineYaw);
      WritePair(RCS, FlatlinePitchReduction);
      WritePair(RCS, FlatlineYawReduction);
      WritePair(RCS, HemlockPitch);
      WritePair(RCS, HemlockYaw);
      WritePair(RCS, HemlockPitchReduction);
      WritePair(RCS, HemlockYawReduction);
      WritePair(RCS, RepeaterPitch);
      WritePair(RCS, RepeaterYaw);
      WritePair(RCS, RepeaterPitchReduction);
      WritePair(RCS, RepeaterYawReduction);
      WritePair(RCS, RampagePitch);
      WritePair(RCS, RampageYaw);
      WritePair(RCS, RampagePitchReduction);
      WritePair(RCS, RampageYawReduction);
      WritePair(RCS, CARSMGPitch);
      WritePair(RCS, CARSMGYaw);
      WritePair(RCS, CARSMGPitchReduction);
      WritePair(RCS, CARSMGYawReduction);
      // Energy
      WritePair(RCS, HavocPitch);
      WritePair(RCS, HavocYaw);
      WritePair(RCS, HavocPitchReduction);
      WritePair(RCS, HavocYawReduction);
      WritePair(RCS, DevotionPitch);
      WritePair(RCS, DevotionYaw);
      WritePair(RCS, DevotionPitchReduction);
      WritePair(RCS, DevotionYawReduction);
      WritePair(RCS, LSTARPitch);
      WritePair(RCS, LSTARYaw);
      WritePair(RCS, LSTARPitchReduction);
      WritePair(RCS, LSTARYawReduction);
      WritePair(RCS, TripleTakePitch);
      WritePair(RCS, TripleTakeYaw);
      WritePair(RCS, TripleTakePitchReduction);
      WritePair(RCS, TripleTakeYawReduction);
      WritePair(RCS, VoltPitch);
      WritePair(RCS, VoltYaw);
      WritePair(RCS, VoltPitchReduction);
      WritePair(RCS, VoltYawReduction);
      WritePair(RCS, NemesisPitch);
      WritePair(RCS, NemesisYaw);
      WritePair(RCS, NemesisPitchReduction);
      WritePair(RCS, NemesisYawReduction);
      // Shotguns
      WritePair(RCS, MozambiquePitch);
      WritePair(RCS, MozambiqueYaw);
      WritePair(RCS, MozambiquePitchReduction);
      WritePair(RCS, MozambiqueYawReduction);
      WritePair(RCS, EVA8Pitch);
      WritePair(RCS, EVA8Yaw);
      WritePair(RCS, EVA8PitchReduction);
      WritePair(RCS, EVA8YawReduction);
      WritePair(RCS, PeacekeeperPitch);
      WritePair(RCS, PeacekeeperYaw);
      WritePair(RCS, PeacekeeperPitchReduction);
      WritePair(RCS, PeacekeeperYawReduction);
      WritePair(RCS, MastiffPitch);
      WritePair(RCS, MastiffYaw);
      WritePair(RCS, MastiffPitchReduction);
      WritePair(RCS, MastiffYawReduction);
      // Snipers
      WritePair(RCS, LongbowPitch);
      WritePair(RCS, LongbowYaw);
      WritePair(RCS, LongbowPitchReduction);
      WritePair(RCS, LongbowYawReduction);
      WritePair(RCS, ChargeRiflePitch);
      WritePair(RCS, ChargeRifleYaw);
      WritePair(RCS, ChargeRiflePitchReduction);
      WritePair(RCS, ChargeRifleYawReduction);
      WritePair(RCS, SentinelPitch);
      WritePair(RCS, SentinelYaw);
      WritePair(RCS, SentinelPitchReduction);
      WritePair(RCS, SentinelYawReduction);
      // Legendary
      WritePair(RCS, WingmanPitch);
      WritePair(RCS, WingmanYaw);
      WritePair(RCS, WingmanPitchReduction);
      WritePair(RCS, WingmanYawReduction);
      WritePair(RCS, ProwlerPitch);
      WritePair(RCS, ProwlerYaw);
      WritePair(RCS, ProwlerPitchReduction);
      WritePair(RCS, ProwlerYawReduction);
      WritePair(RCS, KraberPitch);
      WritePair(RCS, KraberYaw);
      WritePair(RCS, KraberPitchReduction);
      WritePair(RCS, KraberYawReduction);

      WriteSectionEnd();

      WriteSection(Triggerbot);
      WritePair(Triggerbot, Enabled);
      WritePair(Triggerbot, BindMethod);
      WritePair(Triggerbot, TriggerBind);
      WritePair(Triggerbot, OnADS);
      WritePair(Triggerbot, HipfireShotguns);
      WritePair(Triggerbot, Delay);
      WritePair(Triggerbot, Range);
      WritePair(Triggerbot, RangeHipfire);

      // Weapon Toggles
      // Light
      WritePair(Triggerbot, P2020);
      WritePair(Triggerbot, RE45);
      WritePair(Triggerbot, Alternator);
      WritePair(Triggerbot, R99);
      WritePair(Triggerbot, R301);
      WritePair(Triggerbot, Spitfire);
      WritePair(Triggerbot, G7);
      // Heavy
      WritePair(Triggerbot, Flatline);
      WritePair(Triggerbot, Hemlock);
      WritePair(Triggerbot, Repeater);
      WritePair(Triggerbot, Rampage);
      WritePair(Triggerbot, CARSMG);
      // Energy
      WritePair(Triggerbot, Havoc);
      WritePair(Triggerbot, Devotion);
      WritePair(Triggerbot, LSTAR);
      WritePair(Triggerbot, TripleTake);
      WritePair(Triggerbot, Volt);
      WritePair(Triggerbot, Nemesis);
      // Shotgun
      WritePair(Triggerbot, Mozambique);
      WritePair(Triggerbot, EVA8);
      WritePair(Triggerbot, Peacekeeper);
      WritePair(Triggerbot, Mastiff);
      // Snipers
      WritePair(Triggerbot, Longbow);
      WritePair(Triggerbot, ChargeRifle);
      WritePair(Triggerbot, Sentinel);
      // Legendary
      WritePair(Triggerbot, Wingman);
      WritePair(Triggerbot, Prowler);
      WritePair(Triggerbot, Bocek);
      WritePair(Triggerbot, Kraber);
      WritePair(Triggerbot, Knife);

      // Advanced Triggerbot
      WritePair(Triggerbot, AdvancedTriggerbot);
      WritePair(Triggerbot, P2020Range);
      WritePair(Triggerbot, RE45Range);
      WritePair(Triggerbot, AlternatorRange);
      WritePair(Triggerbot, R99Range);
      WritePair(Triggerbot, R301Range);
      WritePair(Triggerbot, SpitfireRange);
      WritePair(Triggerbot, G7Range);
      WritePair(Triggerbot, FlatlineRange);
      WritePair(Triggerbot, HemlockRange);
      WritePair(Triggerbot, ProwlerRange);
      WritePair(Triggerbot, RepeaterRange);
      WritePair(Triggerbot, RampageRange);
      WritePair(Triggerbot, CARSMGRange);
      WritePair(Triggerbot, HavocRange);
      WritePair(Triggerbot, DevotionRange);
      WritePair(Triggerbot, LSTARRange);
      WritePair(Triggerbot, TripleTakeRange);
      WritePair(Triggerbot, VoltRange);
      WritePair(Triggerbot, NemesisRange);
      WritePair(Triggerbot, MozambiqueRange);
      WritePair(Triggerbot, PeacekeeperRange);
      WritePair(Triggerbot, MastiffRange);
      WritePair(Triggerbot, LongbowRange);
      WritePair(Triggerbot, ChargeRifleRange);
      WritePair(Triggerbot, SentinelRange);
      WritePair(Triggerbot, WingmanRange);
      WritePair(Triggerbot, EVA8Range);
      WritePair(Triggerbot, BocekRange);
      WritePair(Triggerbot, KraberRange);
      WritePair(Triggerbot, ThrowingKnifeRange);

      WriteSectionEnd();

      WriteSection(Glow);

      // Glow
      WritePair(Glow, NewGlow);
      WritePair(Glow, GlowMaxDistance);
      WritePair(Glow, GlowColorMode);
      WritePair(Glow, GlowColorShieldMode);
      WritePair(Glow, GlowRadius);
      WritePair(Glow, InsideFunction); // Leave
      WritePair(Glow, OutlineFunction); // Leave
      WritePair(Glow, BodyStyle);
      WritePair(Glow, OutlineStyle);
      WritePair(Glow, ViewModelGlow);
      WritePair(Glow, ViewModelGlowSetting);
      WritePair(Glow, ViewModelGlowCombo);

      WriteSectionEnd();

      WriteSection(ItemGlow);

      WritePair(ItemGlow, ItemGlow);
      WritePair(ItemGlow, SelectedItemSelection); // 0 = Simple, 1 = Custom
      WritePair(ItemGlow, Common);
      WritePair(ItemGlow, Rare);
      WritePair(ItemGlow, Epic);
      WritePair(ItemGlow, Gold);
      WritePair(ItemGlow, Legendary);
      WritePair(ItemGlow, Weapons);
      WritePair(ItemGlow, Ammo);
      WritePair(ItemGlow, ItemGlowThickness);
      WritePair(ItemGlow, SelectedInsideStyle);
      WritePair(ItemGlow, SelectedOutlineStyle);

      WriteSectionEnd();

      WriteSection(Sense);

      WritePair(Sense, Enabled);

      // Aimbot
      WritePair(Sense, DrawFOVCircle);
      WritePair(Sense, DrawFilledFOVCircle);
      WritePair(Sense, FOVThickness);
      WritePair(Sense, GameFOV);
      // Other
      WritePair(Sense, DrawCrosshair);
      WritePair(Sense, CrosshairSize);
      WritePair(Sense, CrosshairThickness);
      WritePair(Sense, ShowSpectators);
      WritePair(Sense, DrawSpectatorWarning);
      WritePair(Sense, DrawVisibleWarning);
      WritePair(Sense, WarningTextOutline);
      WritePair(Sense, WarningTextX);
      WritePair(Sense, WarningTextY);
      // Settings
      WritePair(Sense, TextOutline);
      WritePair(Sense, VisibilityCheck);
      WritePair(Sense, ESPMaxDistance);

      WriteSectionEnd();

      WriteSection(SenseEnemy);

      WritePair(SenseEnemy, DrawEnemy);
      WritePair(SenseEnemy, DrawBoxes);
      WritePair(SenseEnemy, BoxType);
      WritePair(SenseEnemy, BoxStyle);
      WritePair(SenseEnemy, BoxThickness);
      WritePair(SenseEnemy, DrawSkeleton);
      WritePair(SenseEnemy, SkeletonThickness);
      WritePair(SenseEnemy, DrawHeadCircle);
      WritePair(SenseEnemy, HeadCircleThickness);
      WritePair(SenseEnemy, DrawBars);
      WritePair(SenseEnemy, HealthBar);
      WritePair(SenseEnemy, ShieldBar);
      WritePair(SenseEnemy, BarMode);
      WritePair(SenseEnemy, BarStyle);
      WritePair(SenseEnemy, BarThickness);
      WritePair(SenseEnemy, BarThickness2);
      WritePair(SenseEnemy, BarHeight);
      WritePair(SenseEnemy, BarWidth);
      WritePair(SenseEnemy, BarColorMode);
      WritePair(SenseEnemy, WeaponColorType);
      WritePair(SenseEnemy, DrawDistance);
      WritePair(SenseEnemy, TracerPosition);
      WritePair(SenseEnemy, TracerBone);
      WritePair(SenseEnemy, DrawTracers);
      WritePair(SenseEnemy, TracerThickness);
      WritePair(SenseEnemy, DrawNames);
      WritePair(SenseEnemy, DrawStatus);
      WritePair(SenseEnemy, DrawWeapon);
      WritePair(SenseEnemy, DrawLegend);
      WritePair(SenseEnemy, ShowMaxStatusValues);

      WriteSectionEnd();

      WriteSection(SenseTeammate);

      WritePair(SenseTeammate, DrawTeam);
      WritePair(SenseTeammate, DrawBoxes);
      WritePair(SenseTeammate, BoxType);
      WritePair(SenseTeammate, BoxStyle);
      WritePair(SenseTeammate, BoxThickness);
      WritePair(SenseTeammate, DrawSkeleton);
      WritePair(SenseTeammate, SkeletonThickness);
      WritePair(SenseTeammate, DrawHeadCircle);
      WritePair(SenseTeammate, HeadCircleThickness);
      WritePair(SenseTeammate, DrawBars);
      WritePair(SenseTeammate, HealthBar);
      WritePair(SenseTeammate, ShieldBar);
      WritePair(SenseTeammate, BarMode);
      WritePair(SenseTeammate, BarStyle);
      WritePair(SenseTeammate, BarThickness);
      WritePair(SenseTeammate, BarThickness2);
      WritePair(SenseTeammate, BarHeight);
      WritePair(SenseTeammate, BarWidth);
      WritePair(SenseTeammate, BarColorMode);
      WritePair(SenseTeammate, BarBackground);
      WritePair(SenseTeammate, WeaponColorType);
      WritePair(SenseTeammate, DrawDistance);
      WritePair(SenseTeammate, TracerPosition);
      WritePair(SenseTeammate, TracerBone);
      WritePair(SenseTeammate, DrawTracers);
      WritePair(SenseTeammate, TracerThickness);
      WritePair(SenseTeammate, DrawNames);
      WritePair(SenseTeammate, DrawStatus);
      WritePair(SenseTeammate, DrawWeapon);
      WritePair(SenseTeammate, DrawLegend);
      WritePair(SenseTeammate, ShowMaxStatusValues);

      WriteSectionEnd();

      WriteSection(SensePositions);

      WritePair(SensePositions, NamePosition);
      WritePair(SensePositions, DistancePosition);
      WritePair(SensePositions, LegendPosition);
      WritePair(SensePositions, WeaponPosition);
      WritePair(SensePositions, StatusPosition);

      WriteSectionEnd();

      WriteSection(Radar);

      WritePair(Radar, MiniMap);
      WritePair(Radar, MiniMapRange);
      WritePair(Radar, MiniMapScaleX);
      WritePair(Radar, MiniMapScaleY);
      WritePair(Radar, MiniMapDotSize);
      WritePair(Radar, MiniMapBlackBGSize);
      WritePair(Radar, MiniMapGuides);
      WritePair(Radar, BigMap);
      WritePair(Radar, BigMapBind);
      WritePair(Radar, CircleColorR);
      WritePair(Radar, CircleColorG);
      WritePair(Radar, CircleColorB);
      WritePair(Radar, CircleColorA);

      WriteSectionEnd();

      WriteSection(Misc);

      WritePair(Misc, SuperGlide);
      WritePair(Misc, SuperGlideMode);
      WritePair(Misc, SuperGlideFPS);

      WritePair(Misc, QuickTurn);
      WritePair(Misc, QuickTurnAngle);
      WritePair(Misc, QuickTurnBind);

      WritePair(Misc, BHop);
      WritePair(Misc, BHopDelay);
      WritePair(Misc, BHopBind);

      WritePair(Misc, RapidFire);
      WritePair(Misc, RapidFireDelay);
      WritePair(Misc, RapidFireBind);

      // Rapid Fire Weapon Toggles
      // Light
      WritePair(Misc, RapidP2020);
      WritePair(Misc, RapidR301);
      WritePair(Misc, RapidG7);
      // Heavy
      WritePair(Misc, RapidFlatline);
      WritePair(Misc, RapidHemlock);
      WritePair(Misc, RapidProwler);
      // Energy
      WritePair(Misc, RapidNemesis);
      // Shotgun
      WritePair(Misc, RapidMozambique);
      WritePair(Misc, RapidEVA8);
      // Legendary
      WritePair(Misc, RapidWingman);

      WritePair(Misc, SkinChanger);
      // Weapon IDs
      // Light
      WritePair(Misc, SkinP2020);
      WritePair(Misc, SkinRE45);
      WritePair(Misc, SkinALTERNATOR);
      WritePair(Misc, SkinR99);
      WritePair(Misc, SkinR301);
      WritePair(Misc, SkinSPITFIRE);
      WritePair(Misc, SkinG7);

      // Heavy
      WritePair(Misc, SkinFLATLINE);
      WritePair(Misc, SkinHEMLOCK);
      WritePair(Misc, SkinREPEATER);
      WritePair(Misc, SkinRAMPAGE);
      WritePair(Misc, SkinCAR);

      // Energy
      WritePair(Misc, SkinHAVOC);
      WritePair(Misc, SkinDEVOTION);
      WritePair(Misc, SkinLSTAR);
      WritePair(Misc, SkinTRIPLETAKE);
      WritePair(Misc, SkinVOLT);
      WritePair(Misc, SkinNEMESIS);

      // Shotgun
      WritePair(Misc, SkinMOZAMBIQUE);
      WritePair(Misc, SkinEVA8);
      WritePair(Misc, SkinPEACEKEEPER);
      WritePair(Misc, SkinMASTIFF);

      // Snipers
      WritePair(Misc, SkinLONGBOW);
      WritePair(Misc, SkinCHARGE_RIFLE);
      WritePair(Misc, SkinSENTINEL);

      // Legendary
      WritePair(Misc, SkinWINGMAN);
      WritePair(Misc, SkinPROWLER);
      WritePair(Misc, SkinBOCEK);
      WritePair(Misc, SkinKRABER);

      WriteSectionEnd();

      WriteSection(Colors);

      WritePair(Colors, WeaponColorMode);
      WritePair(Colors, FOVColorR);
      WritePair(Colors, FOVColorG);
      WritePair(Colors, FOVColorB);
      WritePair(Colors, FOVColorA);
      WritePair(Colors, FilledFOVColorR);
      WritePair(Colors, FilledFOVColorG);
      WritePair(Colors, FilledFOVColorB);
      WritePair(Colors, FilledFOVColorA);
      WritePair(Colors, CrosshairColorR);
      WritePair(Colors, CrosshairColorG);
      WritePair(Colors, CrosshairColorB);
      WritePair(Colors, CrosshairColorA);
      WritePair(Colors, SpectatorWarningColorR);
      WritePair(Colors, SpectatorWarningColorG);
      WritePair(Colors, SpectatorWarningColorB);
      WritePair(Colors, SpectatorWarningColorA);
      WritePair(Colors, VisibleWarningColorR);
      WritePair(Colors, VisibleWarningColorG);
      WritePair(Colors, VisibleWarningColorB);
      WritePair(Colors, VisibleWarningColorA);

      WriteSectionEnd();

      WriteSection(EnemyColors);

      WritePair(EnemyColors, InvisibleBoxColorR);
      WritePair(EnemyColors, InvisibleBoxColorG);
      WritePair(EnemyColors, InvisibleBoxColorB);
      WritePair(EnemyColors, InvisibleBoxColorA);
      WritePair(EnemyColors, VisibleBoxColorR);
      WritePair(EnemyColors, VisibleBoxColorG);
      WritePair(EnemyColors, VisibleBoxColorB);
      WritePair(EnemyColors, VisibleBoxColorA);
      WritePair(EnemyColors, InvisibleFilledBoxColorR);
      WritePair(EnemyColors, InvisibleFilledBoxColorG);
      WritePair(EnemyColors, InvisibleFilledBoxColorB);
      WritePair(EnemyColors, InvisibleFilledBoxColorA);
      WritePair(EnemyColors, VisibleFilledBoxColorR);
      WritePair(EnemyColors, VisibleFilledBoxColorG);
      WritePair(EnemyColors, VisibleFilledBoxColorB);
      WritePair(EnemyColors, VisibleFilledBoxColorA);
      WritePair(EnemyColors, InvisibleTracerColorR);
      WritePair(EnemyColors, InvisibleTracerColorG);
      WritePair(EnemyColors, InvisibleTracerColorB);
      WritePair(EnemyColors, InvisibleTracerColorA);
      WritePair(EnemyColors, VisibleTracerColorR);
      WritePair(EnemyColors, VisibleTracerColorG);
      WritePair(EnemyColors, VisibleTracerColorB);
      WritePair(EnemyColors, VisibleTracerColorA);
      WritePair(EnemyColors, InvisibleSkeletonColorR);
      WritePair(EnemyColors, InvisibleSkeletonColorG);
      WritePair(EnemyColors, InvisibleSkeletonColorB);
      WritePair(EnemyColors, InvisibleSkeletonColorA);
      WritePair(EnemyColors, VisibleSkeletonColorR);
      WritePair(EnemyColors, VisibleSkeletonColorG);
      WritePair(EnemyColors, VisibleSkeletonColorB);
      WritePair(EnemyColors, VisibleSkeletonColorA);
      WritePair(EnemyColors, InvisibleHeadCircleColorR);
      WritePair(EnemyColors, InvisibleHeadCircleColorG);
      WritePair(EnemyColors, InvisibleHeadCircleColorB);
      WritePair(EnemyColors, InvisibleHeadCircleColorA);
      WritePair(EnemyColors, VisibleHeadCircleColorR);
      WritePair(EnemyColors, VisibleHeadCircleColorG);
      WritePair(EnemyColors, VisibleHeadCircleColorB);
      WritePair(EnemyColors, VisibleHeadCircleColorA);
      WritePair(EnemyColors, InvisibleNameColorR);
      WritePair(EnemyColors, InvisibleNameColorG);
      WritePair(EnemyColors, InvisibleNameColorB);
      WritePair(EnemyColors, InvisibleNameColorA);
      WritePair(EnemyColors, VisibleNameColorR);
      WritePair(EnemyColors, VisibleNameColorG);
      WritePair(EnemyColors, VisibleNameColorB);
      WritePair(EnemyColors, VisibleNameColorA);
      WritePair(EnemyColors, InvisibleDistanceColorR);
      WritePair(EnemyColors, InvisibleDistanceColorG);
      WritePair(EnemyColors, InvisibleDistanceColorB);
      WritePair(EnemyColors, InvisibleDistanceColorA);
      WritePair(EnemyColors, VisibleDistanceColorR);
      WritePair(EnemyColors, VisibleDistanceColorG);
      WritePair(EnemyColors, VisibleDistanceColorB);
      WritePair(EnemyColors, VisibleDistanceColorA);
      WritePair(EnemyColors, InvisibleLegendColorR);
      WritePair(EnemyColors, InvisibleLegendColorG);
      WritePair(EnemyColors, InvisibleLegendColorB);
      WritePair(EnemyColors, InvisibleLegendColorA);
      WritePair(EnemyColors, VisibleLegendColorR);
      WritePair(EnemyColors, VisibleLegendColorG);
      WritePair(EnemyColors, VisibleLegendColorB);
      WritePair(EnemyColors, VisibleLegendColorA);
      // Bar
      WritePair(EnemyColors, BarColorMode);
      // WeaponESP Colors
      WritePair(EnemyColors, InvisibleWeaponColorR);
      WritePair(EnemyColors, InvisibleWeaponColorG);
      WritePair(EnemyColors, InvisibleWeaponColorB);
      WritePair(EnemyColors, InvisibleWeaponColorA);
      WritePair(EnemyColors, VisibleWeaponColorR);
      WritePair(EnemyColors, VisibleWeaponColorG);
      WritePair(EnemyColors, VisibleWeaponColorB);
      WritePair(EnemyColors, VisibleWeaponColorA);
      // Multiple
      WritePair(EnemyColors, LightWeaponColorR);
      WritePair(EnemyColors, LightWeaponColorG);
      WritePair(EnemyColors, LightWeaponColorB);
      WritePair(EnemyColors, LightWeaponColorA);
      WritePair(EnemyColors, HeavyWeaponColorR);
      WritePair(EnemyColors, HeavyWeaponColorG);
      WritePair(EnemyColors, HeavyWeaponColorB);
      WritePair(EnemyColors, HeavyWeaponColorA);
      WritePair(EnemyColors, EnergyWeaponColorR);
      WritePair(EnemyColors, EnergyWeaponColorG);
      WritePair(EnemyColors, EnergyWeaponColorB);
      WritePair(EnemyColors, EnergyWeaponColorA);
      WritePair(EnemyColors, ShotgunWeaponColorR);
      WritePair(EnemyColors, ShotgunWeaponColorG);
      WritePair(EnemyColors, ShotgunWeaponColorB);
      WritePair(EnemyColors, ShotgunWeaponColorA);
      WritePair(EnemyColors, SniperWeaponColorR);
      WritePair(EnemyColors, SniperWeaponColorG);
      WritePair(EnemyColors, SniperWeaponColorB);
      WritePair(EnemyColors, SniperWeaponColorA);
      WritePair(EnemyColors, LegendaryWeaponColorR);
      WritePair(EnemyColors, LegendaryWeaponColorG);
      WritePair(EnemyColors, LegendaryWeaponColorB);
      WritePair(EnemyColors, LegendaryWeaponColorA);
      WritePair(EnemyColors, MeleeWeaponColorR);
      WritePair(EnemyColors, MeleeWeaponColorG);
      WritePair(EnemyColors, MeleeWeaponColorB);
      WritePair(EnemyColors, MeleeWeaponColorA);
      WritePair(EnemyColors, ThrowableWeaponColorR);
      WritePair(EnemyColors, ThrowableWeaponColorG);
      WritePair(EnemyColors, ThrowableWeaponColorB);
      WritePair(EnemyColors, ThrowableWeaponColorA);
      // Glow
      WritePair(EnemyColors, InvisibleGlowColorR);
      WritePair(EnemyColors, InvisibleGlowColorG);
      WritePair(EnemyColors, InvisibleGlowColorB);
      WritePair(EnemyColors, VisibleGlowColorR);
      WritePair(EnemyColors, VisibleGlowColorG);
      WritePair(EnemyColors, VisibleGlowColorB);

      WritePair(EnemyColors, RedShieldColorR);
      WritePair(EnemyColors, RedShieldColorG);
      WritePair(EnemyColors, RedShieldColorG);
      WritePair(EnemyColors, PurpleShieldColorR);
      WritePair(EnemyColors, PurpleShieldColorG);
      WritePair(EnemyColors, PurpleShieldColorB);
      WritePair(EnemyColors, BlueShieldColorR);
      WritePair(EnemyColors, BlueShieldColorG);
      WritePair(EnemyColors, BlueShieldColorB);
      WritePair(EnemyColors, GreyShieldColorR);
      WritePair(EnemyColors, GreyShieldColorG);
      WritePair(EnemyColors, GreyShieldColorB);

      WriteSectionEnd();

      WriteSection(TeammateColors);

      WritePair(TeammateColors, InvisibleBoxColorR);
      WritePair(TeammateColors, InvisibleBoxColorG);
      WritePair(TeammateColors, InvisibleBoxColorB);
      WritePair(TeammateColors, InvisibleBoxColorA);
      WritePair(TeammateColors, VisibleBoxColorR);
      WritePair(TeammateColors, VisibleBoxColorG);
      WritePair(TeammateColors, VisibleBoxColorB);
      WritePair(TeammateColors, VisibleBoxColorA);
      WritePair(TeammateColors, InvisibleFilledBoxColorR);
      WritePair(TeammateColors, InvisibleFilledBoxColorG);
      WritePair(TeammateColors, InvisibleFilledBoxColorB);
      WritePair(TeammateColors, InvisibleFilledBoxColorA);
      WritePair(TeammateColors, VisibleFilledBoxColorR);
      WritePair(TeammateColors, VisibleFilledBoxColorG);
      WritePair(TeammateColors, VisibleFilledBoxColorB);
      WritePair(TeammateColors, VisibleFilledBoxColorA);
      WritePair(TeammateColors, InvisibleTracerColorR);
      WritePair(TeammateColors, InvisibleTracerColorG);
      WritePair(TeammateColors, InvisibleTracerColorB);
      WritePair(TeammateColors, InvisibleTracerColorA);
      WritePair(TeammateColors, VisibleTracerColorR);
      WritePair(TeammateColors, VisibleTracerColorG);
      WritePair(TeammateColors, VisibleTracerColorB);
      WritePair(TeammateColors, VisibleTracerColorA);
      WritePair(TeammateColors, InvisibleSkeletonColorR);
      WritePair(TeammateColors, InvisibleSkeletonColorG);
      WritePair(TeammateColors, InvisibleSkeletonColorB);
      WritePair(TeammateColors, InvisibleSkeletonColorA);
      WritePair(TeammateColors, VisibleSkeletonColorR);
      WritePair(TeammateColors, VisibleSkeletonColorG);
      WritePair(TeammateColors, VisibleSkeletonColorB);
      WritePair(TeammateColors, VisibleSkeletonColorA);
      WritePair(TeammateColors, InvisibleHeadCircleColorR);
      WritePair(TeammateColors, InvisibleHeadCircleColorG);
      WritePair(TeammateColors, InvisibleHeadCircleColorB);
      WritePair(TeammateColors, InvisibleHeadCircleColorA);
      WritePair(TeammateColors, VisibleHeadCircleColorR);
      WritePair(TeammateColors, VisibleHeadCircleColorG);
      WritePair(TeammateColors, VisibleHeadCircleColorB);
      WritePair(TeammateColors, VisibleHeadCircleColorA);
      WritePair(TeammateColors, InvisibleNameColorR);
      WritePair(TeammateColors, InvisibleNameColorG);
      WritePair(TeammateColors, InvisibleNameColorB);
      WritePair(TeammateColors, InvisibleNameColorA);
      WritePair(TeammateColors, VisibleNameColorR);
      WritePair(TeammateColors, VisibleNameColorG);
      WritePair(TeammateColors, VisibleNameColorB);
      WritePair(TeammateColors, VisibleNameColorA);

      WritePair(TeammateColors, InvisibleDistanceColorR);
      WritePair(TeammateColors, InvisibleDistanceColorG);
      WritePair(TeammateColors, InvisibleDistanceColorB);
      WritePair(TeammateColors, InvisibleDistanceColorA);
      WritePair(TeammateColors, VisibleDistanceColorR);
      WritePair(TeammateColors, VisibleDistanceColorG);
      WritePair(TeammateColors, VisibleDistanceColorB);
      WritePair(TeammateColors, VisibleDistanceColorA);

      WritePair(TeammateColors, InvisibleLegendColorR);
      WritePair(TeammateColors, InvisibleLegendColorG);
      WritePair(TeammateColors, InvisibleLegendColorB);
      WritePair(TeammateColors, InvisibleLegendColorA);
      WritePair(TeammateColors, VisibleLegendColorR);
      WritePair(TeammateColors, VisibleLegendColorG);
      WritePair(TeammateColors, VisibleLegendColorB);
      WritePair(TeammateColors, VisibleLegendColorA);
      // Bar
      WritePair(TeammateColors, BarColorMode);
      // WeaponESP Colors
      WritePair(TeammateColors, InvisibleWeaponColorR);
      WritePair(TeammateColors, InvisibleWeaponColorG);
      WritePair(TeammateColors, InvisibleWeaponColorB);
      WritePair(TeammateColors, InvisibleWeaponColorA);
      WritePair(TeammateColors, VisibleWeaponColorR);
      WritePair(TeammateColors, VisibleWeaponColorG);
      WritePair(TeammateColors, VisibleWeaponColorB);
      WritePair(TeammateColors, VisibleWeaponColorA);
      // Multiple
      WritePair(TeammateColors, LightWeaponColorR);
      WritePair(TeammateColors, LightWeaponColorG);
      WritePair(TeammateColors, LightWeaponColorB);
      WritePair(TeammateColors, LightWeaponColorA);
      WritePair(TeammateColors, HeavyWeaponColorR);
      WritePair(TeammateColors, HeavyWeaponColorG);
      WritePair(TeammateColors, HeavyWeaponColorB);
      WritePair(TeammateColors, HeavyWeaponColorA);
      WritePair(TeammateColors, EnergyWeaponColorR);
      WritePair(TeammateColors, EnergyWeaponColorG);
      WritePair(TeammateColors, EnergyWeaponColorB);
      WritePair(TeammateColors, EnergyWeaponColorA);
      WritePair(TeammateColors, ShotgunWeaponColorR);
      WritePair(TeammateColors, ShotgunWeaponColorG);
      WritePair(TeammateColors, ShotgunWeaponColorB);
      WritePair(TeammateColors, ShotgunWeaponColorA);
      WritePair(TeammateColors, SniperWeaponColorR);
      WritePair(TeammateColors, SniperWeaponColorG);
      WritePair(TeammateColors, SniperWeaponColorB);
      WritePair(TeammateColors, SniperWeaponColorA);
      WritePair(TeammateColors, LegendaryWeaponColorR);
      WritePair(TeammateColors, LegendaryWeaponColorG);
      WritePair(TeammateColors, LegendaryWeaponColorB);
      WritePair(TeammateColors, LegendaryWeaponColorA);
      WritePair(TeammateColors, MeleeWeaponColorR);
      WritePair(TeammateColors, MeleeWeaponColorG);
      WritePair(TeammateColors, MeleeWeaponColorB);
      WritePair(TeammateColors, MeleeWeaponColorA);
      WritePair(TeammateColors, ThrowableWeaponColorR);
      WritePair(TeammateColors, ThrowableWeaponColorG);
      WritePair(TeammateColors, ThrowableWeaponColorB);
      WritePair(TeammateColors, ThrowableWeaponColorA);

      WriteSectionEnd();

      WriteSection(Watermark);

      WritePair(Watermark, Enabled);
      WritePair(Watermark, WatermarkPosition);
      WritePair(Watermark, Name);
      WritePair(Watermark, ProcessingSpeed);
      WritePair(Watermark, Spectators);
      WritePair(Watermark, GameFPS);

      WriteSectionEnd();

      WriteSection(Settings);

      WritePair(Settings, ESPEnabled);
      WritePair(Settings, OverlayEnabled);
      WritePair(Settings, FPSCap);
      WritePair(Settings, CappedFPS);

      WriteSectionEnd();

      conf.close();
    }
  }

  void SaveConfig() {
    if (!Legitbot::Save())
      std::cout << "something went wrong trying to save Legitbot settings" << std::endl;
    if (!Triggerbot::Save())
      std::cout << "something went wrong trying to save Triggerbot settings" << std::endl;
    if (!Glow::Save())
      std::cout << "something went wrong trying to save Glow settings" << std::endl;
    if (!Sense::Save())
      std::cout << "something went wrong trying to save Sense/ESP settings" << std::endl;
    if (!Misc::Save())
      std::cout << "something went wrong trying to save Misc settings" << std::endl;
    if (!Radar::Save())
      std::cout << "something went wrong trying to save Radar settings" << std::endl;
    if (!SaveOtherSettings())
      std::cout << "something went wrong trying to save Other settings" << std::endl;
    UpdateConfig();
  }

  static bool SaveOtherSettings() {
    try {
      Config::Settings::ESPEnabled = Features::Settings::ESPEnabled;
      Config::Settings::OverlayEnabled = Features::Settings::OverlayEnabled;
      Config::Settings::FPSCap = Features::Settings::FPSCap;
      Config::Settings::CappedFPS = Features::Settings::CappedFPS;

      return true;
    } catch (...) { return false; }
  }

  void LoadConfig() {
    std::string ConfigName1 = "Configs/" + std::string(configName) + ".ini";
    if (ReadConfig())
      std::cout << tc::color<255, 190, 0> << " ⚡ " << tc::reset << ">> Loaded config " << configName << std::endl;
    else
      std::cout << tc::red << " ! " << tc::reset << " >> Failed to load config " << configName << ", created new one instead" << std::endl;

    Features::Aimbot::AimbotEnabled = Config::Aimbot::AimbotEnabled;
    Features::Aimbot::BindMethod = Config::Aimbot::BindMethod;
    Features::Aimbot::InputMethod = Config::Aimbot::InputMethod;
    Features::Aimbot::ClosestHitbox = Config::Aimbot::ClosestHitbox;
    Features::Aimbot::OnFire = Config::Aimbot::OnFire;
    Features::Aimbot::OnADS = Config::Aimbot::OnADS;
    Features::Aimbot::VisCheck = Config::Aimbot::VisCheck;
    Features::Aimbot::TeamCheck = Config::Aimbot::TeamCheck;
    Features::Aimbot::TargetSwitching = Config::Aimbot::TargetSwitching;
    Features::Aimbot::Priority = Config::Aimbot::Priority;
    Features::Aimbot::PredictMovement = Config::Aimbot::PredictMovement;
    Features::Aimbot::PredictBulletDrop = Config::Aimbot::PredictBulletDrop;
    Features::Aimbot::FinalDistance = Config::Aimbot::FinalDistance;
    Features::Aimbot::Smooth = Config::Aimbot::Smooth;
    Features::Aimbot::Speed = Config::Aimbot::Speed;
    Features::Aimbot::SmoothingMethod = Config::Aimbot::SmoothingMethod;
    Features::Aimbot::HipfireSmooth = Config::Aimbot::HipfireSmooth;
    Features::Aimbot::ADSSmooth = Config::Aimbot::ADSSmooth;
    Features::Aimbot::MinHipfireSmooth = Config::Aimbot::MinHipfireSmooth;
    Features::Aimbot::MaxHipfireSmooth = Config::Aimbot::MaxHipfireSmooth;
    Features::Aimbot::MinADSSmooth = Config::Aimbot::MinADSSmooth;
    Features::Aimbot::MaxADSSmooth = Config::Aimbot::MaxADSSmooth;
    // Aimbot 3 Testing
    Features::Aimbot::MouseHipfireSmoothing = Config::Aimbot::MouseHipfireSmoothing;
    Features::Aimbot::MouseADSSmoothing = Config::Aimbot::MouseADSSmoothing;
    Features::Aimbot::MouseExtraSmoothing = Config::Aimbot::MouseExtraSmoothing;
    Features::Aimbot::MinMouseHipfireSmoothing = Config::Aimbot::MinMouseHipfireSmoothing;
    Features::Aimbot::MaxMouseHipfireSmoothing = Config::Aimbot::MaxMouseHipfireSmoothing;
    Features::Aimbot::MinMouseADSSmoothing = Config::Aimbot::MinMouseADSSmoothing;
    Features::Aimbot::MaxMouseADSSmoothing = Config::Aimbot::MaxMouseADSSmoothing;

    Features::Aimbot::Delay = Config::Aimbot::Delay;
    Features::Aimbot::FOV = Config::Aimbot::FOV;
    Features::Aimbot::ZoomScale = Config::Aimbot::ZoomScale;
    Features::Aimbot::MinDistance = Config::Aimbot::MinDistance;
    Features::Aimbot::MaxDistance = Config::Aimbot::MaxDistance;
    Features::Aimbot::HipfireDistance = Config::Aimbot::HipfireDistance;
    Features::Aimbot::ZoomDistance = Config::Aimbot::ZoomDistance;
    // AimMode 2
    Features::Aimbot::HipfireSmooth1 = Config::Aimbot::HipfireSmooth1;
    Features::Aimbot::ADSSmooth1 = Config::Aimbot::ADSSmooth1;
    Features::Aimbot::ExtraSmoothing = Config::Aimbot::ExtraSmoothing;
    Features::Aimbot::Deadzone = Config::Aimbot::Deadzone;
    Features::Aimbot::FOV1 = Config::Aimbot::FOV1;
    // Weapon Toggles
    // Light
    Features::Aimbot::P2020 = Config::Aimbot::P2020;
    Features::Aimbot::RE45 = Config::Aimbot::RE45;
    Features::Aimbot::Alternator = Config::Aimbot::Alternator;
    Features::Aimbot::R99 = Config::Aimbot::R99;
    Features::Aimbot::R301 = Config::Aimbot::R301;
    Features::Aimbot::Spitfire = Config::Aimbot::Spitfire;
    Features::Aimbot::G7 = Config::Aimbot::G7;
    // Heavy
    Features::Aimbot::Flatline = Config::Aimbot::Flatline;
    Features::Aimbot::Hemlock = Config::Aimbot::Hemlock;
    Features::Aimbot::Repeater = Config::Aimbot::Repeater;
    Features::Aimbot::Rampage = Config::Aimbot::Rampage;
    Features::Aimbot::CARSMG = Config::Aimbot::CARSMG;
    // Energy
    Features::Aimbot::Havoc = Config::Aimbot::Havoc;
    Features::Aimbot::Devotion = Config::Aimbot::Devotion;
    Features::Aimbot::LSTAR = Config::Aimbot::LSTAR;
    Features::Aimbot::TripleTake = Config::Aimbot::TripleTake;
    Features::Aimbot::Volt = Config::Aimbot::Volt;
    Features::Aimbot::Nemesis = Config::Aimbot::Nemesis;
    // Shotgun
    Features::Aimbot::Mozambique = Config::Aimbot::Mozambique;
    Features::Aimbot::EVA8 = Config::Aimbot::EVA8;
    Features::Aimbot::Peacekeeper = Config::Aimbot::Peacekeeper;
    Features::Aimbot::Mastiff = Config::Aimbot::Mastiff;
    // Snipers
    Features::Aimbot::Longbow = Config::Aimbot::Longbow;
    Features::Aimbot::ChargeRifle = Config::Aimbot::ChargeRifle;
    Features::Aimbot::Sentinel = Config::Aimbot::Sentinel;
    // Legendary
    Features::Aimbot::Wingman = Config::Aimbot::Wingman;
    Features::Aimbot::Prowler = Config::Aimbot::Prowler;
    Features::Aimbot::Bocek = Config::Aimbot::Bocek;
    Features::Aimbot::Kraber = Config::Aimbot::Kraber;
    Features::Aimbot::Knife = Config::Aimbot::Knife;

    Features::AimbotBinds::AimBind = static_cast<InputKeyType>(Config::AimbotBinds::AimBind);
    Features::AimbotBinds::ExtraBind = static_cast<InputKeyType>(Config::AimbotBinds::ExtraBind);

    Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(Config::AimbotHitboxes::Hitbox);

    Features::RCS::RCSEnabled = Config::RCS::RCSEnabled;
    Features::RCS::RCSMode = Config::RCS::RCSMode;
    Features::RCS::OnADS = Config::RCS::OnADS;
    Features::RCS::PitchPower = Config::RCS::PitchPower;
    Features::RCS::YawPower = Config::RCS::YawPower;
    Features::RCS::PitchReduction = Config::RCS::PitchReduction;
    Features::RCS::YawReduction = Config::RCS::YawReduction;
    // Weapon Toggles
    // Light
    Features::RCS::P2020 = Config::RCS::P2020;
    Features::RCS::RE45 = Config::RCS::RE45;
    Features::RCS::Alternator = Config::RCS::Alternator;
    Features::RCS::R99 = Config::RCS::R99;
    Features::RCS::R301 = Config::RCS::R301;
    Features::RCS::Spitfire = Config::RCS::Spitfire;
    Features::RCS::G7 = Config::RCS::G7;
    // Heavy
    Features::RCS::Flatline = Config::RCS::Flatline;
    Features::RCS::Hemlock = Config::RCS::Hemlock;
    Features::RCS::Repeater = Config::RCS::Repeater;
    Features::RCS::Rampage = Config::RCS::Rampage;
    Features::RCS::CARSMG = Config::RCS::CARSMG;
    // Energy
    Features::RCS::Havoc = Config::RCS::Havoc;
    Features::RCS::Devotion = Config::RCS::Devotion;
    Features::RCS::LSTAR = Config::RCS::LSTAR;
    Features::RCS::TripleTake = Config::RCS::TripleTake;
    Features::RCS::Volt = Config::RCS::Volt;
    Features::RCS::Nemesis = Config::RCS::Nemesis;
    // Shotgun
    Features::RCS::Mozambique = Config::RCS::Mozambique;
    Features::RCS::EVA8 = Config::RCS::EVA8;
    Features::RCS::Peacekeeper = Config::RCS::Peacekeeper;
    Features::RCS::Mastiff = Config::RCS::Mastiff;
    // Snipers
    Features::RCS::Longbow = Config::RCS::Longbow;
    Features::RCS::ChargeRifle = Config::RCS::ChargeRifle;
    Features::RCS::Sentinel = Config::RCS::Sentinel;
    // Legendary
    Features::RCS::Wingman = Config::RCS::Wingman;
    Features::RCS::Prowler = Config::RCS::Prowler;
    Features::RCS::Kraber = Config::RCS::Kraber;
    // Advanced
    Features::RCS::AdvancedRCS = Config::RCS::AdvancedRCS;
    Features::RCS::AdvancedPitchPower = Config::RCS::AdvancedPitchPower;
    Features::RCS::AdvancedYawPower = Config::RCS::AdvancedYawPower;
    Features::RCS::AdvancedPitchReduction = Config::RCS::AdvancedPitchReduction;
    Features::RCS::AdvancedYawReduction = Config::RCS::AdvancedYawReduction;
    Features::RCS::P2020Pitch = Config::RCS::P2020Pitch;
    Features::RCS::P2020Yaw = Config::RCS::P2020Yaw;
    Features::RCS::P2020PitchReduction = Config::RCS::P2020PitchReduction;
    Features::RCS::P2020YawReduction = Config::RCS::P2020YawReduction;
    Features::RCS::RE45Pitch = Config::RCS::RE45Pitch;
    Features::RCS::RE45Yaw = Config::RCS::RE45Yaw;
    Features::RCS::RE45PitchReduction = Config::RCS::RE45PitchReduction;
    Features::RCS::RE45YawReduction = Config::RCS::RE45YawReduction;
    Features::RCS::AlternatorPitch = Config::RCS::AlternatorPitch;
    Features::RCS::AlternatorYaw = Config::RCS::AlternatorYaw;
    Features::RCS::AlternatorPitchReduction = Config::RCS::AlternatorPitchReduction;
    Features::RCS::AlternatorYawReduction = Config::RCS::AlternatorYawReduction;
    Features::RCS::R99Pitch = Config::RCS::R99Pitch;
    Features::RCS::R99Yaw = Config::RCS::R99Yaw;
    Features::RCS::R99PitchReduction = Config::RCS::R99PitchReduction;
    Features::RCS::R99YawReduction = Config::RCS::R99YawReduction;
    Features::RCS::R301Pitch = Config::RCS::R301Pitch;
    Features::RCS::R301Yaw = Config::RCS::R301Yaw;
    Features::RCS::R301PitchReduction = Config::RCS::R301PitchReduction;
    Features::RCS::R301YawReduction = Config::RCS::R301YawReduction;
    Features::RCS::SpitfirePitch = Config::RCS::SpitfirePitch;
    Features::RCS::SpitfireYaw = Config::RCS::SpitfireYaw;
    Features::RCS::SpitfirePitchReduction = Config::RCS::SpitfirePitchReduction;
    Features::RCS::SpitfireYawReduction = Config::RCS::SpitfireYawReduction;
    Features::RCS::G7Pitch = Config::RCS::G7Pitch;
    Features::RCS::G7Yaw = Config::RCS::G7Yaw;
    Features::RCS::G7PitchReduction = Config::RCS::G7PitchReduction;
    Features::RCS::G7YawReduction = Config::RCS::G7YawReduction;
    Features::RCS::FlatlinePitch = Config::RCS::FlatlinePitch;
    Features::RCS::FlatlineYaw = Config::RCS::FlatlineYaw;
    Features::RCS::FlatlinePitchReduction = Config::RCS::FlatlinePitchReduction;
    Features::RCS::FlatlineYawReduction = Config::RCS::FlatlineYawReduction;
    Features::RCS::HemlockPitch = Config::RCS::HemlockPitch;
    Features::RCS::HemlockYaw = Config::RCS::HemlockYaw;
    Features::RCS::HemlockPitchReduction = Config::RCS::HemlockPitchReduction;
    Features::RCS::HemlockYawReduction = Config::RCS::HemlockYawReduction;
    Features::RCS::ProwlerPitch = Config::RCS::ProwlerPitch;
    Features::RCS::ProwlerYaw = Config::RCS::ProwlerYaw;
    Features::RCS::ProwlerPitchReduction = Config::RCS::ProwlerPitchReduction;
    Features::RCS::ProwlerYawReduction = Config::RCS::ProwlerYawReduction;
    Features::RCS::RepeaterPitch = Config::RCS::RepeaterPitch;
    Features::RCS::RepeaterYaw = Config::RCS::RepeaterYaw;
    Features::RCS::RepeaterPitchReduction = Config::RCS::RepeaterPitchReduction;
    Features::RCS::RepeaterYawReduction = Config::RCS::RepeaterYawReduction;
    Features::RCS::RampagePitch = Config::RCS::RampagePitch;
    Features::RCS::RampageYaw = Config::RCS::RampageYaw;
    Features::RCS::RampagePitchReduction = Config::RCS::RampagePitchReduction;
    Features::RCS::RampageYawReduction = Config::RCS::RampageYawReduction;
    Features::RCS::CARSMGPitch = Config::RCS::CARSMGPitch;
    Features::RCS::CARSMGYaw = Config::RCS::CARSMGYaw;
    Features::RCS::CARSMGPitchReduction = Config::RCS::CARSMGPitchReduction;
    Features::RCS::CARSMGYawReduction = Config::RCS::CARSMGYawReduction;
    Features::RCS::HavocPitch = Config::RCS::HavocPitch;
    Features::RCS::HavocYaw = Config::RCS::HavocYaw;
    Features::RCS::HavocPitchReduction = Config::RCS::HavocPitchReduction;
    Features::RCS::HavocYawReduction = Config::RCS::HavocYawReduction;
    Features::RCS::DevotionPitch = Config::RCS::DevotionPitch;
    Features::RCS::DevotionYaw = Config::RCS::DevotionYaw;
    Features::RCS::DevotionPitchReduction = Config::RCS::DevotionPitchReduction;
    Features::RCS::DevotionYawReduction = Config::RCS::DevotionYawReduction;
    Features::RCS::LSTARPitch = Config::RCS::LSTARPitch;
    Features::RCS::LSTARYaw = Config::RCS::LSTARYaw;
    Features::RCS::LSTARPitchReduction = Config::RCS::LSTARPitchReduction;
    Features::RCS::LSTARYawReduction = Config::RCS::LSTARYawReduction;
    Features::RCS::TripleTakePitch = Config::RCS::TripleTakePitch;
    Features::RCS::TripleTakeYaw = Config::RCS::TripleTakeYaw;
    Features::RCS::TripleTakePitchReduction = Config::RCS::TripleTakePitchReduction;
    Features::RCS::TripleTakeYawReduction = Config::RCS::TripleTakeYawReduction;
    Features::RCS::VoltPitch = Config::RCS::VoltPitch;
    Features::RCS::VoltYaw = Config::RCS::VoltYaw;
    Features::RCS::VoltPitchReduction = Config::RCS::VoltPitchReduction;
    Features::RCS::VoltYawReduction = Config::RCS::VoltYawReduction;
    Features::RCS::NemesisPitch = Config::RCS::NemesisPitch;
    Features::RCS::NemesisYaw = Config::RCS::NemesisYaw;
    Features::RCS::NemesisPitchReduction = Config::RCS::NemesisPitchReduction;
    Features::RCS::NemesisYawReduction = Config::RCS::NemesisYawReduction;
    Features::RCS::MozambiquePitch = Config::RCS::MozambiquePitch;
    Features::RCS::MozambiqueYaw = Config::RCS::MozambiqueYaw;
    Features::RCS::MozambiquePitchReduction = Config::RCS::MozambiquePitchReduction;
    Features::RCS::MozambiqueYawReduction = Config::RCS::MozambiqueYawReduction;
    Features::RCS::PeacekeeperPitch = Config::RCS::PeacekeeperPitch;
    Features::RCS::PeacekeeperYaw = Config::RCS::PeacekeeperYaw;
    Features::RCS::PeacekeeperPitchReduction = Config::RCS::PeacekeeperPitchReduction;
    Features::RCS::PeacekeeperYawReduction = Config::RCS::PeacekeeperYawReduction;
    Features::RCS::MastiffPitch = Config::RCS::MastiffPitch;
    Features::RCS::MastiffYaw = Config::RCS::MastiffYaw;
    Features::RCS::MastiffPitchReduction = Config::RCS::MastiffPitchReduction;
    Features::RCS::MastiffYawReduction = Config::RCS::MastiffYawReduction;
    Features::RCS::LongbowPitch = Config::RCS::LongbowPitch;
    Features::RCS::LongbowYaw = Config::RCS::LongbowYaw;
    Features::RCS::LongbowPitchReduction = Config::RCS::LongbowPitchReduction;
    Features::RCS::LongbowYawReduction = Config::RCS::LongbowYawReduction;
    Features::RCS::ChargeRiflePitch = Config::RCS::ChargeRiflePitch;
    Features::RCS::ChargeRifleYaw = Config::RCS::ChargeRifleYaw;
    Features::RCS::ChargeRiflePitchReduction = Config::RCS::ChargeRiflePitchReduction;
    Features::RCS::ChargeRifleYawReduction = Config::RCS::ChargeRifleYawReduction;
    Features::RCS::SentinelPitch = Config::RCS::SentinelPitch;
    Features::RCS::SentinelYaw = Config::RCS::SentinelYaw;
    Features::RCS::SentinelPitchReduction = Config::RCS::SentinelPitchReduction;
    Features::RCS::SentinelYawReduction = Config::RCS::SentinelYawReduction;
    Features::RCS::WingmanPitch = Config::RCS::WingmanPitch;
    Features::RCS::WingmanYaw = Config::RCS::WingmanYaw;
    Features::RCS::WingmanPitchReduction = Config::RCS::WingmanPitchReduction;
    Features::RCS::WingmanYawReduction = Config::RCS::WingmanYawReduction;
    Features::RCS::EVA8Pitch = Config::RCS::EVA8Pitch;
    Features::RCS::EVA8Yaw = Config::RCS::EVA8Yaw;
    Features::RCS::EVA8PitchReduction = Config::RCS::EVA8PitchReduction;
    Features::RCS::EVA8YawReduction = Config::RCS::EVA8YawReduction;
    Features::RCS::KraberPitch = Config::RCS::KraberPitch;
    Features::RCS::KraberYaw = Config::RCS::KraberYaw;
    Features::RCS::KraberPitchReduction = Config::RCS::KraberPitchReduction;
    Features::RCS::KraberYawReduction = Config::RCS::KraberYawReduction;

    Features::Triggerbot::Enabled = Config::Triggerbot::Enabled;
    Features::Triggerbot::BindMethod = Config::Triggerbot::BindMethod;
    Features::Triggerbot::TriggerBind = static_cast<InputKeyType>(Config::Triggerbot::TriggerBind);
    Features::Triggerbot::OnADS = Config::Triggerbot::OnADS;
    Features::Triggerbot::HipfireShotguns = Config::Triggerbot::HipfireShotguns;
    Features::Triggerbot::Range = Config::Triggerbot::Range;
    Features::Triggerbot::RangeHipfire = Config::Triggerbot::RangeHipfire;
    // Weapon Toggles
    // Light
    Features::Triggerbot::P2020 = Config::Triggerbot::P2020;
    Features::Triggerbot::RE45 = Config::Triggerbot::RE45;
    Features::Triggerbot::Alternator = Config::Triggerbot::Alternator;
    Features::Triggerbot::R99 = Config::Triggerbot::R99;
    Features::Triggerbot::R301 = Config::Triggerbot::R301;
    Features::Triggerbot::Spitfire = Config::Triggerbot::Spitfire;
    Features::Triggerbot::G7 = Config::Triggerbot::G7;
    // Heavy
    Features::Triggerbot::Flatline = Config::Triggerbot::Flatline;
    Features::Triggerbot::Hemlock = Config::Triggerbot::Hemlock;
    Features::Triggerbot::Repeater = Config::Triggerbot::Repeater;
    Features::Triggerbot::Rampage = Config::Triggerbot::Rampage;
    Features::Triggerbot::CARSMG = Config::Triggerbot::CARSMG;
    // Energy
    Features::Triggerbot::Havoc = Config::Triggerbot::Havoc;
    Features::Triggerbot::Devotion = Config::Triggerbot::Devotion;
    Features::Triggerbot::LSTAR = Config::Triggerbot::LSTAR;
    Features::Triggerbot::TripleTake = Config::Triggerbot::TripleTake;
    Features::Triggerbot::Volt = Config::Triggerbot::Volt;
    Features::Triggerbot::Nemesis = Config::Triggerbot::Nemesis;
    // Shotgun
    Features::Triggerbot::Mozambique = Config::Triggerbot::Mozambique;
    Features::Triggerbot::EVA8 = Config::Triggerbot::EVA8;
    Features::Triggerbot::Peacekeeper = Config::Triggerbot::Peacekeeper;
    Features::Triggerbot::Mastiff = Config::Triggerbot::Mastiff;
    // Snipers
    Features::Triggerbot::Longbow = Config::Triggerbot::Longbow;
    Features::Triggerbot::ChargeRifle = Config::Triggerbot::ChargeRifle;
    Features::Triggerbot::Sentinel = Config::Triggerbot::Sentinel;
    // Legendary
    Features::Triggerbot::Wingman = Config::Triggerbot::Wingman;
    Features::Triggerbot::Prowler = Config::Triggerbot::Prowler;
    Features::Triggerbot::Bocek = Config::Triggerbot::Bocek;
    Features::Triggerbot::Kraber = Config::Triggerbot::Kraber;
    Features::Triggerbot::Knife = Config::Triggerbot::Knife;
    // Advanced
    Features::Triggerbot::AdvancedTriggerbot = Config::Triggerbot::AdvancedTriggerbot;
    Features::Triggerbot::P2020Range = Config::Triggerbot::P2020Range;
    Features::Triggerbot::RE45Range = Config::Triggerbot::RE45Range;
    Features::Triggerbot::AlternatorRange = Config::Triggerbot::AlternatorRange;
    Features::Triggerbot::R99Range = Config::Triggerbot::R99Range;
    Features::Triggerbot::R301Range = Config::Triggerbot::R301Range;
    Features::Triggerbot::SpitfireRange = Config::Triggerbot::SpitfireRange;
    Features::Triggerbot::G7Range = Config::Triggerbot::G7Range;
    Features::Triggerbot::FlatlineRange = Config::Triggerbot::FlatlineRange;
    Features::Triggerbot::HemlockRange = Config::Triggerbot::HemlockRange;
    Features::Triggerbot::ProwlerRange = Config::Triggerbot::ProwlerRange;
    Features::Triggerbot::RepeaterRange = Config::Triggerbot::RepeaterRange;
    Features::Triggerbot::RampageRange = Config::Triggerbot::RampageRange;
    Features::Triggerbot::CARSMGRange = Config::Triggerbot::CARSMGRange;
    Features::Triggerbot::HavocRange = Config::Triggerbot::HavocRange;
    Features::Triggerbot::DevotionRange = Config::Triggerbot::DevotionRange;
    Features::Triggerbot::LSTARRange = Config::Triggerbot::LSTARRange;
    Features::Triggerbot::TripleTakeRange = Config::Triggerbot::TripleTakeRange;
    Features::Triggerbot::VoltRange = Config::Triggerbot::VoltRange;
    Features::Triggerbot::NemesisRange = Config::Triggerbot::NemesisRange;
    Features::Triggerbot::LongbowRange = Config::Triggerbot::LongbowRange;
    Features::Triggerbot::ChargeRifleRange = Config::Triggerbot::ChargeRifleRange;
    Features::Triggerbot::SentinelRange = Config::Triggerbot::SentinelRange;
    Features::Triggerbot::MozambiqueRange = Config::Triggerbot::MozambiqueRange;
    Features::Triggerbot::PeacekeeperRange = Config::Triggerbot::PeacekeeperRange;
    Features::Triggerbot::MastiffRange = Config::Triggerbot::MastiffRange;
    Features::Triggerbot::LongbowRange = Config::Triggerbot::LongbowRange;
    Features::Triggerbot::ChargeRifleRange = Config::Triggerbot::ChargeRifleRange;
    Features::Triggerbot::SentinelRange = Config::Triggerbot::SentinelRange;
    Features::Triggerbot::WingmanRange = Config::Triggerbot::WingmanRange;
    Features::Triggerbot::EVA8Range = Config::Triggerbot::EVA8Range;
    Features::Triggerbot::KraberRange = Config::Triggerbot::KraberRange;
    Features::Triggerbot::BocekRange = Config::Triggerbot::BocekRange;
    Features::Triggerbot::ThrowingKnifeRange = Config::Triggerbot::ThrowingKnifeRange;

    Features::Glow::NewGlow = Config::Glow::NewGlow;
    Features::Glow::GlowMaxDistance = Config::Glow::GlowMaxDistance;
    Features::Glow::GlowColorMode = Config::Glow::GlowColorMode;
    Features::Glow::GlowColorShieldMode = Config::Glow::GlowColorShieldMode;
    Features::Glow::GlowRadius = Config::Glow::GlowRadius;
    Features::Glow::BodyStyle = Config::Glow::BodyStyle;
    Features::Glow::OutlineStyle = Config::Glow::OutlineStyle;
    Features::Glow::ViewModelGlow = Config::Glow::ViewModelGlow;
    Features::Glow::ViewModelGlowSetting = Config::Glow::ViewModelGlowSetting;
    Features::Glow::ViewModelGlowCombo = Config::Glow::ViewModelGlowCombo;

    Features::Glow::Item::ItemGlow = Config::ItemGlow::ItemGlow;
    Features::Glow::Item::SelectedItemSelection = Config::ItemGlow::SelectedItemSelection;
    Features::Glow::Item::Common = Config::ItemGlow::Common;
    Features::Glow::Item::Rare = Config::ItemGlow::Rare;
    Features::Glow::Item::Epic = Config::ItemGlow::Epic;
    Features::Glow::Item::Gold = Config::ItemGlow::Gold;
    Features::Glow::Item::Legendary = Config::ItemGlow::Legendary;
    Features::Glow::Item::Weapons = Config::ItemGlow::Weapons;
    Features::Glow::Item::Ammo = Config::ItemGlow::Ammo;
    Features::Glow::Item::ItemGlowThickness = Config::ItemGlow::ItemGlowThickness;
    Features::Glow::Item::SelectedInsideStyle = Config::ItemGlow::SelectedInsideStyle;
    Features::Glow::Item::SelectedOutlineStyle = Config::ItemGlow::SelectedOutlineStyle;

    Features::Sense::Enabled = Config::Sense::Enabled;
    Features::Sense::DrawFOVCircle = Config::Sense::DrawFOVCircle;
    Features::Sense::DrawFilledFOVCircle = Config::Sense::DrawFilledFOVCircle;
    Features::Sense::FOVThickness = Config::Sense::FOVThickness;
    Features::Sense::GameFOV = Config::Sense::GameFOV;
    Features::Sense::DrawCrosshair = Config::Sense::DrawCrosshair;
    Features::Sense::CrosshairSize = Config::Sense::CrosshairSize;
    Features::Sense::CrosshairThickness = Config::Sense::CrosshairThickness;
    Features::Sense::ShowSpectators = Config::Sense::ShowSpectators;
    Features::Sense::DrawSpectatorWarning = Config::Sense::DrawSpectatorWarning;
    Features::Sense::DrawVisibleWarning = Config::Sense::DrawVisibleWarning;
    Features::Sense::WarningTextOutline = Config::Sense::WarningTextOutline;
    Features::Sense::WarningTextX = Config::Sense::WarningTextX;
    Features::Sense::WarningTextY = Config::Sense::WarningTextY;
    Features::Sense::TextOutline = Config::Sense::TextOutline;
    Features::Sense::VisibilityCheck = Config::Sense::VisibilityCheck;
    Features::Sense::ESPMaxDistance = Config::Sense::ESPMaxDistance;

    Features::Sense::Enemy::DrawEnemy = Config::SenseEnemy::DrawEnemy;
    Features::Sense::Enemy::DrawBoxes = Config::SenseEnemy::DrawBoxes;
    Features::Sense::Enemy::BoxType = Config::SenseEnemy::BoxType;
    Features::Sense::Enemy::BoxStyle = Config::SenseEnemy::BoxStyle;
    Features::Sense::Enemy::BoxThickness = Config::SenseEnemy::BoxThickness;
    Features::Sense::Enemy::DrawSkeleton = Config::SenseEnemy::DrawSkeleton;
    Features::Sense::Enemy::SkeletonThickness = Config::SenseEnemy::SkeletonThickness;
    Features::Sense::Enemy::DrawHeadCircle = Config::SenseEnemy::DrawHeadCircle;
    Features::Sense::Enemy::HeadCircleThickness = Config::SenseEnemy::HeadCircleThickness;
    Features::Sense::Enemy::DrawBars = Config::SenseEnemy::DrawBars;
    Features::Sense::Enemy::HealthBar = Config::SenseEnemy::HealthBar;
    Features::Sense::Enemy::ShieldBar = Config::SenseEnemy::ShieldBar;
    Features::Sense::Enemy::BarMode = Config::SenseEnemy::BarMode;
    Features::Sense::Enemy::BarStyle = Config::SenseEnemy::BarStyle;
    Features::Sense::Enemy::BarThickness = Config::SenseEnemy::BarThickness;
    Features::Sense::Enemy::BarThickness2 = Config::SenseEnemy::BarThickness2;
    Features::Sense::Enemy::BarHeight = Config::SenseEnemy::BarHeight;
    Features::Sense::Enemy::BarWidth = Config::SenseEnemy::BarWidth;
    Features::Sense::Enemy::BarColorMode = Config::SenseEnemy::BarColorMode;
    Features::Sense::Enemy::WeaponColorType = Config::SenseEnemy::WeaponColorType;
    Features::Sense::Enemy::DrawDistance = Config::SenseEnemy::DrawDistance;
    Features::Sense::Enemy::TracerPosition = Config::SenseEnemy::TracerPosition;
    Features::Sense::Enemy::TracerBone = Config::SenseEnemy::TracerBone;
    Features::Sense::Enemy::DrawTracers = Config::SenseEnemy::DrawTracers;
    Features::Sense::Enemy::TracerThickness = Config::SenseEnemy::TracerThickness;
    Features::Sense::Enemy::DrawNames = Config::SenseEnemy::DrawNames;
    Features::Sense::Enemy::DrawStatus = Config::SenseEnemy::DrawStatus;
    Features::Sense::Enemy::ShowMaxStatusValues = Config::SenseEnemy::ShowMaxStatusValues;
    Features::Sense::Enemy::DrawWeapon = Config::SenseEnemy::DrawWeapon;
    Features::Sense::Enemy::DrawLegend = Config::SenseEnemy::DrawLegend;

    Features::Sense::Teammate::DrawTeam = Config::SenseTeammate::DrawTeam;
    Features::Sense::Teammate::DrawBoxes = Config::SenseTeammate::DrawBoxes;
    Features::Sense::Teammate::BoxType = Config::SenseTeammate::BoxType;
    Features::Sense::Teammate::BoxStyle = Config::SenseTeammate::BoxStyle;
    Features::Sense::Teammate::BoxThickness = Config::SenseTeammate::BoxThickness;
    Features::Sense::Teammate::DrawSkeleton = Config::SenseTeammate::DrawSkeleton;
    Features::Sense::Teammate::SkeletonThickness = Config::SenseTeammate::SkeletonThickness;
    Features::Sense::Teammate::DrawHeadCircle = Config::SenseTeammate::DrawHeadCircle;
    Features::Sense::Teammate::HeadCircleThickness = Config::SenseTeammate::HeadCircleThickness;
    Features::Sense::Teammate::DrawBars = Config::SenseTeammate::DrawBars;
    Features::Sense::Teammate::HealthBar = Config::SenseTeammate::HealthBar;
    Features::Sense::Teammate::ShieldBar = Config::SenseTeammate::ShieldBar;
    Features::Sense::Teammate::BarMode = Config::SenseTeammate::BarMode;
    Features::Sense::Teammate::BarStyle = Config::SenseTeammate::BarStyle;
    Features::Sense::Teammate::BarThickness = Config::SenseTeammate::BarThickness;
    Features::Sense::Teammate::BarThickness2 = Config::SenseTeammate::BarThickness2;
    Features::Sense::Teammate::BarHeight = Config::SenseTeammate::BarHeight;
    Features::Sense::Teammate::BarWidth = Config::SenseTeammate::BarWidth;
    Features::Sense::Teammate::BarColorMode = Config::SenseTeammate::BarColorMode;
    Features::Sense::Teammate::WeaponColorType = Config::SenseTeammate::WeaponColorType;
    Features::Sense::Teammate::DrawDistance = Config::SenseTeammate::DrawDistance;
    Features::Sense::Teammate::TracerPosition = Config::SenseTeammate::TracerPosition;
    Features::Sense::Teammate::TracerBone = Config::SenseTeammate::TracerBone;
    Features::Sense::Teammate::DrawTracers = Config::SenseTeammate::DrawTracers;
    Features::Sense::Teammate::TracerThickness = Config::SenseTeammate::TracerThickness;
    Features::Sense::Teammate::DrawNames = Config::SenseTeammate::DrawNames;
    Features::Sense::Teammate::DrawStatus = Config::SenseTeammate::DrawStatus;
    Features::Sense::Teammate::ShowMaxStatusValues = Config::SenseTeammate::ShowMaxStatusValues;
    Features::Sense::Teammate::DrawWeapon = Config::SenseTeammate::DrawWeapon;
    Features::Sense::Teammate::DrawLegend = Config::SenseTeammate::DrawLegend;

    Features::Sense::Positions::NamePosition = Config::SensePositions::NamePosition;
    Features::Sense::Positions::DistancePosition = Config::SensePositions::DistancePosition;
    Features::Sense::Positions::LegendPosition = Config::SensePositions::LegendPosition;
    Features::Sense::Positions::WeaponPosition = Config::SensePositions::WeaponPosition;
    Features::Sense::Positions::StatusPosition = Config::SensePositions::StatusPosition;

    Features::Radar::MiniMap = Config::Radar::MiniMap;
    Features::Radar::MiniMapRange = Config::Radar::MiniMapRange;
    Features::Radar::MiniMapScaleX = Config::Radar::MiniMapScaleX;
    Features::Radar::MiniMapScaleY = Config::Radar::MiniMapScaleY;
    Features::Radar::MiniMapDotSize = Config::Radar::MiniMapDotSize;
    Features::Radar::MiniMapBlackBGSize = Config::Radar::MiniMapBlackBGSize;
    Features::Radar::MiniMapGuides = Config::Radar::MiniMapGuides;
    Features::Radar::BigMap = Config::Radar::BigMap;
    Features::Radar::BigMapBind = static_cast<InputKeyType>(Config::Radar::BigMapBind);
    Features::Radar::CircleColor[0] = Config::Radar::CircleColorR;
    Features::Radar::CircleColor[1] = Config::Radar::CircleColorG;
    Features::Radar::CircleColor[2] = Config::Radar::CircleColorB;
    Features::Radar::CircleColor[3] = Config::Radar::CircleColorA;

    Features::Misc::SuperGlide = Config::Misc::SuperGlide;
    Features::Misc::SuperGlideMode = Config::Misc::SuperGlideMode;
    Features::Misc::SuperGlideFPS = Config::Misc::SuperGlideFPS;
    Features::Misc::QuickTurn = Config::Misc::QuickTurn;
    Features::Misc::QuickTurnAngle = Config::Misc::QuickTurnAngle;
    Features::Misc::QuickTurnBind = static_cast<InputKeyType>(Config::Misc::QuickTurnBind);
    Features::Misc::BHop = Config::Misc::BHop;
    Features::Misc::BHopDelay = Config::Misc::BHopDelay;
    Features::Misc::BHopBind = static_cast<InputKeyType>(Config::Misc::BHopBind);
    Features::Misc::RapidFire = Config::Misc::RapidFire;
    Features::Misc::RapidFireDelay = Config::Misc::RapidFireDelay;
    Features::Misc::RapidFireBind = static_cast<InputKeyType>(Config::Misc::RapidFireBind);

    Features::Misc::RapidP2020 = Config::Misc::RapidP2020;
    Features::Misc::RapidR301 = Config::Misc::RapidR301;
    Features::Misc::RapidG7 = Config::Misc::RapidG7;
    Features::Misc::RapidFlatline = Config::Misc::RapidFlatline;
    Features::Misc::RapidHemlock = Config::Misc::RapidHemlock;
    Features::Misc::RapidProwler = Config::Misc::RapidProwler;
    Features::Misc::RapidNemesis = Config::Misc::RapidNemesis;
    Features::Misc::RapidMozambique = Config::Misc::RapidMozambique;
    Features::Misc::RapidEVA8 = Config::Misc::RapidEVA8;
    Features::Misc::RapidWingman = Config::Misc::RapidWingman;
    Features::Misc::SkinChanger = Config::Misc::SkinChanger;
    // Weapons //
    Features::Misc::SkinP2020 = Config::Misc::SkinP2020;
    Features::Misc::SkinRE45 = Config::Misc::SkinRE45;
    Features::Misc::SkinALTERNATOR = Config::Misc::SkinALTERNATOR;
    Features::Misc::SkinR99 = Config::Misc::SkinR99;
    Features::Misc::SkinR301 = Config::Misc::SkinR301;
    Features::Misc::SkinSPITFIRE = Config::Misc::SkinSPITFIRE;
    Features::Misc::SkinG7 = Config::Misc::SkinG7;
    Features::Misc::SkinFLATLINE = Config::Misc::SkinFLATLINE;
    Features::Misc::SkinHEMLOCK = Config::Misc::SkinHEMLOCK;
    Features::Misc::SkinREPEATER = Config::Misc::SkinREPEATER;
    Features::Misc::SkinRAMPAGE = Config::Misc::SkinRAMPAGE;
    Features::Misc::SkinCAR = Config::Misc::SkinCAR;
    Features::Misc::SkinHAVOC = Config::Misc::SkinHAVOC;
    Features::Misc::SkinDEVOTION = Config::Misc::SkinDEVOTION;
    Features::Misc::SkinLSTAR = Config::Misc::SkinLSTAR;
    Features::Misc::SkinTRIPLETAKE = Config::Misc::SkinTRIPLETAKE;
    Features::Misc::SkinVOLT = Config::Misc::SkinVOLT;
    Features::Misc::SkinNEMESIS = Config::Misc::SkinNEMESIS;
    Features::Misc::SkinMOZAMBIQUE = Config::Misc::SkinMOZAMBIQUE;
    Features::Misc::SkinEVA8 = Config::Misc::SkinEVA8;
    Features::Misc::SkinPEACEKEEPER = Config::Misc::SkinPEACEKEEPER;
    Features::Misc::SkinMASTIFF = Config::Misc::SkinMASTIFF;
    Features::Misc::SkinLONGBOW = Config::Misc::SkinLONGBOW;
    Features::Misc::SkinCHARGE_RIFLE = Config::Misc::SkinCHARGE_RIFLE;
    Features::Misc::SkinSENTINEL = Config::Misc::SkinSENTINEL;
    Features::Misc::SkinWINGMAN = Config::Misc::SkinWINGMAN;
    Features::Misc::SkinPROWLER = Config::Misc::SkinPROWLER;
    Features::Misc::SkinBOCEK = Config::Misc::SkinBOCEK;
    Features::Misc::SkinKRABER = Config::Misc::SkinKRABER;

    Features::Colors::WeaponColorMode = Config::Colors::WeaponColorMode;
    Features::Colors::FOVColor[0] = Config::Colors::FOVColorR;
    Features::Colors::FOVColor[1] = Config::Colors::FOVColorG;
    Features::Colors::FOVColor[2] = Config::Colors::FOVColorB;
    Features::Colors::FOVColor[3] = Config::Colors::FOVColorA;
    Features::Colors::FilledFOVColor[0] = Config::Colors::FilledFOVColorR;
    Features::Colors::FilledFOVColor[1] = Config::Colors::FilledFOVColorG;
    Features::Colors::FilledFOVColor[2] = Config::Colors::FilledFOVColorB;
    Features::Colors::FilledFOVColor[3] = Config::Colors::FilledFOVColorA;
    Features::Colors::CrosshairColor[0] = Config::Colors::CrosshairColorR;
    Features::Colors::CrosshairColor[1] = Config::Colors::CrosshairColorG;
    Features::Colors::CrosshairColor[2] = Config::Colors::CrosshairColorB;
    Features::Colors::CrosshairColor[3] = Config::Colors::CrosshairColorA;
    Features::Colors::SpectatorWarningColor[0] = Config::Colors::SpectatorWarningColorR;
    Features::Colors::SpectatorWarningColor[1] = Config::Colors::SpectatorWarningColorG;
    Features::Colors::SpectatorWarningColor[2] = Config::Colors::SpectatorWarningColorB;
    Features::Colors::SpectatorWarningColor[3] = Config::Colors::SpectatorWarningColorA;
    Features::Colors::VisibleWarningColor[0] = Config::Colors::VisibleWarningColorR;
    Features::Colors::VisibleWarningColor[1] = Config::Colors::VisibleWarningColorG;
    Features::Colors::VisibleWarningColor[2] = Config::Colors::VisibleWarningColorB;
    Features::Colors::VisibleWarningColor[3] = Config::Colors::VisibleWarningColorA;

    Features::Colors::Enemy::InvisibleBoxColor[0] = Config::EnemyColors::InvisibleBoxColorR;
    Features::Colors::Enemy::InvisibleBoxColor[1] = Config::EnemyColors::InvisibleBoxColorG;
    Features::Colors::Enemy::InvisibleBoxColor[2] = Config::EnemyColors::InvisibleBoxColorB;
    Features::Colors::Enemy::InvisibleBoxColor[3] = Config::EnemyColors::InvisibleBoxColorA;
    Features::Colors::Enemy::VisibleBoxColor[0] = Config::EnemyColors::VisibleBoxColorR;
    Features::Colors::Enemy::VisibleBoxColor[1] = Config::EnemyColors::VisibleBoxColorG;
    Features::Colors::Enemy::VisibleBoxColor[2] = Config::EnemyColors::VisibleBoxColorB;
    Features::Colors::Enemy::VisibleBoxColor[3] = Config::EnemyColors::VisibleBoxColorA;
    Features::Colors::Enemy::InvisibleFilledBoxColor[0] = Config::EnemyColors::InvisibleFilledBoxColorR;
    Features::Colors::Enemy::InvisibleFilledBoxColor[1] = Config::EnemyColors::InvisibleFilledBoxColorG;
    Features::Colors::Enemy::InvisibleFilledBoxColor[2] = Config::EnemyColors::InvisibleFilledBoxColorB;
    Features::Colors::Enemy::InvisibleFilledBoxColor[3] = Config::EnemyColors::InvisibleFilledBoxColorA;
    Features::Colors::Enemy::VisibleFilledBoxColor[0] = Config::EnemyColors::VisibleFilledBoxColorR;
    Features::Colors::Enemy::VisibleFilledBoxColor[1] = Config::EnemyColors::VisibleFilledBoxColorG;
    Features::Colors::Enemy::VisibleFilledBoxColor[2] = Config::EnemyColors::VisibleFilledBoxColorB;
    Features::Colors::Enemy::VisibleFilledBoxColor[3] = Config::EnemyColors::VisibleFilledBoxColorA;
    Features::Colors::Enemy::InvisibleTracerColor[0] = Config::EnemyColors::InvisibleTracerColorR;
    Features::Colors::Enemy::InvisibleTracerColor[1] = Config::EnemyColors::InvisibleTracerColorG;
    Features::Colors::Enemy::InvisibleTracerColor[2] = Config::EnemyColors::InvisibleTracerColorB;
    Features::Colors::Enemy::InvisibleTracerColor[3] = Config::EnemyColors::InvisibleTracerColorA;
    Features::Colors::Enemy::VisibleTracerColor[0] = Config::EnemyColors::VisibleTracerColorR;
    Features::Colors::Enemy::VisibleTracerColor[1] = Config::EnemyColors::VisibleTracerColorG;
    Features::Colors::Enemy::VisibleTracerColor[2] = Config::EnemyColors::VisibleTracerColorB;
    Features::Colors::Enemy::VisibleTracerColor[3] = Config::EnemyColors::VisibleTracerColorA;
    Features::Colors::Enemy::InvisibleSkeletonColor[0] = Config::EnemyColors::InvisibleSkeletonColorR;
    Features::Colors::Enemy::InvisibleSkeletonColor[1] = Config::EnemyColors::InvisibleSkeletonColorG;
    Features::Colors::Enemy::InvisibleSkeletonColor[2] = Config::EnemyColors::InvisibleSkeletonColorB;
    Features::Colors::Enemy::InvisibleSkeletonColor[3] = Config::EnemyColors::InvisibleSkeletonColorA;
    Features::Colors::Enemy::VisibleSkeletonColor[0] = Config::EnemyColors::VisibleSkeletonColorR;
    Features::Colors::Enemy::VisibleSkeletonColor[1] = Config::EnemyColors::VisibleSkeletonColorG;
    Features::Colors::Enemy::VisibleSkeletonColor[2] = Config::EnemyColors::VisibleSkeletonColorB;
    Features::Colors::Enemy::VisibleSkeletonColor[3] = Config::EnemyColors::VisibleSkeletonColorA;
    Features::Colors::Enemy::InvisibleHeadCircleColor[0] = Config::EnemyColors::InvisibleHeadCircleColorR;
    Features::Colors::Enemy::InvisibleHeadCircleColor[1] = Config::EnemyColors::InvisibleHeadCircleColorG;
    Features::Colors::Enemy::InvisibleHeadCircleColor[2] = Config::EnemyColors::InvisibleHeadCircleColorB;
    Features::Colors::Enemy::InvisibleHeadCircleColor[3] = Config::EnemyColors::InvisibleHeadCircleColorA;
    Features::Colors::Enemy::VisibleHeadCircleColor[0] = Config::EnemyColors::VisibleHeadCircleColorR;
    Features::Colors::Enemy::VisibleHeadCircleColor[1] = Config::EnemyColors::VisibleHeadCircleColorG;
    Features::Colors::Enemy::VisibleHeadCircleColor[2] = Config::EnemyColors::VisibleHeadCircleColorB;
    Features::Colors::Enemy::VisibleHeadCircleColor[3] = Config::EnemyColors::VisibleHeadCircleColorA;
    Features::Colors::Enemy::InvisibleNameColor[0] = Config::EnemyColors::InvisibleNameColorR;
    Features::Colors::Enemy::InvisibleNameColor[1] = Config::EnemyColors::InvisibleNameColorG;
    Features::Colors::Enemy::InvisibleNameColor[2] = Config::EnemyColors::InvisibleNameColorB;
    Features::Colors::Enemy::InvisibleNameColor[3] = Config::EnemyColors::InvisibleNameColorA;
    Features::Colors::Enemy::VisibleNameColor[0] = Config::EnemyColors::VisibleNameColorR;
    Features::Colors::Enemy::VisibleNameColor[1] = Config::EnemyColors::VisibleNameColorG;
    Features::Colors::Enemy::VisibleNameColor[2] = Config::EnemyColors::VisibleNameColorB;
    Features::Colors::Enemy::VisibleNameColor[3] = Config::EnemyColors::VisibleNameColorA;
    Features::Colors::Enemy::InvisibleDistanceColor[0] = Config::EnemyColors::InvisibleDistanceColorR;
    Features::Colors::Enemy::InvisibleDistanceColor[1] = Config::EnemyColors::InvisibleDistanceColorG;
    Features::Colors::Enemy::InvisibleDistanceColor[2] = Config::EnemyColors::InvisibleDistanceColorB;
    Features::Colors::Enemy::InvisibleDistanceColor[3] = Config::EnemyColors::InvisibleDistanceColorA;
    Features::Colors::Enemy::VisibleDistanceColor[0] = Config::EnemyColors::VisibleDistanceColorR;
    Features::Colors::Enemy::VisibleDistanceColor[1] = Config::EnemyColors::VisibleDistanceColorG;
    Features::Colors::Enemy::VisibleDistanceColor[2] = Config::EnemyColors::VisibleDistanceColorB;
    Features::Colors::Enemy::VisibleDistanceColor[3] = Config::EnemyColors::VisibleDistanceColorA;
    Features::Colors::Enemy::InvisibleLegendColor[0] = Config::EnemyColors::InvisibleLegendColorR;
    Features::Colors::Enemy::InvisibleLegendColor[1] = Config::EnemyColors::InvisibleLegendColorG;
    Features::Colors::Enemy::InvisibleLegendColor[2] = Config::EnemyColors::InvisibleLegendColorB;
    Features::Colors::Enemy::InvisibleLegendColor[3] = Config::EnemyColors::InvisibleLegendColorA;
    Features::Colors::Enemy::VisibleLegendColor[0] = Config::EnemyColors::VisibleLegendColorR;
    Features::Colors::Enemy::VisibleLegendColor[1] = Config::EnemyColors::VisibleLegendColorG;
    Features::Colors::Enemy::VisibleLegendColor[2] = Config::EnemyColors::VisibleLegendColorB;
    Features::Colors::Enemy::VisibleLegendColor[3] = Config::EnemyColors::VisibleLegendColorA;
    Features::Colors::Enemy::InvisibleWeaponColor[0] = Config::EnemyColors::InvisibleWeaponColorR;
    Features::Colors::Enemy::InvisibleWeaponColor[1] = Config::EnemyColors::InvisibleWeaponColorG;
    Features::Colors::Enemy::InvisibleWeaponColor[2] = Config::EnemyColors::InvisibleWeaponColorB;
    Features::Colors::Enemy::InvisibleWeaponColor[3] = Config::EnemyColors::InvisibleWeaponColorA;
    Features::Colors::Enemy::VisibleWeaponColor[0] = Config::EnemyColors::VisibleWeaponColorR;
    Features::Colors::Enemy::VisibleWeaponColor[1] = Config::EnemyColors::VisibleWeaponColorG;
    Features::Colors::Enemy::VisibleWeaponColor[2] = Config::EnemyColors::VisibleWeaponColorB;
    Features::Colors::Enemy::VisibleWeaponColor[3] = Config::EnemyColors::VisibleWeaponColorA;
    Features::Colors::Enemy::BarColorMode = Config::EnemyColors::BarColorMode;
    Features::Colors::Enemy::LightWeaponColor[0] = Config::EnemyColors::LightWeaponColorR;
    Features::Colors::Enemy::LightWeaponColor[1] = Config::EnemyColors::LightWeaponColorG;
    Features::Colors::Enemy::LightWeaponColor[2] = Config::EnemyColors::LightWeaponColorB;
    Features::Colors::Enemy::LightWeaponColor[3] = Config::EnemyColors::LightWeaponColorA;
    Features::Colors::Enemy::HeavyWeaponColor[0] = Config::EnemyColors::HeavyWeaponColorR;
    Features::Colors::Enemy::HeavyWeaponColor[1] = Config::EnemyColors::HeavyWeaponColorG;
    Features::Colors::Enemy::HeavyWeaponColor[2] = Config::EnemyColors::HeavyWeaponColorB;
    Features::Colors::Enemy::HeavyWeaponColor[3] = Config::EnemyColors::HeavyWeaponColorA;
    Features::Colors::Enemy::EnergyWeaponColor[0] = Config::EnemyColors::EnergyWeaponColorR;
    Features::Colors::Enemy::EnergyWeaponColor[1] = Config::EnemyColors::EnergyWeaponColorG;
    Features::Colors::Enemy::EnergyWeaponColor[2] = Config::EnemyColors::EnergyWeaponColorB;
    Features::Colors::Enemy::EnergyWeaponColor[3] = Config::EnemyColors::EnergyWeaponColorA;
    Features::Colors::Enemy::ShotgunWeaponColor[0] = Config::EnemyColors::ShotgunWeaponColorR;
    Features::Colors::Enemy::ShotgunWeaponColor[1] = Config::EnemyColors::ShotgunWeaponColorG;
    Features::Colors::Enemy::ShotgunWeaponColor[2] = Config::EnemyColors::ShotgunWeaponColorB;
    Features::Colors::Enemy::ShotgunWeaponColor[3] = Config::EnemyColors::ShotgunWeaponColorA;
    Features::Colors::Enemy::SniperWeaponColor[0] = Config::EnemyColors::SniperWeaponColorR;
    Features::Colors::Enemy::SniperWeaponColor[1] = Config::EnemyColors::SniperWeaponColorG;
    Features::Colors::Enemy::SniperWeaponColor[2] = Config::EnemyColors::SniperWeaponColorB;
    Features::Colors::Enemy::SniperWeaponColor[3] = Config::EnemyColors::SniperWeaponColorA;
    Features::Colors::Enemy::LegendaryWeaponColor[0] = Config::EnemyColors::LegendaryWeaponColorR;
    Features::Colors::Enemy::LegendaryWeaponColor[1] = Config::EnemyColors::LegendaryWeaponColorG;
    Features::Colors::Enemy::LegendaryWeaponColor[2] = Config::EnemyColors::LegendaryWeaponColorB;
    Features::Colors::Enemy::LegendaryWeaponColor[3] = Config::EnemyColors::LegendaryWeaponColorA;
    Features::Colors::Enemy::MeleeWeaponColor[0] = Config::EnemyColors::MeleeWeaponColorR;
    Features::Colors::Enemy::MeleeWeaponColor[1] = Config::EnemyColors::MeleeWeaponColorG;
    Features::Colors::Enemy::MeleeWeaponColor[2] = Config::EnemyColors::MeleeWeaponColorB;
    Features::Colors::Enemy::MeleeWeaponColor[3] = Config::EnemyColors::MeleeWeaponColorA;
    Features::Colors::Enemy::ThrowableWeaponColor[0] = Config::EnemyColors::ThrowableWeaponColorR;
    Features::Colors::Enemy::ThrowableWeaponColor[1] = Config::EnemyColors::ThrowableWeaponColorG;
    Features::Colors::Enemy::ThrowableWeaponColor[2] = Config::EnemyColors::ThrowableWeaponColorB;
    Features::Colors::Enemy::ThrowableWeaponColor[3] = Config::EnemyColors::ThrowableWeaponColorA;
    Features::Colors::Enemy::InvisibleGlowColor[0] = Config::EnemyColors::InvisibleGlowColorR;
    Features::Colors::Enemy::InvisibleGlowColor[1] = Config::EnemyColors::InvisibleGlowColorG;
    Features::Colors::Enemy::InvisibleGlowColor[2] = Config::EnemyColors::InvisibleGlowColorB;
    Features::Colors::Enemy::VisibleGlowColor[0] = Config::EnemyColors::VisibleGlowColorR;
    Features::Colors::Enemy::VisibleGlowColor[1] = Config::EnemyColors::VisibleGlowColorG;
    Features::Colors::Enemy::VisibleGlowColor[2] = Config::EnemyColors::VisibleGlowColorB;
    Features::Colors::Enemy::RedShieldColor[0] = Config::EnemyColors::RedShieldColorR;
    Features::Colors::Enemy::RedShieldColor[1] = Config::EnemyColors::RedShieldColorG;
    Features::Colors::Enemy::RedShieldColor[2] = Config::EnemyColors::RedShieldColorR;
    Features::Colors::Enemy::PurpleShieldColor[0] = Config::EnemyColors::PurpleShieldColorR;
    Features::Colors::Enemy::PurpleShieldColor[1] = Config::EnemyColors::PurpleShieldColorG;
    Features::Colors::Enemy::PurpleShieldColor[2] = Config::EnemyColors::PurpleShieldColorB;
    Features::Colors::Enemy::BlueShieldColor[0] = Config::EnemyColors::BlueShieldColorR;
    Features::Colors::Enemy::BlueShieldColor[1] = Config::EnemyColors::BlueShieldColorG;
    Features::Colors::Enemy::BlueShieldColor[2] = Config::EnemyColors::BlueShieldColorB;
    Features::Colors::Enemy::GreyShieldColor[0] = Config::EnemyColors::GreyShieldColorR;
    Features::Colors::Enemy::GreyShieldColor[1] = Config::EnemyColors::GreyShieldColorG;
    Features::Colors::Enemy::GreyShieldColor[2] = Config::EnemyColors::GreyShieldColorB;

    Features::Colors::Teammate::InvisibleBoxColor[0] = Config::TeammateColors::InvisibleBoxColorR;
    Features::Colors::Teammate::InvisibleBoxColor[1] = Config::TeammateColors::InvisibleBoxColorG;
    Features::Colors::Teammate::InvisibleBoxColor[2] = Config::TeammateColors::InvisibleBoxColorB;
    Features::Colors::Teammate::InvisibleBoxColor[3] = Config::TeammateColors::InvisibleBoxColorA;
    Features::Colors::Teammate::VisibleBoxColor[0] = Config::TeammateColors::VisibleBoxColorR;
    Features::Colors::Teammate::VisibleBoxColor[1] = Config::TeammateColors::VisibleBoxColorG;
    Features::Colors::Teammate::VisibleBoxColor[2] = Config::TeammateColors::VisibleBoxColorB;
    Features::Colors::Teammate::VisibleBoxColor[3] = Config::TeammateColors::VisibleBoxColorA;
    Features::Colors::Teammate::InvisibleFilledBoxColor[0] = Config::TeammateColors::InvisibleFilledBoxColorR;
    Features::Colors::Teammate::InvisibleFilledBoxColor[1] = Config::TeammateColors::InvisibleFilledBoxColorG;
    Features::Colors::Teammate::InvisibleFilledBoxColor[2] = Config::TeammateColors::InvisibleFilledBoxColorB;
    Features::Colors::Teammate::InvisibleFilledBoxColor[3] = Config::TeammateColors::InvisibleFilledBoxColorA;
    Features::Colors::Teammate::VisibleFilledBoxColor[0] = Config::TeammateColors::VisibleFilledBoxColorR;
    Features::Colors::Teammate::VisibleFilledBoxColor[1] = Config::TeammateColors::VisibleFilledBoxColorG;
    Features::Colors::Teammate::VisibleFilledBoxColor[2] = Config::TeammateColors::VisibleFilledBoxColorB;
    Features::Colors::Teammate::VisibleFilledBoxColor[3] = Config::TeammateColors::VisibleFilledBoxColorA;
    Features::Colors::Teammate::InvisibleTracerColor[0] = Config::TeammateColors::InvisibleTracerColorR;
    Features::Colors::Teammate::InvisibleTracerColor[1] = Config::TeammateColors::InvisibleTracerColorG;
    Features::Colors::Teammate::InvisibleTracerColor[2] = Config::TeammateColors::InvisibleTracerColorB;
    Features::Colors::Teammate::InvisibleTracerColor[3] = Config::TeammateColors::InvisibleTracerColorA;
    Features::Colors::Teammate::VisibleTracerColor[0] = Config::TeammateColors::VisibleTracerColorR;
    Features::Colors::Teammate::VisibleTracerColor[1] = Config::TeammateColors::VisibleTracerColorG;
    Features::Colors::Teammate::VisibleTracerColor[2] = Config::TeammateColors::VisibleTracerColorB;
    Features::Colors::Teammate::VisibleTracerColor[3] = Config::TeammateColors::VisibleTracerColorA;
    Features::Colors::Teammate::InvisibleSkeletonColor[0] = Config::TeammateColors::InvisibleSkeletonColorR;
    Features::Colors::Teammate::InvisibleSkeletonColor[1] = Config::TeammateColors::InvisibleSkeletonColorG;
    Features::Colors::Teammate::InvisibleSkeletonColor[2] = Config::TeammateColors::InvisibleSkeletonColorB;
    Features::Colors::Teammate::InvisibleSkeletonColor[3] = Config::TeammateColors::InvisibleSkeletonColorA;
    Features::Colors::Teammate::VisibleSkeletonColor[0] = Config::TeammateColors::VisibleSkeletonColorR;
    Features::Colors::Teammate::VisibleSkeletonColor[1] = Config::TeammateColors::VisibleSkeletonColorG;
    Features::Colors::Teammate::VisibleSkeletonColor[2] = Config::TeammateColors::VisibleSkeletonColorB;
    Features::Colors::Teammate::VisibleSkeletonColor[3] = Config::TeammateColors::VisibleSkeletonColorA;
    Features::Colors::Teammate::InvisibleHeadCircleColor[0] = Config::TeammateColors::InvisibleHeadCircleColorR;
    Features::Colors::Teammate::InvisibleHeadCircleColor[1] = Config::TeammateColors::InvisibleHeadCircleColorG;
    Features::Colors::Teammate::InvisibleHeadCircleColor[2] = Config::TeammateColors::InvisibleHeadCircleColorB;
    Features::Colors::Teammate::InvisibleHeadCircleColor[3] = Config::TeammateColors::InvisibleHeadCircleColorA;
    Features::Colors::Teammate::VisibleHeadCircleColor[0] = Config::TeammateColors::VisibleHeadCircleColorR;
    Features::Colors::Teammate::VisibleHeadCircleColor[1] = Config::TeammateColors::VisibleHeadCircleColorG;
    Features::Colors::Teammate::VisibleHeadCircleColor[2] = Config::TeammateColors::VisibleHeadCircleColorB;
    Features::Colors::Teammate::VisibleHeadCircleColor[3] = Config::TeammateColors::VisibleHeadCircleColorA;
    Features::Colors::Teammate::InvisibleNameColor[0] = Config::TeammateColors::InvisibleNameColorR;
    Features::Colors::Teammate::InvisibleNameColor[1] = Config::TeammateColors::InvisibleNameColorG;
    Features::Colors::Teammate::InvisibleNameColor[2] = Config::TeammateColors::InvisibleNameColorB;
    Features::Colors::Teammate::InvisibleNameColor[3] = Config::TeammateColors::InvisibleNameColorA;
    Features::Colors::Teammate::VisibleNameColor[0] = Config::TeammateColors::VisibleNameColorR;
    Features::Colors::Teammate::VisibleNameColor[1] = Config::TeammateColors::VisibleNameColorG;
    Features::Colors::Teammate::VisibleNameColor[2] = Config::TeammateColors::VisibleNameColorB;
    Features::Colors::Teammate::VisibleNameColor[3] = Config::TeammateColors::VisibleNameColorA;
    Features::Colors::Teammate::InvisibleDistanceColor[0] = Config::TeammateColors::InvisibleDistanceColorR;
    Features::Colors::Teammate::InvisibleDistanceColor[1] = Config::TeammateColors::InvisibleDistanceColorG;
    Features::Colors::Teammate::InvisibleDistanceColor[2] = Config::TeammateColors::InvisibleDistanceColorB;
    Features::Colors::Teammate::InvisibleDistanceColor[3] = Config::TeammateColors::InvisibleDistanceColorA;
    Features::Colors::Teammate::VisibleDistanceColor[0] = Config::TeammateColors::VisibleDistanceColorR;
    Features::Colors::Teammate::VisibleDistanceColor[1] = Config::TeammateColors::VisibleDistanceColorG;
    Features::Colors::Teammate::VisibleDistanceColor[2] = Config::TeammateColors::VisibleDistanceColorB;
    Features::Colors::Teammate::VisibleDistanceColor[3] = Config::TeammateColors::VisibleDistanceColorA;
    Features::Colors::Teammate::InvisibleLegendColor[0] = Config::TeammateColors::InvisibleLegendColorR;
    Features::Colors::Teammate::InvisibleLegendColor[1] = Config::TeammateColors::InvisibleLegendColorG;
    Features::Colors::Teammate::InvisibleLegendColor[2] = Config::TeammateColors::InvisibleLegendColorB;
    Features::Colors::Teammate::InvisibleLegendColor[3] = Config::TeammateColors::InvisibleLegendColorA;
    Features::Colors::Teammate::VisibleLegendColor[0] = Config::TeammateColors::VisibleLegendColorR;
    Features::Colors::Teammate::VisibleLegendColor[1] = Config::TeammateColors::VisibleLegendColorG;
    Features::Colors::Teammate::VisibleLegendColor[2] = Config::TeammateColors::VisibleLegendColorB;
    Features::Colors::Teammate::VisibleLegendColor[3] = Config::TeammateColors::VisibleLegendColorA;
    Features::Colors::Teammate::InvisibleWeaponColor[0] = Config::TeammateColors::InvisibleWeaponColorR;
    Features::Colors::Teammate::InvisibleWeaponColor[1] = Config::TeammateColors::InvisibleWeaponColorG;
    Features::Colors::Teammate::InvisibleWeaponColor[2] = Config::TeammateColors::InvisibleWeaponColorB;
    Features::Colors::Teammate::InvisibleWeaponColor[3] = Config::TeammateColors::InvisibleWeaponColorA;
    Features::Colors::Teammate::VisibleWeaponColor[0] = Config::TeammateColors::VisibleWeaponColorR;
    Features::Colors::Teammate::VisibleWeaponColor[1] = Config::TeammateColors::VisibleWeaponColorG;
    Features::Colors::Teammate::VisibleWeaponColor[2] = Config::TeammateColors::VisibleWeaponColorB;
    Features::Colors::Teammate::VisibleWeaponColor[3] = Config::TeammateColors::VisibleWeaponColorA;
    Features::Colors::Teammate::BarColorMode = Config::TeammateColors::BarColorMode;
    Features::Colors::Teammate::LightWeaponColor[0] = Config::TeammateColors::LightWeaponColorR;
    Features::Colors::Teammate::LightWeaponColor[1] = Config::TeammateColors::LightWeaponColorG;
    Features::Colors::Teammate::LightWeaponColor[2] = Config::TeammateColors::LightWeaponColorB;
    Features::Colors::Teammate::LightWeaponColor[3] = Config::TeammateColors::LightWeaponColorA;
    Features::Colors::Teammate::HeavyWeaponColor[0] = Config::TeammateColors::HeavyWeaponColorR;
    Features::Colors::Teammate::HeavyWeaponColor[1] = Config::TeammateColors::HeavyWeaponColorG;
    Features::Colors::Teammate::HeavyWeaponColor[2] = Config::TeammateColors::HeavyWeaponColorB;
    Features::Colors::Teammate::HeavyWeaponColor[3] = Config::TeammateColors::HeavyWeaponColorA;
    Features::Colors::Teammate::EnergyWeaponColor[0] = Config::TeammateColors::EnergyWeaponColorR;
    Features::Colors::Teammate::EnergyWeaponColor[1] = Config::TeammateColors::EnergyWeaponColorG;
    Features::Colors::Teammate::EnergyWeaponColor[2] = Config::TeammateColors::EnergyWeaponColorB;
    Features::Colors::Teammate::EnergyWeaponColor[3] = Config::TeammateColors::EnergyWeaponColorA;
    Features::Colors::Teammate::ShotgunWeaponColor[0] = Config::TeammateColors::ShotgunWeaponColorR;
    Features::Colors::Teammate::ShotgunWeaponColor[1] = Config::TeammateColors::ShotgunWeaponColorG;
    Features::Colors::Teammate::ShotgunWeaponColor[2] = Config::TeammateColors::ShotgunWeaponColorB;
    Features::Colors::Teammate::ShotgunWeaponColor[3] = Config::TeammateColors::ShotgunWeaponColorA;
    Features::Colors::Teammate::SniperWeaponColor[0] = Config::TeammateColors::SniperWeaponColorR;
    Features::Colors::Teammate::SniperWeaponColor[1] = Config::TeammateColors::SniperWeaponColorG;
    Features::Colors::Teammate::SniperWeaponColor[2] = Config::TeammateColors::SniperWeaponColorB;
    Features::Colors::Teammate::SniperWeaponColor[3] = Config::TeammateColors::SniperWeaponColorA;
    Features::Colors::Teammate::LegendaryWeaponColor[0] = Config::TeammateColors::LegendaryWeaponColorR;
    Features::Colors::Teammate::LegendaryWeaponColor[1] = Config::TeammateColors::LegendaryWeaponColorG;
    Features::Colors::Teammate::LegendaryWeaponColor[2] = Config::TeammateColors::LegendaryWeaponColorB;
    Features::Colors::Teammate::LegendaryWeaponColor[3] = Config::TeammateColors::LegendaryWeaponColorA;
    Features::Colors::Teammate::MeleeWeaponColor[0] = Config::TeammateColors::MeleeWeaponColorR;
    Features::Colors::Teammate::MeleeWeaponColor[1] = Config::TeammateColors::MeleeWeaponColorG;
    Features::Colors::Teammate::MeleeWeaponColor[2] = Config::TeammateColors::MeleeWeaponColorB;
    Features::Colors::Teammate::MeleeWeaponColor[3] = Config::TeammateColors::MeleeWeaponColorA;
    Features::Colors::Teammate::ThrowableWeaponColor[0] = Config::TeammateColors::ThrowableWeaponColorR;
    Features::Colors::Teammate::ThrowableWeaponColor[1] = Config::TeammateColors::ThrowableWeaponColorG;
    Features::Colors::Teammate::ThrowableWeaponColor[2] = Config::TeammateColors::ThrowableWeaponColorB;
    Features::Colors::Teammate::ThrowableWeaponColor[3] = Config::TeammateColors::ThrowableWeaponColorA;

    Features::Watermark::Enabled = Config::Watermark::Enabled;
    Features::Watermark::WatermarkPosition = Config::Watermark::WatermarkPosition;
    Features::Watermark::Name = Config::Watermark::Name;
    Features::Watermark::ProcessingSpeed = Config::Watermark::ProcessingSpeed;
    Features::Watermark::Spectators = Config::Watermark::Spectators;
    Features::Watermark::GameFPS = Config::Watermark::GameFPS;

    Features::Settings::ESPEnabled = Config::Settings::ESPEnabled;
    Features::Settings::OverlayEnabled = Config::Settings::OverlayEnabled;
    Features::Settings::FPSCap = Config::Settings::FPSCap;
    Features::Settings::CappedFPS = Config::Settings::CappedFPS;
  }

  bool ReadConfig() {
    const std::string ConfigName = "Configs/" + std::string(configName) + ".ini";
    const INIReader reader(ConfigName);
    if (reader.ParseError() < 0) {
      UpdateConfig();
      return false;
    }

    ReadBool(Aimbot, AimbotEnabled);
    ReadInt(Aimbot, BindMethod);
    ReadInt(Aimbot, InputMethod); // MoveMouse or Controller (Write To ViewAngles)

    ReadBool(Aimbot, ClosestHitbox);

    ReadBool(Aimbot, OnFire);
    ReadBool(Aimbot, OnADS);
    ReadBool(Aimbot, VisCheck);
    ReadBool(Aimbot, TeamCheck);
    ReadBool(Aimbot, TargetSwitching);
    ReadInt(Aimbot, Priority);

    ReadBool(Aimbot, PredictMovement);
    ReadBool(Aimbot, PredictBulletDrop);

    ReadFloat(Aimbot, FinalDistance);
    ReadFloat(Aimbot, Smooth);

    ReadFloat(Aimbot, Speed);
    ReadInt(Aimbot, SmoothingMethod); // 0 = Static, 1 = Random

    ReadFloat(Aimbot, HipfireSmooth);
    ReadFloat(Aimbot, ADSSmooth);
    ReadFloat(Aimbot, MinHipfireSmooth);
    ReadFloat(Aimbot, MaxHipfireSmooth);
    ReadFloat(Aimbot, MinADSSmooth);
    ReadFloat(Aimbot, MaxADSSmooth);

    //AimMode 3 (Testing)
    ReadFloat(Aimbot, MouseHipfireSmoothing);
    ReadFloat(Aimbot, MouseADSSmoothing);
    ReadFloat(Aimbot, MouseExtraSmoothing);
    ReadFloat(Aimbot, MinMouseHipfireSmoothing);
    ReadFloat(Aimbot, MaxMouseHipfireSmoothing);
    ReadFloat(Aimbot, MinMouseADSSmoothing);
    ReadFloat(Aimbot, MaxMouseADSSmoothing);

    ReadInt(Aimbot, Delay);
    ReadFloat(Aimbot, FOV);
    ReadFloat(Aimbot, ZoomScale);
    ReadFloat(Aimbot, MinDistance);
    ReadFloat(Aimbot, MaxDistance);
    ReadFloat(Aimbot, HipfireDistance);
    ReadFloat(Aimbot, ZoomDistance);

    //AimMode 2
    ReadFloat(Aimbot, HipfireSmooth1);
    ReadFloat(Aimbot, ADSSmooth1);
    ReadFloat(Aimbot, MinHipfireSmooth1);
    ReadFloat(Aimbot, MaxHipfireSmooth1);
    ReadFloat(Aimbot, MinADSSmooth1);
    ReadFloat(Aimbot, MaxADSSmooth1);
    ReadFloat(Aimbot, ExtraSmoothing);
    ReadFloat(Aimbot, Deadzone);
    ReadFloat(Aimbot, FOV1);

    // Weapon Toggles
    // Light
    ReadBool(Aimbot, P2020);
    ReadBool(Aimbot, RE45);
    ReadBool(Aimbot, Alternator);
    ReadBool(Aimbot, R99);
    ReadBool(Aimbot, R301);
    ReadBool(Aimbot, Spitfire);
    ReadBool(Aimbot, G7);

    // Heavy
    ReadBool(Aimbot, Flatline);
    ReadBool(Aimbot, Hemlock);
    ReadBool(Aimbot, Repeater);
    ReadBool(Aimbot, Rampage);
    ReadBool(Aimbot, CARSMG);

    // Energy
    ReadBool(Aimbot, Havoc);
    ReadBool(Aimbot, Devotion);
    ReadBool(Aimbot, LSTAR);
    ReadBool(Aimbot, TripleTake);
    ReadBool(Aimbot, Volt);
    ReadBool(Aimbot, Nemesis);

    // Shotgun
    ReadBool(Aimbot, Mozambique);
    ReadBool(Aimbot, EVA8);
    ReadBool(Aimbot, Peacekeeper);
    ReadBool(Aimbot, Mastiff);

    // Snipers
    ReadBool(Aimbot, Longbow);
    ReadBool(Aimbot, ChargeRifle);
    ReadBool(Aimbot, Sentinel);

    // Legendary
    ReadBool(Aimbot, Wingman);
    ReadBool(Aimbot, Prowler);
    ReadBool(Aimbot, Bocek);
    ReadBool(Aimbot, Kraber);
    ReadBool(Aimbot, Knife);

    ReadInt(AimbotBinds, AimBind);
    ReadInt(AimbotBinds, ExtraBind);

    ReadInt(AimbotHitboxes, Hitbox);

    ReadBool(RCS, RCSEnabled);
    ReadInt(RCS, RCSMode);

    ReadBool(RCS, OnADS);

    ReadFloat(RCS, PitchPower);
    ReadFloat(RCS, YawPower);
    ReadFloat(RCS, PitchReduction);
    ReadFloat(RCS, YawReduction);

    // Weapon Toggles
    // Light
    ReadBool(RCS, P2020);
    ReadBool(RCS, RE45);
    ReadBool(RCS, Alternator);
    ReadBool(RCS, R99);
    ReadBool(RCS, R301);
    ReadBool(RCS, Spitfire);
    ReadBool(RCS, G7);

    // Heavy
    ReadBool(RCS, Flatline);
    ReadBool(RCS, Hemlock);
    ReadBool(RCS, Repeater);
    ReadBool(RCS, Rampage);
    ReadBool(RCS, CARSMG);

    // Energy
    ReadBool(RCS, Havoc);
    ReadBool(RCS, Devotion);
    ReadBool(RCS, LSTAR);
    ReadBool(RCS, TripleTake);
    ReadBool(RCS, Volt);
    ReadBool(RCS, Nemesis);

    // Shotgun
    ReadBool(RCS, Mozambique);
    ReadBool(RCS, EVA8);
    ReadBool(RCS, Peacekeeper);
    ReadBool(RCS, Mastiff);

    // Snipers
    ReadBool(RCS, Longbow);
    ReadBool(RCS, ChargeRifle);
    ReadBool(RCS, Sentinel);

    // Legendary
    ReadBool(RCS, Wingman); // Emotional damage!
    ReadBool(RCS, Prowler);
    ReadBool(RCS, Kraber);

    //---------------Advanced---------------//
    ReadBool(RCS, AdvancedRCS);
    ReadFloat(RCS, AdvancedPitchPower);
    ReadFloat(RCS, AdvancedYawPower);
    ReadFloat(RCS, AdvancedPitchReduction);
    ReadFloat(RCS, AdvancedYawReduction);

    // Weapons
    // Light
    ReadFloat(RCS, P2020Pitch);
    ReadFloat(RCS, P2020Yaw);
    ReadFloat(RCS, P2020PitchReduction);
    ReadFloat(RCS, P2020YawReduction);
    ReadFloat(RCS, RE45Pitch);
    ReadFloat(RCS, RE45Yaw);
    ReadFloat(RCS, RE45PitchReduction);
    ReadFloat(RCS, RE45YawReduction);
    ReadFloat(RCS, AlternatorPitch);
    ReadFloat(RCS, AlternatorYaw);
    ReadFloat(RCS, AlternatorPitchReduction);
    ReadFloat(RCS, AlternatorYawReduction);
    ReadFloat(RCS, R99Pitch);
    ReadFloat(RCS, R99Yaw);
    ReadFloat(RCS, R99PitchReduction);
    ReadFloat(RCS, R99YawReduction);
    ReadFloat(RCS, R301Pitch);
    ReadFloat(RCS, R301Yaw);
    ReadFloat(RCS, R301PitchReduction);
    ReadFloat(RCS, R301YawReduction);
    ReadFloat(RCS, SpitfirePitch);
    ReadFloat(RCS, SpitfireYaw);
    ReadFloat(RCS, SpitfirePitchReduction);
    ReadFloat(RCS, SpitfireYawReduction);
    ReadFloat(RCS, G7Pitch);
    ReadFloat(RCS, G7Yaw);
    ReadFloat(RCS, G7PitchReduction);
    ReadFloat(RCS, G7YawReduction);
    // Heavy
    ReadFloat(RCS, FlatlinePitch);
    ReadFloat(RCS, FlatlineYaw);
    ReadFloat(RCS, FlatlinePitchReduction);
    ReadFloat(RCS, FlatlineYawReduction);
    ReadFloat(RCS, HemlockPitch);
    ReadFloat(RCS, HemlockYaw);
    ReadFloat(RCS, HemlockPitchReduction);
    ReadFloat(RCS, HemlockYawReduction);
    ReadFloat(RCS, RepeaterPitch);
    ReadFloat(RCS, RepeaterYaw);
    ReadFloat(RCS, RepeaterPitchReduction);
    ReadFloat(RCS, RepeaterYawReduction);
    ReadFloat(RCS, RampagePitch);
    ReadFloat(RCS, RampageYaw);
    ReadFloat(RCS, RampagePitchReduction);
    ReadFloat(RCS, RampageYawReduction);
    ReadFloat(RCS, CARSMGPitch);
    ReadFloat(RCS, CARSMGYaw);
    ReadFloat(RCS, CARSMGPitchReduction);
    ReadFloat(RCS, CARSMGYawReduction);
    // Energy
    ReadFloat(RCS, HavocPitch);
    ReadFloat(RCS, HavocYaw);
    ReadFloat(RCS, HavocPitchReduction);
    ReadFloat(RCS, HavocYawReduction);
    ReadFloat(RCS, DevotionPitch);
    ReadFloat(RCS, DevotionYaw);
    ReadFloat(RCS, DevotionPitchReduction);
    ReadFloat(RCS, DevotionYawReduction);
    ReadFloat(RCS, LSTARPitch);
    ReadFloat(RCS, LSTARYaw);
    ReadFloat(RCS, LSTARPitchReduction);
    ReadFloat(RCS, LSTARYawReduction);
    ReadFloat(RCS, TripleTakePitch);
    ReadFloat(RCS, TripleTakeYaw);
    ReadFloat(RCS, TripleTakePitchReduction);
    ReadFloat(RCS, TripleTakeYawReduction);
    ReadFloat(RCS, VoltPitch);
    ReadFloat(RCS, VoltYaw);
    ReadFloat(RCS, VoltPitchReduction);
    ReadFloat(RCS, VoltYawReduction);
    ReadFloat(RCS, NemesisPitch);
    ReadFloat(RCS, NemesisYaw);
    ReadFloat(RCS, NemesisPitchReduction);
    ReadFloat(RCS, NemesisYawReduction);
    // Shotguns
    ReadFloat(RCS, MozambiquePitch);
    ReadFloat(RCS, MozambiqueYaw);
    ReadFloat(RCS, MozambiquePitchReduction);
    ReadFloat(RCS, MozambiqueYawReduction);
    ReadFloat(RCS, EVA8Pitch);
    ReadFloat(RCS, EVA8Yaw);
    ReadFloat(RCS, EVA8PitchReduction);
    ReadFloat(RCS, EVA8YawReduction);
    ReadFloat(RCS, PeacekeeperPitch);
    ReadFloat(RCS, PeacekeeperYaw);
    ReadFloat(RCS, PeacekeeperPitchReduction);
    ReadFloat(RCS, PeacekeeperYawReduction);
    ReadFloat(RCS, MastiffPitch);
    ReadFloat(RCS, MastiffYaw);
    ReadFloat(RCS, MastiffPitchReduction);
    ReadFloat(RCS, MastiffYawReduction);
    // Snipers
    ReadFloat(RCS, LongbowPitch);
    ReadFloat(RCS, LongbowYaw);
    ReadFloat(RCS, LongbowPitchReduction);
    ReadFloat(RCS, LongbowYawReduction);
    ReadFloat(RCS, ChargeRiflePitch);
    ReadFloat(RCS, ChargeRifleYaw);
    ReadFloat(RCS, ChargeRiflePitchReduction);
    ReadFloat(RCS, ChargeRifleYawReduction);
    ReadFloat(RCS, SentinelPitch);
    ReadFloat(RCS, SentinelYaw);
    ReadFloat(RCS, SentinelPitchReduction);
    ReadFloat(RCS, SentinelYawReduction);
    // Legendary
    ReadFloat(RCS, WingmanPitch);
    ReadFloat(RCS, WingmanYaw);
    ReadFloat(RCS, WingmanPitchReduction);
    ReadFloat(RCS, WingmanYawReduction);
    ReadFloat(RCS, ProwlerPitch);
    ReadFloat(RCS, ProwlerYaw);
    ReadFloat(RCS, ProwlerPitchReduction);
    ReadFloat(RCS, ProwlerYawReduction);
    ReadFloat(RCS, KraberPitch);
    ReadFloat(RCS, KraberYaw);
    ReadFloat(RCS, KraberPitchReduction);
    ReadFloat(RCS, KraberYawReduction);

    ReadBool(Triggerbot, Enabled);
    ReadInt(Triggerbot, BindMethod);
    ReadInt(Triggerbot, TriggerBind);
    ReadBool(Triggerbot, OnADS);
    ReadBool(Triggerbot, HipfireShotguns);
    ReadInt(Triggerbot, Delay);
    ReadFloat(Triggerbot, Range);
    ReadFloat(Triggerbot, RangeHipfire);
    // Weapon Toggles
    // Light
    ReadBool(Triggerbot, P2020);
    ReadBool(Triggerbot, RE45);
    ReadBool(Triggerbot, Alternator);
    ReadBool(Triggerbot, R99);
    ReadBool(Triggerbot, R301);
    ReadBool(Triggerbot, Spitfire);
    ReadBool(Triggerbot, G7);
    // Heavy
    ReadBool(Triggerbot, Flatline);
    ReadBool(Triggerbot, Hemlock);
    ReadBool(Triggerbot, Repeater);
    ReadBool(Triggerbot, Rampage);
    ReadBool(Triggerbot, CARSMG);
    // Energy
    ReadBool(Triggerbot, Havoc);
    ReadBool(Triggerbot, Devotion);
    ReadBool(Triggerbot, LSTAR);
    ReadBool(Triggerbot, TripleTake);
    ReadBool(Triggerbot, Volt);
    ReadBool(Triggerbot, Nemesis);
    // Shotgun
    ReadBool(Triggerbot, Mozambique);
    ReadBool(Triggerbot, EVA8);
    ReadBool(Triggerbot, Peacekeeper);
    ReadBool(Triggerbot, Mastiff);
    // Snipers
    ReadBool(Triggerbot, Longbow);
    ReadBool(Triggerbot, ChargeRifle);
    ReadBool(Triggerbot, Sentinel);
    // Legendary
    ReadBool(Triggerbot, Wingman);
    ReadBool(Triggerbot, Prowler);
    ReadBool(Triggerbot, Bocek);
    ReadBool(Triggerbot, Kraber);
    ReadBool(Triggerbot, Knife);
    // Advanced Triggerbot
    ReadBool(Triggerbot, AdvancedTriggerbot);
    ReadFloat(Triggerbot, P2020Range);
    ReadFloat(Triggerbot, RE45Range);
    ReadFloat(Triggerbot, AlternatorRange);
    ReadFloat(Triggerbot, R99Range);
    ReadFloat(Triggerbot, R301Range);
    ReadFloat(Triggerbot, SpitfireRange);
    ReadFloat(Triggerbot, G7Range);
    ReadFloat(Triggerbot, FlatlineRange);
    ReadFloat(Triggerbot, HemlockRange);
    ReadFloat(Triggerbot, ProwlerRange);
    ReadFloat(Triggerbot, RepeaterRange);
    ReadFloat(Triggerbot, RampageRange);
    ReadFloat(Triggerbot, CARSMGRange);
    ReadFloat(Triggerbot, HavocRange);
    ReadFloat(Triggerbot, DevotionRange);
    ReadFloat(Triggerbot, LSTARRange);
    ReadFloat(Triggerbot, TripleTakeRange);
    ReadFloat(Triggerbot, VoltRange);
    ReadFloat(Triggerbot, NemesisRange);
    ReadFloat(Triggerbot, MozambiqueRange);
    ReadFloat(Triggerbot, PeacekeeperRange);
    ReadFloat(Triggerbot, MastiffRange);
    ReadFloat(Triggerbot, LongbowRange);
    ReadFloat(Triggerbot, ChargeRifleRange);
    ReadFloat(Triggerbot, SentinelRange);
    ReadFloat(Triggerbot, WingmanRange);
    ReadFloat(Triggerbot, EVA8Range);
    ReadFloat(Triggerbot, BocekRange);
    ReadFloat(Triggerbot, KraberRange);
    ReadFloat(Triggerbot, ThrowingKnifeRange);

    ReadBool(Glow, NewGlow);
    ReadFloat(Glow, GlowMaxDistance);
    ReadInt(Glow, GlowColorMode);
    ReadInt(Glow, GlowColorShieldMode);
    ReadInt(Glow, GlowRadius);
    ReadInt(Glow, InsideFunction);
    ReadInt(Glow, OutlineFunction);
    ReadInt(Glow, BodyStyle);
    ReadInt(Glow, OutlineStyle);
    ReadBool(Glow, ViewModelGlow);
    ReadInt(Glow, ViewModelGlowSetting);
    ReadInt(Glow, ViewModelGlowCombo);

    ReadBool(ItemGlow, ItemGlow);
    ReadInt(ItemGlow, SelectedItemSelection);
    ReadBool(ItemGlow, Common);
    ReadBool(ItemGlow, Rare);
    ReadBool(ItemGlow, Epic);
    ReadBool(ItemGlow, Gold);
    ReadBool(ItemGlow, Legendary);
    ReadBool(ItemGlow, Weapons);
    ReadBool(ItemGlow, Ammo);
    ReadInt(ItemGlow, ItemGlowThickness);
    ReadInt(ItemGlow, SelectedInsideStyle);
    ReadInt(ItemGlow, SelectedOutlineStyle);

    ReadBool(Sense, Enabled);
    // Aimbot
    ReadBool(Sense, DrawFOVCircle);
    ReadBool(Sense, DrawFilledFOVCircle);
    ReadFloat(Sense, FOVThickness);
    ReadFloat(Sense, GameFOV);
    // Other
    ReadBool(Sense, DrawCrosshair);
    ReadFloat(Sense, CrosshairSize);
    ReadFloat(Sense, CrosshairThickness);
    ReadBool(Sense, ShowSpectators);
    ReadBool(Sense, DrawSpectatorWarning);
    ReadBool(Sense, DrawVisibleWarning);
    ReadBool(Sense, WarningTextOutline);
    ReadInt(Sense, WarningTextX);
    ReadInt(Sense, WarningTextY);
    // Settings
    ReadBool(Sense, TextOutline);
    ReadBool(Sense, VisibilityCheck);
    ReadFloat(Sense, ESPMaxDistance);

    ReadBool(SenseEnemy, DrawEnemy);
    ReadBool(SenseEnemy, DrawBoxes);
    ReadInt(SenseEnemy, BoxType);
    ReadInt(SenseEnemy, BoxStyle);
    ReadFloat(SenseEnemy, BoxThickness);
    ReadBool(SenseEnemy, DrawSkeleton);
    ReadFloat(SenseEnemy, SkeletonThickness);
    ReadBool(SenseEnemy, DrawHeadCircle);
    ReadFloat(SenseEnemy, HeadCircleThickness);
    ReadBool(SenseEnemy, DrawBars);
    ReadBool(SenseEnemy, HealthBar);
    ReadBool(SenseEnemy, ShieldBar);
    ReadInt(SenseEnemy, BarMode);
    ReadInt(SenseEnemy, BarStyle);
    ReadFloat(SenseEnemy, BarThickness);
    ReadFloat(SenseEnemy, BarThickness2);
    ReadFloat(SenseEnemy, BarHeight);
    ReadFloat(SenseEnemy, BarWidth);
    ReadInt(SenseEnemy, BarColorMode);
    ReadInt(SenseEnemy, WeaponColorType);
    ReadBool(SenseEnemy, DrawDistance);
    ReadInt(SenseEnemy, TracerPosition);
    ReadInt(SenseEnemy, TracerBone);
    ReadBool(SenseEnemy, DrawTracers);
    ReadFloat(SenseEnemy, TracerThickness);
    ReadBool(SenseEnemy, DrawNames);
    ReadBool(SenseEnemy, DrawStatus);
    ReadBool(SenseEnemy, DrawWeapon);
    ReadBool(SenseEnemy, DrawLegend);
    ReadBool(SenseEnemy, ShowMaxStatusValues);

    ReadBool(SenseTeammate, DrawTeam);
    ReadBool(SenseTeammate, DrawBoxes);
    ReadInt(SenseTeammate, BoxType);
    ReadInt(SenseTeammate, BoxStyle);
    ReadFloat(SenseTeammate, BoxThickness);
    ReadBool(SenseTeammate, DrawSkeleton);
    ReadFloat(SenseTeammate, SkeletonThickness);
    ReadBool(SenseTeammate, DrawHeadCircle);
    ReadFloat(SenseTeammate, HeadCircleThickness);
    ReadBool(SenseTeammate, DrawBars);
    ReadBool(SenseTeammate, HealthBar);
    ReadBool(SenseTeammate, ShieldBar);
    ReadInt(SenseTeammate, BarMode);
    ReadInt(SenseTeammate, BarStyle);
    ReadFloat(SenseTeammate, BarThickness);
    ReadFloat(SenseTeammate, BarThickness2);
    ReadFloat(SenseTeammate, BarHeight);
    ReadFloat(SenseTeammate, BarWidth);
    ReadInt(SenseTeammate, BarColorMode);
    ReadBool(SenseTeammate, BarBackground);
    ReadInt(SenseTeammate, WeaponColorType);
    ReadBool(SenseTeammate, DrawDistance);
    ReadInt(SenseTeammate, TracerPosition);
    ReadInt(SenseTeammate, TracerBone);
    ReadBool(SenseTeammate, DrawTracers);
    ReadFloat(SenseTeammate, TracerThickness);
    ReadBool(SenseTeammate, DrawNames);
    ReadBool(SenseTeammate, DrawStatus);
    ReadBool(SenseTeammate, DrawWeapon);
    ReadBool(SenseTeammate, DrawLegend);
    ReadBool(SenseTeammate, ShowMaxStatusValues);

    ReadInt(SensePositions, NamePosition);
    ReadInt(SensePositions, DistancePosition);
    ReadInt(SensePositions, LegendPosition);
    ReadInt(SensePositions, WeaponPosition);
    ReadInt(SensePositions, StatusPosition);

    ReadBool(Radar, MiniMap);
    ReadFloat(Radar, MiniMapRange);
    ReadInt(Radar, MiniMapScaleX);
    ReadInt(Radar, MiniMapScaleY);
    ReadInt(Radar, MiniMapDotSize);
    ReadInt(Radar, MiniMapBlackBGSize);
    ReadBool(Radar, MiniMapGuides);
    ReadBool(Radar, BigMap);
    ReadInt(Radar, BigMapBind);
    ReadFloat(Radar, CircleColorR);
    ReadFloat(Radar, CircleColorG);
    ReadFloat(Radar, CircleColorB);
    ReadFloat(Radar, CircleColorA);

    ReadBool(Misc, SuperGlide);
    ReadInt(Misc, SuperGlideMode);
    ReadInt(Misc, SuperGlideFPS);
    ReadBool(Misc, QuickTurn);
    ReadInt(Misc, QuickTurnAngle);
    ReadInt(Misc, QuickTurnBind);
    ReadBool(Misc, BHop);
    ReadInt(Misc, BHopDelay);
    ReadInt(Misc, BHopBind);
    ReadBool(Misc, RapidFire);
    ReadInt(Misc, RapidFireDelay);
    ReadInt(Misc, RapidFireBind);
    // Rapid Fire Weapon Toggles
    // Light
    ReadBool(Misc, RapidP2020);
    ReadBool(Misc, RapidR301);
    ReadBool(Misc, RapidG7);
    // Heavy
    ReadBool(Misc, RapidFlatline);
    ReadBool(Misc, RapidHemlock);
    ReadBool(Misc, RapidProwler);
    // Energy
    ReadBool(Misc, RapidNemesis);
    // Shotgun
    ReadBool(Misc, RapidMozambique);
    ReadBool(Misc, RapidEVA8);
    // Legendary
    ReadBool(Misc, RapidWingman);
    ReadBool(Misc, SkinChanger);
    // Skin IDs
    // Light
    ReadInt(Misc, SkinP2020);
    ReadInt(Misc, SkinRE45);
    ReadInt(Misc, SkinALTERNATOR);
    ReadInt(Misc, SkinR99);
    ReadInt(Misc, SkinR301);
    ReadInt(Misc, SkinSPITFIRE);
    ReadInt(Misc, SkinG7);
    // Heavy
    ReadInt(Misc, SkinFLATLINE);
    ReadInt(Misc, SkinHEMLOCK);
    ReadInt(Misc, SkinREPEATER);
    ReadInt(Misc, SkinRAMPAGE);
    ReadInt(Misc, SkinCAR);
    // Energy
    ReadInt(Misc, SkinHAVOC);
    ReadInt(Misc, SkinDEVOTION);
    ReadInt(Misc, SkinLSTAR);
    ReadInt(Misc, SkinTRIPLETAKE);
    ReadInt(Misc, SkinVOLT);
    ReadInt(Misc, SkinNEMESIS);
    // Shotgun
    ReadInt(Misc, SkinMOZAMBIQUE);
    ReadInt(Misc, SkinEVA8);
    ReadInt(Misc, SkinPEACEKEEPER);
    ReadInt(Misc, SkinMASTIFF);
    // Snipers
    ReadInt(Misc, SkinLONGBOW);
    ReadInt(Misc, SkinCHARGE_RIFLE);
    ReadInt(Misc, SkinSENTINEL);
    // Legendary
    ReadInt(Misc, SkinWINGMAN);
    ReadInt(Misc, SkinPROWLER);
    ReadInt(Misc, SkinBOCEK);
    ReadInt(Misc, SkinKRABER);

    ReadInt(Colors, WeaponColorMode);
    ReadFloat(Colors, FOVColorR);
    ReadFloat(Colors, FOVColorG);
    ReadFloat(Colors, FOVColorB);
    ReadFloat(Colors, FOVColorA);
    ReadFloat(Colors, FilledFOVColorR);
    ReadFloat(Colors, FilledFOVColorG);
    ReadFloat(Colors, FilledFOVColorB);
    ReadFloat(Colors, FilledFOVColorA);
    ReadFloat(Colors, CrosshairColorR);
    ReadFloat(Colors, CrosshairColorG);
    ReadFloat(Colors, CrosshairColorB);
    ReadFloat(Colors, CrosshairColorA);
    ReadFloat(Colors, SpectatorWarningColorR);
    ReadFloat(Colors, SpectatorWarningColorG);
    ReadFloat(Colors, SpectatorWarningColorB);
    ReadFloat(Colors, SpectatorWarningColorA);
    ReadFloat(Colors, VisibleWarningColorR);
    ReadFloat(Colors, VisibleWarningColorG);
    ReadFloat(Colors, VisibleWarningColorB);
    ReadFloat(Colors, VisibleWarningColorA);

    ReadFloat(EnemyColors, InvisibleBoxColorR);
    ReadFloat(EnemyColors, InvisibleBoxColorG);
    ReadFloat(EnemyColors, InvisibleBoxColorB);
    ReadFloat(EnemyColors, InvisibleBoxColorA);
    ReadFloat(EnemyColors, VisibleBoxColorR);
    ReadFloat(EnemyColors, VisibleBoxColorG);
    ReadFloat(EnemyColors, VisibleBoxColorB);
    ReadFloat(EnemyColors, VisibleBoxColorA);
    ReadFloat(EnemyColors, InvisibleFilledBoxColorR);
    ReadFloat(EnemyColors, InvisibleFilledBoxColorG);
    ReadFloat(EnemyColors, InvisibleFilledBoxColorB);
    ReadFloat(EnemyColors, InvisibleFilledBoxColorA);
    ReadFloat(EnemyColors, VisibleFilledBoxColorR);
    ReadFloat(EnemyColors, VisibleFilledBoxColorG);
    ReadFloat(EnemyColors, VisibleFilledBoxColorB);
    ReadFloat(EnemyColors, VisibleFilledBoxColorA);
    ReadFloat(EnemyColors, InvisibleTracerColorR);
    ReadFloat(EnemyColors, InvisibleTracerColorG);
    ReadFloat(EnemyColors, InvisibleTracerColorB);
    ReadFloat(EnemyColors, InvisibleTracerColorA);
    ReadFloat(EnemyColors, VisibleTracerColorR);
    ReadFloat(EnemyColors, VisibleTracerColorG);
    ReadFloat(EnemyColors, VisibleTracerColorB);
    ReadFloat(EnemyColors, VisibleTracerColorA);
    ReadFloat(EnemyColors, InvisibleSkeletonColorR);
    ReadFloat(EnemyColors, InvisibleSkeletonColorG);
    ReadFloat(EnemyColors, InvisibleSkeletonColorB);
    ReadFloat(EnemyColors, InvisibleSkeletonColorA);
    ReadFloat(EnemyColors, VisibleSkeletonColorR);
    ReadFloat(EnemyColors, VisibleSkeletonColorG);
    ReadFloat(EnemyColors, VisibleSkeletonColorB);
    ReadFloat(EnemyColors, VisibleSkeletonColorA);
    ReadFloat(EnemyColors, InvisibleHeadCircleColorR);
    ReadFloat(EnemyColors, InvisibleHeadCircleColorG);
    ReadFloat(EnemyColors, InvisibleHeadCircleColorB);
    ReadFloat(EnemyColors, InvisibleHeadCircleColorA);
    ReadFloat(EnemyColors, VisibleHeadCircleColorR);
    ReadFloat(EnemyColors, VisibleHeadCircleColorG);
    ReadFloat(EnemyColors, VisibleHeadCircleColorB);
    ReadFloat(EnemyColors, VisibleHeadCircleColorA);
    ReadFloat(EnemyColors, InvisibleNameColorR);
    ReadFloat(EnemyColors, InvisibleNameColorG);
    ReadFloat(EnemyColors, InvisibleNameColorB);
    ReadFloat(EnemyColors, InvisibleNameColorA);
    ReadFloat(EnemyColors, VisibleNameColorR);
    ReadFloat(EnemyColors, VisibleNameColorG);
    ReadFloat(EnemyColors, VisibleNameColorB);
    ReadFloat(EnemyColors, VisibleNameColorA);
    ReadFloat(EnemyColors, InvisibleDistanceColorR);
    ReadFloat(EnemyColors, InvisibleDistanceColorG);
    ReadFloat(EnemyColors, InvisibleDistanceColorB);
    ReadFloat(EnemyColors, InvisibleDistanceColorA);
    ReadFloat(EnemyColors, VisibleDistanceColorR);
    ReadFloat(EnemyColors, VisibleDistanceColorG);
    ReadFloat(EnemyColors, VisibleDistanceColorB);
    ReadFloat(EnemyColors, VisibleDistanceColorA);
    ReadFloat(EnemyColors, InvisibleLegendColorR);
    ReadFloat(EnemyColors, InvisibleLegendColorG);
    ReadFloat(EnemyColors, InvisibleLegendColorB);
    ReadFloat(EnemyColors, InvisibleLegendColorA);
    ReadFloat(EnemyColors, VisibleLegendColorR);
    ReadFloat(EnemyColors, VisibleLegendColorG);
    ReadFloat(EnemyColors, VisibleLegendColorB);
    ReadFloat(EnemyColors, VisibleLegendColorA);
    // Bar
    ReadInt(EnemyColors, BarColorMode);
    // WeaponESP Colors
    ReadFloat(EnemyColors, InvisibleWeaponColorR);
    ReadFloat(EnemyColors, InvisibleWeaponColorG);
    ReadFloat(EnemyColors, InvisibleWeaponColorB);
    ReadFloat(EnemyColors, InvisibleWeaponColorA);
    ReadFloat(EnemyColors, VisibleWeaponColorR);
    ReadFloat(EnemyColors, VisibleWeaponColorG);
    ReadFloat(EnemyColors, VisibleWeaponColorB);
    ReadFloat(EnemyColors, VisibleWeaponColorA);
    // Multiple
    ReadFloat(EnemyColors, LightWeaponColorR);
    ReadFloat(EnemyColors, LightWeaponColorG);
    ReadFloat(EnemyColors, LightWeaponColorB);
    ReadFloat(EnemyColors, LightWeaponColorA);
    ReadFloat(EnemyColors, HeavyWeaponColorR);
    ReadFloat(EnemyColors, HeavyWeaponColorG);
    ReadFloat(EnemyColors, HeavyWeaponColorB);
    ReadFloat(EnemyColors, HeavyWeaponColorA);
    ReadFloat(EnemyColors, EnergyWeaponColorR);
    ReadFloat(EnemyColors, EnergyWeaponColorG);
    ReadFloat(EnemyColors, EnergyWeaponColorB);
    ReadFloat(EnemyColors, EnergyWeaponColorA);
    ReadFloat(EnemyColors, ShotgunWeaponColorR);
    ReadFloat(EnemyColors, ShotgunWeaponColorG);
    ReadFloat(EnemyColors, ShotgunWeaponColorB);
    ReadFloat(EnemyColors, ShotgunWeaponColorA);
    ReadFloat(EnemyColors, SniperWeaponColorR);
    ReadFloat(EnemyColors, SniperWeaponColorG);
    ReadFloat(EnemyColors, SniperWeaponColorB);
    ReadFloat(EnemyColors, SniperWeaponColorA);
    ReadFloat(EnemyColors, LegendaryWeaponColorR);
    ReadFloat(EnemyColors, LegendaryWeaponColorG);
    ReadFloat(EnemyColors, LegendaryWeaponColorB);
    ReadFloat(EnemyColors, LegendaryWeaponColorA);
    ReadFloat(EnemyColors, MeleeWeaponColorR);
    ReadFloat(EnemyColors, MeleeWeaponColorG);
    ReadFloat(EnemyColors, MeleeWeaponColorB);
    ReadFloat(EnemyColors, MeleeWeaponColorA);
    ReadFloat(EnemyColors, ThrowableWeaponColorR);
    ReadFloat(EnemyColors, ThrowableWeaponColorG);
    ReadFloat(EnemyColors, ThrowableWeaponColorB);
    ReadFloat(EnemyColors, ThrowableWeaponColorA);
    // Glow
    ReadFloat(EnemyColors, InvisibleGlowColorR);
    ReadFloat(EnemyColors, InvisibleGlowColorG);
    ReadFloat(EnemyColors, InvisibleGlowColorB);
    ReadFloat(EnemyColors, VisibleGlowColorR);
    ReadFloat(EnemyColors, VisibleGlowColorG);
    ReadFloat(EnemyColors, VisibleGlowColorB);
    ReadFloat(EnemyColors, RedShieldColorR);
    ReadFloat(EnemyColors, RedShieldColorG);
    ReadFloat(EnemyColors, RedShieldColorG);
    ReadFloat(EnemyColors, PurpleShieldColorR);
    ReadFloat(EnemyColors, PurpleShieldColorG);
    ReadFloat(EnemyColors, PurpleShieldColorB);
    ReadFloat(EnemyColors, BlueShieldColorR);
    ReadFloat(EnemyColors, BlueShieldColorG);
    ReadFloat(EnemyColors, BlueShieldColorB);
    ReadFloat(EnemyColors, GreyShieldColorR);
    ReadFloat(EnemyColors, GreyShieldColorG);
    ReadFloat(EnemyColors, GreyShieldColorB);

    ReadFloat(TeammateColors, InvisibleBoxColorR);
    ReadFloat(TeammateColors, InvisibleBoxColorG);
    ReadFloat(TeammateColors, InvisibleBoxColorB);
    ReadFloat(TeammateColors, InvisibleBoxColorA);
    ReadFloat(TeammateColors, VisibleBoxColorR);
    ReadFloat(TeammateColors, VisibleBoxColorG);
    ReadFloat(TeammateColors, VisibleBoxColorB);
    ReadFloat(TeammateColors, VisibleBoxColorA);
    ReadFloat(TeammateColors, InvisibleFilledBoxColorR);
    ReadFloat(TeammateColors, InvisibleFilledBoxColorG);
    ReadFloat(TeammateColors, InvisibleFilledBoxColorB);
    ReadFloat(TeammateColors, InvisibleFilledBoxColorA);
    ReadFloat(TeammateColors, VisibleFilledBoxColorR);
    ReadFloat(TeammateColors, VisibleFilledBoxColorG);
    ReadFloat(TeammateColors, VisibleFilledBoxColorB);
    ReadFloat(TeammateColors, VisibleFilledBoxColorA);
    ReadFloat(TeammateColors, InvisibleTracerColorR);
    ReadFloat(TeammateColors, InvisibleTracerColorG);
    ReadFloat(TeammateColors, InvisibleTracerColorB);
    ReadFloat(TeammateColors, InvisibleTracerColorA);
    ReadFloat(TeammateColors, VisibleTracerColorR);
    ReadFloat(TeammateColors, VisibleTracerColorG);
    ReadFloat(TeammateColors, VisibleTracerColorB);
    ReadFloat(TeammateColors, VisibleTracerColorA);
    ReadFloat(TeammateColors, InvisibleSkeletonColorR);
    ReadFloat(TeammateColors, InvisibleSkeletonColorG);
    ReadFloat(TeammateColors, InvisibleSkeletonColorB);
    ReadFloat(TeammateColors, InvisibleSkeletonColorA);
    ReadFloat(TeammateColors, VisibleSkeletonColorR);
    ReadFloat(TeammateColors, VisibleSkeletonColorG);
    ReadFloat(TeammateColors, VisibleSkeletonColorB);
    ReadFloat(TeammateColors, VisibleSkeletonColorA);
    ReadFloat(TeammateColors, InvisibleHeadCircleColorR);
    ReadFloat(TeammateColors, InvisibleHeadCircleColorG);
    ReadFloat(TeammateColors, InvisibleHeadCircleColorB);
    ReadFloat(TeammateColors, InvisibleHeadCircleColorA);
    ReadFloat(TeammateColors, VisibleHeadCircleColorR);
    ReadFloat(TeammateColors, VisibleHeadCircleColorG);
    ReadFloat(TeammateColors, VisibleHeadCircleColorB);
    ReadFloat(TeammateColors, VisibleHeadCircleColorA);
    ReadFloat(TeammateColors, InvisibleNameColorR);
    ReadFloat(TeammateColors, InvisibleNameColorG);
    ReadFloat(TeammateColors, InvisibleNameColorB);
    ReadFloat(TeammateColors, InvisibleNameColorA);
    ReadFloat(TeammateColors, VisibleNameColorR);
    ReadFloat(TeammateColors, VisibleNameColorG);
    ReadFloat(TeammateColors, VisibleNameColorB);
    ReadFloat(TeammateColors, VisibleNameColorA);
    ReadFloat(TeammateColors, InvisibleDistanceColorR);
    ReadFloat(TeammateColors, InvisibleDistanceColorG);
    ReadFloat(TeammateColors, InvisibleDistanceColorB);
    ReadFloat(TeammateColors, InvisibleDistanceColorA);
    ReadFloat(TeammateColors, VisibleDistanceColorR);
    ReadFloat(TeammateColors, VisibleDistanceColorG);
    ReadFloat(TeammateColors, VisibleDistanceColorB);
    ReadFloat(TeammateColors, VisibleDistanceColorA);
    ReadFloat(TeammateColors, InvisibleLegendColorR);
    ReadFloat(TeammateColors, InvisibleLegendColorG);
    ReadFloat(TeammateColors, InvisibleLegendColorB);
    ReadFloat(TeammateColors, InvisibleLegendColorA);
    ReadFloat(TeammateColors, VisibleLegendColorR);
    ReadFloat(TeammateColors, VisibleLegendColorG);
    ReadFloat(TeammateColors, VisibleLegendColorB);
    ReadFloat(TeammateColors, VisibleLegendColorA);
    // Bar
    ReadInt(TeammateColors, BarColorMode);
    // WeaponESP Colors
    ReadFloat(TeammateColors, InvisibleWeaponColorR);
    ReadFloat(TeammateColors, InvisibleWeaponColorG);
    ReadFloat(TeammateColors, InvisibleWeaponColorB);
    ReadFloat(TeammateColors, InvisibleWeaponColorA);
    ReadFloat(TeammateColors, VisibleWeaponColorR);
    ReadFloat(TeammateColors, VisibleWeaponColorG);
    ReadFloat(TeammateColors, VisibleWeaponColorB);
    ReadFloat(TeammateColors, VisibleWeaponColorA);
    // Multiple
    ReadFloat(TeammateColors, LightWeaponColorR);
    ReadFloat(TeammateColors, LightWeaponColorG);
    ReadFloat(TeammateColors, LightWeaponColorB);
    ReadFloat(TeammateColors, LightWeaponColorA);
    ReadFloat(TeammateColors, HeavyWeaponColorR);
    ReadFloat(TeammateColors, HeavyWeaponColorG);
    ReadFloat(TeammateColors, HeavyWeaponColorB);
    ReadFloat(TeammateColors, HeavyWeaponColorA);
    ReadFloat(TeammateColors, EnergyWeaponColorR);
    ReadFloat(TeammateColors, EnergyWeaponColorG);
    ReadFloat(TeammateColors, EnergyWeaponColorB);
    ReadFloat(TeammateColors, EnergyWeaponColorA);
    ReadFloat(TeammateColors, ShotgunWeaponColorR);
    ReadFloat(TeammateColors, ShotgunWeaponColorG);
    ReadFloat(TeammateColors, ShotgunWeaponColorB);
    ReadFloat(TeammateColors, ShotgunWeaponColorA);
    ReadFloat(TeammateColors, SniperWeaponColorR);
    ReadFloat(TeammateColors, SniperWeaponColorG);
    ReadFloat(TeammateColors, SniperWeaponColorB);
    ReadFloat(TeammateColors, SniperWeaponColorA);
    ReadFloat(TeammateColors, LegendaryWeaponColorR);
    ReadFloat(TeammateColors, LegendaryWeaponColorG);
    ReadFloat(TeammateColors, LegendaryWeaponColorB);
    ReadFloat(TeammateColors, LegendaryWeaponColorA);
    ReadFloat(TeammateColors, MeleeWeaponColorR);
    ReadFloat(TeammateColors, MeleeWeaponColorG);
    ReadFloat(TeammateColors, MeleeWeaponColorB);
    ReadFloat(TeammateColors, MeleeWeaponColorA);
    ReadFloat(TeammateColors, ThrowableWeaponColorR);
    ReadFloat(TeammateColors, ThrowableWeaponColorG);
    ReadFloat(TeammateColors, ThrowableWeaponColorB);
    ReadFloat(TeammateColors, ThrowableWeaponColorA);

    ReadBool(Watermark, Enabled);
    ReadInt(Watermark, WatermarkPosition);
    ReadBool(Watermark, Name);
    ReadBool(Watermark, ProcessingSpeed);
    ReadBool(Watermark, Spectators);
    ReadBool(Watermark, GameFPS);

    ReadBool(Settings, ESPEnabled);
    ReadBool(Settings, OverlayEnabled);
    ReadBool(Settings, FPSCap);
    ReadInt(Settings, CappedFPS);

    UpdateConfig();
    return true;
  }
};
