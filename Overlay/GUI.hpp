// Externals
#pragma once
#include <string>
#include "../imgui/imgui.h"
#include "../imgui/imconfig.h"
#include "../imgui/imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

// Internals
#include "../Utils/Features.hpp"
#include "AdvancedGUI.hpp"
#include "Overlay.hpp"
#include "../Core/LocalPlayer.hpp"

struct Menu {
  ImVec4 DetailColor = ImVec4(1.00f, 0.65f, 0.00f, 1.00f);
  ImVec4 TextColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

  ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;
  ImGuiColorEditFlags ColorEditFlags = ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs;

  float WindowWidth = 1000.0f; // 1000 // 950 // 1000
  float WindowHeight = 495.0f; // 600 // 450 // 648
  float NavbarWidth = WindowWidth / 6;
  float NavbarHeight = WindowHeight;
  float MainWidth = WindowWidth - NavbarWidth;
  float MainHeight = WindowHeight;

  enum MenuTabs {
    Legitbot,
    Triggerbot,
    Glow,
    ESP,
    Misc,
    Settings,
    Config
  };

  int SelectedLegitbotSubTab = 0; // 4
  int SelectedTriggerbotSubTab = 0; // 2
  int SelectedGlowSubTab = 0; // 2
  int SelectedESPSubTabLeft = 0; // 2
  int SelectedESPSubTabRight = 0; // 3

  MenuTabs CurrentTab = MenuTabs::Legitbot;

  LocalPlayer *Myself;
  AdvancedGUI *Advanced;

  Menu(LocalPlayer *Myself, AdvancedGUI *Advanced) {
    this->Myself = Myself;
    this->Advanced = Advanced;
  }

  static void DoubleSpacing() {
    ImGui::Spacing();
    ImGui::Spacing();
  }

  static void ComboBox(const char *label, const char *desc, int *current_item, const char *items_separated_by_zeros, const int height_in_items) {
    ImGui::Spacing();
    ImGui::SameLine(15);
    ImGui::TextColored(ImColor(255, 255, 255, 255), label);

    ImGui::Spacing();
    ImGui::SameLine(15);
    ImGui::TextColored(ImColor(97, 97, 97, 255), desc);
    ImGui::ComboBox(label, current_item, items_separated_by_zeros, height_in_items);
    ImGui::Spacing();
  }

  void RenderLegitbot() {
    ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::BeginGroup();
    ImGui::Spacing();
    ImGui::SameLine();
    if (ImGui::SubTab("AIMBOT", 0 == SelectedLegitbotSubTab, ImVec2(111, 25)))
      SelectedLegitbotSubTab = 0;
    ImGui::SameLine();
    if (ImGui::SubTab("ADVANCED##AIMBOT", 1 == SelectedLegitbotSubTab, ImVec2(111, 25)))
      SelectedLegitbotSubTab = 1;
    ImGui::SameLine();
    if (ImGui::SubTab("WEAPONS##AIMBOT", 2 == SelectedLegitbotSubTab, ImVec2(111, 25)))
      SelectedLegitbotSubTab = 2;
    ImGui::SameLine();
    if (ImGui::SubTab("RCS", 3 == SelectedLegitbotSubTab, ImVec2(111, 25)))
      SelectedLegitbotSubTab = 3;
    ImGui::SameLine();
    if (ImGui::SubTab("WEAPONS##RCS", 4 == SelectedLegitbotSubTab, ImVec2(111, 25)))
      SelectedLegitbotSubTab = 4;
    ImGui::EndGroup();

    ImGui::BeginChild("workzone", ImVec2(WindowWidth - 220, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

    DoubleSpacing();

    // Aimbot
    if (SelectedLegitbotSubTab == 0) {
      ImGui::BeginChildFrame(1, ImVec2(0, 135), true); {
        ImGui::Spacing();
        ImGui::Checkbox("Enabled", &Features::Aimbot::AimbotEnabled);
        if (Features::Aimbot::AimbotEnabled) {
          const char *AimbotModeIndex[] = {"Beta V1", "Grinder", "Beta V2"};
          ImGui::ComboBox("Aimbot method", &Features::Aimbot::AimbotMode, AimbotModeIndex, IM_ARRAYSIZE(AimbotModeIndex));
          const char *InputMethodIndex[] = {"Mouse movement", "Write memory"};
          ImGui::ComboBox("Input method", &Features::Aimbot::InputMethod, InputMethodIndex, IM_ARRAYSIZE(InputMethodIndex));
        }
        ImGui::EndChildFrame();
      }

      if (Features::Aimbot::AimbotEnabled && !Features::Aimbot::AdvancedAim) {
        ImGui::Columns(2, nullptr, false);
        ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 613, 93), true); {
          ImGui::Spacing();
          ImGui::Text("Selected Hitbox");
          ImGui::Checkbox("Closest To Crosshair", &Features::Aimbot::ClosestHitbox);
          if (!Features::Aimbot::ClosestHitbox) {
            const char *HitboxTypes[] = {"Head", "Neck", "Upper Chest", "Lower Chest", "Stomach", "Hip"};
            int HitboxTypeIndex = static_cast<int>(Features::AimbotHitboxes::Hitbox);
            ImGui::ComboBox("Hitbox Type", &HitboxTypeIndex, HitboxTypes, IM_ARRAYSIZE(HitboxTypes));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Which bone the aimbot will aim at.");
            Features::AimbotHitboxes::Hitbox = static_cast<HitboxType>(HitboxTypeIndex);
          }
          ImGui::EndChildFrame();
        }

        ImGui::BeginChildFrame(3, ImVec2(WindowWidth - 613, 190), true); {
          ImGui::Spacing();
          const char *BindMethodIndex[] = {"Memory", "Keybinds"};
          ImGui::ComboBox("Aim Bind Method", &Features::Aimbot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
          if (!Features::Aimbot::AdvancedAim) {
            if (Features::Aimbot::BindMethod == 0) { // OnFire and OnADS
              ImGui::Checkbox("On Fire", &Features::Aimbot::OnFire);
              ImGui::SameLine();
              ImGui::Checkbox("On ADS", &Features::Aimbot::OnADS);
            }
            if (Features::Aimbot::BindMethod == 1) { // Keybinds
              int AimBind = static_cast<int>(Features::AimbotBinds::AimBind);
              ImGui::ComboBox("Aim Bind##Aimbot", &AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
              Features::AimbotBinds::AimBind = static_cast<InputKeyType>(AimBind);
              int ExtraBind = static_cast<int>(Features::AimbotBinds::ExtraBind);
              ImGui::ComboBox("Extra Bind##Aimbot", &ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
              Features::AimbotBinds::ExtraBind = static_cast<InputKeyType>(ExtraBind);
            }
            ImGui::Text("Aim Conditions");
            ImGui::Checkbox("Team Check##Aimbot", &Features::Aimbot::TeamCheck);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Disable this if doing 1v1s in the firing range.\nMay not work with Grinder Aim Method.");
            ImGui::SameLine();
            ImGui::Checkbox("Visibility Check", &Features::Aimbot::VisCheck);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Aims At Only Visible Enemies.");

            ImGui::Text("Targeting Options");
            ImGui::Checkbox("Allow Target Switching", &Features::Aimbot::TargetSwitching);
            const char *PriorityIndex[] = {"Closest To Crosshair", "Closest To LocalPlayer", "Both"};
            ImGui::ComboBox("Target Priority", &Features::Aimbot::Priority, PriorityIndex, IM_ARRAYSIZE(PriorityIndex));
            DoubleSpacing();
          }
          ImGui::EndChildFrame();
        }

        if (!Features::Aimbot::AdvancedAim) {
          ImGui::BeginChildFrame(4, ImVec2(WindowWidth - 613, 169), true); {
            ImGui::Spacing();
            const char *SmoothingMethodIndex[] = {"Static", "Random"};
            ImGui::ComboBox("Smoothing Method", &Features::Aimbot::SmoothingMethod, SmoothingMethodIndex, IM_ARRAYSIZE(SmoothingMethodIndex));

            if (Features::Aimbot::InputMethod == 0) // Mouse Only
              ImGui::MainSliderFloat("Speed", &Features::Aimbot::Speed, 1, 100, "%.0f");

            if (Features::Aimbot::SmoothingMethod == 0) { // Static
              ImGui::MainSliderFloat("Hipfire Smoothing", &Features::Aimbot::HipfireSmooth, 0, 0.99, "%.3f");
              ImGui::MainSliderFloat("ADS Smoothing", &Features::Aimbot::ADSSmooth, 0, 0.99, "%.3f");
            }

            if (Features::Aimbot::SmoothingMethod == 1) { // Random
              if (Features::Aimbot::AimbotMode == 0) {
                ImGui::MainSliderFloat("Minimum Hipfire Smoothing", &Features::Aimbot::MinHipfireSmooth, 0, 0.99, "%.3f");
                ImGui::MainSliderFloat("Maximum Hipfire Smoothing", &Features::Aimbot::MaxHipfireSmooth, 0, 0.99, "%.3f");
                ImGui::MainSliderFloat("Minimum ADS Smoothing", &Features::Aimbot::MinADSSmooth, 0, 0.99, "%.3f");
                ImGui::MainSliderFloat("Maximum ADS Smoothing", &Features::Aimbot::MaxADSSmooth, 0, 0.99, "%.3f");
              }
              if (Features::Aimbot::AimbotMode == 2) {
                ImGui::MainSliderFloat("Minimum Hipfire Smoothing##Test", &Features::Aimbot::MinMouseHipfireSmoothing, 1, 1000, "%.0f");
                ImGui::MainSliderFloat("Maximum Hipfire Smoothing##Test", &Features::Aimbot::MaxMouseHipfireSmoothing, 1, 1000, "%.0f");
                ImGui::MainSliderFloat("Minimum ADS Smoothing##Test", &Features::Aimbot::MinMouseADSSmoothing, 1, 1000, "%.0f");
                ImGui::MainSliderFloat("Maximum ADS Smoothing##Test", &Features::Aimbot::MaxMouseADSSmoothing, 1, 1000, "%.0f");
              }
            }

            if (Features::Aimbot::AimbotMode == 2) {
              ImGui::MainSliderFloat("Distance Smoothing##Test", &Features::Aimbot::MouseExtraSmoothing, 1, 9999, "%.0f");
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
            }

            ImGui::MainSliderInt("Delay", &Features::Aimbot::Delay, 1, 50);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Delay time for the aimbot smoothing.\n");

            ImGui::EndChildFrame();
          }

          ImGui::NextColumn();

          ImGui::BeginChildFrame(5, ImVec2(WindowWidth - 630, 93), true); {
            ImGui::Spacing();
            ImGui::Text("Prediction");
            ImGui::Checkbox("Predict Movement", &Features::Aimbot::PredictMovement);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Predict target's movement");
            ImGui::SameLine();
            ImGui::Checkbox("Predict Bullet Drop", &Features::Aimbot::PredictBulletDrop);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Predict weapon's bullet drop");

            ImGui::EndChildFrame();
          }

          ImGui::BeginChildFrame(6, ImVec2(WindowWidth - 630, 190), true); {
            ImGui::Spacing();
            ImGui::MainSliderFloat("FOV", &Features::Aimbot::FOV, 1, 90, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Field of View");
            ImGui::MainSliderFloat("Zoom Scale", &Features::Aimbot::ZoomScale, 0, 5, "%.1f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Field of View For Scopes");

            ImGui::EndChildFrame();
          }

          ImGui::BeginChildFrame(7, ImVec2(WindowWidth - 630, 169), true); {
            ImGui::Spacing();
            ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::AdvancedMinDistance1, 1, 500, "%.0f"); // Ignore advanced, will work for both advanced and simple aimbot
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Min distance for Aim-Assist to work");
            ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::AdvancedMaxDistance1, 1, 500, "%.0f"); // Ignore advanced, will work for both advanced and simple aimbot
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Max distance for Aim-Assist to work");
            ImGui::EndChildFrame();
          }
          ImGui::Spacing();
        }
      }

      if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AimbotMode == 1 && !Features::Aimbot::AdvancedAim && Features::Aimbot::InputMethod == 0) {
        ImGui::Columns(2, nullptr, false);
        ImGui::BeginChildFrame(3, ImVec2(WindowWidth - 613, 217), true); {
          ImGui::Spacing();
          const char *BindMethodIndex[] = {"Memory", "Keybinds"};
          ImGui::ComboBox("Aim Bind Method", &Features::Aimbot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
          if (!Features::Aimbot::AdvancedAim) {
            if (Features::Aimbot::BindMethod == 0) { // OnFire and OnADS
              ImGui::Checkbox("On Fire", &Features::Aimbot::OnFire);
              ImGui::SameLine();
              ImGui::Checkbox("On ADS", &Features::Aimbot::OnADS);
            }
            if (Features::Aimbot::BindMethod == 1) { // Keybinds
              int AimBind = static_cast<int>(Features::AimbotBinds::AimBind);
              ImGui::ComboBox("Aim Bind##Aimbot", &AimBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
              Features::AimbotBinds::AimBind = static_cast<InputKeyType>(AimBind);
              int ExtraBind = static_cast<int>(Features::AimbotBinds::ExtraBind);
              ImGui::ComboBox("Extra Bind##Aimbot", &ExtraBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
              Features::AimbotBinds::ExtraBind = static_cast<InputKeyType>(ExtraBind);
            }
            ImGui::Text("Aim Conditions");
            ImGui::Checkbox("Team Check##Aimbot", &Features::Aimbot::TeamCheck);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Disable this if doing 1v1s in the firing range.\nMay not work with Grinder Aim Method.");
          }
          ImGui::EndChildFrame();
        }

        ImGui::BeginChildFrame(4, ImVec2(WindowWidth - 613, 217), true); {
          ImGui::Spacing();

          const char *SmoothingMethodIndex[] = {"Static", "Random"};
          ImGui::ComboBox("Smoothing Method", &Features::Aimbot::SmoothingMethod, SmoothingMethodIndex, IM_ARRAYSIZE(SmoothingMethodIndex));

          if (Features::Aimbot::SmoothingMethod == 0) // Static
          {
            ImGui::MainSliderFloat("Hipfire Smoothing##Grinder", &Features::Aimbot::HipfireSmooth1, 1, 1000, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Smoothing Of The Aim-Assist Whilst Hipfiring.\nHigher = Smoother");
            ImGui::MainSliderFloat("ADS Smoothing##Grinder", &Features::Aimbot::ADSSmooth1, 1, 1000, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Smoothing Of The Aim-Assist Longbow Whilst ADS.\nHigher = Smoother");
          }

          if (Features::Aimbot::SmoothingMethod == 1) // Random
          {
            ImGui::MainSliderFloat("Min Hipfire Smoothing##Grinder", &Features::Aimbot::MinHipfireSmooth1, 1, 1000, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist Whilst Hipfiring.\nHigher = Smoother");
            ImGui::MainSliderFloat("Max Hipfire Smoothing##Grinder", &Features::Aimbot::MaxHipfireSmooth1, 1, 1000, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist Whilst Hipfiring.\nHigher = Smoother");

            ImGui::MainSliderFloat("Min ADS Smoothing##Grinder", &Features::Aimbot::MinADSSmooth1, 1, 1000, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Minimum Smoothing Of The Aim-Assist Whilst ADS.\nHigher = Smoother");
            ImGui::MainSliderFloat("Max ADS Smoothing##Grinder", &Features::Aimbot::MaxADSSmooth1, 1, 1000, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Maximum Smoothing Of The Aim-Assist Whilst ADS.\nHigher = Smoother");
          }

          ImGui::MainSliderFloat("Extra Smoothing##Grinder", &Features::Aimbot::ExtraSmoothing, 1, 9999, "%.0f");
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Increases the smoothing depending on the distance of the player.");
          ImGui::MainSliderFloat("Deadzone##Grinder", &Features::Aimbot::Deadzone, 0, 10, "%.03f");
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("If the aimbot is close enough then the aimbot will stop trying to get any closer.\n If you have very low smoothing then you might want to up this to prevent 'shaking'.");
          ImGui::EndChildFrame();
        }

        ImGui::NextColumn();

        ImGui::BeginChildFrame(6, ImVec2(WindowWidth - 630, 217), true); {
          ImGui::Spacing();
          ImGui::MainSliderFloat("FOV##Grinder", &Features::Aimbot::FOV1, 1, 90, "%.0f");
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Field of View.");
          ImGui::EndChildFrame();
        }

        ImGui::BeginChildFrame(7, ImVec2(WindowWidth - 630, 217), true); {
          ImGui::Spacing();
          ImGui::MainSliderFloat("Min Distance", &Features::Aimbot::AdvancedMinDistance1, 1, 500, "%.0f"); // Ignore advanced, will work for both advanced and simple aimbot
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Min distance for Aim-Assist to work");
          ImGui::MainSliderFloat("Max Distance", &Features::Aimbot::AdvancedMaxDistance1, 1, 500, "%.0f"); // Ignore advanced, will work for both advanced and simple aimbot
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Max distance for Aim-Assist to work");
          ImGui::EndChildFrame();
        }
        ImGui::Spacing();
      }

      if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AimbotMode == 1 && Features::Aimbot::InputMethod == 1) { ImGui::Text("Selected Input Method Is Not Compatible With Selected Aimbot Method, Please Switch Aimbot Method Or Input Method."); }

      if (Features::Aimbot::AimbotEnabled && Features::Aimbot::AdvancedAim) { ImGui::Text("Advanced Aim Is Enabled, Use The Advanced Tab."); }
    }

    // Aimbot weapon config
    if (SelectedLegitbotSubTab == 1) { Advanced->AdvancedAimbotTab(Myself->WeaponIndex); }

    // Aimbot weapon selection
    if (SelectedLegitbotSubTab == 2) {
      if (Features::Aimbot::AimbotEnabled) {
          ImGui::Text("Aimbot is disabled");
      } else  {
        ImGui::Columns(3, "##aimbotSelection", false);
        const ImVec2 WeaponGroupSize = {(MainWidth - 70) / 3, (MainHeight - 137) / 2};

        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
        if (ImGui::BeginChildFrame(11, WeaponGroupSize, true)) {
          ImGui::Checkbox("P2020##Aimbot", &Features::Aimbot::P2020);
          ImGui::Checkbox("RE-45 Auto##Aimbot", &Features::Aimbot::RE45);
          ImGui::Checkbox("Alternator SMG##Aimbot", &Features::Aimbot::Alternator);
          ImGui::Checkbox("R-99 SMG##Aimbot", &Features::Aimbot::R99);
          ImGui::Checkbox("R-301 Carbine##Aimbot", &Features::Aimbot::R301);
          ImGui::Checkbox("M600 Spitfire##Aimbot", &Features::Aimbot::Spitfire);
          ImGui::Checkbox("G7 Scout##Aimbot", &Features::Aimbot::G7);
          ImGui::EndChildFrame();
        }

        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
        if (ImGui::BeginChildFrame(12, WeaponGroupSize, true)) {
          ImGui::Checkbox("VK-47 Flatline##Aimbot", &Features::Aimbot::Flatline);
          ImGui::Checkbox("Prowler Burst SMG##Aimbot", &Features::Aimbot::Prowler);
          ImGui::Checkbox("Hemlock Burst AR##Aimbot", &Features::Aimbot::Hemlock);
          ImGui::Checkbox("30-30 Repeater##Aimbot", &Features::Aimbot::Repeater);
          ImGui::Checkbox("Rampage LMG##Aimbot", &Features::Aimbot::Rampage);
          ImGui::Checkbox("C.A.R SMG##Aimbot", &Features::Aimbot::CARSMG);
          ImGui::EndChildFrame();
        }

        ImGui::NextColumn();

        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
        if (ImGui::BeginChildFrame(13, WeaponGroupSize, true)) {
          ImGui::Checkbox("Havoc Rifle##Aimbot", &Features::Aimbot::Havoc);
          ImGui::Checkbox("Devotion LMG##Aimbot", &Features::Aimbot::Devotion);
          ImGui::Checkbox("L-Star EMG##Aimbot", &Features::Aimbot::LSTAR);
          ImGui::Checkbox("Triple-Take##Aimbot", &Features::Aimbot::TripleTake);
          ImGui::Checkbox("Volt##Aimbot", &Features::Aimbot::Volt);
          ImGui::Checkbox("Nemesis Burst AR##Aimbot", &Features::Aimbot::Nemesis);
          ImGui::EndChildFrame();
        }

        ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
        if (ImGui::BeginChildFrame(14, WeaponGroupSize, true)) {
          ImGui::Checkbox("Mozambique##Aimbot", &Features::Aimbot::Mozambique);
          ImGui::Checkbox("Peacekeeper##Aimbot", &Features::Aimbot::Peacekeeper);
          ImGui::Checkbox("Mastiff##Aimbot", &Features::Aimbot::Mastiff);
          ImGui::EndChildFrame();
        }

        ImGui::NextColumn();

        ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
        if (ImGui::BeginChildFrame(15, WeaponGroupSize, true)) {
          ImGui::Checkbox("Longbow DMR##Aimbot", &Features::Aimbot::Longbow);
          ImGui::Checkbox("Charge Rifle##Aimbot", &Features::Aimbot::ChargeRifle);
          ImGui::Checkbox("Sentinel##Aimbot", &Features::Aimbot::Sentinel);
          ImGui::EndChildFrame();
        }

        ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
        if (ImGui::BeginChildFrame(16, WeaponGroupSize, true)) {
          ImGui::Checkbox("Wingman##Aimbot", &Features::Aimbot::Wingman);
          ImGui::Checkbox("EVA-8 Auto##Aimbot", &Features::Aimbot::EVA8);
          ImGui::Checkbox("Kraber .50-CAL Sniper##Aimbot", &Features::Aimbot::Kraber);
          ImGui::EndChildFrame();
        }
        ImGui::NextColumn();
      }
    }

    // Recoil control system
    if (SelectedLegitbotSubTab == 3) {
      ImGui::Text("Recoil control system");
      ImGui::BeginChildFrame(17, ImVec2(0, 0), true); {
        ImGui::Spacing();
        ImGui::Checkbox("Enabled", &Features::RCS::RCSEnabled);
        if (Features::RCS::RCSEnabled)
          ImGui::Checkbox("Advanced", &Features::RCS::AdvancedRCS);

        if (Features::RCS::RCSEnabled && !Features::RCS::AdvancedRCS) {
          const char *RCSModeIndex[] = {"Standalone", "Combined"};
          ImGui::ComboBox("Mode", &Features::RCS::RCSMode, RCSModeIndex, IM_ARRAYSIZE(RCSModeIndex));
        }
        if (Features::RCS::RCSMode == 0 && Features::Aimbot::InputMethod == 1) {
          ImGui::Text("Standalone RCS is incompatible with memory aim");
        }

        if (Features::RCS::RCSEnabled && !Features::RCS::AdvancedRCS && !(Features::RCS::RCSMode == 0 && Features::Aimbot::InputMethod == 1)) {
          ImGui::Spacing();
          ImGui::Checkbox("Require ADS", &Features::RCS::OnADS);

          if (Features::RCS::RCSMode == 0) { // Standalone RCS
            ImGui::MainSliderFloat("Pitch", &Features::RCS::PitchPower, 1, 50, "%.1f");
            ImGui::MainSliderFloat("Yaw", &Features::RCS::YawPower, 1, 50, "%.1f");
          }

          if (Features::RCS::RCSMode == 1 ) { // Combined RCS
            ImGui::MainSliderFloat("Pitch Reduction %", &Features::RCS::PitchReduction, 0, 100, "%.0f");
            ImGui::MainSliderFloat("Yaw Reduction %", &Features::RCS::YawReduction, 0, 100, "%.0f");
          }
        }

        if (Features::RCS::RCSEnabled && Features::RCS::AdvancedRCS) {
          Advanced->AdvancedRCSTab(Myself->WeaponIndex);
        }
        ImGui::EndChildFrame();
      }
    }

    // Recoil control system weapon selection
    if (SelectedLegitbotSubTab == 4) {
      if (!Features::RCS::RCSEnabled) {
        ImGui::Text("RCS is disabled");
      } else {
        ImGui::Columns(3, "##rcsSelection", false);
        const ImVec2 WeaponGroupSize = {(MainWidth - 70) / 3, (MainHeight - 137) / 2};

        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
        if (ImGui::BeginChildFrame(7, WeaponGroupSize, true)) {
          ImGui::Checkbox("P2020##RCS", &Features::RCS::P2020);
          ImGui::Checkbox("RE-45 Auto##RCS", &Features::RCS::RE45);
          ImGui::Checkbox("Alternator SMG##RCS", &Features::RCS::Alternator);
          ImGui::Checkbox("R-99 SMG##RCS", &Features::RCS::R99);
          ImGui::Checkbox("R-301 Carbine##RCS", &Features::RCS::R301);
          ImGui::Checkbox("M600 Spitfire##RCS", &Features::RCS::Spitfire);
          ImGui::Checkbox("G7 Scout##RCS", &Features::RCS::G7);
          ImGui::EndChildFrame();
        }

        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
        if (ImGui::BeginChildFrame(8, WeaponGroupSize, true)) {
          ImGui::Checkbox("VK-47 Flatline##RCS", &Features::RCS::Flatline);
          ImGui::Checkbox("Prowler Burst SMG##RCS", &Features::RCS::Prowler);
          ImGui::Checkbox("Hemlock Burst AR##RCS", &Features::RCS::Hemlock);
          ImGui::Checkbox("30-30 Repeater##RCS", &Features::RCS::Repeater);
          ImGui::Checkbox("Rampage LMG##RCS", &Features::RCS::Rampage);
          ImGui::Checkbox("C.A.R SMG##RCS", &Features::RCS::CARSMG);
          ImGui::EndChildFrame();
        }

        ImGui::NextColumn();

        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
        if (ImGui::BeginChildFrame(9, WeaponGroupSize, true)) {
          ImGui::Checkbox("Havoc Rifle##RCS", &Features::RCS::Havoc);
          ImGui::Checkbox("Devotion LMG##RCS", &Features::RCS::Devotion);
          ImGui::Checkbox("L-Star EMG##RCS", &Features::RCS::LSTAR);
          ImGui::Checkbox("Triple-Take##RCS", &Features::RCS::TripleTake);
          ImGui::Checkbox("Volt##RCS", &Features::RCS::Volt);
          ImGui::Checkbox("Nemesis Burst AR##RCS", &Features::RCS::Nemesis);
          ImGui::EndChildFrame();
        }

        ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
        if (ImGui::BeginChildFrame(10, WeaponGroupSize, true)) {
          ImGui::Checkbox("Mozambique##RCS", &Features::RCS::Mozambique);
          ImGui::Checkbox("Peacekeeper##RCS", &Features::RCS::Peacekeeper);
          ImGui::Checkbox("Mastiff##RCS", &Features::RCS::Mastiff);
          ImGui::EndChildFrame();
        }

        ImGui::NextColumn();

        ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
        if (ImGui::BeginChildFrame(11, WeaponGroupSize, true)) {
          ImGui::Checkbox("Longbow DMR##RCS", &Features::RCS::Longbow);
          ImGui::Checkbox("Charge Rifle##RCS", &Features::RCS::ChargeRifle);
          ImGui::Checkbox("Sentinel##RCS", &Features::RCS::Sentinel);
          ImGui::EndChildFrame();
        }

        ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
        if (ImGui::BeginChildFrame(12, WeaponGroupSize, true)) {
          ImGui::Checkbox("Wingman##RCS", &Features::RCS::Wingman);
          ImGui::Checkbox("EVA-8 Auto##RCS", &Features::RCS::EVA8);
          ImGui::Checkbox("Kraber .50-CAL Sniper##RCS", &Features::RCS::Kraber);
          ImGui::EndChildFrame();
        }
        ImGui::NextColumn();
      }
    }

    ImGui::EndChild();
    ImGui::EndChild();
  }

  void RenderTriggerbot() {
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::BeginGroup();
    ImGui::Spacing();
    ImGui::SameLine();
    if (ImGui::SubTab("TRIGGERBOT", 0 == SelectedTriggerbotSubTab, ImVec2(205, 25)))
      SelectedTriggerbotSubTab = 0;
    ImGui::SameLine();
    if (ImGui::SubTab("ADVANCED", 1 == SelectedTriggerbotSubTab, ImVec2(205, 25)))
      SelectedTriggerbotSubTab = 1;
    ImGui::SameLine();
    if (ImGui::SubTab("WEAPONS", 2 == SelectedTriggerbotSubTab, ImVec2(205, 25)))
      SelectedTriggerbotSubTab = 2;
    ImGui::EndGroup();

    ImGui::SetCursorPos({15, 35});

    ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

    ImGui::Separator();
    DoubleSpacing();

    if (SelectedTriggerbotSubTab == 0) {
      ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 220, 43), true); {
        ImGui::Text("Triggerbot");
        ImGui::Checkbox("Enabled", &Features::Triggerbot::Enabled);
        ImGui::EndChildFrame();
      }

      if (Features::Triggerbot::Enabled && !Features::Triggerbot::AdvancedTriggerbot) {
        ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 220, 149), true); {
          ImGui::Spacing();
          const char *BindMethodIndex[] = { "Memory", "Keybind" };
          ImGui::ComboBox("Bind method", &Features::Triggerbot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
          if (Features::Triggerbot::BindMethod == 0) {
            ImGui::Checkbox("Require ADS", &Features::Triggerbot::OnADS);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Fire only when aiming down sights");
            if (Features::Triggerbot::OnADS) {
              ImGui::Checkbox("Always on for shotguns", &Features::Triggerbot::HipfireShotguns);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Don't require ADS on shotguns");
            }
          }

          if (Features::Triggerbot::BindMethod == 1) {
            int TriggerBind = static_cast<int>(Features::Triggerbot::TriggerBind);
            ImGui::ComboBox("Bind", &TriggerBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
            Features::Triggerbot::TriggerBind = static_cast<InputKeyType>(TriggerBind);
          }

          ImGui::MainSliderFloat("Range", &Features::Triggerbot::Range, 0, 1000, "%.0f");
          if (Features::Triggerbot::BindMethod == 0)
            ImGui::MainSliderFloat("Range (hip fire)", &Features::Triggerbot::RangeHipfire, 0, 1000, "%.0f");
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("If 'Require ADS' & 'Always on for shotguns' are enabled, this only applies to shotguns");
          ImGui::EndChildFrame();
        }
      }

      if (Features::Triggerbot::Enabled && Features::Triggerbot::AdvancedTriggerbot) { ImGui::Text("Advanced Triggerbot Is Enabled!"); }
    }

    if (SelectedTriggerbotSubTab == 1) { Advanced->AdvancedTriggerbotTab(Myself->WeaponIndex); }

    if (SelectedTriggerbotSubTab == 2) {
      if (!Features::Triggerbot::Enabled) { ImGui::Text("Triggerbot Is Disabled!"); }

      if (Features::Triggerbot::Enabled) {
        ImGui::Spacing();
        ImGui::Columns(3, "##triggerbotSelection", false);
        if (ImGui::BeginChildFrame(7, ImVec2({264, 240}), true)) {
          ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
          ImGui::Checkbox("P2020##Triggerbot", &Features::Triggerbot::P2020);
          ImGui::Checkbox("RE-45 Auto##Triggerbot", &Features::Triggerbot::RE45);
          ImGui::Checkbox("Alternator SMG##Triggerbot", &Features::Triggerbot::Alternator);
          ImGui::Checkbox("R-99 SMG##Triggerbot", &Features::Triggerbot::R99);
          ImGui::Checkbox("R-301 Carbine##Triggerbot", &Features::Triggerbot::R301);
          ImGui::Checkbox("M600 Spitfire##Triggerbot", &Features::Triggerbot::Spitfire);
          ImGui::Checkbox("G7 Scout##Triggerbot", &Features::Triggerbot::G7);
          ImGui::EndChildFrame();
        }
        if (ImGui::BeginChildFrame(8, ImVec2({264, 240}), true)) {
          ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
          ImGui::Checkbox("VK-47 Flatline##Triggerbot", &Features::Triggerbot::Flatline);
          ImGui::Checkbox("Prowler Burst SMG##Triggerbot", &Features::Triggerbot::Prowler);
          ImGui::Checkbox("Hemlock Burst AR##Triggerbot", &Features::Triggerbot::Hemlock);
          ImGui::Checkbox("30-30 Repeater##Triggerbot", &Features::Triggerbot::Repeater);
          ImGui::Checkbox("Rampage LMG##Triggerbot", &Features::Triggerbot::Rampage);
          ImGui::Checkbox("C.A.R SMG##Triggerbot", &Features::Triggerbot::CARSMG);
          ImGui::EndChildFrame();
        }

        ImGui::NextColumn();

        if (ImGui::BeginChildFrame(9, ImVec2({264, 240}), true)) {
          ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
          ImGui::Checkbox("Havoc Rifle##Triggerbot", &Features::Triggerbot::Havoc);
          ImGui::Checkbox("Devotion LMG##Triggerbot", &Features::Triggerbot::Devotion);
          ImGui::Checkbox("L-Star EMG##Triggerbot", &Features::Triggerbot::LSTAR);
          ImGui::Checkbox("Triple-Take##Triggerbot", &Features::Triggerbot::TripleTake);
          ImGui::Checkbox("Volt##Triggerbot", &Features::Triggerbot::Volt);
          ImGui::Checkbox("Nemesis Burst AR##Triggerbot", &Features::Triggerbot::Nemesis);
          ImGui::EndChildFrame();
        }
        if (ImGui::BeginChildFrame(10, ImVec2({264, 240}), true)) {
          ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
          ImGui::Checkbox("Mozambique##Triggerbot", &Features::Triggerbot::Mozambique);
          ImGui::Checkbox("Peacekeeper##Triggerbot", &Features::Triggerbot::Peacekeeper);
          ImGui::Checkbox("Mastiff##Triggerbot", &Features::Triggerbot::Mastiff);
          ImGui::EndChildFrame();
        }

        ImGui::NextColumn();

        if (ImGui::BeginChildFrame(11, ImVec2({237, 240}), true)) {
          ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
          ImGui::Checkbox("Longbow DMR##Triggerbot", &Features::Triggerbot::Longbow);
          ImGui::Checkbox("Charge Rifle##Triggerbot", &Features::Triggerbot::ChargeRifle);
          ImGui::Checkbox("Sentinel##Triggerbot", &Features::Triggerbot::Sentinel);
          ImGui::EndChildFrame();
        }
        if (ImGui::BeginChildFrame(12, ImVec2({237, 240}), true)) {
          ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
          ImGui::Checkbox("Wingman##Triggerbot", &Features::Triggerbot::Wingman);
          ImGui::Checkbox("EVA-8 Auto##Triggerbot", &Features::Triggerbot::EVA8);
          ImGui::Checkbox("Kraber .50-CAL Sniper##Triggerbot", &Features::Triggerbot::Kraber);
          ImGui::EndChildFrame();
        }
        ImGui::NextColumn();
      }
    }
    ImGui::EndChild();
    ImGui::EndChild();
  }

  void RenderGlow() {
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::BeginGroup();
    ImGui::Spacing();
    ImGui::SameLine();
    if (ImGui::SubTab("PLAYER", 0 == SelectedGlowSubTab, ImVec2(205, 25)))
      SelectedGlowSubTab = 0;
    ImGui::SameLine();
    if (ImGui::SubTab("ITEM", 1 == SelectedGlowSubTab, ImVec2(205, 25)))
      SelectedGlowSubTab = 1;
    ImGui::SameLine();
    if (ImGui::SubTab("VIEWMODEl", 2 == SelectedGlowSubTab, ImVec2(205, 25)))
      SelectedGlowSubTab = 2;
    ImGui::EndGroup();

    ImGui::SetCursorPos({15, 35});

    ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

    ImGui::Separator();
    DoubleSpacing();

    if (SelectedGlowSubTab == 0) {
      ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 220, 83), true); {
        ImGui::Spacing();
        ImGui::Text("Glow");
        ImGui::Checkbox("Player Glow", &Features::Glow::NewGlow);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Toggle Player Glow.");
        if (Features::Glow::NewGlow) {
          ImGui::MainSliderFloat("Glow Max Distance", &Features::Glow::GlowMaxDistance, 0, 1000, "%.0f");
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Only those in range will glow");
        }
        ImGui::EndChildFrame();
      }

      if (Features::Glow::NewGlow) {
        ImGui::Columns(2, "Player Glow Column", false);
        ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 613, WindowHeight - 198), true); {
          ImGui::Spacing();
          ImGui::Text("Settings");
          ImGui::MainSliderInt("Border Thickness##Glow", &Features::Glow::GlowRadius, 32, 200);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("How Thick The Border Is Around A Player.");

          const char *GlowBodyStyleIndex[] = {"None", "Pink", "Pink Visible Only", "Pulsing 1", "Pulsing Line Invisible Only", "Dark Pulsing Line", "Sharp Pulsing Visible", "Sharp Pulsing", "Pulsing Red Line", "Fast Pulsing Invisible Only", "Pulsing Up Visible Only", "Solid Pulsing", "Solid Pulsing 2", "Bright", "Bright 2", "Light", "Light Solid", "Red Pulsing Visible Only", "Wave", "Shaded Visible", "Wireframe", "Wireframe Visible Only", "Black", "Black Visible Only"};
          ImGui::ComboBox("Body Style", &Features::Glow::BodyStyle, GlowBodyStyleIndex, IM_ARRAYSIZE(GlowBodyStyleIndex));
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Changes The Player's Body Style.");

          const char *GlowOutlineStyleIndex[] = {"None", "Bright", "Bright Invisible Only", "Dark", "Pink", "White", "Gold Flashing", "Gold", "Brown", "Wave", "Red Visible Only", "Red Bright", "Heartbeat Visible Only", "Green Invisible Only", "Visible Only", "Bright Orange", "Red 2"};
          ImGui::ComboBox("Outline Style", &Features::Glow::OutlineStyle, GlowOutlineStyleIndex, IM_ARRAYSIZE(GlowOutlineStyleIndex));
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Changes The Player's Outline Style.");
          ImGui::EndChildFrame();
        }

        ImGui::NextColumn(); // Right

        ImGui::BeginChildFrame(3, ImVec2(WindowWidth - 630, WindowHeight - 198), true); {
          ImGui::Spacing();
          const char *GlowColorModeIndex[] = {"Shield Based", "Custom Color"};
          ImGui::ComboBox("Color Mode", &Features::Glow::GlowColorMode, GlowColorModeIndex, IM_ARRAYSIZE(GlowColorModeIndex));
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("What Color The Glow Will Be.\nShield Based = What Shield The Player Has\nCustom Color = Whatever Color You Want.");

          if (Features::Glow::GlowColorMode == 0) {
            const char *GlowShieldModeIndex[] = {"Current Shield", "Max Shield"};
            ImGui::ComboBox("Shield Mode", &Features::Glow::GlowColorShieldMode, GlowShieldModeIndex, IM_ARRAYSIZE(GlowShieldModeIndex));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("What Color The Glow Will Change To\nCurrent Shield = Player's Current Shield Points\nMax Shield = Player's Max Shield Points.");
            ImGui::ColorEdit3("Red Shield##GlowColor", Features::Colors::Enemy::RedShieldColor, ColorEditFlags);
            ImGui::SameLine();
            ImGui::ColorEdit3("Purple Shield##GlowColor", Features::Colors::Enemy::PurpleShieldColor, ColorEditFlags);
            ImGui::SameLine();
            ImGui::ColorEdit3("Blue Shield##GlowColor", Features::Colors::Enemy::BlueShieldColor, ColorEditFlags);
            ImGui::ColorEdit3("Grey Shield##GlowColor", Features::Colors::Enemy::GreyShieldColor, ColorEditFlags);
            ImGui::SameLine();
          }

          if (Features::Glow::GlowColorMode == 0 && Features::Glow::GlowColorShieldMode == 0) {
            ImGui::ColorEdit3("Low HP Color##GlowColor", Features::Colors::Enemy::LowGlowColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("What Color The Glow Will Change To When The Player Has No Shield.");
            ImGui::SameLine();
          }

          if (Features::Glow::GlowColorMode == 1) {
            ImGui::ColorEdit3("Invisible Color##GlowColor", Features::Colors::Enemy::InvisibleGlowColor, ColorEditFlags);
            ImGui::SameLine();
          }

          ImGui::ColorEdit3("Visible Color##GlowColor", Features::Colors::Enemy::VisibleGlowColor, ColorEditFlags);
          ImGui::EndChildFrame();
        }
      }
    }

    if (SelectedGlowSubTab == 1) {
      ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 220, WindowHeight - 110), true); {
        ImGui::Spacing();
        ImGui::Text("Item Glow");
        ImGui::Checkbox("Enabled##Item", &Features::Glow::Item::ItemGlow);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Items Will Glow Through Walls.\nIncludes Deathboxes.");
        if (Features::Glow::Item::ItemGlow) {
          const char *ItemGlowBodyStyleIndex[] = {"Clear", "Light", "Solid", "Light To Dark Fade"};
          ImGui::ComboBox("Inside Style", &Features::Glow::Item::SelectedInsideStyle, ItemGlowBodyStyleIndex, IM_ARRAYSIZE(ItemGlowBodyStyleIndex));
          const char *ItemGlowOutlineIndex[] = {"None", "Light 1", "Light 2", "Solid", "Gold", "Orange", "Pulsing", "Light Red (Visible Only)", "Red", "Fading (Visible Only)", "Soft", "Visible Only"};
          ImGui::ComboBox("Outline Style", &Features::Glow::Item::SelectedOutlineStyle, ItemGlowOutlineIndex, IM_ARRAYSIZE(ItemGlowOutlineIndex));
          ImGui::MainSliderInt("Glow Thickness", &Features::Glow::Item::ItemGlowThickness, 0, 250);
          ImGui::Text("Item Glow Toggles");
          const char *ItemGlowItemSelection[] = {"Simple", "Custom"};
          ImGui::ComboBox("Item Selection", &Features::Glow::Item::SelectedItemSelection, ItemGlowItemSelection, IM_ARRAYSIZE(ItemGlowItemSelection));

          if (Features::Glow::Item::SelectedItemSelection == 1) {
            ImGui::Checkbox("Common", &Features::Glow::Item::Common);
            ImGui::Checkbox("Rare", &Features::Glow::Item::Rare);
            ImGui::Checkbox("Epic", &Features::Glow::Item::Epic);
            ImGui::Checkbox("Gold", &Features::Glow::Item::Gold);
            ImGui::Checkbox("Legendary", &Features::Glow::Item::Legendary);
            ImGui::Checkbox("Weapons", &Features::Glow::Item::Weapons);
            ImGui::Checkbox("Ammo", &Features::Glow::Item::Ammo);
          }
        }

        ImGui::EndChildFrame();
      }
    }

    if (SelectedGlowSubTab == 2) {
      ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 220, WindowHeight - 110), true); {
        ImGui::Spacing();
        ImGui::Text("Viewmodel Glow");
        ImGui::Checkbox("Enabled", &Features::Glow::ViewModelGlow);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Toggle ViewModel Glow.");
        if (Features::Glow::ViewModelGlow) {
          const char *ViewmodelGlowIndex[] = {"Cyan Outline", "Light Red Outline", "White Outline", "Orange Outline", "Yellow Outline", "Solid Green", "Solid Orange", "Solid Yellow", "Solid Yellow Pulsing", "Solid Purple", "Solid Light Blue", "Solid Light Grey", "Solid White", "Solid Cyan", "Solid Hot Pink", "Solid Light Yellow", "Solid Light Orange", "Solid Light Green", "Solid Black", "Chrome"};
          ImGui::ComboBox("Selected Color", &Features::Glow::ViewModelGlowCombo, ViewmodelGlowIndex, IM_ARRAYSIZE(ViewmodelGlowIndex));
        }

        ImGui::EndChildFrame();
      }
    }
    ImGui::EndChild();
    ImGui::EndChild();
  }

  void RenderESP(const Overlay &OverlayWindow) {
    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::BeginChild("workzone", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::BeginGroup();
    ImGui::Spacing();
    ImGui::SameLine();
    if (ImGui::SubTab("PLAYER", 0 == SelectedESPSubTabLeft, ImVec2(135, 25)))
      SelectedESPSubTabLeft = 0;
    ImGui::SameLine();
    if (ImGui::SubTab("TEAM", 1 == SelectedESPSubTabLeft, ImVec2(135, 25)))
      SelectedESPSubTabLeft = 1;
    ImGui::SameLine();
    if (ImGui::SubTab("SETTINGS", 2 == SelectedESPSubTabLeft, ImVec2(135, 25)))
      SelectedESPSubTabLeft = 2;
    ImGui::SameLine();
    if (ImGui::SubTab("COLORS", 0 == SelectedESPSubTabRight, ImVec2(92, 25)))
      SelectedESPSubTabRight = 0;
    ImGui::SameLine();
    if (ImGui::SubTab("RADAR", 1 == SelectedESPSubTabRight, ImVec2(92, 25)))
      SelectedESPSubTabRight = 1;
    ImGui::SameLine();
    if (ImGui::SubTab("CROSSHAIR", 2 == SelectedESPSubTabRight, ImVec2(92, 25)))
      SelectedESPSubTabRight = 2;
    ImGui::SameLine();
    if (ImGui::SubTab("OTHER", 3 == SelectedESPSubTabRight, ImVec2(92, 25)))
      SelectedESPSubTabRight = 3;
    ImGui::EndGroup();

    ImGui::SetCursorPos({15, 35});

    ImGui::BeginChild("workzone", ImVec2(WindowWidth - 186, WindowHeight - 90), false, ImGuiWindowFlags_NoScrollbar);

    ImGui::Separator();
    DoubleSpacing();
    ImGui::Columns(2, "ESP Columns", false);
    ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 613, WindowHeight - 110), true); {
      ImGui::Spacing();
      if (SelectedESPSubTabLeft == 0) {
        ImGui::Text("Player ESP");
        ImGui::Checkbox("Draw Players", &Features::Sense::Enemy::DrawEnemy);

        if (Features::Sense::Enemy::DrawEnemy) {
          ImGui::Text("Boxes");
          ImGui::Checkbox("Draw Boxes", &Features::Sense::Enemy::DrawBoxes);
          if (Features::Sense::Enemy::DrawBoxes) {
            const char *BoxTypeIndex[] = {"2D", "2D Filled", "2D Corners"};
            ImGui::ComboBox("Box Type", &Features::Sense::Enemy::BoxType, BoxTypeIndex, IM_ARRAYSIZE(BoxTypeIndex));

            ImGui::MainSliderFloat("Box Thickness", &Features::Sense::Enemy::BoxThickness, 1, 10, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes the thickness of the boxes");
          }

          ImGui::Text("Tracers");
          ImGui::Checkbox("Draw Tracers", &Features::Sense::Enemy::DrawTracers);
          if (Features::Sense::Enemy::DrawTracers) {
            const char *TracerPos[] = {"Top", "Crosshair", "Bottom"};
            ImGui::ComboBox("Tracer Position", &Features::Sense::Enemy::TracerPosition, TracerPos, IM_ARRAYSIZE(TracerPos));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Where tracers will be drawn from.");
            const char *TracerBones[] = {"Top", "Bottom"};
            ImGui::ComboBox("Tracer Bone", &Features::Sense::Enemy::TracerBone, TracerBones, IM_ARRAYSIZE(TracerBones));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Where tracers will be drawn to.");
            ImGui::MainSliderFloat("Tracer Thickness", &Features::Sense::Enemy::TracerThickness, 1, 10, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes the thickness of the tracers");
          }

          ImGui::Text("Skeleton");
          ImGui::Checkbox("Draw Skeleton", &Features::Sense::Enemy::DrawSkeleton);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Draw the enemies skeletons (Spooky)");
          if (Features::Sense::Enemy::DrawSkeleton) {
            ImGui::MainSliderFloat("Skeleton Thickness", &Features::Sense::Enemy::SkeletonThickness, 1, 10, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes the thickness of the bones");
          }

          ImGui::Text("Head Circle");
          ImGui::Checkbox("Draw Head Circle", &Features::Sense::Enemy::DrawHeadCircle);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Draw the enemies Head");
          if (Features::Sense::Enemy::DrawHeadCircle) {
            ImGui::MainSliderFloat("Head Circle Thickness", &Features::Sense::Enemy::HeadCircleThickness, 1, 10, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes the thickness of the Circle");
          }

          ImGui::Text("Info Bars");
          ImGui::Checkbox("Draw Bars", &Features::Sense::Enemy::DrawBars);
          if (Features::Sense::Enemy::DrawBars) {
            const char *BarStyleIndex[] = {"Side", "Top", "Seer"};
            ImGui::ComboBox("Bar Style", &Features::Sense::Enemy::BarStyle, BarStyleIndex, IM_ARRAYSIZE(BarStyleIndex));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Where AND What Style Of Health + Shield Bar Will Be.\nSeer = Seer's Ability.");

            if (!Features::Sense::Enemy::BarStyle == 2) { Features::Sense::Enemy::DrawSeer = false; }

            if (Features::Sense::Enemy::BarStyle == 0 or Features::Sense::Enemy::BarStyle == 1) {
              const char *BarModeIndex[] = {"Health Only", "Shield Only", "Health & Shield"};
              ImGui::ComboBox("Bar Mode", &Features::Sense::Enemy::BarMode, BarModeIndex, IM_ARRAYSIZE(BarModeIndex));
            }

            if (Features::Sense::Enemy::BarStyle == 2) { // Seer
              ImGui::Checkbox("Draw Seer", &Features::Sense::Enemy::DrawSeer);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Draw Seer's abilitiy (Show Health & Armor) on enemies");
            }

            if (Features::Sense::Enemy::BarStyle == 1) { // Top
              ImGui::MainSliderFloat("Bar Height", &Features::Sense::Enemy::BarHeight, 5, 20, "%.0f");
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Height of the enemy bar");
              ImGui::MainSliderFloat("Bar Width", &Features::Sense::Enemy::BarWidth, 10, 125, "%.0f");
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Width of the enemy bar");
            }

            if (Features::Sense::Enemy::BarStyle == 1) { // Top
              ImGui::MainSliderFloat("Bar Thickness", &Features::Sense::Enemy::BarThickness, 1, 10, "%.0f");
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Thickness of the health/shield bar");
            }
          }

          ImGui::Text("Player Info");
          ImGui::Checkbox("Draw Names", &Features::Sense::Enemy::DrawNames);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Show enemies names.");

          ImGui::Checkbox("Draw Distance", &Features::Sense::Enemy::DrawDistance);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Show how far away the enemies are");

          ImGui::Checkbox("Draw Legend", &Features::Sense::Enemy::DrawLegend);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Show What Legend The Enemy Is Playing As.");

          ImGui::Checkbox("Draw Weapon", &Features::Sense::Enemy::DrawWeapon);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Show what weapon an enemy is currently holding.");

          ImGui::Checkbox("Draw Status", &Features::Sense::Enemy::DrawStatus);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Draw enemies current health and armor");
          if (Features::Sense::Enemy::DrawStatus) {
            ImGui::SameLine();
            ImGui::Checkbox("Show Max Values", &Features::Sense::Enemy::ShowMaxStatusValues);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Adds their max health and max armor at the end.");
          }

          DoubleSpacing();
        }
      }

      if (SelectedESPSubTabLeft == 1) {
        ImGui::Text("Team ESP");
        ImGui::Checkbox("Draw Teammates", &Features::Sense::Teammate::DrawTeam);

        if (Features::Sense::Teammate::DrawTeam) {
          ImGui::Text("Boxes");
          ImGui::Checkbox("Draw Boxes", &Features::Sense::Teammate::DrawBoxes);
          if (Features::Sense::Teammate::DrawBoxes) {
            const char *BoxTypeIndex[] = {"2D", "2D Filled", "2D Corners"};
            ImGui::ComboBox("Box Type", &Features::Sense::Teammate::BoxType, BoxTypeIndex, IM_ARRAYSIZE(BoxTypeIndex));

            ImGui::MainSliderFloat("Box Thickness", &Features::Sense::Teammate::BoxThickness, 1, 10, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes the thickness of the boxes");
          }

          ImGui::Text("Tracers");
          ImGui::Checkbox("Draw Tracers", &Features::Sense::Teammate::DrawTracers);
          if (Features::Sense::Teammate::DrawTracers) {
            const char *TracerPos[] = {"Top", "Crosshair", "Bottom"};
            ImGui::ComboBox("Tracer Position", &Features::Sense::Teammate::TracerPosition, TracerPos, IM_ARRAYSIZE(TracerPos));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Where tracers will be drawn from.");
            const char *TracerBones[] = {"Top", "Bottom"};
            ImGui::ComboBox("Tracer Bone", &Features::Sense::Teammate::TracerBone, TracerBones, IM_ARRAYSIZE(TracerBones));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Where tracers will be drawn to.");
            ImGui::MainSliderFloat("Tracer Thickness", &Features::Sense::Teammate::TracerThickness, 1, 10, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes the thickness of the tracers");
          }

          ImGui::Text("Skeleton");
          ImGui::Checkbox("Draw Skeleton", &Features::Sense::Teammate::DrawSkeleton);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Draw the enemies skeletons (Spooky)");
          if (Features::Sense::Teammate::DrawSkeleton) {
            ImGui::MainSliderFloat("Skeleton Thickness", &Features::Sense::Teammate::SkeletonThickness, 1, 10, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes the thickness of the bones");
          }

          ImGui::Text("Head Circle");
          ImGui::Checkbox("Draw Head Circle", &Features::Sense::Teammate::DrawHeadCircle);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Draw the enemies Head");
          if (Features::Sense::Teammate::DrawHeadCircle) {
            ImGui::MainSliderFloat("Head Circle Thickness", &Features::Sense::Teammate::HeadCircleThickness, 1, 10, "%.0f");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes the thickness of the Circle");
          }

          ImGui::Text("Info Bars");
          ImGui::Checkbox("Draw Bars", &Features::Sense::Teammate::DrawBars);
          if (Features::Sense::Teammate::DrawBars) {
            const char *BarStyleIndex[] = {"Side", "Top", "Seer"};
            ImGui::ComboBox("Bar Style", &Features::Sense::Teammate::BarStyle, BarStyleIndex, IM_ARRAYSIZE(BarStyleIndex));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Where AND What Style Of Health + Shield Bar Will Be.\nSeer = Seer's Ability.");

            if (!Features::Sense::Teammate::BarStyle == 2) { Features::Sense::Teammate::DrawSeer = false; }

            if (Features::Sense::Teammate::BarStyle == 0 or Features::Sense::Teammate::BarStyle == 1) {
              const char *BarModeIndex[] = {"Health Only", "Shield Only", "Health & Shield"};
              ImGui::ComboBox("Bar Mode", &Features::Sense::Teammate::BarMode, BarModeIndex, IM_ARRAYSIZE(BarModeIndex));
            }

            if (Features::Sense::Teammate::BarStyle == 2) { // Seer
              ImGui::Checkbox("Draw Seer", &Features::Sense::Teammate::DrawSeer);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Draw Seer's abilitiy (Show Health & Armor) on enemies");
            }

            if (Features::Sense::Teammate::BarStyle == 1) { // Top
              ImGui::MainSliderFloat("Bar Height", &Features::Sense::Teammate::BarHeight, 5, 20, "%.0f");
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Height of the Teammate bar");
              ImGui::MainSliderFloat("Bar Width", &Features::Sense::Teammate::BarWidth, 10, 125, "%.0f");
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Width of the Teammate bar");
            }

            if (Features::Sense::Teammate::BarStyle == 1) { // Top
              ImGui::MainSliderFloat("Bar Thickness", &Features::Sense::Teammate::BarThickness, 1, 10, "%.0f");
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Thickness of the health/shield bar");
            }
          }

          ImGui::Text("Player Info");
          ImGui::Checkbox("Draw Names", &Features::Sense::Teammate::DrawNames);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Show enemies names.");

          ImGui::Checkbox("Draw Distance", &Features::Sense::Teammate::DrawDistance);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Show how far away the enemies are");

          ImGui::Checkbox("Draw Legend", &Features::Sense::Teammate::DrawLegend);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Show What Legend The Teammate Is Playing As.");

          ImGui::Checkbox("Draw Weapon", &Features::Sense::Teammate::DrawWeapon);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Show what weapon an Teammate is currently holding.");

          ImGui::Checkbox("Draw Status", &Features::Sense::Teammate::DrawStatus);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Draw enemies current health and armor");
          if (Features::Sense::Teammate::DrawStatus) {
            ImGui::SameLine();
            ImGui::Checkbox("Show Max Values", &Features::Sense::Teammate::ShowMaxStatusValues);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Adds their max health and max armor at the end.");
          }

          DoubleSpacing();
        }
      }

      if (SelectedESPSubTabLeft == 2) {
        ImGui::Spacing();
        ImGui::Text("Settings");
        ImGui::Checkbox("Visibility Check", &Features::Sense::VisibilityCheck);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Draw's ESP ONLY On Visible Players");
        ImGui::MainSliderFloat("ESP Max Distance", &Features::Sense::ESPMaxDistance, 0, 1000, "%.0f");
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Only those in range will be shown.");
        ImGui::Checkbox("Text Outline", &Features::Sense::TextOutline);

        ImGui::Text("Position Changer");
        const char *PositionIndex[] = {"Top 1", "Top 2", "Bottom 1", "Bottom 2", "Bottom 3"};
        ImGui::ComboBox("Name Position", &Features::Sense::Positions::NamePosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
        ImGui::ComboBox("Distance Position", &Features::Sense::Positions::DistancePosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
        ImGui::ComboBox("Legend Position", &Features::Sense::Positions::LegendPosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
        ImGui::ComboBox("Weapon Position", &Features::Sense::Positions::WeaponPosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
        ImGui::ComboBox("Status Position", &Features::Sense::Positions::StatusPosition, PositionIndex, IM_ARRAYSIZE(PositionIndex));
      }

      ImGui::EndChildFrame();
    }

    ImGui::NextColumn();

    ImGui::BeginChildFrame(2, ImVec2(WindowWidth - 630, WindowHeight - 110), true); {
      if (SelectedESPSubTabRight == 0) {
        ImGui::Spacing();
        if (SelectedESPSubTabLeft == 0 or SelectedESPSubTabLeft == 2) {
          ImGui::Text("Colors - Players");
          if (Features::Sense::Enemy::DrawBoxes) {
            ImGui::Text("Boxes");
            ImGui::ColorEdit4("Visible##EnemyBoxColor", Features::Colors::Enemy::VisibleBoxColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Box Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##EnemyBoxColor", Features::Colors::Enemy::InvisibleBoxColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Box Invisible Color");

            if (Features::Sense::Enemy::BoxType == 1) {
              ImGui::SameLine();
              ImGui::ColorEdit4("Filled Visible##Enemy", Features::Colors::Enemy::VisibleFilledBoxColor, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Filled Box Visible Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Filled Invisible##Enemy", Features::Colors::Enemy::InvisibleFilledBoxColor, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Filled Box Invisible Color");
            }
          }

          if (Features::Sense::Enemy::DrawTracers) {
            ImGui::Text("Tracers");
            ImGui::ColorEdit4("Visible##EnemyTracer", Features::Colors::Enemy::VisibleTracerColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Tracer Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##EnemyTracer", Features::Colors::Enemy::InvisibleTracerColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Tracer Invisible Color");
          }

          if (Features::Sense::Enemy::DrawSkeleton) {
            ImGui::Text("Skeleton");
            ImGui::ColorEdit4("Visible##EnemySkeletonColor", Features::Colors::Enemy::VisibleSkeletonColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Skeleton Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##EnemySkeletonColor", Features::Colors::Enemy::InvisibleSkeletonColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Skeleton Invisible Color");
          }

          if (Features::Sense::Enemy::DrawHeadCircle) {
            ImGui::Text("Head Circle");
            ImGui::ColorEdit4("Visible##EnemyHeadCircleColor", Features::Colors::Enemy::VisibleHeadCircleColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Head Circle Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##EnemyHeadCircleColor", Features::Colors::Enemy::InvisibleHeadCircleColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Head Circle Invisible Color");
          }

          if (Features::Sense::Enemy::DrawBars) {
            if (Features::Sense::Enemy::BarMode == 0 or Features::Sense::Enemy::BarMode == 1) {
              ImGui::Text("Info Bars");
              const char *BarColorModeIndex[] = {"Max Shield", "Current Shield"};
              ImGui::ComboBox("Bar Color", &Features::Sense::Enemy::BarColorMode, BarColorModeIndex, IM_ARRAYSIZE(BarColorModeIndex));
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("What Color The Shield Bar Will Be.");
            }
          }

          if (Features::Sense::Enemy::DrawNames) {
            ImGui::Text("Names");
            ImGui::ColorEdit4("Visible##EnemyNameColor", Features::Colors::Enemy::VisibleNameColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Name Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##EnemyNameColor", Features::Colors::Enemy::InvisibleNameColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Name Invisible Color");
          }

          if (Features::Sense::Enemy::DrawDistance) {
            ImGui::Text("Distance");
            ImGui::ColorEdit4("Visible##EnemyDistanceColor", Features::Colors::Enemy::VisibleDistanceColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Distance Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##EnemyDistanceColor", Features::Colors::Enemy::InvisibleDistanceColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Distance Invisible Color");
          }

          if (Features::Sense::Enemy::DrawLegend) {
            ImGui::Text("Legend");
            ImGui::ColorEdit4("Visible##EnemyLegendColor", Features::Colors::Enemy::VisibleLegendColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Legend Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##EnemyLegendColor", Features::Colors::Enemy::InvisibleLegendColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Legend Invisible Color");
          }

          if (Features::Sense::Enemy::DrawWeapon) {
            ImGui::Text("Weapon");
            const char *WeaponColorModeIndex[] = {"Single Color", "Multiple Colors"};
            ImGui::ComboBox("Weapon Color Mode", &Features::Colors::WeaponColorMode, WeaponColorModeIndex, IM_ARRAYSIZE(WeaponColorModeIndex));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes The Weapon Text Color To The Ammo Type Of The Weapon.");

            if (Features::Colors::WeaponColorMode == 0) {
              ImGui::ColorEdit4("Visible##EnemyWeaponColor", Features::Colors::Enemy::VisibleWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Weapon Visible Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Invisible##EnemyWeaponColor", Features::Colors::Enemy::InvisibleWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Weapon Invisible Color");
            }

            if (Features::Colors::WeaponColorMode == 1) {
              ImGui::ColorEdit4("Light##ESPEnemyWeaponColor", Features::Colors::Enemy::LightWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Light Weapon Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Heavy##ESPEnemyWeaponColor", Features::Colors::Enemy::HeavyWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Heavy Weapon Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Energy##ESPEnemyWeaponColor", Features::Colors::Enemy::EnergyWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Energy Weapon Color");

              ImGui::ColorEdit4("Shotguns##ESPEnemyWeaponColor", Features::Colors::Enemy::ShotgunWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Shotgun Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Snipers##ESPEnemyWeaponColor", Features::Colors::Enemy::SniperWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Sniper Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Legendary##ESPEnemyWeaponColor", Features::Colors::Enemy::LegendaryWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Legendary Weapon Color");

              ImGui::ColorEdit4("Throwables##ESPEnemyWeapon", Features::Colors::Enemy::ThrowableWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Throwable Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Melee##ESPEnemyWeapon", Features::Colors::Enemy::MeleeWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Melee Color");
            }
          }
        }

        if (SelectedESPSubTabLeft == 1) {
          ImGui::Text("Colors - Teammates");
          if (Features::Sense::Teammate::DrawBoxes) {
            ImGui::Text("Boxes");
            ImGui::ColorEdit4("Visible##TeammateBoxColor", Features::Colors::Teammate::VisibleBoxColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Box Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##TeammateBoxColor", Features::Colors::Teammate::InvisibleBoxColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Box Invisible Color");

            if (Features::Sense::Teammate::BoxType == 1) {
              ImGui::SameLine();
              ImGui::ColorEdit4("Filled Visible##Teammate", Features::Colors::Teammate::VisibleFilledBoxColor, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Filled Box Visible Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Filled Invisible##Teammate", Features::Colors::Teammate::InvisibleFilledBoxColor, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Filled Box Invisible Color");
            }
          }

          if (Features::Sense::Teammate::DrawTracers) {
            ImGui::Text("Tracers");
            ImGui::ColorEdit4("Visible##TeammateTracer", Features::Colors::Teammate::VisibleTracerColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Tracer Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##TeammateTracer", Features::Colors::Teammate::InvisibleTracerColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Tracer Invisible Color");
          }

          if (Features::Sense::Teammate::DrawSkeleton) {
            ImGui::Text("Skeleton");
            ImGui::ColorEdit4("Visible##TeammateSkeletonColor", Features::Colors::Teammate::VisibleSkeletonColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Skeleton Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##TeammateSkeletonColor", Features::Colors::Teammate::InvisibleSkeletonColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Skeleton Invisible Color");
          }

          if (Features::Sense::Teammate::DrawHeadCircle) {
            ImGui::Text("Head Circle");
            ImGui::ColorEdit4("Visible##TeammateHeadCircleColor", Features::Colors::Teammate::VisibleHeadCircleColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Head Circle Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##TeammateHeadCircleColor", Features::Colors::Teammate::InvisibleHeadCircleColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Head Circle Invisible Color");
          }

          if (Features::Sense::Teammate::DrawBars) {
            if (Features::Sense::Teammate::BarMode == 0 or Features::Sense::Teammate::BarMode == 1) {
              ImGui::Text("Info Bars");
              const char *BarColorModeIndex[] = {"Max Shield", "Current Shield"};
              ImGui::ComboBox("Bar Color", &Features::Sense::Teammate::BarColorMode, BarColorModeIndex, IM_ARRAYSIZE(BarColorModeIndex));
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("What Color The Shield Bar Will Be.");
            }
          }

          if (Features::Sense::Teammate::DrawNames) {
            ImGui::Text("Names");
            ImGui::ColorEdit4("Visible##TeammateNameColor", Features::Colors::Teammate::VisibleNameColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Name Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##TeammateNameColor", Features::Colors::Teammate::InvisibleNameColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Name Invisible Color");
          }

          if (Features::Sense::Teammate::DrawDistance) {
            ImGui::Text("Distance");
            ImGui::ColorEdit4("Visible##TeammateDistanceColor", Features::Colors::Teammate::VisibleDistanceColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Distance Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##TeammateDistanceColor", Features::Colors::Teammate::InvisibleDistanceColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Distance Invisible Color");
          }

          if (Features::Sense::Teammate::DrawLegend) {
            ImGui::Text("Legend");
            ImGui::ColorEdit4("Visible##TeammateLegendColor", Features::Colors::Teammate::VisibleLegendColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Legend Visible Color");
            ImGui::SameLine();
            ImGui::ColorEdit4("Invisible##TeammateLegendColor", Features::Colors::Teammate::InvisibleLegendColor, ColorEditFlags);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Legend Invisible Color");
          }

          if (Features::Sense::Teammate::DrawWeapon) {
            ImGui::Text("Weapon");
            const char *WeaponColorModeIndex[] = {"Single Color", "Multiple Colors"};
            ImGui::ComboBox("Weapon Color Mode", &Features::Colors::WeaponColorMode, WeaponColorModeIndex, IM_ARRAYSIZE(WeaponColorModeIndex));
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Changes The Weapon Text Color To The Ammo Type Of The Weapon.");

            if (Features::Colors::WeaponColorMode == 0) {
              ImGui::ColorEdit4("Visible##TeammateWeaponColor", Features::Colors::Teammate::VisibleWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Weapon Visible Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Invisible##TeammateWeaponColor", Features::Colors::Teammate::InvisibleWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Weapon Invisible Color");
            }

            if (Features::Colors::WeaponColorMode == 1) {
              ImGui::ColorEdit4("Light##ESPTeammateWeaponColor", Features::Colors::Teammate::LightWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Light Weapon Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Heavy##ESPTeammateWeaponColor", Features::Colors::Teammate::HeavyWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Heavy Weapon Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Energy##ESPTeammateWeaponColor", Features::Colors::Teammate::EnergyWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Energy Weapon Color");

              ImGui::ColorEdit4("Shotguns##ESPTeammateWeaponColor", Features::Colors::Teammate::ShotgunWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Shotgun Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Snipers##ESPTeammateWeaponColor", Features::Colors::Teammate::SniperWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Sniper Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Legendary##ESPTeammateWeaponColor", Features::Colors::Teammate::LegendaryWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Legendary Weapon Color");

              ImGui::ColorEdit4("Throwables##ESPTeammateWeapon", Features::Colors::Teammate::ThrowableWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Throwable Color");
              ImGui::SameLine();
              ImGui::ColorEdit4("Melee##ESPTeammateWeapon", Features::Colors::Teammate::MeleeWeaponColor, ColorEditFlags);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Melee Color");
            }
          }
        }
      }

      if (SelectedESPSubTabRight == 1) {
        ImGui::Spacing();
        ImGui::Text("Mini Map");
        ImGui::Checkbox("Enabled##MiniMap", &Features::Radar::MiniMap);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Toggle the mini map radar on the top left of the screen");
        if (Features::Radar::MiniMap) {
          ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "May not be on-point.");
          ImGui::Separator();
          ImGui::Text("Range");
          ImGui::MainSliderFloat("Mini Map Radar Range", &Features::Radar::MiniMapRange, 0, 180, "%.0f");
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Mini Map range from 0 to 200.");

          ImGui::Checkbox("Mini Map Guides", &Features::Radar::MiniMapGuides);
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Toggle the mini map guides.");

          ImGui::Text("Position");
          ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "Turn on Mini Map Guides and allign with your player's arrow on the in-game minimap.");
          ImGui::MainSliderInt("Mini Map Position X", &Features::Radar::MiniMapScaleX, 0, 2560);
          ImGui::MainSliderInt("Mini Map Position Y", &Features::Radar::MiniMapScaleY, 0, 1440);

          ImGui::Text("Enemy Identifier");
          ImGui::MainSliderInt("Mini Map Radar Dot Size", &Features::Radar::MiniMapDotSize, 0, 10);
          ImGui::ColorEdit4("Circle Color##Radar", Features::Radar::CircleColor, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs);
        }

        ImGui::Text("ALGS Style Map");
        ImGui::Checkbox("Enabled##BigMap", &Features::Radar::BigMap);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Toggle the ALGS Style Map.");
        if (Features::Radar::BigMap) {
          int BigMapBind = static_cast<int>(Features::Radar::BigMapBind);
          ImGui::ComboBox("Bind##BigMap", &BigMapBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Bind For ALGS Map");
          Features::Radar::BigMapBind = static_cast<InputKeyType>(BigMapBind);
          ImGui::TextColored(ImVec4(0.99, 0, 0, 0.99), "Make sure to close out of the in-game map before activating or you will crash!");
        }
      }

      if (SelectedESPSubTabRight == 2) {
        ImGui::Spacing();
        ImGui::Text("Crosshair");
        ImGui::Checkbox("Draw Crosshair", &Features::Sense::DrawCrosshair);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Draws a crosshair");
        if (Features::Sense::DrawCrosshair) {
          ImGui::MainSliderFloat("Crosshair Size", &Features::Sense::CrosshairSize, 0, 1000, "%.0f");
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Changes the size of the crosshair");
          ImGui::MainSliderFloat("Crosshair Thickness", &Features::Sense::CrosshairThickness, 1, 50, "%.0f");
          if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Changes the Crosshair's thickness");
          ImGui::ColorEdit4("Crosshair Color", Features::Colors::CrosshairColor, ColorEditFlags);
        }
      }

      if (SelectedESPSubTabRight == 3) {
        ImGui::Spacing();
        ImGui::Text("Spectator List");
        ImGui::Checkbox("Draw Spectator List", &Features::Sense::ShowSpectators);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
          ImGui::SetTooltip("Show Spectators");

        ImGui::Text("Watermark");
        ImGui::Checkbox("Draw Watermark", &Features::Watermark::Watermark);
        if (Features::Watermark::Watermark) {
          ImGui::Text("Watermark Settings");
          ImGui::Checkbox("Display Name", &Features::Watermark::Name);
          ImGui::Checkbox("Display Processing Speed", &Features::Watermark::ProcessingSpeed);
          ImGui::Checkbox("Display Spectators Number", &Features::Watermark::Spectators);
          ImGui::Checkbox("Display Game FPS", &Features::Watermark::GameFPS);
        }

        ImGui::Text("Warning Text");
        ImGui::Checkbox("Draw Spectator Warning", &Features::Sense::DrawSpectatorWarning);
        ImGui::Checkbox("Draw Visible Warning", &Features::Sense::DrawVisibleWarning);
        if (Features::Sense::DrawSpectatorWarning or Features::Sense::DrawVisibleWarning) {
          ImGui::Checkbox("Warning Text Outline", &Features::Sense::WarningTextOutline);
          int ScreenWidth;
          int ScreenHeight;
          OverlayWindow.GetScreenResolution(ScreenWidth, ScreenHeight);
          ImGui::MainSliderInt("Warning Text Position X", &Features::Sense::WarningTextX, 0, ScreenWidth);
          ImGui::MainSliderInt("Warning Text Position Y", &Features::Sense::WarningTextY, 0, ScreenHeight);
          if (ImGui::Button("Auto Set Position", ImVec2(125, 25))) {
            const int AutoWidth = ScreenWidth / 2;
            const int AutoHeight = (ScreenHeight / 2) + 80;
            Features::Sense::WarningTextX = AutoWidth;
            Features::Sense::WarningTextY = AutoHeight;
          }

          if (Features::Sense::DrawSpectatorWarning) {
            ImGui::ColorEdit4("Spectator Warning", Features::Colors::SpectatorWarningColor, ColorEditFlags);
            ImGui::SameLine();
          }

          if (Features::Sense::DrawVisibleWarning) { ImGui::ColorEdit4("Visible Warning", Features::Colors::VisibleWarningColor, ColorEditFlags); }
        }
      }
      ImGui::EndChildFrame();
    }
    ImGui::EndChild();
    ImGui::EndChild();
  }

  void RenderMisc() const {
    ImGui::SetCursorPos(ImVec2(15, 15));
    ImGui::BeginChild("misc", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
    ImGui::Spacing();
    ImGui::SameLine();

    ImGui::Columns(2, "Misc columns", false);

    ImGui::Text("Auto shoot");
    ImGui::BeginChildFrame(1, ImVec2((WindowWidth - 230) / 2, (WindowHeight - 100) / 2), true); {
      ImGui::Spacing();
      ImGui::Checkbox("Enable", &Features::Misc::RapidFire);
      if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        ImGui::SetTooltip("Turns semi-automatic + slow firing weapons automatic");
      if (Features::Misc::RapidFire) {
        ImGui::MainSliderInt("Delay", &Features::Misc::RapidFireDelay, 25, 200);        ImGui::PushItemWidth(-100);

        int RapidFireBind = static_cast<int>(Features::Misc::RapidFireBind);
        ImGui::ComboBox("Bind", &RapidFireBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
        Features::Misc::RapidFireBind = static_cast<InputKeyType>(RapidFireBind);

        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
        ImGui::Checkbox("P2020##Misc", &Features::Misc::RapidP2020);
        ImGui::SameLine();
        ImGui::Checkbox("R-301 Carbine##Misc", &Features::Misc::RapidR301);
        ImGui::SameLine();
        ImGui::Checkbox("G7 Scout##Misc", &Features::Misc::RapidG7);

        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
        ImGui::Checkbox("VK-47 Flatline##Misc", &Features::Misc::RapidFlatline);
        ImGui::SameLine();
        ImGui::Checkbox("Prowler Burst SMG##Misc", &Features::Misc::RapidProwler);
        ImGui::SameLine();
        ImGui::Checkbox("Hemlock Burst AR##Misc", &Features::Misc::RapidHemlock);

        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
        ImGui::Checkbox("Nemesis Burst AR##Misc", &Features::Misc::RapidNemesis);

        ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
        ImGui::Checkbox("Mozambique##Misc", &Features::Misc::RapidMozambique);

        ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
        ImGui::Checkbox("Wingman##Misc", &Features::Misc::RapidWingman);
        ImGui::SameLine();
        ImGui::Checkbox("EVA-8 Auto##Misc", &Features::Misc::RapidEVA8);
      }
      ImGui::EndChildFrame();
    }

    ImGui::Text("Skins");
    ImGui::BeginChildFrame(2, ImVec2((WindowWidth - 230) / 2, 0), true); {
      ImGui::Spacing();
      ImGui::Checkbox("Skin changer", &Features::Misc::SkinChanger);
      if (Features::Misc::SkinChanger) {
        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Light");
        ImGui::MainSliderInt("P2020", &Features::Misc::SkinP2020, 0, 10);
        ImGui::MainSliderInt("RE-45 Auto", &Features::Misc::SkinRE45, 0, 16);
        ImGui::MainSliderInt("Alternator SMG", &Features::Misc::SkinALTERNATOR, 0, 16);
        ImGui::MainSliderInt("R-99 SMG", &Features::Misc::SkinR99, 0, 16);
        ImGui::MainSliderInt("R-301 Carbine", &Features::Misc::SkinR301, 0, 18);
        ImGui::MainSliderInt("M600 Spitfire", &Features::Misc::SkinSPITFIRE, 0, 16);
        ImGui::MainSliderInt("G7 Scout", &Features::Misc::SkinG7, 0, 21);

        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Heavy");
        ImGui::MainSliderInt("VK-47 Flatline", &Features::Misc::SkinFLATLINE, 0, 20);
        ImGui::MainSliderInt("Hemlock Burst AR", &Features::Misc::SkinHEMLOCK, 0, 18);
        ImGui::MainSliderInt("Prowler Burst SMG", &Features::Misc::SkinPROWLER, 0, 11);
        ImGui::MainSliderInt("30-30 Repeater", &Features::Misc::SkinREPEATER, 0, 11);
        ImGui::MainSliderInt("Rampage LMG", &Features::Misc::SkinRAMPAGE, 0, 11);
        ImGui::MainSliderInt("C.A.R SMG", &Features::Misc::SkinCAR, 0, 11);

        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Energy");
        ImGui::MainSliderInt("Havoc Rifle", &Features::Misc::SkinHAVOC, 0, 14);
        ImGui::MainSliderInt("Devotion LMG", &Features::Misc::SkinDEVOTION, 0, 11);
        ImGui::MainSliderInt("L-Star EMG", &Features::Misc::SkinLSTAR, 0, 11);
        ImGui::MainSliderInt("Triple-Take", &Features::Misc::SkinTRIPLETAKE, 0, 11);
        ImGui::MainSliderInt("Volt", &Features::Misc::SkinVOLT, 0, 14);
        ImGui::MainSliderInt("Nemesis Burst AR", &Features::Misc::SkinNEMESIS, 0, 9);

        ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Shotguns");
        ImGui::MainSliderInt("Mozambique", &Features::Misc::SkinMOZAMBIQUE, 0, 11);
        ImGui::MainSliderInt("Peacekeeper", &Features::Misc::SkinPEACEKEEPER, 0, 16);
        ImGui::MainSliderInt("Mastiff", &Features::Misc::SkinMASTIFF, 0, 11);

        ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Snipers");
        ImGui::MainSliderInt("Longbow DMR", &Features::Misc::SkinLONGBOW, 0, 11);
        ImGui::MainSliderInt("Charge Rifle", &Features::Misc::SkinCHARGE_RIFLE, 0, 11);
        ImGui::MainSliderInt("Sentinel", &Features::Misc::SkinSENTINEL, 0, 10);

        ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Legendary");
        ImGui::MainSliderInt("Wingman", &Features::Misc::SkinWINGMAN, 0, 11);
        ImGui::MainSliderInt("EVA-8 Auto", &Features::Misc::SkinEVA8, 0, 11);
        ImGui::MainSliderInt("Bocek Compound Bow", &Features::Misc::SkinBOCEK, 0, 11);
        ImGui::MainSliderInt("Kraber .50-CAL Sniper", &Features::Misc::SkinKRABER, 0, 11);

        DoubleSpacing();
      }

      ImGui::EndChildFrame();
    }

    ImGui::NextColumn();

    ImGui::Text("Movement");
    ImGui::BeginChildFrame(3, ImVec2((WindowWidth - 225) / 2, (WindowHeight - 115) / 2 - 70), true); {
      ImGui::Spacing();

      ImGui::Checkbox("Super glide", &Features::Misc::SuperGlide);
      if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        ImGui::SetTooltip("Hold [ SPACE ] when climbing over an object to gain speed");
      //if (Features::Misc::SuperGlide) {
      //  const char *SuperGlideFPSIndex[] = { "75", "144", "240" };
      //  ImGui::ComboBox("Superglide framerate", &Features::Misc::SuperGlideFPS, SuperGlideFPSIndex, IM_ARRAYSIZE(SuperGlideFPSIndex));
      //}

      ImGui::Checkbox("Bunny hop", &Features::Misc::BHop);
      if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        ImGui::SetTooltip("Activates when holding a selected keybind and [ SPACE ]");
      if (Features::Misc::BHop) {
        int BhopBind = static_cast<int>(Features::Misc::BHopBind);
        ImGui::ComboBox("Bind##Bunny hop", &BhopBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
        Features::Misc::BHopBind = static_cast<InputKeyType>(BhopBind);
        ImGui::MainSliderInt("Delay", &Features::Misc::BHopDelay, 1, 200);
      }

      ImGui::EndChildFrame();
    }

    ImGui::Text("Camera");
    ImGui::BeginChildFrame(4, ImVec2((WindowWidth - 225) / 2, (WindowHeight - 115) / 2 - 90), true); {
      ImGui::Spacing();
      ImGui::Checkbox("Quick turn", &Features::Misc::QuickTurn);
      if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        ImGui::SetTooltip("Turn your camera quickly (no smoothing applied)");
      if (Features::Misc::QuickTurn) {
        int QuickTurnBind = static_cast<int>(Features::Misc::QuickTurnBind);
        ImGui::ComboBox("Bind##Quick turn", &QuickTurnBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
        Features::Misc::QuickTurnBind = static_cast<InputKeyType>(QuickTurnBind);
        ImGui::MainSliderInt("Angle", &Features::Misc::QuickTurnAngle, 1, 360);
      }

      ImGui::EndChildFrame();
    }

    ImGui::Text("Settings");
    ImGui::BeginChildFrame(5, ImVec2((WindowWidth - 225) / 2, 0), true); {
      ImGui::Spacing();

      ImGui::Checkbox("Enable overlay", &Features::Settings::OverlayEnabled);

      if (Features::Settings::OverlayEnabled) { ImGui::Checkbox("Enable ESP", &Features::Settings::ESPEnabled); }

      ImGui::Checkbox("FPS Cap", &Features::Settings::FPSCap);
      if (Features::Settings::FPSCap) { ImGui::MainSliderInt("Max FPS", &Features::Settings::CappedFPS, 30, 480); }

      ImGui::EndChildFrame();
    }

    ImGui::EndChild();
  }
};