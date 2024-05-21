#pragma once
#include <string>
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

  void Read() {
    BasePointer = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + ((Index + 1) << 5));
    if (BasePointer == 0)
      return;

    Name = Memory::ReadString(BasePointer + OFF_NAME);
    Team = Memory::Read<int>(BasePointer + OFF_TEAM_NUMBER);

    if (!IsPlayer() && !IsDummy()) {
      BasePointer = 0;
      return;
    }

    IsDead = (IsDummy()) ? false : Memory::Read<short>(BasePointer + OFF_LIFE_STATE) > 0;
    IsKnocked = (IsDummy()) ? false : Memory::Read<short>(BasePointer + OFF_BLEEDOUT_STATE) > 0;

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
      long WeaponHandle = Memory::Read<long>(BasePointer + OFF_WEAPON_HANDLE);
      long WeaponHandleMasked = WeaponHandle & 0xffff;
      WeaponEntity = Memory::Read<long>(OFF_REGION + OFF_ENTITY_LIST + (WeaponHandleMasked << 5));

      int OffHandWeaponID = Memory::Read<int>(BasePointer + OFF_OFFHAND_WEAPON);
      IsHoldingGrenade = OffHandWeaponID == -251 ? true : false;

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

  [[nodiscard]] std::string GetPlayerName() const {
    const auto NameIndex = Memory::Read<uintptr_t>(BasePointer + OFF_NAME_INDEX);
    const auto NameOffset = Memory::Read<uintptr_t>(OFF_REGION + OFF_NAME_LIST + ((NameIndex - 1) * 24));
    std::string PlayerName = Memory::ReadString(NameOffset, 64);
    return PlayerName;
  }

  [[nodiscard]] std::string getPlayerModelName() const {
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

  [[nodiscard]] float GetViewYaw() const {
    if (!IsDummy() || IsPlayer()) {
      return Memory::Read<float>(BasePointer + OFF_YAW);
    }
    return 0.0f;
  }

  [[nodiscard]] bool IsValid() const {
    return BasePointer != 0 && Health > 0 && (IsPlayer() || IsDummy());
  }

  [[nodiscard]] bool IsCombatReady() const {
    return IsValid() && (!IsDead && !IsKnocked || IsDummy());
  }

  [[nodiscard]] bool IsPlayer() const {
    return Name == "player";
  }

  [[nodiscard]] bool IsDummy() const {
    return Team == 97;
  }

  [[nodiscard]] bool IsTeammate() const {
    return LvMap::m_mixtape && Myself->Squad == -1 ? (Team & 1) == (Myself->Team & 1) : Team == Myself->Team;
  }

  [[nodiscard]] bool IsSpectating() const {
    if (!IsDead)
      return false;

    const auto SpecIndex = Memory::Read<int>(Memory::Read<uint64_t>(OFF_REGION + OFF_OBSERVER_LIST) + Memory::Read<int>(BasePointer + 0x38) * 8 + 0x964);
    return Memory::Read<uint64_t>(OFF_REGION + OFF_ENTITY_LIST + ((SpecIndex & 0xFFFF) << 5)) == Myself->BasePointer;
  }

  // Bones //
  [[nodiscard]] int GetBoneFromHitbox(HitboxType HitBox) const {
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

  [[nodiscard]] Vector3D GetBonePosition(const HitboxType HitBox) const {
    const Vector3D Offset = Vector3D(0.0f, 0.0f, 0.0f);

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
