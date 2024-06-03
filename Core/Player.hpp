#pragma once
#include <string>
#include <Weapons.hpp>

#include "LocalPlayer.hpp"
#include "Offsets.hpp"
#include "../Math/Matrix.hpp"
#include "../Math/Vector2D.hpp"
#include "../Math/Vector3D.hpp"
#include "../Overlay/Overlay.hpp"
#include "../Utils/HitboxType.hpp"
#include "../Utils/Memory.hpp"

struct Player {
  LocalPlayer *Myself;

  int Index;
  long BasePointer{};

  std::string Name;
  int Team{};

  int GlowEnable{};
  int GlowThroughWall{};
  int HighlightID{};

  bool IsDead{};
  bool IsKnocked{};

  Vector2D ViewAngles;
  Vector3D LocalOrigin;
  Vector3D AbsoluteVelocity;

  int Health{};
  int MaxHealth{};
  int Shield{};
  int MaxShield{};

  int LastTimeAimedAt{};
  int LastTimeAimedAtPrevious{};
  bool IsAimedAt{};

  bool IsVisible{};

  bool IsLocal{};
  bool IsAlly{};
  bool IsHostile{};

  int WeaponIndex{};
  bool IsHoldingGrenade{};
  long WeaponEntity{};

  float DistanceToLocalPlayer{};
  float Distance2DToLocalPlayer{};

  float ViewYaw{};

  bool IsLockedOn = false;

  Player(const int PlayerIndex, LocalPlayer *Me) {
    this->Index = PlayerIndex;
    this->Myself = Me;
  }

  auto shortRead() -> void {
    BasePointer = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (Index + 1 << 5));
    if (BasePointer == 0)
      return;

    LocalOrigin = Memory::Read<Vector3D>(BasePointer + OFF_LOCAL_ORIGIN);
    AbsoluteVelocity = Memory::Read<Vector3D>(BasePointer + OFF_ABSVELOCITY);
    ViewAngles = Memory::Read<Vector2D>(BasePointer + OFF_VIEW_ANGLES);
    ViewYaw = Memory::Read<float>(BasePointer + OFF_YAW);
  }

  auto fullRead() -> void {
    BasePointer = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (Index + 1 << 5));
    if (BasePointer == 0)
      return;

    Name = Memory::ReadString(BasePointer + OFF_NAME);
    Team = Memory::Read<int>(BasePointer + OFF_TEAM_NUMBER);

    if (!IsPlayer() && !IsDummy()) {
      BasePointer = 0;
      return;
    }

    IsDead = !IsDummy() && Memory::Read<short>(BasePointer + OFF_LIFE_STATE) > 0;
    IsKnocked = !IsDummy() && Memory::Read<short>(BasePointer + OFF_BLEEDOUT_STATE) > 0;

    LocalOrigin = Memory::Read<Vector3D>(BasePointer + OFF_LOCAL_ORIGIN);
    AbsoluteVelocity = Memory::Read<Vector3D>(BasePointer + OFF_ABSVELOCITY);
    ViewAngles = Memory::Read<Vector2D>(BasePointer + OFF_VIEW_ANGLES);
    ViewYaw = Memory::Read<float>(BasePointer + OFF_YAW);

    GlowEnable = Memory::Read<int>(BasePointer + OFF_GLOW_ENABLE);
    GlowThroughWall = Memory::Read<int>(BasePointer + OFF_GLOW_THROUGH_WALL);
    HighlightID = Memory::Read<int>(BasePointer + OFF_GLOW_HIGHLIGHT_ID + 1);

    LastTimeAimedAt = Memory::Read<int>(BasePointer + OFF_LAST_AIMEDAT_TIME);
    IsAimedAt = LastTimeAimedAtPrevious < LastTimeAimedAt;
    LastTimeAimedAtPrevious = LastTimeAimedAt;

    const auto WorldTime = Memory::Read<float>(Myself->BasePointer + OFF_TIME_BASE);
    const auto Time1 = Memory::Read<float>(BasePointer + OFF_LAST_VISIBLE_TIME);
    IsVisible = (Time1 + 0.2) >= WorldTime || IsAimedAt;

    Health = Memory::Read<int>(BasePointer + OFF_HEALTH);
    MaxHealth = Memory::Read<int>(BasePointer + OFF_MAXHEALTH);
    Shield = Memory::Read<int>(BasePointer + OFF_SHIELD);
    MaxShield = Memory::Read<int>(BasePointer + OFF_MAXSHIELD);

    if (!IsDead && !IsKnocked && IsHostile) {
      const long WeaponHandleMasked = Memory::Read<long>(BasePointer + OFF_WEAPON_HANDLE) & 0xffff;
      WeaponEntity = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (WeaponHandleMasked << 5));
      IsHoldingGrenade = Memory::Read<int>(BasePointer + OFF_OFFHAND_WEAPON) == -251;
      WeaponIndex = Memory::Read<int>(WeaponEntity + OFF_WEAPON_INDEX);
    }

    if (Myself->IsValid()) {
      IsLocal = Myself->BasePointer == BasePointer;
      IsAlly = IsTeammate();
      IsHostile = !IsAlly;
      DistanceToLocalPlayer = Myself->LocalOrigin.Distance(LocalOrigin);
      Distance2DToLocalPlayer = Myself->LocalOrigin.To2D().Distance(LocalOrigin.To2D());
    }

    DistanceToLocalPlayer = Myself->LocalOrigin.Distance(LocalOrigin);
    Distance2DToLocalPlayer = Myself->LocalOrigin.To2D().Distance(LocalOrigin.To2D());
  }

  [[nodiscard]] auto GetPlayerName() const -> std::string {
    const auto NameIndex = Memory::Read<uintptr_t>(BasePointer + OFF_NAME_INDEX);
    const auto NameOffset = Memory::Read<uintptr_t>(OFF_REGION + OFF_NAME_LIST + ((NameIndex - 1) * 24));
    std::string PlayerName = Memory::ReadString(NameOffset, 64);
    return PlayerName;
  }

  [[nodiscard]] auto GetPlayerModelName() const -> std::string {
    const auto ModelOffset = Memory::Read<uintptr_t>(BasePointer + OFF_MODELNAME);
    const std::string ModelName = Memory::ReadString(ModelOffset, 1024);

    const std::unordered_map<std::string, std::string> ModelNameMap = {{"dummie", "Dummy"}, {"ash", "Ash"}, {"alter", "Alter"}, {"ballistic", "Ballistic"}, {"bangalore", "Bangalore"}, {"bloodhound", "Bloodhound"}, {"catalyst", "Catalyst"}, {"caustic", "Caustic"}, {"conduit", "Conduit"}, {"crypto", "Crypto"}, {"fuse", "Fuse"}, {"gibraltar", "Gibraltar"}, {"horizon", "Horizon"}, {"nova", "Nova"}, {"holo", "Holo"}, {"mirage", "Mirage"}, {"lifeline", "Lifeline"}, {"loba", "Loba"}, {"madmaggie", "Mad Maggie"}, {"newcastle", "Newcastle"}, {"octane", "Octane"}, {"pathfinder", "Pathfinder"}, {"rampart", "Rampart"}, {"revenant", "Revenant"}, {"seer", "Seer"}, {"stim", "Stim"}, {"valkyrie", "Valkyrie"}, {"vantage", "Vantage"}, {"wattson", "Wattson"}, {"wraith", "Wraith"},};

    std::string ReplacedName = ModelName;
    for (const auto &[fst, snd]: ModelNameMap) {
      if (ModelName.find(fst) != std::string::npos) {
        ReplacedName = snd;
        break;
      }
    }

    return ReplacedName;
  }

  [[nodiscard]] auto GetWeaponHeldName() const -> std::string {
    if (IsHoldingGrenade)
        return "Throwable";

    static std::unordered_map<int, std::string> WeaponMap = { {WeaponIDs::P2020, "P2020"}, {WeaponIDs::RE45, "RE-45"}, {WeaponIDs::ALTERNATOR, "Alternator"}, {WeaponIDs::R301, "R-301"}, {WeaponIDs::R99, "R-99"}, {WeaponIDs::SPITFIRE, "Spitfire"}, {WeaponIDs::G7, "G7 Scout"}, {WeaponIDs::FLATLINE, "Flatline"}, {WeaponIDs::PROWLER, "Prowler"}, {WeaponIDs::HEMLOCK, "Hemlock"}, {WeaponIDs::REPEATER, "30-30 Repeater"}, {WeaponIDs::RAMPAGE, "Rampage"}, {WeaponIDs::CAR, "CAR-SMG"}, {WeaponIDs::HAVOC, "Havoc"}, {WeaponIDs::DEVOTION, "Devotion"}, {WeaponIDs::LSTAR, "L-STAR"}, {WeaponIDs::TRIPLETAKE, "Triple Take"}, {WeaponIDs::VOLT, "Volt"}, {WeaponIDs::NEMESIS, "Nemesis"}, {WeaponIDs::MOZAMBIQUE, "Mozambique"}, {WeaponIDs::PEACEKEEPER, "Peacekeeper"}, {WeaponIDs::MASTIFF, "Mastiff"}, {WeaponIDs::SENTINEL, "Sentinel"}, {WeaponIDs::CHARGE_RIFLE, "Charge Rifle"}, {WeaponIDs::LONGBOW, "Longbow"}, {WeaponIDs::WINGMAN, "Wingman"}, {WeaponIDs::EVA8, "EVA-8 Auto"}, {WeaponIDs::BOCEK, "Bocek"}, {WeaponIDs::KRABER, "Kraber"}, {WeaponIDs::KNIFE, "Throwing Knife"}, {WeaponIDs::HANDS, "Melee"}, };

    if (const auto it = WeaponMap.find(WeaponIndex); it != WeaponMap.end())
      return it->second;

    return "Hands";
  }

  [[nodiscard]] auto GetWeaponHeldColor() const -> ImColor {
    ImColor LightCol, HeavyCol, EnergyCol, ShotgunCol, SniperCol, LegendaryCol, MeleeCol;
    if (IsHoldingGrenade) {
      if (IsHostile)
        return {Features::Colors::Enemy::ThrowableWeaponColor[0], Features::Colors::Enemy::ThrowableWeaponColor[1], Features::Colors::Enemy::ThrowableWeaponColor[2], Features::Colors::Enemy::ThrowableWeaponColor[3]};
      return {Features::Colors::Teammate::ThrowableWeaponColor[0], Features::Colors::Teammate::ThrowableWeaponColor[1], Features::Colors::Teammate::ThrowableWeaponColor[2], Features::Colors::Teammate::ThrowableWeaponColor[3]};
    }

    if (IsHostile) {
      LightCol = ImColor(Features::Colors::Enemy::LightWeaponColor[0], Features::Colors::Enemy::LightWeaponColor[1], Features::Colors::Enemy::LightWeaponColor[2], Features::Colors::Enemy::LightWeaponColor[3]);
      HeavyCol = ImColor(Features::Colors::Enemy::HeavyWeaponColor[0], Features::Colors::Enemy::HeavyWeaponColor[1], Features::Colors::Enemy::HeavyWeaponColor[2], Features::Colors::Enemy::HeavyWeaponColor[3]);
      EnergyCol = ImColor(Features::Colors::Enemy::EnergyWeaponColor[0], Features::Colors::Enemy::EnergyWeaponColor[1], Features::Colors::Enemy::EnergyWeaponColor[2], Features::Colors::Enemy::EnergyWeaponColor[3]);
      ShotgunCol = ImColor(Features::Colors::Enemy::ShotgunWeaponColor[0], Features::Colors::Enemy::ShotgunWeaponColor[1], Features::Colors::Enemy::ShotgunWeaponColor[2], Features::Colors::Enemy::ShotgunWeaponColor[3]);
      SniperCol = ImColor(Features::Colors::Enemy::SniperWeaponColor[0], Features::Colors::Enemy::SniperWeaponColor[1], Features::Colors::Enemy::SniperWeaponColor[2], Features::Colors::Enemy::SniperWeaponColor[3]);
      LegendaryCol = ImColor(Features::Colors::Enemy::LegendaryWeaponColor[0], Features::Colors::Enemy::LegendaryWeaponColor[1], Features::Colors::Enemy::LegendaryWeaponColor[2], Features::Colors::Enemy::LegendaryWeaponColor[3]);
      MeleeCol = ImColor(Features::Colors::Enemy::MeleeWeaponColor[0], Features::Colors::Enemy::MeleeWeaponColor[1], Features::Colors::Enemy::MeleeWeaponColor[2], Features::Colors::Enemy::MeleeWeaponColor[3]);
    } else {
      LightCol = ImColor(Features::Colors::Teammate::LightWeaponColor[0], Features::Colors::Teammate::LightWeaponColor[1], Features::Colors::Teammate::LightWeaponColor[2], Features::Colors::Teammate::LightWeaponColor[3]);
      HeavyCol = ImColor(Features::Colors::Teammate::HeavyWeaponColor[0], Features::Colors::Teammate::HeavyWeaponColor[1], Features::Colors::Teammate::HeavyWeaponColor[2], Features::Colors::Teammate::HeavyWeaponColor[3]);
      EnergyCol = ImColor(Features::Colors::Teammate::EnergyWeaponColor[0], Features::Colors::Teammate::EnergyWeaponColor[1], Features::Colors::Teammate::EnergyWeaponColor[2], Features::Colors::Teammate::EnergyWeaponColor[3]);
      ShotgunCol = ImColor(Features::Colors::Teammate::ShotgunWeaponColor[0], Features::Colors::Teammate::ShotgunWeaponColor[1], Features::Colors::Teammate::ShotgunWeaponColor[2], Features::Colors::Teammate::ShotgunWeaponColor[3]);
      SniperCol = ImColor(Features::Colors::Teammate::SniperWeaponColor[0], Features::Colors::Teammate::SniperWeaponColor[1], Features::Colors::Teammate::SniperWeaponColor[2], Features::Colors::Teammate::SniperWeaponColor[3]);
      LegendaryCol = ImColor(Features::Colors::Teammate::LegendaryWeaponColor[0], Features::Colors::Teammate::LegendaryWeaponColor[1], Features::Colors::Teammate::LegendaryWeaponColor[2], Features::Colors::Teammate::LegendaryWeaponColor[3]);
      MeleeCol = ImColor(Features::Colors::Teammate::MeleeWeaponColor[0], Features::Colors::Teammate::MeleeWeaponColor[1], Features::Colors::Teammate::MeleeWeaponColor[2], Features::Colors::Teammate::MeleeWeaponColor[3]);
    }

    static std::unordered_map<int, ImColor> WeaponMap = { {WeaponIDs::P2020, LightCol}, {WeaponIDs::RE45, LightCol}, {WeaponIDs::ALTERNATOR, LightCol}, {WeaponIDs::R301, LightCol}, {WeaponIDs::R99, LightCol}, {WeaponIDs::SPITFIRE, LightCol}, {WeaponIDs::G7, LightCol}, {WeaponIDs::FLATLINE, HeavyCol}, {WeaponIDs::PROWLER, HeavyCol}, {WeaponIDs::HEMLOCK, HeavyCol}, {WeaponIDs::REPEATER, HeavyCol}, {WeaponIDs::RAMPAGE, HeavyCol}, {WeaponIDs::CAR, HeavyCol}, {WeaponIDs::HAVOC, EnergyCol}, {WeaponIDs::DEVOTION, EnergyCol}, {WeaponIDs::LSTAR, EnergyCol}, {WeaponIDs::TRIPLETAKE, EnergyCol}, {WeaponIDs::VOLT, EnergyCol}, {WeaponIDs::NEMESIS, EnergyCol}, {WeaponIDs::MOZAMBIQUE, ShotgunCol}, {WeaponIDs::PEACEKEEPER, ShotgunCol}, {WeaponIDs::MASTIFF, ShotgunCol}, {WeaponIDs::SENTINEL, SniperCol}, {WeaponIDs::CHARGE_RIFLE, SniperCol}, {WeaponIDs::LONGBOW, SniperCol}, {WeaponIDs::WINGMAN, LegendaryCol}, {WeaponIDs::EVA8, LegendaryCol}, {WeaponIDs::BOCEK, LegendaryCol}, {WeaponIDs::KRABER, LegendaryCol}, {WeaponIDs::KNIFE, LegendaryCol}, {WeaponIDs::HANDS, MeleeCol}, };

    if (const auto it = WeaponMap.find(WeaponIndex); it != WeaponMap.end())
      return it->second;

    return {255, 255, 255};
  }

  [[nodiscard]] auto GetViewYaw() const -> float {
    if (!IsDummy() || IsPlayer()) {
      return Memory::Read<float>(BasePointer + OFF_YAW);
    }
    return 0.0f;
  }

  [[nodiscard]] auto IsValid() const -> bool {
    return BasePointer != 0 && Health > 0 && (IsPlayer() || IsDummy());
  }

  [[nodiscard]] auto IsCombatReady() const -> bool {
    return IsValid() && (!IsDead && !IsKnocked || IsDummy());
  }

  [[nodiscard]] auto IsPlayer() const -> bool {
    return Name == "player";
  }

  [[nodiscard]] auto IsDummy() const -> bool {
    return Team == 97;
  }

  [[nodiscard]] auto IsTeammate() const -> bool {
    return LvMap::m_mixtape && Myself->Squad == -1 ? (Team & 1) == (Myself->Team & 1) : Team == Myself->Team;
  }

  [[nodiscard]] auto IsSpectating() const -> bool {
    if (!IsDead)
      return false;

    const auto SpecIndex = Memory::Read<int>(Memory::Read<uint64_t>(OFF_REGION + OFF_OBSERVER_LIST) + Memory::Read<int>(BasePointer + 0x38) * 8 + 0x964);
    return Memory::Read<uint64_t>(OFF_REGION + OFF_ENTITY_LIST + ((SpecIndex & 0xFFFF) << 5)) == Myself->BasePointer;
  }

  // Bones //
  [[nodiscard]] auto GetBoneFromHitbox(HitboxType HitBox) const -> int {
    const long ModelPointer = Memory::Read<long>(BasePointer + OFF_STUDIOHDR);
    if (!Memory::IsValidPointer(ModelPointer))
      return -1;

    const long StudioHDR = Memory::Read<long>(ModelPointer + 0x8);
    if (!Memory::IsValidPointer(StudioHDR + 0x34))
      return -1;

    const auto HitboxCache = Memory::Read<uint16_t>(StudioHDR + 0x34);
    const auto HitboxArray = StudioHDR + (static_cast<uint16_t>(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));
    if (!Memory::IsValidPointer(HitboxArray + 0x4))
      return -1;

    const auto IndexCache = Memory::Read<uint16_t>(HitboxArray + 0x4);
    const auto HitboxIndex = (static_cast<uint16_t>(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));
    const auto BonePointer = HitboxIndex + HitboxArray + (static_cast<int>(HitBox) * 0x20);
    if (!Memory::IsValidPointer(BonePointer))
      return -1;

    return Memory::Read<uint16_t>(BonePointer);
  }

  [[nodiscard]] auto GetBonePosition(const HitboxType HitBox) const -> Vector3D {
    const auto Offset = Vector3D(0.0f, 0.0f, 0.0f);

    const int Bone = GetBoneFromHitbox(HitBox);
    if (Bone < 0 || Bone > 255)
      return LocalOrigin.Add(Offset);

    const long BonePtr = Memory::Read<long>(BasePointer + OFF_BONES) + Bone * sizeof(Matrix3x4);
    if (!Memory::IsValidPointer(BonePtr))
      return LocalOrigin.Add(Offset);

    const auto BoneMatrix = Memory::Read<Matrix3x4>(BonePtr);
    Vector3D BonePosition = BoneMatrix.GetPosition();

    if (!BonePosition.IsValid())
      return LocalOrigin.Add(Vector3D(0, 0, 0));

    BonePosition += LocalOrigin;
    return BonePosition;
  }
};
