// Externals
#pragma once
#include <string>
#include "../imgui/imgui.h"
#include "../imgui/imconfig.h"
#define IMGUI_DEFINE_MATH_OPERATORS

// Internals
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/Weapons.hpp"

struct AdvancedGUI {
  ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;
  ImGuiColorEditFlags ColorEditFlags = ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel;

  float WindowWidth = 1000.0f; // 1000 // 950 // 1000
  float WindowHeight = 495.0f; // 600 // 450 // 1000 (?)

  int ColumnOffsetTest = 250;

  // Padding between controls
  static void Space(const bool NoSeparator = false) {
    ImGui::Spacing();
    if (!NoSeparator) {
      ImGui::Spacing();
      ImGui::Separator();
    }
    ImGui::Spacing();
    ImGui::Spacing();
  }

  // Two Spacings In One! Who Would've Thought!
  static void DoubleSpacing() {
    ImGui::Spacing();
    ImGui::Spacing();
  }

  // Ok, Three Spacings In One Is Pushing It.
  static void TripleSpacing() {
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
  }

  // Help Marker
  static void DrawHelpMarker(const char *desc) {
    ImGui::SameLine(ImGui::GetWindowWidth() - 50);
    ImGui::TextDisabled("[?]");
    if (ImGui::IsItemHovered()) {
      ImGui::BeginTooltip();
      ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
      ImGui::TextUnformatted(desc);
      ImGui::PopTextWrapPos();
      ImGui::EndTooltip();
    }
  }

  // Help Marker
  static void Helper(const char *desc) {
    ImGui::SameLine(0.f, 5.f);
    ImGui::Text("(?)");
    if (ImGui::IsItemHovered()) {
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
      ImGui::BeginTooltip();
      ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
      ImGui::Text(desc);
      ImGui::PopTextWrapPos();
      ImGui::EndTooltip();
      ImGui::PopStyleVar();
    }
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

  // Render Tabs

  void AdvancedRCSTab(const int WeaponID) const { // this is absolutely horrible, but the advanced aimbot tab is worse
    if (!Features::RCS::RCSEnabled)
      ImGui::Text("RCS is disabled");

    if (Features::RCS::RCSEnabled && Features::RCS::AdvancedRCS) {
      const char *RCSModeIndex[] = { "Standalone", "Combined" };
      ImGui::ComboBox("Mode", &Features::RCS::RCSMode, RCSModeIndex, IM_ARRAYSIZE(RCSModeIndex));
      ImGui::Checkbox("Require ADS", &Features::RCS::OnADS);

      ImGui::Text("Current Held Weapon: ");
      if (Features::RCS::P2020 && WeaponID == WeaponIDs::P2020) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "P2020");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedP2020", &Features::RCS::P2020Pitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedP2020", &Features::RCS::P2020Yaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedP2020", &Features::RCS::P2020PitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedP2020", &Features::RCS::P2020YawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::RE45 && WeaponID == WeaponIDs::RE45) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "RE45");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedRE45", &Features::RCS::RE45Pitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedRE45", &Features::RCS::RE45Yaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedRE45", &Features::RCS::RE45PitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedRE45", &Features::RCS::RE45YawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Alternator && WeaponID == WeaponIDs::ALTERNATOR) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Alternator");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedAlternator", &Features::RCS::AlternatorPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedAlternator", &Features::RCS::AlternatorYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedAlternator", &Features::RCS::AlternatorPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedAlternator", &Features::RCS::AlternatorYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::R99 && WeaponID == WeaponIDs::R99) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "R99");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedR99", &Features::RCS::R99Pitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedR99", &Features::RCS::R99Yaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedR99", &Features::RCS::R99PitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedR99", &Features::RCS::R99YawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::R301 && WeaponID == WeaponIDs::R301) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "R301");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedR301", &Features::RCS::R301Pitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedR301", &Features::RCS::R301Yaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedR301", &Features::RCS::R301PitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedR301", &Features::RCS::R301YawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Spitfire && WeaponID == WeaponIDs::SPITFIRE) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Spitfire");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedSpitfire", &Features::RCS::SpitfirePitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedSpitfire", &Features::RCS::SpitfireYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedSpitfire", &Features::RCS::SpitfirePitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedSpitfire", &Features::RCS::SpitfireYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::G7 && WeaponID == WeaponIDs::G7) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "G7");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedG7", &Features::RCS::G7Pitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedG7", &Features::RCS::G7Yaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedG7", &Features::RCS::G7PitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedG7", &Features::RCS::G7YawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Flatline && WeaponID == WeaponIDs::FLATLINE) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Flatline");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedFlatline", &Features::RCS::FlatlinePitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedFlatline", &Features::RCS::FlatlineYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedFlatline", &Features::RCS::FlatlinePitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedFlatline", &Features::RCS::FlatlineYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Hemlock && WeaponID == WeaponIDs::HEMLOCK) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Hemlock");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedHemlock", &Features::RCS::HemlockPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedHemlock", &Features::RCS::HemlockYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedHemlock", &Features::RCS::HemlockPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedHemlock", &Features::RCS::HemlockYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Prowler && WeaponID == WeaponIDs::PROWLER) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Prowler");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedProwler", &Features::RCS::ProwlerPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedProwler", &Features::RCS::ProwlerYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedProwler", &Features::RCS::ProwlerPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedProwler", &Features::RCS::ProwlerYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Repeater && WeaponID == WeaponIDs::REPEATER) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Repeater");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedRepeater", &Features::RCS::RepeaterPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedRepeater", &Features::RCS::RepeaterYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedRepeater", &Features::RCS::RepeaterPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedRepeater", &Features::RCS::RepeaterYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Rampage && WeaponID == WeaponIDs::RAMPAGE) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Rampage");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedRampage", &Features::RCS::RampagePitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedRampage", &Features::RCS::RampageYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedRampage", &Features::RCS::RampagePitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedRampage", &Features::RCS::RampageYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::CARSMG && WeaponID == WeaponIDs::CAR) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "CARSMG");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedCARSMG", &Features::RCS::CARSMGPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedCARSMG", &Features::RCS::CARSMGYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedCARSMG", &Features::RCS::CARSMGPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedCARSMG", &Features::RCS::CARSMGYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Havoc && WeaponID == WeaponIDs::HAVOC) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Havoc");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedHavoc", &Features::RCS::HavocPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedHavoc", &Features::RCS::HavocYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedHavoc", &Features::RCS::HavocPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedHavoc", &Features::RCS::HavocYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Devotion && WeaponID == WeaponIDs::DEVOTION) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Devotion");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedDevotion", &Features::RCS::DevotionPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedDevotion", &Features::RCS::DevotionYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedDevotion", &Features::RCS::DevotionPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedDevotion", &Features::RCS::DevotionYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::LSTAR && WeaponID == WeaponIDs::LSTAR) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "LSTAR");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedLSTAR", &Features::RCS::LSTARPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedLSTAR", &Features::RCS::LSTARYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedLSTAR", &Features::RCS::LSTARPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedLSTAR", &Features::RCS::LSTARYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::TripleTake && WeaponID == WeaponIDs::TRIPLETAKE) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "TripleTake");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedTripleTake", &Features::RCS::TripleTakePitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedTripleTake", &Features::RCS::TripleTakeYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedTripleTake", &Features::RCS::TripleTakePitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedTripleTake", &Features::RCS::TripleTakeYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Volt && WeaponID == WeaponIDs::VOLT) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Volt");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedVolt", &Features::RCS::VoltPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedVolt", &Features::RCS::VoltYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedVolt", &Features::RCS::VoltPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedVolt", &Features::RCS::VoltYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Nemesis && WeaponID == WeaponIDs::NEMESIS) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Nemesis");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedNemesis", &Features::RCS::NemesisPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedNemesis", &Features::RCS::NemesisYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedNemesis", &Features::RCS::NemesisPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedNemesis", &Features::RCS::NemesisYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Mozambique && WeaponID == WeaponIDs::MOZAMBIQUE) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Mozambique");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedMozambique", &Features::RCS::MozambiquePitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedMozambique", &Features::RCS::MozambiqueYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedMozambique", &Features::RCS::MozambiquePitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedMozambique", &Features::RCS::MozambiqueYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Peacekeeper && WeaponID == WeaponIDs::PEACEKEEPER) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Peacekeeper");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedPeacekeeper", &Features::RCS::PeacekeeperPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedPeacekeeper", &Features::RCS::PeacekeeperYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedPeacekeeper", &Features::RCS::PeacekeeperPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedPeacekeeper", &Features::RCS::PeacekeeperYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Mastiff && WeaponID == WeaponIDs::MASTIFF) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.99, 0, 0, 1.00f), "Mastiff");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedMastiff", &Features::RCS::MastiffPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedMastiff", &Features::RCS::MastiffYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedMastiff", &Features::RCS::MastiffPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedMastiff", &Features::RCS::MastiffYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Longbow && WeaponID == WeaponIDs::LONGBOW) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Longbow");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedLongbow", &Features::RCS::LongbowPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedLongbow", &Features::RCS::LongbowYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedLongbow", &Features::RCS::LongbowPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedLongbow", &Features::RCS::LongbowYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::ChargeRifle && WeaponID == WeaponIDs::CHARGE_RIFLE) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "ChargeRifle");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedChargeRifle", &Features::RCS::ChargeRiflePitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedChargeRifle", &Features::RCS::ChargeRifleYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedChargeRifle", &Features::RCS::ChargeRiflePitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedChargeRifle", &Features::RCS::ChargeRifleYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Sentinel && WeaponID == WeaponIDs::SENTINEL) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Sentinel");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedSentinel", &Features::RCS::SentinelPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedSentinel", &Features::RCS::SentinelYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedSentinel", &Features::RCS::SentinelPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedSentinel", &Features::RCS::SentinelYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Wingman && WeaponID == WeaponIDs::WINGMAN) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Wingman");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedWingman", &Features::RCS::WingmanPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedWingman", &Features::RCS::WingmanYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedWingman", &Features::RCS::WingmanPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedWingman", &Features::RCS::WingmanYawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::EVA8 && WeaponID == WeaponIDs::EVA8) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "EVA8");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedEVA8", &Features::RCS::EVA8Pitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedEVA8", &Features::RCS::EVA8Yaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedEVA8", &Features::RCS::EVA8PitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedEVA8", &Features::RCS::EVA8YawReduction, 0, 100, "%.0f");
        }
      }

      if (Features::RCS::Kraber && WeaponID == WeaponIDs::KRABER) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Kraber");
        if (Features::RCS::RCSMode == 0) {
          ImGui::MainSliderFloat("Pitch##AdvancedKraber", &Features::RCS::KraberPitch, 1, 50, "%.1f");
          ImGui::MainSliderFloat("Yaw##AdvancedKraber", &Features::RCS::KraberYaw, 1, 50, "%.1f");
        }
        if (Features::RCS::RCSMode == 1) {
          ImGui::MainSliderFloat("Pitch Reduction %##AdvancedKraber", &Features::RCS::KraberPitchReduction, 0, 100, "%.0f");
          ImGui::MainSliderFloat("Yaw Reduction %##AdvancedKraber", &Features::RCS::KraberYawReduction, 0, 100, "%.0f");
        }
      } else {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.99, 0.99, 0.99, 1.00f), "Unknown");
      }
    }
  }

  void AdvancedTriggerbotTab(const int WeaponID) const {
    if (!Features::Triggerbot::Enabled) { ImGui::Text("Triggerbot Is Disabled!"); }

    if (Features::Triggerbot::Enabled) {
      ImGui::BeginChildFrame(1, ImVec2(WindowWidth - 220, 136), true); {
        ImGui::Spacing();
        ImGui::Text("Advanced Triggerbot");
        ImGui::Checkbox("Enabled", &Features::Triggerbot::AdvancedTriggerbot);
        if (Features::Triggerbot::AdvancedTriggerbot) {
          const char *BindMethodIndex[] = { "Memory", "Keybind" };
          ImGui::ComboBox("Bind Method", &Features::Triggerbot::BindMethod, BindMethodIndex, IM_ARRAYSIZE(BindMethodIndex));
          if (Features::Triggerbot::BindMethod == 0) {
            ImGui::Checkbox("On ADS Only?", &Features::Triggerbot::OnADS);
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
              ImGui::SetTooltip("Fire only when ADS");
            if (Features::Triggerbot::OnADS) {
              ImGui::SameLine();
              ImGui::Checkbox("Always On For Shotguns", &Features::Triggerbot::HipfireShotguns);
              if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                ImGui::SetTooltip("Overrides The Triggerbot Condition (OnADS?) For Shotguns Only.\nSimple Terms: Other Guns Require ADS, Shotguns Will Not.");
            }
          }

          if (Features::Triggerbot::BindMethod == 1) {
            int TriggerBind = static_cast<int>(Features::Triggerbot::TriggerBind);
            ImGui::ComboBox("Triggerbot Bind", &TriggerBind, InputKeyTypeNames, IM_ARRAYSIZE(InputKeyTypeNames));
            Features::Triggerbot::TriggerBind = static_cast<InputKeyType>(TriggerBind);
          }
        }
        ImGui::EndChildFrame();
      }

      if (Features::Triggerbot::AdvancedTriggerbot) {
        ImGui::BeginChildFrame(2, ImVec2({ WindowWidth - 220, 96 }), true); {
          ImGui::Spacing();
          ImGui::Text("Current Held Weapon: ");

          if (Features::Triggerbot::P2020 && WeaponID == WeaponIDs::P2020) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "P2020");
            ImGui::MainSliderFloat("Range##P2020Triggerbot", &Features::Triggerbot::P2020Range, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::RE45 && WeaponID == WeaponIDs::RE45) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "RE45");
            ImGui::MainSliderFloat("Range##RE45Triggerbot", &Features::Triggerbot::RE45Range, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Alternator && WeaponID == WeaponIDs::ALTERNATOR) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Alternator");
            ImGui::MainSliderFloat("Range##AlternatorTriggerbot", &Features::Triggerbot::AlternatorRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::R99 && WeaponID == WeaponIDs::R99) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "R99");
            ImGui::MainSliderFloat("Range##R99Triggerbot", &Features::Triggerbot::R99Range, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::R301 && WeaponID == WeaponIDs::R301) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "R301");
            ImGui::MainSliderFloat("Range##R301Triggerbot", &Features::Triggerbot::R301Range, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Spitfire && WeaponID == WeaponIDs::SPITFIRE) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "Spitfire");
            ImGui::MainSliderFloat("Range##SpitfireTriggerbot", &Features::Triggerbot::SpitfireRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::G7 && WeaponID == WeaponIDs::G7) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.990, 0.768, 0.039, 1.00f), "G7");
            ImGui::MainSliderFloat("Range##G7Triggerbot", &Features::Triggerbot::G7Range, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Flatline && WeaponID == WeaponIDs::FLATLINE) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Flatline");
            ImGui::MainSliderFloat("Range##FlatlineTriggerbot", &Features::Triggerbot::FlatlineRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Prowler && WeaponID == WeaponIDs::PROWLER) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Prowler");
            ImGui::MainSliderFloat("Range##ProwlerTriggerbot", &Features::Triggerbot::ProwlerRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Hemlock && WeaponID == WeaponIDs::HEMLOCK) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Hemlock");
            ImGui::MainSliderFloat("Range##HemlockTriggerbot", &Features::Triggerbot::HemlockRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Repeater && WeaponID == WeaponIDs::REPEATER) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Repeater");
            ImGui::MainSliderFloat("Range##RepeaterTriggerbot", &Features::Triggerbot::RepeaterRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Rampage && WeaponID == WeaponIDs::RAMPAGE) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "Rampage");
            ImGui::MainSliderFloat("Range##RampageTriggerbot", &Features::Triggerbot::RampageRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::CARSMG && WeaponID == WeaponIDs::CAR) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.990, 0.761, 1.00f), "CARSMG");
            ImGui::MainSliderFloat("Range##CARSMGTriggerbot", &Features::Triggerbot::CARSMGRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Havoc && WeaponID == WeaponIDs::HAVOC) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Havoc");
            ImGui::MainSliderFloat("Range##HavocTriggerbot", &Features::Triggerbot::HavocRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Devotion && WeaponID == WeaponIDs::DEVOTION) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Devotion");
            ImGui::MainSliderFloat("Range##DevotionTriggerbot", &Features::Triggerbot::DevotionRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::LSTAR && WeaponID == WeaponIDs::LSTAR) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "LSTAR");
            ImGui::MainSliderFloat("Range##LSTARTriggerbot", &Features::Triggerbot::LSTARRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::TripleTake && WeaponID == WeaponIDs::TRIPLETAKE) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "TripleTake");
            ImGui::MainSliderFloat("Range##TripleTakeTriggerbot", &Features::Triggerbot::TripleTakeRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Volt && WeaponID == WeaponIDs::VOLT) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Volt");
            ImGui::MainSliderFloat("Range##VoltTriggerbot", &Features::Triggerbot::VoltRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Nemesis && WeaponID == WeaponIDs::NEMESIS) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0, 0.99, 0, 1.00f), "Nemesis");
            ImGui::MainSliderFloat("Range##NemesisTriggerbot", &Features::Triggerbot::NemesisRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Mozambique && WeaponID == WeaponIDs::MOZAMBIQUE) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.00f, 0, 0, 1.00f), "Mozambique");
            ImGui::MainSliderFloat("Range##MozambiqueTriggerbot", &Features::Triggerbot::MozambiqueRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Peacekeeper && WeaponID == WeaponIDs::PEACEKEEPER) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.00f, 0, 0, 1.00f), "Peacekeeper");
            ImGui::MainSliderFloat("Range##PeacekeeperTriggerbot", &Features::Triggerbot::PeacekeeperRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Mastiff && WeaponID == WeaponIDs::MASTIFF) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.00f, 0, 0, 1.00f), "Mastiff");
            ImGui::MainSliderFloat("Range##MastiffTriggerbot", &Features::Triggerbot::MastiffRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Longbow && WeaponID == WeaponIDs::LONGBOW) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Longbow");
            ImGui::MainSliderFloat("Range##LongbowTriggerbot", &Features::Triggerbot::LongbowRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::ChargeRifle && WeaponID == WeaponIDs::CHARGE_RIFLE) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "ChargeRifle");
            ImGui::MainSliderFloat("Range##ChargeRifleTriggerbot", &Features::Triggerbot::ChargeRifleRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Sentinel && WeaponID == WeaponIDs::SENTINEL) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.00990, 0.337, 0.990, 1.00f), "Sentinel");
            ImGui::MainSliderFloat("Range##SentinelTriggerbot", &Features::Triggerbot::SentinelRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Wingman && WeaponID == WeaponIDs::WINGMAN) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Wingman");
            ImGui::MainSliderFloat("Range##WingmanTriggerbot", &Features::Triggerbot::WingmanRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::EVA8 && WeaponID == WeaponIDs::EVA8) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "EVA8");
            ImGui::MainSliderFloat("Range##EVA8Triggerbot", &Features::Triggerbot::EVA8Range, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Bocek && WeaponID == WeaponIDs::BOCEK) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Bocek");
            ImGui::MainSliderFloat("Range##BocekTriggerbot", &Features::Triggerbot::BocekRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Kraber && WeaponID == WeaponIDs::KRABER) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "Kraber");
            ImGui::MainSliderFloat("Range##KraberTriggerbot", &Features::Triggerbot::KraberRange, 0, 1000, "%.0f");
          }

          if (Features::Triggerbot::Knife && WeaponID == WeaponIDs::KNIFE) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.99, 0.530, 0.945, 1.00f), "ThrowingKnife");
            ImGui::MainSliderFloat("Range##ThrowingKnifeTriggerbot", &Features::Triggerbot::ThrowingKnifeRange, 0, 1000, "%.0f");
          } else {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.99, 0.99, 0.99, 1.00f), "Unknown (Check Your Selected Weapon!)");
          }

          ImGui::EndChildFrame();
        }
      }
    }
  }
};
