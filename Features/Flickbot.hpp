#pragma once
#include <iostream>
#include <vector>
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

// Conversion
#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

struct Flickbot
{
	std::chrono::milliseconds LastClickTime;

	int FinalDistance = 0;

	XDisplay *X11Display;
	LocalPlayer *Myself;
	std::vector<Player *> *Players;
	Level *Map;

	Player *CurrentTarget = nullptr;
	bool TargetSelected = true;
	std::chrono::milliseconds LastAimTime;
	std::chrono::milliseconds LastFlickTime;
	std::chrono::milliseconds LastFlickBackTime;

	Flickbot(XDisplay *X11Display, Level *Map, LocalPlayer *Myself, std::vector<Player *> *GamePlayers) {
		this->X11Display = X11Display;
		this->Myself = Myself;
		this->Map = Map;
		this->Players = GamePlayers;
	}

	bool Save()
	{
		try {
			Config::Flickbot::Flickbot = Features::Flickbot::Flickbot;
			Config::Flickbot::FlickbotMethod = Features::Flickbot::FlickbotMethod;
			Config::Flickbot::FlickBind = static_cast<int>(Features::Flickbot::FlickBind);
			Config::Flickbot::ClosestHitbox = Features::Flickbot::ClosestHitbox;
			Config::Flickbot::Hitbox = static_cast<int>(Features::Flickbot::Hitbox);
			Config::Flickbot::Priority = Features::Flickbot::Priority;
			Config::Flickbot::AutoShoot = Features::Flickbot::AutoShoot;
			Config::Flickbot::AutoShootDelay = Features::Flickbot::AutoShootDelay;
			Config::Flickbot::FlickBack = Features::Flickbot::FlickBack;
			Config::Flickbot::FlickBackDelay = Features::Flickbot::FlickBackDelay;
			Config::Flickbot::PredictMovement = Features::Flickbot::PredictMovement;
			Config::Flickbot::PredictBulletDrop = Features::Flickbot::PredictBulletDrop;
			Config::Flickbot::TeamCheck = Features::Flickbot::TeamCheck;
			Config::Flickbot::PreditcionAmount = Features::Flickbot::PreditcionAmount;
			Config::Flickbot::FinalDistance = Features::Flickbot::FinalDistance;
			Config::Flickbot::HipfireSmooth = Features::Flickbot::HipfireSmooth;
			Config::Flickbot::ADSSmooth = Features::Flickbot::ADSSmooth;
			Config::Flickbot::SmoothDistance = Features::Flickbot::SmoothDistance;
			Config::Flickbot::Delay = Features::Flickbot::Delay;
			Config::Flickbot::FOV = Features::Flickbot::FOV;
			Config::Flickbot::ZoomScale = Features::Flickbot::ZoomScale;
			Config::Flickbot::MinDistance = Features::Flickbot::MinDistance;
			Config::Flickbot::HipfireDistance = Features::Flickbot::HipfireDistance;
			Config::Flickbot::ZoomDistance = Features::Flickbot::ZoomDistance;
			//Weapon Toggles
			//Light
			Config::Flickbot::P2020 = Features::Flickbot::P2020;
			Config::Flickbot::RE45 = Features::Flickbot::RE45;
			Config::Flickbot::Alternator = Features::Flickbot::Alternator;
			Config::Flickbot::R99 = Features::Flickbot::R99;
			Config::Flickbot::R301 = Features::Flickbot::R301;
			Config::Flickbot::Spitfire = Features::Flickbot::Spitfire;
			Config::Flickbot::G7 = Features::Flickbot::G7;
			//Heavy
			Config::Flickbot::Flatline = Features::Flickbot::Flatline;
			Config::Flickbot::Hemlock = Features::Flickbot::Hemlock;
			Config::Flickbot::Repeater = Features::Flickbot::Repeater;
			Config::Flickbot::Rampage = Features::Flickbot::Rampage;
			Config::Flickbot::CARSMG = Features::Flickbot::CARSMG;
			//Energy
			Config::Flickbot::Havoc = Features::Flickbot::Havoc;
			Config::Flickbot::Devotion = Features::Flickbot::Devotion;
			Config::Flickbot::LSTAR = Features::Flickbot::LSTAR;
			Config::Flickbot::TripleTake = Features::Flickbot::TripleTake;
			Config::Flickbot::Volt = Features::Flickbot::Volt;
			Config::Flickbot::Nemesis = Features::Flickbot::Nemesis;
			//Shotgun
			Config::Flickbot::Mozambique = Features::Flickbot::Mozambique;
			Config::Flickbot::EVA8 = Features::Flickbot::EVA8;
			Config::Flickbot::Peacekeeper = Features::Flickbot::Peacekeeper;
			Config::Flickbot::Mastiff = Features::Flickbot::Mastiff;
			//Snipers
			Config::Flickbot::Longbow = Features::Flickbot::Longbow;
			Config::Flickbot::ChargeRifle = Features::Flickbot::ChargeRifle;
			Config::Flickbot::Sentinel = Features::Flickbot::Sentinel;
			//Legendary
			Config::Flickbot::Wingman = Features::Flickbot::Wingman;
			Config::Flickbot::Prowler = Features::Flickbot::Prowler;
			Config::Flickbot::Bocek = Features::Flickbot::Bocek;
			Config::Flickbot::Kraber = Features::Flickbot::Kraber;
			Config::Flickbot::Knife = Features::Flickbot::Knife;

			return true;
		} catch (...) {
			return false;
		}
	}

	void UpdateFlickList()
	{
		Features::Flickbot::FlickList.clear();
		// Light
		if (Features::Flickbot::P2020)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_P2020);
		if (Features::Flickbot::RE45)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_RE45);
		if (Features::Flickbot::Alternator)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_ALTERNATOR);
		if (Features::Flickbot::R99)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_R99);
		if (Features::Flickbot::R301)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_R301);
		if (Features::Flickbot::Spitfire)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_SPITFIRE);
		if (Features::Flickbot::G7)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_G7);
		// Heavy
		if (Features::Flickbot::Flatline)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_FLATLINE);
		if (Features::Flickbot::Hemlock)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_HEMLOCK);
		if (Features::Flickbot::Repeater)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_REPEATER);
		if (Features::Flickbot::Rampage)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_RAMPAGE);
		if (Features::Flickbot::CARSMG)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_CAR);
		// Energy
		if (Features::Flickbot::Havoc)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_HAVOC);
		if (Features::Flickbot::Devotion)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_DEVOTION);
		if (Features::Flickbot::LSTAR)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_LSTAR);
		if (Features::Flickbot::TripleTake)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_TRIPLETAKE);
		if (Features::Flickbot::Volt)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_VOLT);
		if (Features::Flickbot::Nemesis)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_NEMESIS);
		// Shotguns
		if (Features::Flickbot::Mozambique)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_MOZAMBIQUE);
		if (Features::Flickbot::EVA8)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_EVA8);
		if (Features::Flickbot::Peacekeeper)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_PEACEKEEPER);
		if (Features::Flickbot::Mastiff)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_MASTIFF);
		// Snipers
		if (Features::Flickbot::Longbow)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_LONGBOW);
		if (Features::Flickbot::ChargeRifle)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_CHARGE_RIFLE);
		if (Features::Flickbot::Sentinel)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_SENTINEL);
		// Legendary
		if (Features::Flickbot::Wingman)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_WINGMAN);
		if (Features::Flickbot::Prowler)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_PROWLER);
		if (Features::Flickbot::Bocek)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_BOCEK);
		if (Features::Flickbot::Kraber)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_KRABER);
		if (Features::Flickbot::Knife)
			Features::Flickbot::FlickList.insert(WeaponIDs::WEAPON_KNIFE);
	}

	void Update()
	{
		if (!Features::Flickbot::Flickbot) {
			ReleaseTarget();
			return;
		}

		if (Features::Flickbot::Flickbot) {

			if (Myself->IsZooming)
				FinalDistance = Features::Flickbot::ZoomDistance;
			else
				FinalDistance = Features::Flickbot::HipfireDistance;

			if (!Myself->IsCombatReady()) {
				CurrentTarget = nullptr;
				return;
			}

			if (Features::Flickbot::FlickList.find(Myself->WeaponIndex) == Features::Flickbot::FlickList.end()) {
				ReleaseTarget();
				return;
			}

			if (Myself->IsHoldingGrenade) {
				ReleaseTarget();
				return;
			}

			if (!isKeybindDown()) {
				ReleaseTarget();
				return;
			}

			Player *Target = CurrentTarget;
			if (!IsValidTarget(Target)) {
				if (TargetSelected)
					return;

				Target = FindBestTarget();
				if (!IsValidTarget(Target)) {
					ReleaseTarget();
					return;
				}

				CurrentTarget = Target;
				// CurrentTarget->IsLockedOn = true;
				TargetSelected = true;
			}

			if (TargetSelected && CurrentTarget) {
				std::chrono::milliseconds Now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
				if (Now >= LastAimTime + std::chrono::milliseconds(Features::Flickbot::Delay)) {
					StartAiming();
					LastAimTime = Now + std::chrono::milliseconds((int)Utils::RandomRange(1, 10));
				}
				return;
			}
		}
	}

	bool isKeybindDown()
	{
		bool ActivatedByAimBind = InputManager::isKeyDownOrPress(Features::Flickbot::FlickBind);
		bool active = (ActivatedByAimBind);
		return active;
	}

	void StartAiming()
	{
		// Get Target Angle
		QAngle DesiredAngles = QAngle(0, 0);
		if (!GetAngle(CurrentTarget, DesiredAngles))
			return;

		// Smoothing
		SmoothAngle(DesiredAngles);

		if (DesiredAngles == QAngle(0, 0))
			return;
		DesiredAngles.NormalizeAngles();

		if (Features::Flickbot::FlickbotMethod == 0) { // Mouse
			Vector2D FlickbotDelta = Vector2D(CalculatePitchIncrement(DesiredAngles), CalculateYawIncrement(DesiredAngles)).Multiply(25);
			/*int totalYawIncrementInt = RoundHalfEven(AL1AF0(FlickbotDelta.x));
			int totalPitchIncrementInt = RoundHalfEven(AL1AF0(FlickbotDelta.y * -1));*/
			if (FlickbotDelta.x == 0 && FlickbotDelta.y == 0) return;

			Vector2D CurrentAngles = Memory::Read<Vector2D>(Myself->BasePointer + OFF_VIEW_ANGLES);

			// Flick Angles
			if (InputManager::isKeyDownOrPress(Features::Flickbot::FlickBind)) {
				X11Display->MoveMouse(FlickbotDelta.x, FlickbotDelta.y * -1);
				if (Features::Flickbot::AutoShoot) {
					std::this_thread::sleep_for(std::chrono::milliseconds(Features::Flickbot::AutoShootDelay));
					X11Display->MouseClickLeft();
				}

				if (Features::Flickbot::FlickBack) {
					std::this_thread::sleep_for(std::chrono::milliseconds(Features::Flickbot::FlickBackDelay));
					Myself->SetViewAngle(CurrentAngles);
				}
			}
		} else if (Features::Flickbot::FlickbotMethod == 1) { // Memory
			Vector2D CurrentAngles = Memory::Read<Vector2D>(Myself->BasePointer + OFF_VIEW_ANGLES);

			// Flick Angles
			if (InputManager::isKeyDownOrPress(Features::Flickbot::FlickBind)) {
				//Change QAngle To Vector2D
				Vector2D VectorDesiredAngles = Vector2D(DesiredAngles.x, DesiredAngles.y);

				Myself->SetViewAngle(VectorDesiredAngles);
				if (Features::Flickbot::AutoShoot) {
					std::this_thread::sleep_for(std::chrono::milliseconds(Features::Flickbot::AutoShootDelay));
					X11Display->MouseClickLeft();
				}

				if (Features::Flickbot::FlickBack) {
					std::this_thread::sleep_for(std::chrono::milliseconds(Features::Flickbot::FlickBackDelay));
					Myself->SetViewAngle(CurrentAngles);
				}
			}
		}
	}

	void SmoothAngle(QAngle &Angle)
	{
		QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
		QAngle Delta = Angle - ViewAngles;
		Delta.NormalizeAngles();

		if (Myself->IsZooming) {
			Features::Flickbot::Smooth = Features::Flickbot::ADSSmooth;
			float SmoothValue = powf(Features::Flickbot::Smooth, 0.4f);
			SmoothValue = std::min(0.99f, SmoothValue);
		} else if (!Myself->IsZooming) {
			Features::Flickbot::Smooth = Features::Flickbot::HipfireSmooth;
			float SmoothValue = powf(Features::Flickbot::Smooth, 0.4f);
			SmoothValue = std::min(0.99f, SmoothValue);
		}

		QAngle ToChange = QAngle();
		ToChange = Delta - Delta * Features::Flickbot::Smooth;

		Angle = ViewAngles + ToChange;
	}

	void SmoothBackAngle(QAngle &Angle)
	{
		QAngle ViewAngles = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
		QAngle Delta = Angle - ViewAngles;
		Delta.NormalizeAngles();

		Features::Flickbot::FlickBackSmooth = Features::Flickbot::FlickBackSmoothing;
		float SmoothValue = powf(Features::Flickbot::FlickBackSmooth, 0.4f);
		SmoothValue = std::min(0.99f, SmoothValue);

		QAngle ToChange = QAngle();
		ToChange = Delta - Delta * Features::Flickbot::FlickBackSmooth;

		Angle = ViewAngles + ToChange;
	}

	bool GetAngle(Player *Target, QAngle &Angle)
	{
		const QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();
		if (!CurrentAngle.isValid())
			return false;

		if (!GetAngleToTarget(Target, Angle))
			return false;

		return true;
	}

	bool GetAngleToTarget(Player *Target, QAngle &Angle)
	{
		Vector3D TargetPosition;
		if (!Features::Flickbot::ClosestHitbox) {
			TargetPosition = Target->GetBonePosition(Features::Flickbot::Hitbox);
		}
		if (Features::Flickbot::ClosestHitbox) {
			TargetPosition = Target->GetBonePosition(static_cast<HitboxType>(GetBestBone(Target)));
		}
		Vector3D TargetPos = Target->GetBonePosition(Features::Flickbot::Hitbox);
		Vector3D TargetVelocity = Target->AbsoluteVelocity;
		Vector3D CameraPosition = Myself->CameraPosition;

		if (Myself->WeaponProjectileSpeed > 1.0f) {
			if (Features::Flickbot::PredictBulletDrop && Features::Flickbot::PredictMovement) {
				return Resolver::CalculateAimRotationNew(CameraPosition, TargetPos, TargetVelocity, Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, Features::Flickbot::PreditcionAmount, Angle);
			} else if (Features::Flickbot::PredictBulletDrop) {
				return Resolver::CalculateAimRotationNew(CameraPosition, TargetPos, Vector3D(0, 0, 0), Myself->WeaponProjectileSpeed, Myself->WeaponProjectileScale, Features::Flickbot::PreditcionAmount, Angle);
			} else if (Features::Flickbot::PredictMovement) {
				return Resolver::CalculateAimRotation(CameraPosition, TargetPos, TargetVelocity, Myself->WeaponProjectileSpeed, Angle);
			}
		}

		Angle = Resolver::CalculateAngle(CameraPosition, TargetPos);
		return true;
	}

	bool IsValidTarget(Player *target)
	{
		if (target == nullptr ||
			!target->IsValid() ||
			!target->IsCombatReady() ||
			!target->IsVisible ||
			!target->IsHostile ||
			target->Distance2DToLocalPlayer < Conversion::ToGameUnits(Features::Flickbot::MinDistance) ||
			target->Distance2DToLocalPlayer > Conversion::ToGameUnits(FinalDistance))
			return false;
		return true;
	}

	float CalculatePitchIncrement(QAngle FlickbotDesiredAngles)
	{
		float wayA = FlickbotDesiredAngles.x - Myself->ViewAngles.x;
		float wayB = 180 - abs(wayA);
		if (wayA > 0 && wayB > 0)
			wayB *= -1;
		if (fabs(wayA) < fabs(wayB))
			return wayA;
		return wayB;
	}

	float CalculateYawIncrement(QAngle FlickbotDesiredAngles)
	{
		float wayA = FlickbotDesiredAngles.y - Myself->ViewAngles.y;
		float wayB = 360 - abs(wayA);
		if (wayA > 0 && wayB > 0)
			wayB *= -1;
		if (fabs(wayA) < fabs(wayB))
			return wayA;
		return wayB;
	}

	double CalculateDistanceFromCrosshair(Vector3D TargetPosition)
	{
		Vector3D CameraPosition = Myself->CameraPosition;
		QAngle CurrentAngle = QAngle(Myself->ViewAngles.x, Myself->ViewAngles.y).NormalizeAngles();

		if (CameraPosition.Distance(TargetPosition) <= 0.0001f)
			return -1;

		QAngle TargetAngle = Resolver::CalculateAngle(CameraPosition, TargetPosition);
		if (!TargetAngle.isValid())
			return -1;

		return CurrentAngle.distanceTo(TargetAngle);
	}

	void ReleaseTarget()
	{
		if (CurrentTarget != nullptr && CurrentTarget->IsValid())
			CurrentTarget->IsLockedOn = false;

		TargetSelected = false;
		CurrentTarget = nullptr;
	}

	int RoundHalfEven(float x)
	{
		return (x >= 0.0)
				   ? static_cast<int>(std::round(x))
				   : static_cast<int>(std::round(-x)) * -1;
	}

	float AL1AF0(float num)
	{
		if (num > 0)
			return std::max(num, 1.0f);
		return std::min(num, -1.0f);
	}

	float GetFOVScale()
	{
		if (Myself->IsValid()) {
			if (Myself->IsZooming) {
				if (Myself->TargetZoomFOV > 1.0 && Myself->TargetZoomFOV < 90.0) {
					return tanf(DEG2RAD(Myself->TargetZoomFOV) * (0.64285714285)); // what is this magic number?!
				}
			}
		}
		return 1.0;
	}

	int GetBestBone(Player *Target)
	{
		float NearestDistance = 999;
		int NearestBone = 2;
		for (int i = 0; i < 6; i++) {
			HitboxType Bone = static_cast<HitboxType>(i);
			double DistanceFromCrosshair = CalculateDistanceFromCrosshair(Target->GetBonePosition(Bone));
			if (DistanceFromCrosshair < NearestDistance) {
				NearestBone = i;
				NearestDistance = DistanceFromCrosshair;
			}
		}
		return NearestBone;
	}

	Player *FindBestTarget()
	{
		Player *NearestTarget = nullptr;
		float BestDistance = 9999;
		float BestFOV = std::min(Features::Flickbot::FOV, Features::Flickbot::FOV * (GetFOVScale() * Features::Flickbot::ZoomScale));
		float LastPov = 9999;
		Vector3D CameraPosition = Myself->CameraPosition;
		for (int i = 0; i < Players->size(); i++)
		{
			Player *p = Players->at(i);
			if (!IsValidTarget(p))
				continue;
			if (p->DistanceToLocalPlayer < Conversion::ToGameUnits(Features::Flickbot::ZoomDistance)) {
				HitboxType BestBone = static_cast<HitboxType>(GetBestBone(p));
				Vector3D TargetPosition = p->GetBonePosition(BestBone);

				float Distance = CameraPosition.Distance(TargetPosition);
				float FOV = CalculateDistanceFromCrosshair(TargetPosition);

				if (FOV > BestFOV)
					continue;

				if (FOV > LastPov)
					continue;

				NearestTarget = p;
				BestDistance = Distance;
				LastPov = FOV;
			}
		}
		return NearestTarget;
	}
};
