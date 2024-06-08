#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "IniReader.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

constexpr char ConfigFile[] = "config.ini";

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

namespace Config {
  namespace Settings {
    bool ESPEnabled = true;
    bool OverlayEnabled = true;
    bool FPSCap = false;
    int CappedFPS = 144;
    bool DodgeWindows = true;
  };

  namespace AimbotHitboxes {
    int Hitbox = 2;
  };

  namespace AimbotBinds {
    int AimBind = 56;
    int ExtraBind = 57;
  }

  namespace Aimbot {
    bool AimbotEnabled = false;
    int BindMethod = 0;
    int InputMethod = 0; // MoveMouse or Controller (Write To ViewAngles)

    bool ClosestHitbox = false;

    bool OnFire = true;
    bool OnADS = true;
    bool VisCheck = true;
    bool TeamCheck = true;
    bool TargetSwitching = true;
    int Priority = 0;

    bool PredictMovement = true;
    bool PredictBulletDrop = true;

    float FinalDistance = 0;
    float Smooth = 0.9;

    float Speed = 16;
    int SmoothingMethod = 0; // 0 = Static, 1 = Random

    float HipfireSmooth = 0.9;
    float ADSSmooth = 0.99;
    float MinHipfireSmooth = 0.9;
    float MaxHipfireSmooth = 0.99;
    float MinADSSmooth = 0.9;
    float MaxADSSmooth = 0.99;

    //AimMode 3 (Testing)
    float MouseHipfireSmoothing = 300;
    float MouseADSSmoothing = 350;
    float MouseExtraSmoothing = 5000;
    float MinMouseHipfireSmoothing = 300;
    float MaxMouseHipfireSmoothing = 315;
    float MinMouseADSSmoothing = 350;
    float MaxMouseADSSmoothing = 360;

    int Delay = 10;
    float FOV = 15;
    float ZoomScale = 3.3;
    float MinDistance = 1;
    float MaxDistance = 200;
    float HipfireDistance = 60;
    float ZoomDistance = 160;

    //AimMode 2
    float HipfireSmooth1 = 250;
    float ADSSmooth1 = 230;
    float MinHipfireSmooth1 = 250;
    float MaxHipfireSmooth1 = 300;
    float MinADSSmooth1 = 290;
    float MaxADSSmooth1 = 325;
    float ExtraSmoothing = 1000;
    float Deadzone = 0.5;
    float FOV1 = 10;

    // Weapon Toggles
    // Light
    bool P2020 = true;
    bool RE45 = true;
    bool Alternator = true;
    bool R99 = true;
    bool R301 = true;
    bool Spitfire = true;
    bool G7 = true;

    // Heavy
    bool Flatline = true;
    bool Hemlock = true;
    bool Repeater = true;
    bool Rampage = true;
    bool CARSMG = true;

    // Energy
    bool Havoc = true;
    bool Devotion = true;
    bool LSTAR = true;
    bool TripleTake = true;
    bool Volt = true;
    bool Nemesis = true;

    // Shotgun
    bool Mozambique = true;
    bool EVA8 = true;
    bool Peacekeeper = true;
    bool Mastiff = true;

    // Snipers
    bool Longbow = true;
    bool ChargeRifle = true;
    bool Sentinel = true;

    // Legendary
    bool Wingman = true;
    bool Prowler = true;
    bool Bocek = true;
    bool Kraber = true;
    bool Knife = true;
  };

  namespace RCS {
    bool RCSEnabled = false;
    int RCSMode = 0;

    bool OnADS = true;

    float PitchPower = 3;
    float YawPower = 3;
    float PitchReduction = 50;
    float YawReduction = 50;

    // Weapon Toggles
    // Light
    bool P2020 = true;
    bool RE45 = true;
    bool Alternator = true;
    bool R99 = true;
    bool R301 = true;
    bool Spitfire = true;
    bool G7 = true;

    // Heavy
    bool Flatline = true;
    bool Hemlock = true;
    bool Repeater = true;
    bool Rampage = true;
    bool CARSMG = true;

    // Energy
    bool Havoc = true;
    bool Devotion = true;
    bool LSTAR = true;
    bool TripleTake = true;
    bool Volt = true;
    bool Nemesis = true;

    // Shotgun
    bool Mozambique = true;
    bool EVA8 = true;
    bool Peacekeeper = true;
    bool Mastiff = true;

    // Snipers
    bool Longbow = true;
    bool ChargeRifle = true;
    bool Sentinel = true;

    // Legendary
    bool Wingman = true; // Emotional damage!
    bool Prowler = true;
    bool Kraber = false;

    //---------------Advanced---------------//
    bool AdvancedRCS = false;
    float AdvancedPitchPower = 10;
    float AdvancedYawPower = 10;
    float AdvancedPitchReduction = 25;
    float AdvancedYawReduction = 25;

    // Weapons
    // Light
    float P2020Pitch = 10;
    float P2020Yaw = 10;
    float P2020PitchReduction = 25;
    float P2020YawReduction = 25;
    float RE45Pitch = 10;
    float RE45Yaw = 10;
    float RE45PitchReduction = 25;
    float RE45YawReduction = 25;
    float AlternatorPitch = 10;
    float AlternatorYaw = 10;
    float AlternatorPitchReduction = 25;
    float AlternatorYawReduction = 25;
    float R99Pitch = 10;
    float R99Yaw = 10;
    float R99PitchReduction = 25;
    float R99YawReduction = 25;
    float R301Pitch = 10;
    float R301Yaw = 10;
    float R301PitchReduction = 25;
    float R301YawReduction = 25;
    float SpitfirePitch = 10;
    float SpitfireYaw = 10;
    float SpitfirePitchReduction = 25;
    float SpitfireYawReduction = 25;
    float G7Pitch = 10;
    float G7Yaw = 10;
    float G7PitchReduction = 25;
    float G7YawReduction = 25;
    // Heavy
    float FlatlinePitch = 10;
    float FlatlineYaw = 10;
    float FlatlinePitchReduction = 25;
    float FlatlineYawReduction = 25;
    float HemlockPitch = 10;
    float HemlockYaw = 10;
    float HemlockPitchReduction = 25;
    float HemlockYawReduction = 25;
    float RepeaterPitch = 10;
    float RepeaterYaw = 10;
    float RepeaterPitchReduction = 25;
    float RepeaterYawReduction = 25;
    float RampagePitch = 10;
    float RampageYaw = 10;
    float RampagePitchReduction = 25;
    float RampageYawReduction = 25;
    float CARSMGPitch = 10;
    float CARSMGYaw = 10;
    float CARSMGPitchReduction = 25;
    float CARSMGYawReduction = 25;
    // Energy
    float HavocPitch = 10;
    float HavocYaw = 10;
    float HavocPitchReduction = 25;
    float HavocYawReduction = 25;
    float DevotionPitch = 10;
    float DevotionYaw = 10;
    float DevotionPitchReduction = 25;
    float DevotionYawReduction = 25;
    float LSTARPitch = 10;
    float LSTARYaw = 10;
    float LSTARPitchReduction = 25;
    float LSTARYawReduction = 25;
    float TripleTakePitch = 10;
    float TripleTakeYaw = 10;
    float TripleTakePitchReduction = 25;
    float TripleTakeYawReduction = 25;
    float VoltPitch = 10;
    float VoltYaw = 10;
    float VoltPitchReduction = 25;
    float VoltYawReduction = 25;
    float NemesisPitch = 10;
    float NemesisYaw = 10;
    float NemesisPitchReduction = 25;
    float NemesisYawReduction = 25;
    // Shotguns
    float MozambiquePitch = 10;
    float MozambiqueYaw = 10;
    float MozambiquePitchReduction = 25;
    float MozambiqueYawReduction = 25;
    float EVA8Pitch = 10;
    float EVA8Yaw = 10;
    float EVA8PitchReduction = 25;
    float EVA8YawReduction = 25;
    float PeacekeeperPitch = 10;
    float PeacekeeperYaw = 10;
    float PeacekeeperPitchReduction = 25;
    float PeacekeeperYawReduction = 25;
    float MastiffPitch = 10;
    float MastiffYaw = 10;
    float MastiffPitchReduction = 25;
    float MastiffYawReduction = 25;
    // Snipers
    float LongbowPitch = 10;
    float LongbowYaw = 10;
    float LongbowPitchReduction = 25;
    float LongbowYawReduction = 25;
    float ChargeRiflePitch = 10;
    float ChargeRifleYaw = 10;
    float ChargeRiflePitchReduction = 25;
    float ChargeRifleYawReduction = 25;
    float SentinelPitch = 10;
    float SentinelYaw = 10;
    float SentinelPitchReduction = 25;
    float SentinelYawReduction = 25;
    // Legendary
    float WingmanPitch = 10;
    float WingmanYaw = 10;
    float WingmanPitchReduction = 25;
    float WingmanYawReduction = 25;
    float ProwlerPitch = 10;
    float ProwlerYaw = 10;
    float ProwlerPitchReduction = 25;
    float ProwlerYawReduction = 25;
    float KraberPitch = 10;
    float KraberYaw = 10;
    float KraberPitchReduction = 25;
    float KraberYawReduction = 25;
  };

  namespace Triggerbot {
    bool Enabled = false;
    int BindMethod = 0;
    int TriggerBind = 57;
    bool OnADS = true;
    bool HipfireShotguns = false;
    int Delay = 100;
    float Range = 200;
    float RangeHipfire = 70;

    // Weapon Toggles

    // Light
    bool P2020 = false;
    bool RE45 = false;
    bool Alternator = false;
    bool R99 = false;
    bool R301 = false;
    bool Spitfire = false;
    bool G7 = true;

    // Heavy
    bool Flatline = false;
    bool Hemlock = false;
    bool Repeater = true;
    bool Rampage = false;
    bool CARSMG = false;

    // Energy
    bool Havoc = false;
    bool Devotion = false;
    bool LSTAR = false;
    bool TripleTake = true;
    bool Volt = false;
    bool Nemesis = false;

    // Shotgun
    bool Mozambique = true;
    bool EVA8 = true;
    bool Peacekeeper = true;
    bool Mastiff = true;

    // Snipers
    bool Longbow = true;
    bool ChargeRifle = true;
    bool Sentinel = true;

    // Legendary
    bool Wingman = true;
    bool Prowler = false;
    bool Bocek = true;
    bool Kraber = true;
    bool Knife = true;

    // Advanced Triggerbot
    bool AdvancedTriggerbot = false;

    float P2020Range = 150;
    float RE45Range = 150;
    float AlternatorRange = 150;
    float R99Range = 150;
    float R301Range = 150;
    float SpitfireRange = 150;
    float G7Range = 150;

    float FlatlineRange = 150;
    float HemlockRange = 150;
    float ProwlerRange = 150;
    float RepeaterRange = 150;
    float RampageRange = 150;
    float CARSMGRange = 150;

    float HavocRange = 150;
    float DevotionRange = 150;
    float LSTARRange = 150;
    float TripleTakeRange = 150;
    float VoltRange = 150;
    float NemesisRange = 150;

    float MozambiqueRange = 150;
    float PeacekeeperRange = 150;
    float MastiffRange = 150;

    float LongbowRange = 150;
    float ChargeRifleRange = 150;
    float SentinelRange = 150;

    float WingmanRange = 150;
    float EVA8Range = 150;
    float BocekRange = 150;
    float KraberRange = 150;
    float ThrowingKnifeRange = 150;
  };

  namespace Glow {
    // Glow
    bool NewGlow = false;
    float GlowMaxDistance = 200;

    int GlowColorMode = 1;
    int GlowColorShieldMode = 0;
    int GlowRadius = 64;
    int InsideFunction = 2; // Leave
    int OutlineFunction = 125; // Leave
    int BodyStyle = 15;
    int OutlineStyle = 1;

    bool ViewModelGlow = false;
    static int ViewModelGlowSetting = 65;
    static int ViewModelGlowCombo;
  };

  namespace ItemGlow {
    bool ItemGlow = false;
    int SelectedItemSelection = 0; // 0 = Simple, 1 = Custom
    bool Common = true;
    bool Rare = true;
    bool Epic = true;
    bool Gold = true;
    bool Legendary = true;
    bool Weapons = false;
    bool Ammo = false;

    int ItemGlowThickness = 35;

    int SelectedInsideStyle = 2;
    int SelectedOutlineStyle = 3;
  };

  namespace Sense {
    bool Enabled = false;

    // Aimbot
    bool DrawFOVCircle = true;
    bool DrawFilledFOVCircle = false;
    float FOVThickness = 1.0;
    float GameFOV = 120;

    // Other
    bool DrawCrosshair = true;
    float CrosshairSize = 7.0;
    float CrosshairThickness = 1.0;

    bool ShowSpectators = true;

    bool DrawSpectatorWarning = false;
    bool DrawVisibleWarning = false;
    bool WarningTextOutline = true;
    int WarningTextX;
    int WarningTextY;
    // Settings
    bool TextOutline = true;
    bool VisibilityCheck = false;
    float ESPMaxDistance = 200;
  };

  namespace SenseEnemy {
    bool DrawEnemy = true;

    bool DrawBoxes = true;
    int BoxType = 0;
    int BoxStyle = 1;
    float BoxThickness = 1.0;

    bool DrawSkeleton = true;
    float SkeletonThickness = 1.0;
    bool DrawHeadCircle = true;
    float HeadCircleThickness = 1.0;

    bool DrawBars = true;
    bool HealthBar = true;
    bool ShieldBar = true;
    int BarMode = 2;
    int BarStyle = 0;
    float BarThickness = 1.0f;
    float BarThickness2 = 1.05f;
    float BarHeight = 5.0f;
    float BarWidth = 60.0f;
    int BarColorMode = 0;

    int WeaponColorType = 1;
    bool DrawDistance = true;

    int TracerPosition = 0;
    int TracerBone = 0;
    bool DrawTracers = false;
    float TracerThickness = 2.0;
    bool DrawNames = true;
    bool DrawStatus = false;
    bool DrawWeapon = true;
    bool DrawLegend = true;
    bool ShowMaxStatusValues = true;
  };

  namespace SenseTeammate {
    bool DrawTeam = false;
    bool DrawBoxes = true;
    int BoxType = 0;
    int BoxStyle = 0;
    float BoxThickness = 1.0;

    bool DrawSkeleton = true;
    float SkeletonThickness = 1.0;
    bool DrawHeadCircle = true;
    float HeadCircleThickness = 1.0;

    bool DrawBars = true;
    bool HealthBar = true;
    bool ShieldBar = true;
    int BarMode = 0;
    int BarStyle = 0;
    float BarThickness = 1.0f;
    float BarThickness2 = 0.05f;
    float BarHeight = 5.0f;
    float BarWidth = 60.0f;
    int BarColorMode = 0;
    bool BarBackground = false;

    int WeaponColorType = 1;
    bool DrawDistance = true;

    int TracerPosition = 0;
    int TracerBone = 0;
    bool DrawTracers = true;
    float TracerThickness = 2.0;
    bool DrawNames = true;
    bool DrawStatus = true;
    bool DrawWeapon = false;
    bool DrawLegend = false;
    bool ShowMaxStatusValues = true;
  };

  namespace SensePositions {
    // 0 = Top 1, 1 = Top 2, 2 = Bottom 1, 3 = Bottom 2, 4 = Bottom 3
    int NamePosition = 0;
    int DistancePosition = 0;
    int LegendPosition = 2;
    int WeaponPosition = 3;
    int StatusPosition = 4;
  };

  namespace Radar {
    bool MiniMap = false;
    float MiniMapRange = 100;
    int MiniMapScaleX = 215;
    int MiniMapScaleY = 215;
    int MiniMapDotSize = 5;
    int MiniMapBlackBGSize = 0;
    bool MiniMapGuides = false;

    bool BigMap = false;
    int BigMapBind = 21;

    float CircleColorR = 0.99;
    float CircleColorG = 0;
    float CircleColorB = 0;
    float CircleColorA = 0.99;
  };

  namespace Misc {
    bool SuperGlide = true;
    int SuperGlideMode = 0;
    int SuperGlideFPS = 1; // 0 = 75, 1 = 144, 2 = 240

    bool QuickTurn = false;
    int QuickTurnAngle = 180;
    int QuickTurnBind = 58;

    bool BHop = false;
    int BHopDelay = 25;
    int BHopBind = 34;

    bool RapidFire = false;
    int RapidFireDelay = 75;
    int RapidFireBind = 34;

    // Rapid Fire Weapon Toggles
    // Light
    bool RapidP2020 = true;
    bool RapidR301 = true;
    bool RapidG7 = true;
    // Heavy
    bool RapidFlatline = true;
    bool RapidHemlock = true;
    bool RapidProwler = true;
    // Energy
    bool RapidNemesis = true;
    // Shotgun
    bool RapidMozambique = true;
    bool RapidEVA8 = true;
    // Legendary
    bool RapidWingman = true;

    bool SkinChanger = false;
    // Weapon IDs
    // Light
    int SkinP2020 = 1;
    int SkinRE45 = 1;
    int SkinALTERNATOR = 1;
    int SkinR99 = 1;
    int SkinR301 = 1;
    int SkinSPITFIRE = 1;
    int SkinG7 = 1;

    // Heavy
    int SkinFLATLINE = 1;
    int SkinHEMLOCK = 1;
    int SkinREPEATER = 1;
    int SkinRAMPAGE = 1;
    int SkinCAR = 1;

    // Energy
    int SkinHAVOC = 1;
    int SkinDEVOTION = 1;
    int SkinLSTAR = 1;
    int SkinTRIPLETAKE = 1;
    int SkinVOLT = 1;
    int SkinNEMESIS = 1;

    // Shotgun
    int SkinMOZAMBIQUE = 1;
    int SkinEVA8 = 1;
    int SkinPEACEKEEPER = 1;
    int SkinMASTIFF = 1;

    // Snipers
    int SkinLONGBOW = 1;
    int SkinCHARGE_RIFLE = 1;
    int SkinSENTINEL = 1;

    // Legendary
    int SkinWINGMAN = 1;
    int SkinPROWLER = 1;
    int SkinBOCEK = 1;
    int SkinKRABER = 1;
  };

  namespace Colors {
    int WeaponColorMode = 0;

    float FOVColorR = 0.99;
    float FOVColorG = 0.99;
    float FOVColorB = 0.99;
    float FOVColorA = 0.99;

    float FilledFOVColorR = 0;
    float FilledFOVColorG = 0;
    float FilledFOVColorB = 0;
    float FilledFOVColorA = 0.11;

    float CrosshairColorR = 0.99;
    float CrosshairColorG = 0.99;
    float CrosshairColorB = 0.99;
    float CrosshairColorA = 0.99;

    float SpectatorWarningColorR = 0.99;
    float SpectatorWarningColorG = 0;
    float SpectatorWarningColorB = 0;
    float SpectatorWarningColorA = 0.99;

    float VisibleWarningColorR = 0;
    float VisibleWarningColorG = 0.99;
    float VisibleWarningColorB = 0;
    float VisibleWarningColorA = 0.99;
  };

  namespace EnemyColors {
    // ESP
    float InvisibleBoxColorR = 0.99;
    float InvisibleBoxColorG = 0;
    float InvisibleBoxColorB = 0;
    float InvisibleBoxColorA = 0.99;
    float VisibleBoxColorR = 0;
    float VisibleBoxColorG = 0.99;
    float VisibleBoxColorB = 0;
    float VisibleBoxColorA = 0.99;

    float InvisibleFilledBoxColorR = 0.99;
    float InvisibleFilledBoxColorG = 0;
    float InvisibleFilledBoxColorB = 0;
    float InvisibleFilledBoxColorA = 0.99;
    float VisibleFilledBoxColorR = 0;
    float VisibleFilledBoxColorG = 0.99;
    float VisibleFilledBoxColorB = 0;
    float VisibleFilledBoxColorA = 0.99;

    float InvisibleTracerColorR = 0.99;
    float InvisibleTracerColorG = 0;
    float InvisibleTracerColorB = 0;
    float InvisibleTracerColorA = 0.99;
    float VisibleTracerColorR = 0;
    float VisibleTracerColorG = 0.99;
    float VisibleTracerColorB = 0;
    float VisibleTracerColorA = 0.99;

    float InvisibleSkeletonColorR = 0.99;
    float InvisibleSkeletonColorG = 0;
    float InvisibleSkeletonColorB = 0;
    float InvisibleSkeletonColorA = 0.99;
    float VisibleSkeletonColorR = 0;
    float VisibleSkeletonColorG = 0.99;
    float VisibleSkeletonColorB = 0;
    float VisibleSkeletonColorA = 0.99;

    float InvisibleHeadCircleColorR = 0.99;
    float InvisibleHeadCircleColorG = 0;
    float InvisibleHeadCircleColorB = 0;
    float InvisibleHeadCircleColorA = 0.99;
    float VisibleHeadCircleColorR = 0;
    float VisibleHeadCircleColorG = 0.99;
    float VisibleHeadCircleColorB = 0;
    float VisibleHeadCircleColorA = 0.99;

    float InvisibleNameColorR = 0.99;
    float InvisibleNameColorG = 0;
    float InvisibleNameColorB = 0;
    float InvisibleNameColorA = 0.99;
    float VisibleNameColorR = 0;
    float VisibleNameColorG = 0.99;
    float VisibleNameColorB = 0;
    float VisibleNameColorA = 0.99;

    float InvisibleDistanceColorR = 0.99;
    float InvisibleDistanceColorG = 0;
    float InvisibleDistanceColorB = 0;
    float InvisibleDistanceColorA = 0.99;
    float VisibleDistanceColorR = 0;
    float VisibleDistanceColorG = 0.99;
    float VisibleDistanceColorB = 0;
    float VisibleDistanceColorA = 0.99;

    float InvisibleLegendColorR = 0.99;
    float InvisibleLegendColorG = 0;
    float InvisibleLegendColorB = 0;
    float InvisibleLegendColorA = 0.99;
    float VisibleLegendColorR = 0;
    float VisibleLegendColorG = 0.99;
    float VisibleLegendColorB = 0;
    float VisibleLegendColorA = 0.99;

    // Bar
    int BarColorMode = 2;
    // WeaponESP Colors
    float InvisibleWeaponColorR = 0.99;
    float InvisibleWeaponColorG = 0;
    float InvisibleWeaponColorB = 0;
    float InvisibleWeaponColorA = 0.99;
    float VisibleWeaponColorR = 0;
    float VisibleWeaponColorG = 0.99;
    float VisibleWeaponColorB = 0;
    float VisibleWeaponColorA = 0.99;
    // Multiple
    float LightWeaponColorR = 0.990;
    float LightWeaponColorG = 0.768;
    float LightWeaponColorB = 0.039;
    float LightWeaponColorA = 0.99;
    float HeavyWeaponColorR = 0.00990;
    float HeavyWeaponColorG = 0.990;
    float HeavyWeaponColorB = 0.761;
    float HeavyWeaponColorA = 0.99;
    float EnergyWeaponColorR = 0;
    float EnergyWeaponColorG = 0.99;
    float EnergyWeaponColorB = 0;
    float EnergyWeaponColorA = 0.99;
    float ShotgunWeaponColorR = 0.99;
    float ShotgunWeaponColorG = 0;
    float ShotgunWeaponColorB = 0;
    float ShotgunWeaponColorA = 0.99;
    float SniperWeaponColorR = 0.00990;
    float SniperWeaponColorG = 0.337;
    float SniperWeaponColorB = 0.990;
    float SniperWeaponColorA = 0.99;
    float LegendaryWeaponColorR = 0.99;
    float LegendaryWeaponColorG = 0.530;
    float LegendaryWeaponColorB = 0.945;
    float LegendaryWeaponColorA = 0.99;
    float MeleeWeaponColorR = 0.99;
    float MeleeWeaponColorG = 0.99;
    float MeleeWeaponColorB = 0.99;
    float MeleeWeaponColorA = 0.99;
    float ThrowableWeaponColorR = 0.990;
    float ThrowableWeaponColorG = 0.974;
    float ThrowableWeaponColorB = 0.0495;
    float ThrowableWeaponColorA = 0.99;

    // Glow
    float InvisibleGlowColorR = 1;
    float InvisibleGlowColorG = 0;
    float InvisibleGlowColorB = 0;
    float VisibleGlowColorR = 0;
    float VisibleGlowColorG = 1;
    float VisibleGlowColorB = 0;

    float RedShieldColorR = 1;
    float RedShieldColorG = 0;
    float RedShieldColorB = 0;
    float PurpleShieldColorR = 0.5;
    float PurpleShieldColorG = 0;
    float PurpleShieldColorB = 0.5;
    float BlueShieldColorR = 0;
    float BlueShieldColorG = 0.5;
    float BlueShieldColorB = 1;
    float GreyShieldColorR = 0.540;
    float GreyShieldColorG = 0.545;
    float GreyShieldColorB = 0.545;
  };

  namespace TeammateColors {
    float InvisibleBoxColorR = 0.99;
    float InvisibleBoxColorG = 0;
    float InvisibleBoxColorB = 0;
    float InvisibleBoxColorA = 0.99;
    float VisibleBoxColorR = 0;
    float VisibleBoxColorG = 0.99;
    float VisibleBoxColorB = 0;
    float VisibleBoxColorA = 0.99;

    float InvisibleFilledBoxColorR = 0.99;
    float InvisibleFilledBoxColorG = 0;
    float InvisibleFilledBoxColorB = 0;
    float InvisibleFilledBoxColorA = 0.99;
    float VisibleFilledBoxColorR = 0;
    float VisibleFilledBoxColorG = 0.99;
    float VisibleFilledBoxColorB = 0;
    float VisibleFilledBoxColorA = 0.99;

    float InvisibleTracerColorR = 0.99;
    float InvisibleTracerColorG = 0;
    float InvisibleTracerColorB = 0;
    float InvisibleTracerColorA = 0.99;
    float VisibleTracerColorR = 0;
    float VisibleTracerColorG = 0.99;
    float VisibleTracerColorB = 0;
    float VisibleTracerColorA = 0.99;

    float InvisibleSkeletonColorR = 0.99;
    float InvisibleSkeletonColorG = 0;
    float InvisibleSkeletonColorB = 0;
    float InvisibleSkeletonColorA = 0.99;
    float VisibleSkeletonColorR = 0;
    float VisibleSkeletonColorG = 0.99;
    float VisibleSkeletonColorB = 0;
    float VisibleSkeletonColorA = 0.99;

    float InvisibleHeadCircleColorR = 0.99;
    float InvisibleHeadCircleColorG = 0;
    float InvisibleHeadCircleColorB = 0;
    float InvisibleHeadCircleColorA = 0.99;
    float VisibleHeadCircleColorR = 0;
    float VisibleHeadCircleColorG = 0.99;
    float VisibleHeadCircleColorB = 0;
    float VisibleHeadCircleColorA = 0.99;

    float InvisibleNameColorR = 0.99;
    float InvisibleNameColorG = 0;
    float InvisibleNameColorB = 0;
    float InvisibleNameColorA = 0.99;
    float VisibleNameColorR = 0;
    float VisibleNameColorG = 0.99;
    float VisibleNameColorB = 0;
    float VisibleNameColorA = 0.99;

    float InvisibleDistanceColorR = 0.99;
    float InvisibleDistanceColorG = 0;
    float InvisibleDistanceColorB = 0;
    float InvisibleDistanceColorA = 0.99;
    float VisibleDistanceColorR = 0;
    float VisibleDistanceColorG = 0.99;
    float VisibleDistanceColorB = 0;
    float VisibleDistanceColorA = 0.99;

    float InvisibleLegendColorR = 0.99;
    float InvisibleLegendColorG = 0;
    float InvisibleLegendColorB = 0;
    float InvisibleLegendColorA = 0.99;
    float VisibleLegendColorR = 0;
    float VisibleLegendColorG = 0.99;
    float VisibleLegendColorB = 0;
    float VisibleLegendColorA = 0.99;

    float InvisibleWeaponColorR = 0.99;
    float InvisibleWeaponColorG = 0;
    float InvisibleWeaponColorB = 0;
    float InvisibleWeaponColorA = 0.99;
    float VisibleWeaponColorR = 0;
    float VisibleWeaponColorG = 0.99;
    float VisibleWeaponColorB = 0;
    float VisibleWeaponColorA = 0.99;

    // Bar
    int BarColorMode = 2;
    // WeaponESP Colors
    float InvisibleWeaponColor[4] = {0.99, 0, 0, 0.99};
    float VisibleWeaponColor[4] = {0, 0.99, 0, 0.99};
    // Multiple
    float LightWeaponColorR = 0.990;
    float LightWeaponColorG = 0.768;
    float LightWeaponColorB = 0.039;
    float LightWeaponColorA = 0.99;
    float HeavyWeaponColorR = 0.00990;
    float HeavyWeaponColorG = 0.990;
    float HeavyWeaponColorB = 0.761;
    float HeavyWeaponColorA = 0.99;
    float EnergyWeaponColorR = 0;
    float EnergyWeaponColorG = 0.99;
    float EnergyWeaponColorB = 0;
    float EnergyWeaponColorA = 0.99;
    float ShotgunWeaponColorR = 0.99;
    float ShotgunWeaponColorG = 0;
    float ShotgunWeaponColorB = 0;
    float ShotgunWeaponColorA = 0.99;
    float SniperWeaponColorR = 0.00990;
    float SniperWeaponColorG = 0.337;
    float SniperWeaponColorB = 0.990;
    float SniperWeaponColorA = 0.99;
    float LegendaryWeaponColorR = 0.99;
    float LegendaryWeaponColorG = 0.530;
    float LegendaryWeaponColorB = 0.945;
    float LegendaryWeaponColorA = 0.99;
    float MeleeWeaponColorR = 0.99;
    float MeleeWeaponColorG = 0.99;
    float MeleeWeaponColorB = 0.99;
    float MeleeWeaponColorA = 0.99;
    float ThrowableWeaponColorR = 0.990;
    float ThrowableWeaponColorG = 0.974;
    float ThrowableWeaponColorB = 0.0495;
    float ThrowableWeaponColorA = 0.99;
  };

  namespace Watermark {
    bool Enabled = true;
    int WatermarkPosition = 0;
    bool Name = true;
    bool ProcessingSpeed = true;
    bool Spectators = true;
    bool GameFPS = true;
  };
};
