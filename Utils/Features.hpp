#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../Utils/HitboxType.hpp"
#include "../Utils/InputTypes.hpp"

namespace Features {
  namespace Home {
    inline bool IsMenuOpened = true;
  };

  namespace Settings {
    bool ESPEnabled = true;
    bool OverlayEnabled = true;
    bool FPSCap = false;
    int CappedFPS = 144;
  };

  namespace AimbotHitboxes {
    HitboxType Hitbox = HitboxType::UpperChest;
  };

  namespace AimbotBinds {
    InputKeyType AimBind = InputKeyType::MOUSE_Left;
    InputKeyType ExtraBind = InputKeyType::MOUSE_Right;
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

    //Weapon Toggles
    std::set<int> AimList = {};
    //Light
    bool P2020 = true;
    bool RE45 = true;
    bool Alternator = true;
    bool R99 = true;
    bool R301 = true;
    bool Spitfire = true;
    bool G7 = true;

    //Heavy
    bool Flatline = true;
    bool Hemlock = true;
    bool Repeater = true;
    bool Rampage = true;
    bool CARSMG = true;

    //Energy
    bool Havoc = true;
    bool Devotion = true;
    bool LSTAR = true;
    bool TripleTake = true;
    bool Volt = true;
    bool Nemesis = true;

    //Shotgun
    bool Mozambique = true;
    bool EVA8 = true;
    bool Peacekeeper = true;
    bool Mastiff = true;

    //Snipers
    bool Longbow = true;
    bool ChargeRifle = true;
    bool Sentinel = true;

    //Legendary
    bool Wingman = true;
    bool Prowler = true;
    bool Bocek = true;
    bool Kraber = true;
    bool Knife = true;
  };

  namespace RCS {
    bool RCSEnabled = false;
    std::set<int> RCSList = {};
    int RCSMode = 0;

    bool OnADS = true;

    float PitchPower = 3;
    float YawPower = 3;
    float PitchReduction = 50;
    float YawReduction = 50;

    //Weapon Toggles
    //Light
    bool P2020 = true;
    bool RE45 = true;
    bool Alternator = true;
    bool R99 = true;
    bool R301 = true;
    bool Spitfire = true;
    bool G7 = true;

    //Heavy
    bool Flatline = true;
    bool Hemlock = true;
    bool Repeater = true;
    bool Rampage = true;
    bool CARSMG = true;

    //Energy
    bool Havoc = true;
    bool Devotion = true;
    bool LSTAR = true;
    bool TripleTake = true;
    bool Volt = true;
    bool Nemesis = true;

    //Shotgun
    bool Mozambique = true;
    bool EVA8 = true;
    bool Peacekeeper = true;
    bool Mastiff = true;

    //Snipers
    bool Longbow = true;
    bool ChargeRifle = true;
    bool Sentinel = true;

    //Legendary
    bool Wingman = true; //Emotional damage!
    bool Prowler = true;
    bool Kraber = false;

    //---------------Advanced---------------//
    bool AdvancedRCS = false;
    float AdvancedPitchPower = 10;
    float AdvancedYawPower = 10;
    float AdvancedPitchReduction = 25;
    float AdvancedYawReduction = 25;

    //Weapons
    //Light
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
    //Heavy
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
    //Energy
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
    //Shotguns
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
    //Snipers
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
    //Legendary
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
    InputKeyType TriggerBind = InputKeyType::MOUSE_Right;
    bool OnADS = true;
    bool HipfireShotguns = false;
    int Delay = 100;
    float Range = 200;
    float RangeHipfire = 70;

    //Weapon Toggles

    //Light
    bool P2020 = false;
    bool RE45 = false;
    bool Alternator = false;
    bool R99 = false;
    bool R301 = false;
    bool Spitfire = false;
    bool G7 = true;

    //Heavy
    bool Flatline = false;
    bool Hemlock = false;
    bool Repeater = true;
    bool Rampage = false;
    bool CARSMG = false;

    //Energy
    bool Havoc = false;
    bool Devotion = false;
    bool LSTAR = false;
    bool TripleTake = true;
    bool Volt = false;
    bool Nemesis = false;

    //Shotgun
    bool Mozambique = true;
    bool EVA8 = true;
    bool Peacekeeper = true;
    bool Mastiff = true;

    //Snipers
    bool Longbow = true;
    bool ChargeRifle = true;
    bool Sentinel = true;

    //Legendary
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
    int InsideFunction = 2; //Leave
    int OutlineFunction = 125; //Leave
    int BodyStyle = 15;
    int OutlineStyle = 1;

    bool ViewModelGlow = false;
    static int ViewModelGlowSetting = 65;
    static int ViewModelGlowCombo;
    bool ViewModelGlowLoop = false;
    int ViewModelGlowLoopDelay = 200;

    namespace Item {
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
  };

  namespace Sense {
    bool Enabled = false;

    namespace Enemy {
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

    namespace Teammate {
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

    namespace Positions {
      // 0 = Top 1, 1 = Top 2, 2 = Bottom 1, 3 = Bottom 2, 4 = Bottom 3
      int NamePosition = 0;
      int DistancePosition = 0;
      int LegendPosition = 2;
      int WeaponPosition = 3;
      int StatusPosition = 4;
    };

    // Aimbot
    bool DrawFOVCircle = false;
    bool DrawFilledFOVCircle = false;
    float FOVThickness = 1.0;
    float GameFOV = 120;

    //Other
    bool DrawCrosshair = true;
    float CrosshairSize = 7.0;
    float CrosshairThickness = 1.0;

    bool ShowSpectators = true;

    bool DrawSpectatorWarning = false;
    bool DrawVisibleWarning = false;
    bool WarningTextOutline = true;
    int WarningTextX;
    int WarningTextY;
    int WarningTextScale = 50;

    // Settings
    bool TextOutline = true;
    bool VisibilityCheck = false;
    float ESPMaxDistance = 200;
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
    InputKeyType BigMapBind = InputKeyType::KEYBOARD_K;
    float CircleColor[4] = {0.999, 0, 0, 0.999};
  };

  namespace Misc {
    bool SuperGlide = true;
    int SuperGlideFPS = 1; // 0 = 75, 1 = 144, 2 = 240

    bool QuickTurn = false;
    int QuickTurnAngle = 180;
    InputKeyType QuickTurnBind = InputKeyType::MOUSE_Middle;

    bool BHop = false;
    int BHopDelay = 25;
    InputKeyType BHopBind = InputKeyType::KEYBOARD_X;

    bool RapidFire = false;
    int RapidFireDelay = 75;
    InputKeyType RapidFireBind = InputKeyType::KEYBOARD_X;

    //Rapid Fire Weapon Toggles
    //Light
    bool RapidP2020 = true;
    bool RapidR301 = true;
    bool RapidG7 = true;
    //Heavy
    bool RapidFlatline = true;
    bool RapidHemlock = true;
    bool RapidProwler = true;
    //Energy
    bool RapidNemesis = true;
    //Shotgun
    bool RapidMozambique = true;
    bool RapidEVA8 = true;
    //Legendary
    bool RapidWingman = true;

    bool SkinChanger = false;
    //Weapon IDs
    //Light
    int SkinP2020 = 1;
    int SkinRE45 = 1;
    int SkinALTERNATOR = 1;
    int SkinR99 = 1;
    int SkinR301 = 1;
    int SkinSPITFIRE = 1;
    int SkinG7 = 1;

    //Heavy
    int SkinFLATLINE = 1;
    int SkinHEMLOCK = 1;
    int SkinREPEATER = 1;
    int SkinRAMPAGE = 1;
    int SkinCAR = 1;

    //Energy
    int SkinHAVOC = 1;
    int SkinDEVOTION = 1;
    int SkinLSTAR = 1;
    int SkinTRIPLETAKE = 1;
    int SkinVOLT = 1;
    int SkinNEMESIS = 1;

    //Shotgun
    int SkinMOZAMBIQUE = 1;
    int SkinEVA8 = 1;
    int SkinPEACEKEEPER = 1;
    int SkinMASTIFF = 1;

    //Snipers
    int SkinLONGBOW = 1;
    int SkinCHARGE_RIFLE = 1;
    int SkinSENTINEL = 1;

    //Legendary
    int SkinWINGMAN = 1;
    int SkinPROWLER = 1;
    int SkinBOCEK = 1;
    int SkinKRABER = 1;
  };

  namespace Colors {
    int WeaponColorMode = 0;

    namespace Enemy {
      //ESP
      float InvisibleBoxColor[4] = {0.99, 0, 0, 0.99};
      float VisibleBoxColor[4] = {0, 0.99, 0, 0.99};
      float InvisibleFilledBoxColor[4] = {0, 0, 0, 0.11};
      float VisibleFilledBoxColor[4] = {0, 0, 0, 0.11};
      float InvisibleTracerColor[4] = {0.99, 0, 0, 0.99};
      float VisibleTracerColor[4] = {0, 0.99, 0, 0.99};
      float InvisibleSkeletonColor[4] = {0.99, 0, 0, 0.99};
      float VisibleSkeletonColor[4] = {0, 0.99, 0, 0.99};
      float InvisibleHeadCircleColor[4] = {0.99, 0, 0, 0.99};
      float VisibleHeadCircleColor[4] = {0, 0.99, 0, 0.99};
      float InvisibleNameColor[4] = {0.99, 0, 0, 0.99};
      float VisibleNameColor[4] = {0, 0.99, 0, 0.99};
      float InvisibleDistanceColor[4] = {0.99, 0, 0, 0.99};
      float VisibleDistanceColor[4] = {0, 0.99, 0, 0.99};
      float InvisibleLegendColor[4] = {0.99, 0, 0, 0.99};
      float VisibleLegendColor[4] = {0, 0.99, 0, 0.99};
      float NearColor[4] = {0.99, 0.99, 0.99, 0.99};
      //Bar
      int BarColorMode = 2;
      //WeaponESP Colors
      float InvisibleWeaponColor[4] = {0.99, 0, 0, 0.99};
      float VisibleWeaponColor[4] = {0, 0.99, 0, 0.99};
      //Multiple
      float LightWeaponColor[4] = {0.990, 0.768, 0.039, 0.99};
      float HeavyWeaponColor[4] = {0.00990, 0.990, 0.761};
      float EnergyWeaponColor[4] = {0, 0.99, 0, 0.99};
      float ShotgunWeaponColor[4] = {0.99, 0, 0, 0.99};
      float SniperWeaponColor[4] = {0.00990, 0.337, 0.990, 0.99};
      float LegendaryWeaponColor[4] = {0.99, 0.530, 0.945};
      float MeleeWeaponColor[4] = {0.99, 0.99, 0.99, 0.99};
      float ThrowableWeaponColor[4] = {0.990, 0.974, 0.0495, 0.99};

      //Glow
      float InvisibleGlowColor[3] = {1, 0, 0};
      float VisibleGlowColor[3] = {0, 1, 0};
      float LowGlowColor[3] = {1, 1, 0};

      float RedShieldColor[3] = {1, 0, 0};
      float PurpleShieldColor[3] = {0.5, 0, 0.5};
      float BlueShieldColor[3] = {0, 0.5, 1};
      float GreyShieldColor[3] = {0.540, 0.545, 0.545};
    };

    namespace Teammate {
      float InvisibleBoxColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleBoxColor[4] = {0.00990, 0.827, 0.990, 0.99};
      float InvisibleFilledBoxColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleFilledBoxColor[4] = {0.00990, 0.827, 0.990, 0.99};
      float InvisibleTracerColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleTracerColor[4] = {0.00990, 0.827, 0.990, 0.99};
      float InvisibleSkeletonColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleSkeletonColor[4] = {0.00990, 0.827, 0.990, 0.99};
      float InvisibleHeadCircleColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleHeadCircleColor[4] = {0.00990, 0.827, 0.990, 0.99};
      float InvisibleNameColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleNameColor[4] = {0.00990, 0.827, 0.990, 0.99};
      float InvisibleDistanceColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleDistanceColor[4] = {0.00990, 0.827, 0.990, 0.99};
      float InvisibleLegendColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleLegendColor[4] = {0.00990, 0.827, 0.990, 0.99};
      float TeamNameColor[4] = {0.0846, 0.0693, 0.990, 0.99};

      //Bar
      int BarColorMode = 2;

      //WeaponESP Colors
      float InvisibleWeaponColor[4] = {0.0846, 0.0693, 0.990, 0.99};
      float VisibleWeaponColor[4] = {0.00990, 0.827, 0.990, 0.99};
      //Multiple
      float LightWeaponColor[4] = {0.990, 0.768, 0.039, 0.99};
      float HeavyWeaponColor[4] = {0.00990, 0.990, 0.761};
      float EnergyWeaponColor[4] = {0, 0.99, 0, 0.99};
      float ShotgunWeaponColor[4] = {0.99, 0, 0, 0.99};
      float SniperWeaponColor[4] = {0.00990, 0.337, 0.990, 0.99};
      float LegendaryWeaponColor[4] = {0.99, 0.530, 0.945};
      float MeleeWeaponColor[4] = {0.99, 0.99, 0.99, 0.99};
      float ThrowableWeaponColor[4] = {0.990, 0.974, 0.0495, 0.99};
    };

    float FOVColor[4] = {0.99, 0.99, 0.99, 0.99};
    float FilledFOVColor[4] = {0, 0, 0, 0.11};
    float CrosshairColor[4] = {0.99, 0.99, 0.99, 0.99};

    float SpectatorWarningColor[4] = {0.99, 0, 0, 0.99};
    float VisibleWarningColor[4] = {0, 0.99, 0, 0.99};
  };

  namespace Watermark {
    bool Watermark = true;
    int WatermarkPosition = 0;
    bool Name = true;
    bool ProcessingSpeed = true;
    bool Spectators = true;
    bool GameFPS = true;
  };
}; //End of namespace Features
