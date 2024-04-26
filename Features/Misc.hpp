#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <atomic>
#include <vector>
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/Level.hpp"

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
#include "../Utils/Weapons.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

typedef void *PVOID;

struct Misc {
  std::set<int> RapidFireList = {};

  float HangOnWall1;
  float HangOnWall2;
  float TraversalProgress1;
  float HangOnWall3;
  float HangOnWall4;
  float StartJumpTime1;

  XDisplay *X11Display;
  Level *Map;
  LocalPlayer *Myself;
  std::vector<Player *> *Players;

  Misc(XDisplay *X11Display, Level *Map, LocalPlayer *Myself, std::vector<Player *> *GamePlayers) {
    this->X11Display = X11Display;
    this->Map = Map;
    this->Myself = Myself;
    this->Players = GamePlayers;
  }

  bool Save() {
    try {
      Config::Misc::SuperGlide = Features::Misc::SuperGlide;
      Config::Misc::SuperGlideFPS = Features::Misc::SuperGlideFPS;

      Config::Misc::QuickTurn = Features::Misc::QuickTurn;
      Config::Misc::QuickTurnAngle = Features::Misc::QuickTurnAngle;
      Config::Misc::QuickTurnBind = static_cast<int>(Features::Misc::QuickTurnBind);

      Config::Misc::BHop = Features::Misc::BHop;
      Config::Misc::BHopDelay = Features::Misc::BHopDelay;
      Config::Misc::BHopBind = static_cast<int>(Features::Misc::BHopBind);

      Config::Misc::RapidFire = Features::Misc::RapidFire;
      Config::Misc::RapidFireDelay = Features::Misc::RapidFireDelay;
      Config::Misc::RapidFireBind = static_cast<int>(Features::Misc::RapidFireBind);
      // Rapid Fire Weapons
      Config::Misc::RapidP2020 = Features::Misc::RapidP2020;
      Config::Misc::RapidR301 = Features::Misc::RapidR301;
      Config::Misc::RapidG7 = Features::Misc::RapidG7;
      Config::Misc::RapidFlatline = Features::Misc::RapidFlatline;
      Config::Misc::RapidHemlock = Features::Misc::RapidHemlock;
      Config::Misc::RapidProwler = Features::Misc::RapidProwler;
      Config::Misc::RapidNemesis = Features::Misc::RapidNemesis;
      Config::Misc::RapidMozambique = Features::Misc::RapidMozambique;
      Config::Misc::RapidEVA8 = Features::Misc::RapidEVA8;
      Config::Misc::RapidWingman = Features::Misc::RapidWingman;

      Config::Misc::SkinChanger = Features::Misc::SkinChanger;
      // Weapon IDs
      // Light
      Config::Misc::SkinP2020 = Features::Misc::SkinP2020;
      Config::Misc::SkinRE45 = Features::Misc::SkinRE45;
      Config::Misc::SkinALTERNATOR = Features::Misc::SkinALTERNATOR;
      Config::Misc::SkinR99 = Features::Misc::SkinR99;
      Config::Misc::SkinR301 = Features::Misc::SkinR301;
      Config::Misc::SkinSPITFIRE = Features::Misc::SkinSPITFIRE;
      Config::Misc::SkinG7 = Features::Misc::SkinG7;

      // Heavy
      Config::Misc::SkinFLATLINE = Features::Misc::SkinFLATLINE;
      Config::Misc::SkinHEMLOCK = Features::Misc::SkinHEMLOCK;
      Config::Misc::SkinREPEATER = Features::Misc::SkinREPEATER;
      Config::Misc::SkinRAMPAGE = Features::Misc::SkinRAMPAGE;
      Config::Misc::SkinCAR = Features::Misc::SkinCAR;

      // Energy
      Config::Misc::SkinHAVOC = Features::Misc::SkinHAVOC;
      Config::Misc::SkinDEVOTION = Features::Misc::SkinDEVOTION;
      Config::Misc::SkinLSTAR = Features::Misc::SkinLSTAR;
      Config::Misc::SkinTRIPLETAKE = Features::Misc::SkinTRIPLETAKE;
      Config::Misc::SkinVOLT = Features::Misc::SkinVOLT;
      Config::Misc::SkinNEMESIS = Features::Misc::SkinNEMESIS;

      // Shotgun
      Config::Misc::SkinMOZAMBIQUE = Features::Misc::SkinMOZAMBIQUE;
      Config::Misc::SkinEVA8 = Features::Misc::SkinEVA8;
      Config::Misc::SkinPEACEKEEPER = Features::Misc::SkinPEACEKEEPER;
      Config::Misc::SkinMASTIFF = Features::Misc::SkinMASTIFF;

      // Snipers
      Config::Misc::SkinLONGBOW = Features::Misc::SkinLONGBOW;
      Config::Misc::SkinCHARGE_RIFLE = Features::Misc::SkinCHARGE_RIFLE;
      Config::Misc::SkinSENTINEL = Features::Misc::SkinSENTINEL;

      // Legendary
      Config::Misc::SkinWINGMAN = Features::Misc::SkinWINGMAN;
      Config::Misc::SkinPROWLER = Features::Misc::SkinPROWLER;
      Config::Misc::SkinBOCEK = Features::Misc::SkinBOCEK;
      Config::Misc::SkinKRABER = Features::Misc::SkinKRABER;
      return true;
    } catch (...) { return false; }
  }

  void UpdateRapidFireList() {
    // Update RapidFireList
    RapidFireList.clear();
    if (Features::Misc::RapidP2020)
      RapidFireList.insert(WeaponIDs::WEAPON_P2020);
    if (Features::Misc::RapidR301)
      RapidFireList.insert(WeaponIDs::WEAPON_R301);
    if (Features::Misc::RapidG7)
      RapidFireList.insert(WeaponIDs::WEAPON_G7);
    if (Features::Misc::RapidFlatline)
      RapidFireList.insert(WeaponIDs::WEAPON_FLATLINE);
    if (Features::Misc::RapidHemlock)
      RapidFireList.insert(WeaponIDs::WEAPON_HEMLOCK);
    if (Features::Misc::RapidProwler)
      RapidFireList.insert(WeaponIDs::WEAPON_PROWLER);
    if (Features::Misc::RapidNemesis)
      RapidFireList.insert(WeaponIDs::WEAPON_NEMESIS);
    if (Features::Misc::RapidMozambique)
      RapidFireList.insert(WeaponIDs::WEAPON_MOZAMBIQUE);
    if (Features::Misc::RapidWingman)
      RapidFireList.insert(WeaponIDs::WEAPON_WINGMAN);
    if (Features::Misc::RapidEVA8)
      RapidFireList.insert(WeaponIDs::WEAPON_EVA8);
  }

  void Update() {
    if (!Map->IsPlayable)
      return;
    if (Myself->IsDead)
      return;

    if (Features::Misc::SkinChanger) {
      long wephandle = Memory::Read<long>(Myself->BasePointer + OFF_WEAPON_HANDLE);
      wephandle &= 0xffff;
      long wep_entity = Myself->WeaponEntity;
      std::map<int, int> weaponSkinMap;
      // Light ammo weapons
      weaponSkinMap[WeaponIDs::WEAPON_P2020] = Features::Misc::SkinP2020;
      weaponSkinMap[WeaponIDs::WEAPON_RE45] = Features::Misc::SkinRE45;
      weaponSkinMap[WeaponIDs::WEAPON_ALTERNATOR] = Features::Misc::SkinALTERNATOR;
      weaponSkinMap[WeaponIDs::WEAPON_R99] = Features::Misc::SkinR99;
      weaponSkinMap[WeaponIDs::WEAPON_R301] = Features::Misc::SkinR301;
      weaponSkinMap[WeaponIDs::WEAPON_SPITFIRE] = Features::Misc::SkinSPITFIRE;
      weaponSkinMap[WeaponIDs::WEAPON_G7] = Features::Misc::SkinG7;
      // Heavy ammo weapons
      weaponSkinMap[WeaponIDs::WEAPON_CAR] = Features::Misc::SkinCAR;
      weaponSkinMap[WeaponIDs::WEAPON_RAMPAGE] = Features::Misc::SkinRAMPAGE;
      weaponSkinMap[WeaponIDs::WEAPON_REPEATER] = Features::Misc::SkinREPEATER;
      weaponSkinMap[WeaponIDs::WEAPON_HEMLOCK] = Features::Misc::SkinHEMLOCK;
      weaponSkinMap[WeaponIDs::WEAPON_FLATLINE] = Features::Misc::SkinFLATLINE;
      // Energy ammo weapons
      weaponSkinMap[WeaponIDs::WEAPON_NEMESIS] = Features::Misc::SkinNEMESIS;
      weaponSkinMap[WeaponIDs::WEAPON_VOLT] = Features::Misc::SkinVOLT;
      weaponSkinMap[WeaponIDs::WEAPON_TRIPLETAKE] = Features::Misc::SkinTRIPLETAKE;
      weaponSkinMap[WeaponIDs::WEAPON_LSTAR] = Features::Misc::SkinLSTAR;
      weaponSkinMap[WeaponIDs::WEAPON_DEVOTION] = Features::Misc::SkinDEVOTION;
      weaponSkinMap[WeaponIDs::WEAPON_HAVOC] = Features::Misc::SkinHAVOC;
      // Sniper ammo weapons
      weaponSkinMap[WeaponIDs::WEAPON_SENTINEL] = Features::Misc::SkinSENTINEL;
      weaponSkinMap[WeaponIDs::WEAPON_CHARGE_RIFLE] = Features::Misc::SkinCHARGE_RIFLE;
      weaponSkinMap[WeaponIDs::WEAPON_LONGBOW] = Features::Misc::SkinLONGBOW;
      // Shotgun ammo weapons
      weaponSkinMap[WeaponIDs::WEAPON_MOZAMBIQUE] = Features::Misc::SkinMOZAMBIQUE;
      weaponSkinMap[WeaponIDs::WEAPON_EVA8] = Features::Misc::SkinEVA8;
      weaponSkinMap[WeaponIDs::WEAPON_PEACEKEEPER] = Features::Misc::SkinPEACEKEEPER;
      weaponSkinMap[WeaponIDs::WEAPON_MASTIFF] = Features::Misc::SkinMASTIFF;
      // Legendary ammo weapons
      weaponSkinMap[WeaponIDs::WEAPON_WINGMAN] = Features::Misc::SkinWINGMAN;
      weaponSkinMap[WeaponIDs::WEAPON_PROWLER] = Features::Misc::SkinPROWLER;
      weaponSkinMap[WeaponIDs::WEAPON_BOCEK] = Features::Misc::SkinBOCEK;
      weaponSkinMap[WeaponIDs::WEAPON_KRABER] = Features::Misc::SkinKRABER;

      int waponIndex = Memory::Read<int>(wep_entity + OFF_WEAPON_INDEX);
      if (weaponSkinMap.count(waponIndex) == 0)
        return;
      int skinID = weaponSkinMap[waponIndex];
      // printf("Weapon: %s Activated Skin ID: %d \n", WeaponName(waponIndex).c_str(), skinID);
      Memory::Write<int>(wep_entity + OFF_SKIN, skinID);
    }
  } // End of update

  void SuperGlide() {
    UpdateSuperGlide();
    if (InputManager::isKeyDownOrPress(InputKeyType::KEYBOARD_SPACE)) {
      static float startjumpTime = 0;
      static bool startSg = false;
      static float traversalProgressTmp = 0.0;

      float worldtime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE); // Current time
      float traversalStartTime = Memory::Read<float>(Myself->BasePointer + OFF_TRAVERSAL_START_TIME); // Time to start wall climbing
      float traversalProgress = Memory::Read<float>(Myself->BasePointer + OFF_TRAVERSAL_PROGRESS); // Wall climbing, if > 0.87 it is almost over.
      float HangOnWall = -(traversalStartTime - worldtime);

      if (HangOnWall > HangOnWall1 && HangOnWall < HangOnWall2) { Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4); }
      if (traversalProgress > TraversalProgress1 && !startSg && HangOnWall > HangOnWall3 && HangOnWall < HangOnWall4) {
        // start SG
        startjumpTime = worldtime;
        startSg = true;
      }
      if (startSg) {
        Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
        while (Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE) - startjumpTime < StartJumpTime1); //why is this here...
        {
          Memory::Write<int>(OFF_REGION + OFF_IN_DUCK + 0x8, 6);
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
          Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
          std::this_thread::sleep_for(std::chrono::milliseconds(600));
        }
        startSg = false;
      }
    }
  }

  void UpdateSuperGlide() {
    if (Features::Misc::SuperGlideFPS == 0) // 75 FPS
    {
      HangOnWall1 = 0.1;
      HangOnWall2 = 0.12;
      TraversalProgress1 = 0.87f;
      HangOnWall3 = 0.1f;
      HangOnWall4 = 1.5f;
      StartJumpTime1 = 0.011;
    } else if (Features::Misc::SuperGlideFPS == 1) // 144 FPS
    {
      HangOnWall1 = 0.05;
      HangOnWall2 = 0.07;
      TraversalProgress1 = 0.90f;
      HangOnWall3 = 0.05f;
      HangOnWall4 = 0.75f;
      StartJumpTime1 = 0.007;
    } else if (Features::Misc::SuperGlideFPS == 1) // 240 FPS
    {
      HangOnWall1 = 0.033;
      HangOnWall2 = 0.04;
      TraversalProgress1 = 0.95f;
      HangOnWall3 = 0.033f;
      HangOnWall4 = 0.2f;
      StartJumpTime1 = 0.004;
    }
  }

  void BHop() {
    if (InputManager::isKeyDownOrPress(Features::Misc::BHopBind) && InputManager::isKeyDownOrPress(InputKeyType::KEYBOARD_SPACE)) {
      std::this_thread::sleep_for(std::chrono::milliseconds(Features::Misc::BHopDelay));
      Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x08, 5);
      std::this_thread::sleep_for(std::chrono::milliseconds(Features::Misc::BHopDelay));
      Memory::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x08, 4);
    }
  }

  void QuickTurn() {
    if (Features::Misc::QuickTurn) {
      FloatVector2D localYawtoClamp = Myself->viewAngles;
      localYawtoClamp.clamp();
      float localYaw = localYawtoClamp.y;
      // quickTurn
      if (InputManager::isKeyDown(Features::Misc::QuickTurnBind)) {
        Myself->setYaw((localYaw + Features::Misc::QuickTurnAngle));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
    }
  }

  void RapidFire() {
    if (!Myself->IsCombatReady())
      return;
    if (RapidFireList.find(Myself->WeaponIndex) == RapidFireList.end())
      return;
    if (InputManager::isKeyDownOrPress(Features::Misc::RapidFireBind)) {
      X11Display->MouseClickLeft();
      std::this_thread::sleep_for(std::chrono::milliseconds(Features::Misc::RapidFireDelay));
    }
  }
};
