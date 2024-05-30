#pragma once
#include <vector>
#include <set>
#include "../Core/Player.hpp"
#include "../Core/LocalPlayer.hpp"
#include "../Utils/XDisplay.hpp"
#include "../Utils/Conversion.hpp"
#include "../Utils/Config.hpp"
#include "../Utils/Features.hpp"
#include "../Utils/Weapons.hpp"
#include "../Core/Level.hpp"

struct Triggerbot {
  std::chrono::milliseconds ScopeTime;
  std::set<int> WeaponList = {};
  int Range;
  int RangeHipfire;

  XDisplay *X11Display;
  LocalPlayer *Myself;
  std::vector<Player *> *Players;
  Level *Map;

  Triggerbot(XDisplay *X11Display, Level *Map, LocalPlayer *Myself, std::vector<Player *> *GamePlayers) {
    this->X11Display = X11Display;
    this->Map = Map;
    this->Myself = Myself;
    this->Players = GamePlayers;
  }

  static bool Save() {
    try {
      Config::Triggerbot::Enabled = Features::Triggerbot::Enabled;
      Config::Triggerbot::BindMethod = Features::Triggerbot::BindMethod;
      Config::Triggerbot::TriggerBind = static_cast<int>(Features::Triggerbot::TriggerBind);
      Config::Triggerbot::OnADS = Features::Triggerbot::OnADS;
      Config::Triggerbot::HipfireShotguns = Features::Triggerbot::HipfireShotguns;
      Config::Triggerbot::Range = Features::Triggerbot::Range;
      Config::Triggerbot::RangeHipfire = Features::Triggerbot::RangeHipfire;
      //Weapon Toggles
      //Light
      Config::Triggerbot::P2020 = Features::Triggerbot::P2020;
      Config::Triggerbot::RE45 = Features::Triggerbot::RE45;
      Config::Triggerbot::Alternator = Features::Triggerbot::Alternator;
      Config::Triggerbot::R99 = Features::Triggerbot::R99;
      Config::Triggerbot::R301 = Features::Triggerbot::R301;
      Config::Triggerbot::Spitfire = Features::Triggerbot::Spitfire;
      Config::Triggerbot::G7 = Features::Triggerbot::G7;
      //Heavy
      Config::Triggerbot::Flatline = Features::Triggerbot::Flatline;
      Config::Triggerbot::Hemlock = Features::Triggerbot::Hemlock;
      Config::Triggerbot::Repeater = Features::Triggerbot::Repeater;
      Config::Triggerbot::Rampage = Features::Triggerbot::Rampage;
      Config::Triggerbot::CARSMG = Features::Triggerbot::CARSMG;
      //Energy
      Config::Triggerbot::Havoc = Features::Triggerbot::Havoc;
      Config::Triggerbot::Devotion = Features::Triggerbot::Devotion;
      Config::Triggerbot::LSTAR = Features::Triggerbot::LSTAR;
      Config::Triggerbot::TripleTake = Features::Triggerbot::TripleTake;
      Config::Triggerbot::Volt = Features::Triggerbot::Volt;
      Config::Triggerbot::Nemesis = Features::Triggerbot::Nemesis;
      //Shotgun
      Config::Triggerbot::Mozambique = Features::Triggerbot::Mozambique;
      Config::Triggerbot::EVA8 = Features::Triggerbot::EVA8;
      Config::Triggerbot::Peacekeeper = Features::Triggerbot::Peacekeeper;
      Config::Triggerbot::Mastiff = Features::Triggerbot::Mastiff;
      //Snipers
      Config::Triggerbot::Longbow = Features::Triggerbot::Longbow;
      Config::Triggerbot::ChargeRifle = Features::Triggerbot::ChargeRifle;
      Config::Triggerbot::Sentinel = Features::Triggerbot::Sentinel;
      //Legendary
      Config::Triggerbot::Wingman = Features::Triggerbot::Wingman;
      Config::Triggerbot::Prowler = Features::Triggerbot::Prowler;
      Config::Triggerbot::Bocek = Features::Triggerbot::Bocek;
      Config::Triggerbot::Kraber = Features::Triggerbot::Kraber;
      Config::Triggerbot::Knife = Features::Triggerbot::Knife;
      //Advanced
      Config::Triggerbot::AdvancedTriggerbot = Features::Triggerbot::AdvancedTriggerbot;
      Config::Triggerbot::P2020Range = Features::Triggerbot::P2020Range;
      Config::Triggerbot::RE45Range = Features::Triggerbot::RE45Range;
      Config::Triggerbot::AlternatorRange = Features::Triggerbot::AlternatorRange;
      Config::Triggerbot::R99Range = Features::Triggerbot::R99Range;
      Config::Triggerbot::R301Range = Features::Triggerbot::R301Range;
      Config::Triggerbot::SpitfireRange = Features::Triggerbot::SpitfireRange;
      Config::Triggerbot::G7Range = Features::Triggerbot::G7Range;
      Config::Triggerbot::FlatlineRange = Features::Triggerbot::FlatlineRange;
      Config::Triggerbot::HemlockRange = Features::Triggerbot::HemlockRange;
      Config::Triggerbot::ProwlerRange = Features::Triggerbot::ProwlerRange;
      Config::Triggerbot::RepeaterRange = Features::Triggerbot::RepeaterRange;
      Config::Triggerbot::RampageRange = Features::Triggerbot::RampageRange;
      Config::Triggerbot::CARSMGRange = Features::Triggerbot::CARSMGRange;
      Config::Triggerbot::HavocRange = Features::Triggerbot::HavocRange;
      Config::Triggerbot::DevotionRange = Features::Triggerbot::DevotionRange;
      Config::Triggerbot::LSTARRange = Features::Triggerbot::LSTARRange;
      Config::Triggerbot::TripleTakeRange = Features::Triggerbot::TripleTakeRange;
      Config::Triggerbot::VoltRange = Features::Triggerbot::VoltRange;
      Config::Triggerbot::NemesisRange = Features::Triggerbot::NemesisRange;
      Config::Triggerbot::LongbowRange = Features::Triggerbot::LongbowRange;
      Config::Triggerbot::ChargeRifleRange = Features::Triggerbot::ChargeRifleRange;
      Config::Triggerbot::SentinelRange = Features::Triggerbot::SentinelRange;
      Config::Triggerbot::MozambiqueRange = Features::Triggerbot::MozambiqueRange;
      Config::Triggerbot::PeacekeeperRange = Features::Triggerbot::PeacekeeperRange;
      Config::Triggerbot::MastiffRange = Features::Triggerbot::MastiffRange;
      Config::Triggerbot::LongbowRange = Features::Triggerbot::LongbowRange;
      Config::Triggerbot::ChargeRifleRange = Features::Triggerbot::ChargeRifleRange;
      Config::Triggerbot::SentinelRange = Features::Triggerbot::SentinelRange;
      Config::Triggerbot::WingmanRange = Features::Triggerbot::WingmanRange;
      Config::Triggerbot::EVA8Range = Features::Triggerbot::EVA8Range;
      Config::Triggerbot::KraberRange = Features::Triggerbot::KraberRange;
      Config::Triggerbot::BocekRange = Features::Triggerbot::BocekRange;
      Config::Triggerbot::ThrowingKnifeRange = Features::Triggerbot::ThrowingKnifeRange;

      return true;
    } catch (...) { return false; }
  }

  void UpdateWeaponList() {
    WeaponList.clear();

    // Define a lambda function to reduce repetition
    auto insertIfEnabled = [&](const bool feature, const int weaponID) {
      if (feature)
        WeaponList.insert(weaponID);
    };

    // Light weapons
    insertIfEnabled(Features::Triggerbot::P2020, WeaponIDs::P2020);
    insertIfEnabled(Features::Triggerbot::RE45, WeaponIDs::RE45);
    insertIfEnabled(Features::Triggerbot::Alternator, WeaponIDs::ALTERNATOR);
    insertIfEnabled(Features::Triggerbot::R99, WeaponIDs::R99);
    insertIfEnabled(Features::Triggerbot::R301, WeaponIDs::R301);
    insertIfEnabled(Features::Triggerbot::Spitfire, WeaponIDs::SPITFIRE);
    insertIfEnabled(Features::Triggerbot::G7, WeaponIDs::G7);

    // Heavy weapons
    insertIfEnabled(Features::Triggerbot::Flatline, WeaponIDs::FLATLINE);
    insertIfEnabled(Features::Triggerbot::Hemlock, WeaponIDs::HEMLOCK);
    insertIfEnabled(Features::Triggerbot::Repeater, WeaponIDs::REPEATER);
    insertIfEnabled(Features::Triggerbot::Rampage, WeaponIDs::RAMPAGE);
    insertIfEnabled(Features::Triggerbot::CARSMG, WeaponIDs::CAR);

    // Energy weapons
    insertIfEnabled(Features::Triggerbot::Havoc, WeaponIDs::HAVOC);
    insertIfEnabled(Features::Triggerbot::Devotion, WeaponIDs::DEVOTION);
    insertIfEnabled(Features::Triggerbot::LSTAR, WeaponIDs::LSTAR);
    insertIfEnabled(Features::Triggerbot::TripleTake, WeaponIDs::TRIPLETAKE);
    insertIfEnabled(Features::Triggerbot::Volt, WeaponIDs::VOLT);
    insertIfEnabled(Features::Triggerbot::Nemesis, WeaponIDs::NEMESIS);

    // Shotgun weapons
    insertIfEnabled(Features::Triggerbot::Mozambique, WeaponIDs::MOZAMBIQUE);
    insertIfEnabled(Features::Triggerbot::EVA8, WeaponIDs::EVA8);
    insertIfEnabled(Features::Triggerbot::Peacekeeper, WeaponIDs::PEACEKEEPER);
    insertIfEnabled(Features::Triggerbot::Mastiff, WeaponIDs::MASTIFF);

    // Sniper weapons
    insertIfEnabled(Features::Triggerbot::Longbow, WeaponIDs::LONGBOW);
    insertIfEnabled(Features::Triggerbot::ChargeRifle, WeaponIDs::CHARGE_RIFLE);
    insertIfEnabled(Features::Triggerbot::Sentinel, WeaponIDs::SENTINEL);

    // Legendary weapons
    insertIfEnabled(Features::Triggerbot::Wingman, WeaponIDs::WINGMAN);
    insertIfEnabled(Features::Triggerbot::Prowler, WeaponIDs::PROWLER);
    insertIfEnabled(Features::Triggerbot::Bocek, WeaponIDs::BOCEK);
    insertIfEnabled(Features::Triggerbot::Kraber, WeaponIDs::KRABER);
    insertIfEnabled(Features::Triggerbot::Knife, WeaponIDs::KNIFE);
  }

  void trigger(const int TargetRange) const {
    for (const auto player : *Players) {
      if (!player->IsCombatReady())
        continue;
      if (!player->IsHostile)
        continue;
      if (!player->IsAimedAt)
        continue;
      if (player->DistanceToLocalPlayer < Conversion::ToGameUnits(TargetRange)) {
        X11Display->MouseClickLeft();
        break;
      }
    }
  }

  void Update() {
    if (!Map->IsPlayable) // do we even need this? don't we check in updatecore already
      return;
    if (Features::Home::IsMenuOpened)
      return;
    if (!Features::Triggerbot::Enabled)
      return;

    UpdateTriggerbotSettings(); // Updates Triggerbot Settings - For Advanced And Non-Advanced Triggerbot

    if (!WeaponList.contains(Myself->WeaponIndex))
      return;
    if (!Myself->IsCombatReady())
      return;

    // super ghetto hotfix for now cuz it annoyed me mid game
    const std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    if (Features::Triggerbot::BindMethod == 0) { // Memory
      if (Features::Triggerbot::OnADS && !Features::Triggerbot::HipfireShotguns) { // ADS *FORCED*
        if (!Myself->IsZooming) {
          ScopeTime = now;
          return;
        }

        if (now >= ScopeTime + std::chrono::milliseconds(200))
          trigger(Range);
      } else if (Features::Triggerbot::OnADS && Features::Triggerbot::HipfireShotguns) { // ADS except shotguns
        if (Myself->IsZooming && now >= ScopeTime + std::chrono::milliseconds(200)) {
          trigger(Range);
        } else {
          if (Myself->WeaponIndex == WeaponIDs::MOZAMBIQUE or Myself->WeaponIndex == WeaponIDs::EVA8 or Myself->WeaponIndex == WeaponIDs::PEACEKEEPER or Myself->WeaponIndex == WeaponIDs::MASTIFF) { // Shotgun IDs
            trigger(RangeHipfire);
          }
          if (!Myself->IsZooming)
            ScopeTime = now;
        }
      } else { // No ADS forced
        trigger(Myself->IsZooming ? Range : RangeHipfire);
      }
    } else if (Features::Triggerbot::BindMethod == 1) { // Keybind
      if (!InputManager::isKeyDownOrPress(Features::Triggerbot::TriggerBind))
        return;
      trigger(Range);
    }
  }

  void UpdateTriggerbotSettings() {
    if (!Features::Triggerbot::AdvancedTriggerbot) {
      Range = Features::Triggerbot::Range;
      RangeHipfire = Features::Triggerbot::RangeHipfire;
    }

    if (Features::Triggerbot::AdvancedTriggerbot) {
      if (Features::Triggerbot::P2020 && Myself->WeaponIndex == WeaponIDs::P2020) { Range = Features::Triggerbot::P2020Range; }

      if (Features::Triggerbot::RE45 && Myself->WeaponIndex == WeaponIDs::RE45) { Range = Features::Triggerbot::RE45Range; }

      if (Features::Triggerbot::Alternator && Myself->WeaponIndex == WeaponIDs::ALTERNATOR) { Range = Features::Triggerbot::AlternatorRange; }

      if (Features::Triggerbot::R99 && Myself->WeaponIndex == WeaponIDs::R99) { Range = Features::Triggerbot::R99Range; }

      if (Features::Triggerbot::R301 && Myself->WeaponIndex == WeaponIDs::R301) { Range = Features::Triggerbot::R301Range; }

      if (Features::Triggerbot::Spitfire && Myself->WeaponIndex == WeaponIDs::SPITFIRE) { Range = Features::Triggerbot::SpitfireRange; }

      if (Features::Triggerbot::G7 && Myself->WeaponIndex == WeaponIDs::G7) { Range = Features::Triggerbot::G7Range; }

      if (Features::Triggerbot::Flatline && Myself->WeaponIndex == WeaponIDs::FLATLINE) { Range = Features::Triggerbot::FlatlineRange; }

      if (Features::Triggerbot::Prowler && Myself->WeaponIndex == WeaponIDs::PROWLER) { Range = Features::Triggerbot::ProwlerRange; }

      if (Features::Triggerbot::Hemlock && Myself->WeaponIndex == WeaponIDs::HEMLOCK) { Range = Features::Triggerbot::HemlockRange; }

      if (Features::Triggerbot::Repeater && Myself->WeaponIndex == WeaponIDs::REPEATER) { Range = Features::Triggerbot::RepeaterRange; }

      if (Features::Triggerbot::Rampage && Myself->WeaponIndex == WeaponIDs::RAMPAGE) { Range = Features::Triggerbot::RampageRange; }

      if (Features::Triggerbot::CARSMG && Myself->WeaponIndex == WeaponIDs::CAR) { Range = Features::Triggerbot::CARSMGRange; }

      if (Features::Triggerbot::Havoc && Myself->WeaponIndex == WeaponIDs::HAVOC) { Range = Features::Triggerbot::HavocRange; }

      if (Features::Triggerbot::Devotion && Myself->WeaponIndex == WeaponIDs::DEVOTION) { Range = Features::Triggerbot::DevotionRange; }

      if (Features::Triggerbot::LSTAR && Myself->WeaponIndex == WeaponIDs::LSTAR) { Range = Features::Triggerbot::LSTARRange; }

      if (Features::Triggerbot::TripleTake && Myself->WeaponIndex == WeaponIDs::TRIPLETAKE) { Range = Features::Triggerbot::TripleTakeRange; }

      if (Features::Triggerbot::Volt && Myself->WeaponIndex == WeaponIDs::VOLT) { Range = Features::Triggerbot::VoltRange; }

      if (Features::Triggerbot::Nemesis && Myself->WeaponIndex == WeaponIDs::NEMESIS) { Range = Features::Triggerbot::NemesisRange; }

      if (Features::Triggerbot::Mozambique && Myself->WeaponIndex == WeaponIDs::MOZAMBIQUE) { Range = Features::Triggerbot::MozambiqueRange; }

      if (Features::Triggerbot::Peacekeeper && Myself->WeaponIndex == WeaponIDs::PEACEKEEPER) { Range = Features::Triggerbot::PeacekeeperRange; }

      if (Features::Triggerbot::Mastiff && Myself->WeaponIndex == WeaponIDs::MASTIFF) { Range = Features::Triggerbot::MastiffRange; }

      if (Features::Triggerbot::Longbow && Myself->WeaponIndex == WeaponIDs::LONGBOW) { Range = Features::Triggerbot::LongbowRange; }

      if (Features::Triggerbot::ChargeRifle && Myself->WeaponIndex == WeaponIDs::CHARGE_RIFLE) { Range = Features::Triggerbot::ChargeRifleRange; }

      if (Features::Triggerbot::Sentinel && Myself->WeaponIndex == WeaponIDs::SENTINEL) { Range = Features::Triggerbot::SentinelRange; }

      if (Features::Triggerbot::Wingman && Myself->WeaponIndex == WeaponIDs::WINGMAN) { Range = Features::Triggerbot::WingmanRange; }

      if (Features::Triggerbot::EVA8 && Myself->WeaponIndex == WeaponIDs::EVA8) { Range = Features::Triggerbot::EVA8Range; }

      if (Features::Triggerbot::Bocek && Myself->WeaponIndex == WeaponIDs::BOCEK) { Range = Features::Triggerbot::BocekRange; }

      if (Features::Triggerbot::Kraber && Myself->WeaponIndex == WeaponIDs::KRABER) { Range = Features::Triggerbot::KraberRange; }

      if (Features::Triggerbot::Knife && Myself->WeaponIndex == WeaponIDs::KNIFE) { Range = Features::Triggerbot::ThrowingKnifeRange; }
    }
  }
};
