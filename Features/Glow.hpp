#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <unistd.h>

typedef unsigned long DWORD;
typedef int *DWORD_PTR;

#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Core/Offsets.hpp"
#include "../Core/GlowMode.hpp"
#include "../Core/Camera.hpp"
#include "../Core/Level.hpp"

#include "../Features/Legitbot.hpp"

#include "../Overlay/Overlay.hpp"
#include "../Overlay/Renderer.hpp"

#include "../Utils/Memory.hpp"
#include "../Utils/Color.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/HitboxType.hpp"

// UI //
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

// Geometry
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))
#define ABS(x) ((x < 0) ? (-x) : (x))

/*Viewmodel Glow Settings (OLD)
0, 2, 5 = Off (?)
1 = Pulsing Red + Red Outline
3 = Pulsing Cyan + Cyan Outline
4 = Fast Pulsing White + White Outline (?)
13 = Cyan Outline
15 = Light Red Outline
16 = WTF GREEN
24 = Yellow Outline
25 = Yellow Full Pulsing
27 = Solid Green
28 = Solid Orange
29 = Solid Yellow/Gold
30 = Solid Purple
31 = Solid Light Blue
32 = Solid White
47 = Solid Blue With Light Pulsing
49 = Blinding White
53 = Pulsing Red + Pulsing Red Outline
54 = Pulsing Whie + Pulsing Whie Outline
61 = Pulsing Orange
62 = Pulsing Orange Outline
64 = Faded Orange With Pulsing Line
65 = Green Outline
66 = Faded White With Pulsing Line
67 = Faded Red With Pulsing Line
68 = Faded Turquoise With Pulsing Line
70 = Red Outline
73 = Faded Yellow/Gold With Pulsing Line
74 = Solid Black
76 = Solid Pink
82 = Solid Pink With Red Outline
65 = Invisible with orange outline pulsing
93 = Invisible Red Pulsing
120 = Invisible
130 = Invisible With Pink Outline

Viewmodel Glow Settings (NEW)
0, 2, 5 = Off (?)
13 = Cyan Outline
15 = Light Red Outline
17 = White Outline
18 = Orange Outline
24 = Yellow Outline
25 = Solid Yellow Pulsing
27 = Solid Green
28 = Solid Orange
29 = Solid Yellow/Gold
30 = Solid Purple
31 = Solid Light Blue
32 = Solid Light Grey
34 = Solid White
35 = Solid Cyan (Light Blue)
36 = Solid Hot Pink
37 = Solid Light Yellow
38 = Solid Light Orange
39 = Solid Light Green
49 = Chrome
65 = Invisible Orange Pulsing
74 = Solid Black
93 = Invisible Red Pulsing
150 = Invisible Pink Outline


*/

/*
Item Glow Settings
Inside Function (First Value, not the outline of the object)
(May not apply for all objects, not sure)
If no color is clearly stated, then it depends on the color/rarity of the item
0 = clear
1 = pink
2 = lightly shaded
3 = fast fade from top to bottom, color is red on some and green on some
10 = invisible, disables item glow pretty much
12 = lightly shaded with lines + fading from top to bottom
13 = fading from top to bottom
14 = solid color but with a weird black fade from top to bottom
75 = dark color, with a very light fade
103 = fade from a certain point on the map? from right to left
109 = solid color, quite "thick"
115 = light orange on some objects, shaded and fading effect
117 = lightly shaded fading in and out to solid

Outline Function (Second Value, Outline Color)
0, 10, 75, 77 = off
4 = idfk multicolored or some shit ugly af
5 = flashing gold
6, 125 = solid color
7 = gold, makes thickness cap at 120 ish so its thin
8 = orange glow
9 = striped orange glow
101 = fuzzy glow
102 = light outline
103 = pulsing
107 = red
108 = brighter red
110 = fading in and out
120 = soft, requires high thickness
131 = visible outline only
135 = Distance Based Outline
138 = Distance Based Outline, Visible Only
140 = Green outline through walls, also disables insidefunction glow if not set to solid
261 = flashing gold again

*/

struct Glow {
  // Viewmodel Glow
  int ViewmodelGlowID;
  int ItemGlowInsideFunction = 0; // Leave
  int ItemGlowOutlineFunction = 138; // Leave

  std::chrono::milliseconds LastLoopTime;

  std::vector<GlowMode> *StoredGlowMode = new std::vector<GlowMode>;

  // Variables
  Camera *GameCamera;
  Level *Map;
  LocalPlayer *Myself;
  std::vector<Player *> *Players;
  std::chrono::milliseconds LastUpdateTime;
  int TotalSpectators = 0;
  std::vector<std::string> Spectators;

  Glow(Level *Map, std::vector<Player *> *Players, Camera *GameCamera, LocalPlayer *Myself) {
    this->Players = Players;
    this->Map = Map;
    this->GameCamera = GameCamera;
    this->Myself = Myself;
  }

  bool Save() {
    try {
      Config::Glow::NewGlow = Features::Glow::NewGlow;
      Config::Glow::GlowMaxDistance = Features::Glow::GlowMaxDistance;
      Config::Glow::GlowColorMode = Features::Glow::GlowColorMode;
      Config::Glow::GlowColorShieldMode = Features::Glow::GlowColorShieldMode;
      Config::Glow::GlowRadius = Features::Glow::GlowRadius;
      Config::Glow::BodyStyle = Features::Glow::BodyStyle;
      Config::Glow::OutlineStyle = Features::Glow::OutlineStyle;
      Config::Glow::ViewModelGlow = Features::Glow::ViewModelGlow;
      Config::Glow::ViewModelGlowSetting = Features::Glow::ViewModelGlowSetting;
      Config::Glow::ViewModelGlowCombo = Features::Glow::ViewModelGlowCombo;

      Config::ItemGlow::ItemGlow = Features::Glow::Item::ItemGlow;
      Config::ItemGlow::SelectedItemSelection = Features::Glow::Item::SelectedItemSelection;
      Config::ItemGlow::Common = Features::Glow::Item::Common;
      Config::ItemGlow::Rare = Features::Glow::Item::Rare;
      Config::ItemGlow::Epic = Features::Glow::Item::Epic;
      Config::ItemGlow::Gold = Features::Glow::Item::Gold;
      Config::ItemGlow::Legendary = Features::Glow::Item::Legendary;
      Config::ItemGlow::Weapons = Features::Glow::Item::Weapons;
      Config::ItemGlow::Ammo = Features::Glow::Item::Ammo;
      Config::ItemGlow::ItemGlowThickness = Features::Glow::Item::ItemGlowThickness;
      Config::ItemGlow::SelectedInsideStyle = Features::Glow::Item::SelectedInsideStyle;
      Config::ItemGlow::SelectedOutlineStyle = Features::Glow::Item::SelectedOutlineStyle;

      Config::EnemyColors::InvisibleGlowColorR = Features::Colors::Enemy::InvisibleGlowColor[0];
      Config::EnemyColors::InvisibleGlowColorG = Features::Colors::Enemy::InvisibleGlowColor[1];
      Config::EnemyColors::InvisibleGlowColorB = Features::Colors::Enemy::InvisibleGlowColor[2];
      Config::EnemyColors::VisibleGlowColorR = Features::Colors::Enemy::VisibleGlowColor[0];
      Config::EnemyColors::VisibleGlowColorG = Features::Colors::Enemy::VisibleGlowColor[1];
      Config::EnemyColors::VisibleGlowColorB = Features::Colors::Enemy::VisibleGlowColor[2];
      Config::EnemyColors::RedShieldColorR = Features::Colors::Enemy::RedShieldColor[0];
      Config::EnemyColors::RedShieldColorG = Features::Colors::Enemy::RedShieldColor[1];
      Config::EnemyColors::RedShieldColorB = Features::Colors::Enemy::RedShieldColor[2];
      Config::EnemyColors::PurpleShieldColorR = Features::Colors::Enemy::PurpleShieldColor[0];
      Config::EnemyColors::PurpleShieldColorG = Features::Colors::Enemy::PurpleShieldColor[1];
      Config::EnemyColors::PurpleShieldColorB = Features::Colors::Enemy::PurpleShieldColor[2];
      Config::EnemyColors::BlueShieldColorR = Features::Colors::Enemy::BlueShieldColor[0];
      Config::EnemyColors::BlueShieldColorG = Features::Colors::Enemy::BlueShieldColor[1];
      Config::EnemyColors::BlueShieldColorB = Features::Colors::Enemy::BlueShieldColor[2];
      Config::EnemyColors::GreyShieldColorR = Features::Colors::Enemy::GreyShieldColor[0];
      Config::EnemyColors::GreyShieldColorG = Features::Colors::Enemy::GreyShieldColor[1];
      Config::EnemyColors::GreyShieldColorB = Features::Colors::Enemy::GreyShieldColor[2];

      return true;
    } catch (...) { return false; }
  }

  // Old Glow & Item Glow
  void SetGlowState(long HighlightSettingsPointer, long HighlightSize, int HighlightID, GlowMode NewGlowMode) {
    const GlowMode oldGlowMode = Memory::Read<GlowMode>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 0);
    if (NewGlowMode != oldGlowMode)
      Memory::Write<GlowMode>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 0, NewGlowMode);
  }

  void SetColorState(long HighlightSettingsPointer, long HighlightSize, int HighlightID, Color NewColor) {
    const Color oldColor = Memory::Read<Color>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 4);
    if (oldColor != NewColor)
      Memory::Write<Color>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 4, NewColor);
  }

  void SetGlow(Player *Target, int GlowEnabled, int GlowThroughWall, int HighlightID) {
    if (Target->GlowEnable != GlowEnabled)
      Memory::Write<int>(Target->BasePointer + OFF_GLOW_ENABLE, GlowEnabled);
    if (Target->GlowThroughWall != GlowThroughWall) {
      Memory::Write<int>(Target->BasePointer + OFF_GLOW_THROUGH_WALL, GlowThroughWall);
      Memory::Write<int>(Target->BasePointer + OFF_GLOW_FIX, 1);
    }
    if (Target->HighlightID != HighlightID)
      Memory::Write<int>(Target->BasePointer + OFF_GLOW_HIGHLIGHT_ID + 1, HighlightID);
  }

  // New Glow
  void setGlowEnable(Player *Target, int glowEnable) {
    long ptrLong = Target->BasePointer + OFF_GLOW_ENABLE;
    Memory::Write<int>(ptrLong, glowEnable);
  }

  void setGlowThroughWall(Player *Target, int glowThroughWall) {
    long ptrLong = Target->BasePointer + OFF_GLOW_THROUGH_WALL;
    Memory::Write<int>(ptrLong, glowThroughWall);
  }

  int getGlowThroughWall(Player *Target) {
    int ptrInt = Memory::Read<int>(Target->BasePointer + OFF_GLOW_THROUGH_WALL);
    if (!Memory::IsValidPointer(ptrInt))
      return -1;
    return ptrInt;
  }

  int getGlowEnable(Player *Target) {
    int ptrInt = Memory::Read<int>(Target->BasePointer + OFF_GLOW_ENABLE);
    if (!Memory::IsValidPointer(ptrInt))
      return -1;
    return ptrInt;
  }

  void setCustomGlow(Player *Target, int health, bool isVisible, bool isSameTeam) {
    static const int contextId = 0; // Same as glow enable
    long basePointer = Target->BasePointer;
    int settingIndex = 65;

    // Glow
    int InsideFunction = 2; // Leave
    int OutlineFunction = 125; // Leave

    int bodyStyleArray[] = {
      0, // None
      1, // Pink
      110, // Pink Visible Only
      117, // Pulsing 1
      12, // Pulsing Line Invisible Only
      13, // Dark Pulsing Line
      124, // Sharp Pulsing Visible Only
      126, // Sharp Pulsing
      3, // Pulsing Red Line
      -500, // Fast Pulsing Invisible
      132, // Pulsing Up
      14, // Solid Pulsing
      117, // Solid Pulsing 2
      109, // Bright
      118, // Bright 2
      101, // Light
      112, // Light Solid
      115, // Red Pulsing Visible Only
      103, // Wave
      136, // Shaded Visible
      134, // Wireframe
      133, // Wireframe Visible Only
      75, // Black
      77 // Black Visible Only
    };

    int outlineStyleArray[] = {
      0, // None
      6, // Bright
      102, // Bright Invisible Only
      101, // Dark
      1, // Pink
      4, // White
      5, // Gold Flashing
      7, // Gold
      8, // Brown
      103, // Wave
      107, // Red
      108, // Red Bright
      110, // Heartbeat Visible Only
      -372, // Green Invisible Only
      -249, // Orange
      -151, // Visible Only
      364 // Red
    };

    if (Features::Glow::BodyStyle >= 0 && Features::Glow::BodyStyle <= 23)
      InsideFunction = bodyStyleArray[Features::Glow::BodyStyle];

    if (Features::Glow::OutlineStyle >= 0 && Features::Glow::OutlineStyle <= 16)
      OutlineFunction = outlineStyleArray[Features::Glow::OutlineStyle];

    std::array<unsigned char, 4> highlightFunctionBits = {
      InsideFunction, // InsideFunction							2
      OutlineFunction, // OutlineFunction: HIGHLIGHT_OUTLINE_OBJECTIVE			125
      Features::Glow::GlowRadius, // OutlineRadius: size * 255 / 8				64
      64 // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7) 	64
    };
    std::array<float, 3> glowColorRGB = {0, 0, 0};
    if (Features::Glow::GlowColorMode == 0) {
      if (Features::Glow::GlowColorShieldMode == 0) {
        if (!isVisible) {
          settingIndex = 65;
          glowColorRGB = {Features::Colors::Enemy::VisibleGlowColor[0], Features::Colors::Enemy::VisibleGlowColor[1], Features::Colors::Enemy::VisibleGlowColor[2]}; // Visible Enemies
        } else if (health >= 201) {
          settingIndex = 66;
          glowColorRGB = {Features::Colors::Enemy::RedShieldColor[0], Features::Colors::Enemy::RedShieldColor[1], Features::Colors::Enemy::RedShieldColor[2]}; // red shield
        } else if (health >= 176) {
          settingIndex = 67;
          glowColorRGB = {Features::Colors::Enemy::PurpleShieldColor[0], Features::Colors::Enemy::PurpleShieldColor[1], Features::Colors::Enemy::PurpleShieldColor[2]}; // purple shield
        } else if (health >= 151) {
          settingIndex = 68;
          glowColorRGB = {Features::Colors::Enemy::BlueShieldColor[0], Features::Colors::Enemy::BlueShieldColor[1], Features::Colors::Enemy::BlueShieldColor[2]}; // blue shield
        } else if (health >= 101) {
          settingIndex = 69;
          glowColorRGB = {Features::Colors::Enemy::GreyShieldColor[0], Features::Colors::Enemy::GreyShieldColor[1], Features::Colors::Enemy::GreyShieldColor[2]}; // gray shield // cyan
        } else {
          settingIndex = 70;
          glowColorRGB = {Features::Colors::Enemy::LowGlowColor[0], Features::Colors::Enemy::LowGlowColor[1], Features::Colors::Enemy::LowGlowColor[2]}; // low health enemies // greeen
        }
      }

      if (Features::Glow::GlowColorShieldMode == 1) {
        if (!isVisible) {
          settingIndex = 65;
          glowColorRGB = {Features::Colors::Enemy::VisibleGlowColor[0], Features::Colors::Enemy::VisibleGlowColor[1], Features::Colors::Enemy::VisibleGlowColor[2]}; // Visible Enemies
        } else if (health >= 125) {
          settingIndex = 66;
          glowColorRGB = {Features::Colors::Enemy::RedShieldColor[0], Features::Colors::Enemy::RedShieldColor[1], Features::Colors::Enemy::RedShieldColor[2]}; // red shield
        } else if (health >= 100) {
          settingIndex = 67;
          glowColorRGB = {Features::Colors::Enemy::PurpleShieldColor[0], Features::Colors::Enemy::PurpleShieldColor[1], Features::Colors::Enemy::PurpleShieldColor[2]}; // purple shield
        } else if (health >= 75) {
          settingIndex = 68;
          glowColorRGB = {Features::Colors::Enemy::BlueShieldColor[0], Features::Colors::Enemy::BlueShieldColor[1], Features::Colors::Enemy::BlueShieldColor[2]}; // blue shield
        } else if (health >= 50) {
          settingIndex = 69;
          glowColorRGB = {Features::Colors::Enemy::GreyShieldColor[0], Features::Colors::Enemy::GreyShieldColor[1], Features::Colors::Enemy::GreyShieldColor[2]}; // gray shield // cyan
        } else {
          settingIndex = 70;
          glowColorRGB = {Features::Colors::Enemy::LowGlowColor[0], Features::Colors::Enemy::LowGlowColor[1], Features::Colors::Enemy::LowGlowColor[2]}; // low health enemies // greeen
        }
      }
    }

    if (Features::Glow::GlowColorMode == 1) {
      if (!isVisible) {
        settingIndex = 65;
        glowColorRGB = {Features::Colors::Enemy::VisibleGlowColor[0], Features::Colors::Enemy::VisibleGlowColor[1], Features::Colors::Enemy::VisibleGlowColor[2]}; // Visible Enemies
      } else if (isVisible) {
        settingIndex = 70;
        glowColorRGB = {Features::Colors::Enemy::InvisibleGlowColor[0], Features::Colors::Enemy::InvisibleGlowColor[1], Features::Colors::Enemy::InvisibleGlowColor[2]}; // Invisible Enemies
      }
    }

    Memory::Write<unsigned char>(Target->BasePointer + OFF_GLOW_HIGHLIGHT_ID + contextId, settingIndex);
    long highlightSettingsPtr = Memory::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS);
    if (!isSameTeam) {
      Memory::Write<typeof(highlightFunctionBits)>(highlightSettingsPtr + OFF_HIGHLIGHT_TYPE_SIZE * settingIndex + 0, highlightFunctionBits);
      Memory::Write<typeof(glowColorRGB)>(highlightSettingsPtr + OFF_HIGHLIGHT_TYPE_SIZE * settingIndex + 4, glowColorRGB);
      Memory::Write<int>(Target->BasePointer + OFF_GLOW_FIX, 0);
    }
  }

  void Update() {
    if (!Map->IsPlayable)
      return;
    const long HighlightSettingsPointer = Memory::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS);
    const long HighlightSize = OFF_HIGHLIGHT_TYPE_SIZE;

    int highlightID1;
    int highlightID2;

    // Item Glow Options
    if (!Features::Glow::Item::Ammo && !Features::Glow::Item::Weapons) {
      highlightID1 = 34;
      highlightID2 = 39;
    } else if (Features::Glow::Item::Ammo && !Features::Glow::Item::Weapons) {
      highlightID1 = 34;
      highlightID2 = 47;
    } else if (!Features::Glow::Item::Ammo && Features::Glow::Item::Weapons) {
      highlightID1 = 26;
      highlightID2 = 39;
    } else if (Features::Glow::Item::Ammo && Features::Glow::Item::Weapons) {
      highlightID1 = 26;
      highlightID2 = 47;
    }

    ItemGlowSettings(); // Updates Item Glow Settings

    const GlowMode newGlowMode = {
      ItemGlowInsideFunction, // Inside Glow
      ItemGlowOutlineFunction, // Outline (Border)
      Features::Glow::Item::ItemGlowThickness, // Outline Thickness
      127 // ItemGlowPostProcessing
    };

    const GlowMode SetGlowOff = {0, 0, 0, 0};

    // Item Glow //
    if (Features::Glow::Item::ItemGlow) {
      if (Features::Glow::Item::SelectedItemSelection == 0) { for (int highlightId = 34; highlightId < 39; highlightId++) { SetGlowState(HighlightSettingsPointer, HighlightSize, highlightId, newGlowMode); } }

      if (Features::Glow::Item::SelectedItemSelection == 1) {
        if (Features::Glow::Item::Weapons) { SetGlowState(HighlightSettingsPointer, HighlightSize, 26, newGlowMode); } else {
          const GlowMode newGlowMode = StoredGlowMode->at(26);
          SetGlowState(HighlightSettingsPointer, HighlightSize, 26, SetGlowOff);
        }

        if (Features::Glow::Item::Common) { SetGlowState(HighlightSettingsPointer, HighlightSize, 34, newGlowMode); } else {
          const GlowMode newGlowMode = StoredGlowMode->at(34);
          SetGlowState(HighlightSettingsPointer, HighlightSize, 34, SetGlowOff);
        }

        if (Features::Glow::Item::Rare) { SetGlowState(HighlightSettingsPointer, HighlightSize, 35, newGlowMode); } else { SetGlowState(HighlightSettingsPointer, HighlightSize, 35, SetGlowOff); }

        if (Features::Glow::Item::Epic) { SetGlowState(HighlightSettingsPointer, HighlightSize, 36, newGlowMode); } else { SetGlowState(HighlightSettingsPointer, HighlightSize, 36, SetGlowOff); }

        if (Features::Glow::Item::Gold) { SetGlowState(HighlightSettingsPointer, HighlightSize, 37, newGlowMode); } else { SetGlowState(HighlightSettingsPointer, HighlightSize, 37, SetGlowOff); }

        if (Features::Glow::Item::Legendary) { SetGlowState(HighlightSettingsPointer, HighlightSize, 38, newGlowMode); } else { SetGlowState(HighlightSettingsPointer, HighlightSize, 38, SetGlowOff); }

        SetGlowState(HighlightSettingsPointer, HighlightSize, 39, newGlowMode); // IDK what ID this is (currently)

        if (Features::Glow::Item::Ammo) { SetGlowState(HighlightSettingsPointer, HighlightSize, 46, newGlowMode); } else { SetGlowState(HighlightSettingsPointer, HighlightSize, 46, SetGlowOff); }
      }
    }

    for (int i = 0; i < Players->size(); i++) {
      Player *Target = Players->at(i);
      if (!Target->IsValid())
        continue;
      if (!Target->IsHostile)
        continue;

      if (Features::Glow::NewGlow) {
        if (Features::Glow::GlowColorMode == 0) {
          if (Features::Glow::GlowColorShieldMode == 0) {
            if (Target->IsVisible && !Target->IsKnocked && Target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) {
              setGlowEnable(Target, 1);
              setGlowThroughWall(Target, 1);
              int healthShield = Target->Health + Target->Shield;
              setCustomGlow(Target, healthShield, true, false);
            }
            if (!Target->IsVisible && !Target->IsKnocked && Target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) {
              setGlowEnable(Target, 1);
              setGlowThroughWall(Target, 1);
              int healthShield = Target->Health + Target->Shield;
              setCustomGlow(Target, healthShield, true, false);
            } else if (Target->Distance2DToLocalPlayer > Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) { // If player is out of max distance
              setGlowEnable(Target, 0);
              setGlowThroughWall(Target, 0);
              setCustomGlow(Target, 0, false, false);
            } else if (getGlowEnable(Target) == 1 && getGlowThroughWall(Target) == 1) {
              setGlowEnable(Target, 0);
              setGlowThroughWall(Target, 0);
            }
          }

          if (Features::Glow::GlowColorShieldMode == 1) {
            if (Target->IsVisible && !Target->IsKnocked && Target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) {
              setGlowEnable(Target, 1);
              setGlowThroughWall(Target, 1);
              int healthShield = Target->MaxShield;
              setCustomGlow(Target, healthShield, true, false);
            }
            if (!Target->IsVisible && !Target->IsKnocked && Target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) {
              setGlowEnable(Target, 1);
              setGlowThroughWall(Target, 1);
              int healthShield = Target->MaxShield;
              setCustomGlow(Target, healthShield, false, false);
            } else if (Target->Distance2DToLocalPlayer > Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) { // If player is out of max distance
              setGlowEnable(Target, 0);
              setGlowThroughWall(Target, 0);
              setCustomGlow(Target, 0, false, false);
            } else if (getGlowEnable(Target) == 1 && getGlowThroughWall(Target) == 1) {
              setGlowEnable(Target, 0);
              setGlowThroughWall(Target, 0);
            }
          }
        }

        if (Features::Glow::GlowColorMode == 1) {
          if (Target->IsVisible && !Target->IsKnocked && Target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) {
            setGlowEnable(Target, 1);
            setGlowThroughWall(Target, 1);
            int healthShield = Target->MaxShield;
            setCustomGlow(Target, healthShield, false, false);
          }
          if (!Target->IsVisible && !Target->IsKnocked && Target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) {
            setGlowEnable(Target, 1);
            setGlowThroughWall(Target, 1);
            int healthShield = Target->MaxShield;
            setCustomGlow(Target, healthShield, true, false);
          } else if (Target->Distance2DToLocalPlayer > Conversion::ToGameUnits(Features::Glow::GlowMaxDistance)) { // If player is out of max distance
            setGlowEnable(Target, 0);
            setGlowThroughWall(Target, 0);
            setCustomGlow(Target, 0, false, false);
          } else if (getGlowEnable(Target) == 1 && getGlowThroughWall(Target) == 1) {
            setGlowEnable(Target, 0);
            setGlowThroughWall(Target, 0);
          }
        }
      }
    }
  }

  void ViewModelGlow() {
    if (Features::Glow::ViewModelGlow) {
      ViewmodelGlowSettings(); // Updates the ID for what glow you want (bottom of this file)
      uint64_t actWeaponID = Memory::Read<uint64_t>(Myself->BasePointer + OFF_VIEWMODELS) & 0xFFFF;
      uint64_t currentWeapon = Memory::Read<uint64_t>(OFF_REGION + OFF_ENTITY_LIST + (actWeaponID << 5));

      Memory::Write<uint8_t>(currentWeapon + OFF_GLOW_HIGHLIGHT_ID, ViewmodelGlowID);
    }

    if (!Features::Glow::ViewModelGlow) {
      uint64_t actWeaponID = Memory::Read<uint64_t>(Myself->BasePointer + OFF_VIEWMODELS) & 0xFFFF;
      uint64_t currentWeapon = Memory::Read<uint64_t>(OFF_REGION + OFF_ENTITY_LIST + (actWeaponID << 5));

      Memory::Write<uint8_t>(currentWeapon + OFF_GLOW_HIGHLIGHT_ID, 0);
    }
  }

  void ViewmodelGlowSettings() {
    int viewModelGlowIDs[] = {
      13, // Cyan outline
      15, // Light red outline
      17, // White outline
      18, // Orange outline
      24, // Yellow outline
      27, // Green solid
      28, // Orange solid
      29, // Yellow solid
      25, // Yellow solid pulsing
      30, // Purple solid
      31, // Light Blue solid
      32, // Light Grey solid
      34, // White solid
      35, // Cyan solid
      36, // Hot Pink solid
      37, // Light Yellow solid
      38, // Light Orange solid
      39, // Light Green solid
      74, // Black solid
      49 // Chrome
    };

    if (Features::Glow::ViewModelGlowCombo >= 0 && Features::Glow::ViewModelGlowCombo <= 19)
      ViewmodelGlowID = viewModelGlowIDs[Features::Glow::ViewModelGlowCombo];
  }

  void ItemGlowSettings() {
    int itemGlowInsideFunctionIDs[] = {
      0, // Clear
      137, // Light
      109, // Solid
      117 // Light to dark fade
    };

    int itemGlowOutlineFunctionIDs[] = {
      0, // None
      138, // Light 1
      102, // Light 2
      6, // Solid
      7, // Gold
      8, // Orange
      103, // Pulsing
      107, // Light Red
      108, // Red
      110, // Fading
      120, // Soft
      131 // Visible only
    };

    if (Features::Glow::Item::SelectedInsideStyle >= 0 && Features::Glow::Item::SelectedInsideStyle <= 3)
      ItemGlowInsideFunction = itemGlowInsideFunctionIDs[Features::Glow::Item::SelectedInsideStyle];

    if (Features::Glow::Item::SelectedOutlineStyle >= 0 && Features::Glow::Item::SelectedOutlineStyle <= 11)
      ItemGlowOutlineFunction = itemGlowOutlineFunctionIDs[Features::Glow::Item::SelectedOutlineStyle];
  }
};
