#pragma once
#include "tick.h"
#define ReadPointer(base, offset) (*(PVOID *)(((PBYTE)base + offset)))
#define ReadDWORD(base, offset) (*(PDWORD)(((PBYTE)base + offset)))
#define ReadBYTE(base, offset) (*(((PBYTE)base + offset)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))
#include "offset.h"
#include "skc.h"
#include "setting.h"
#include "hkpresent.h"
#include "engine.h"
#include "Nuklear/demo/d3d11/nuklear_d3d11.h"
#include "data.h"
#include "GetSystemMetrics.h"
#include <list>
VOID(*FreeInternal)(PVOID) = nullptr;
HRESULT(*PresentOriginal)(IDXGISwapChain* pthis, UINT syncInterval, UINT flags) = nullptr;
PVOID(*GetWeaponStats)(PVOID) = nullptr;
namespace Offsets {
	PVOID* uWorld = 0;
	PVOID LaunchCharacter = 0;
	uintptr_t fnGetBounds = 0;
	uintptr_t fnLineOfSightTo = 0;
	uintptr_t fnGetBoneMatrix = 0;
	uintptr_t nObjectsCount = 0;
	uintptr_t uObjects = 0;
	uintptr_t fnGetWeaponStats = 0;

	namespace Engine {
		namespace World {
			DWORD OwningGameInstance = 0x180;
			DWORD Levels = 0x148;
			DWORD PersistentLevel = 0x30;
		}
		namespace SceneComponent {
			DWORD RelativeLocation = 0x11C;
			DWORD ComponentVelocity = 0x140;
		}

		namespace Level {
			DWORD AActors = 0x98;
		}

		namespace GameInstance {
			DWORD LocalPlayers = 0x38;
		}

		namespace Player {
			DWORD PlayerController = 0x30;
		}

		namespace Controller {
			DWORD ControlRotation = 0x288;
			DWORD RemoteViewPitch = 0x232;
			PVOID SetControlRotation = 0;
			PVOID SetActorHiddenInGame = 0;
		}

		namespace PlayerController {
			DWORD AcknowledgedPawn = 0x2A0;
			DWORD PlayerCameraManager = 0x2B8;
		}

		namespace Pawn {
			DWORD PlayerState = 0x240;
		}

		namespace PlayerState {
			PVOID GetPlayerName = 0;
		}

		namespace Actor {
			PVOID SetActorHiddenInGame = 0;
			DWORD CustomTimeDilation = 0x98;
			DWORD RootComponent = 0x130;
		}

		namespace Character {
			DWORD Mesh = 0x280;
		}

		namespace StaticMeshComponent {
			DWORD ComponentToWorld = 0x1C0;
			DWORD StaticMesh = 0x478;
		}

		namespace SkinnedMeshComponent {
			DWORD CachedWorldSpaceBounds = 0x600;
		}
	}

	namespace FortniteGame {
		namespace FortPawn {
			DWORD bIsDBNO = 0x552;
			DWORD bIsDying = 0x538;
			DWORD CurrentWeapon = 0x5A0;
		}
		namespace FortMeatballVehicle {
			DWORD BoostMinPushForce = 0x0478;
			DWORD BoostTopSpeedForceMultiplier = 0x047C;
			DWORD BoostTopSpeedMultiplier = 0x0480;
			DWORD LandTopSpeedMultiplier = 0x0488;
			DWORD LandPushForceMultiplier = 0x048C;
			DWORD BoostSteeringMultiplier = 0x04CC;
			DWORD LandSteeringMultiplier = 0x04D4;
			DWORD LandMinSpeedSteeringAngle = 0x04D8;
			DWORD LandMaxSpeedSteeringAngle = 0x04DC;
		}
		namespace FortPickup {
			DWORD PrimaryPickupItemEntry = 0x298;
		}

		namespace FortItemEntry {
			DWORD ItemDefinition = 0x18;
		}

		namespace FortItemDefinition {
			DWORD DisplayName = 0x70;
			DWORD Tier = 0x54;
		}

		namespace FortPlayerStateAthena {
			DWORD TeamIndex = 0xE88;
		}

		namespace FortWeapon {
			DWORD LastFireTime = 0x8BC;
			DWORD LastFireTimeVerified = 0x8C0;
			DWORD WeaponData = 0x378;
			DWORD LastFireAbilityTime = 0xAB8;
		}

		namespace FortWeaponItemDefinition {
			DWORD WeaponStatHandle = 0x7B8;
		}

		namespace FortProjectileAthena {
			DWORD FireStartLoc = 0x868;
		}

		namespace FortBaseWeaponStats {
			//Reload
			DWORD ReloadTime = 0xFC;
			DWORD ReloadScale = 0x100;
			DWORD ChargeDownTime = 0x12C;
		}

		namespace FortRangedWeaponStats {
			//No Recoil
			DWORD RecoilHoriz = 0x200;
			DWORD RecoilVert = 0x1F0;
			DWORD RecoilDownsightsMultiplier = 0x21C;
			//No Spread
			DWORD Spread = 0x15C;
			DWORD SpreadDownsights = 0x160;
			DWORD StandingStillSpreadMultiplier = 0x164;
			DWORD AthenaJumpingFallingSpreadMultiplier = 0x16C;
			DWORD AthenaCrouchingSpreadMultiplier = 0x168;
			DWORD AthenaSprintingSpreadMultiplier = 0x170;
			DWORD MinSpeedForSpreadMultiplier = 0x174;
			DWORD MaxSpeedForSpreadMultiplier = 0x178;
		}

		namespace BuildingContainer {
			DWORD bAlreadySearched = 0xC71;
		}
	}

	namespace UI {
		namespace ItemCount {
			DWORD ItemDefinition = 0x18;
		}
	}

}
#define M_PI	3.14159265358979323846264338327950288419716939937510
enum eBone
{
	BONE_NULL_1 = 0,
	BONE_NULL_2 = 1,
	BONE_PELVIS_1 = 2,
	BONE_PELVIS_2 = 3,
	BONE_PELVIS_3 = 4,
	BONE_TORSO = 5,

	BONE_CHEST_LOW = 6,
	BONE_CHEST = 7,

	// -------------------------

	BONE_CHEST_LEFT = 8,

	BONE_L_SHOULDER_1 = 9,
	BONE_L_ELBOW = 10,

	BONE_L_HAND_ROOT_1 = 11,

	BONE_L_FINGER_1_ROOT = 12,
	BONE_L_FINGER_1_LOW = 13,
	BONE_L_FINGER_1 = 14,
	BONE_L_FINGER_1_TOP = 15,

	BONE_L_FINGER_2_ROOT = 16,
	BONE_L_FINGER_2_LOW = 17,
	BONE_L_FINGER_2 = 18,
	BONE_L_FINGER_2_TOP = 19,

	BONE_L_FINGER_3_ROOT = 20,
	BONE_L_FINGER_3_LOW = 21,
	BONE_L_FINGER_3 = 22,
	BONE_L_FINGER_3_TOP = 23,

	BONE_L_FINGER_4_ROOT = 24,
	BONE_L_FINGER_4_LOW = 25,
	BONE_L_FINGER_4_ = 26,
	BONE_L_FINGER_4_TOP = 27,

	BONE_L_THUMB_ROOT = 28,
	BONE_L_THUMB_LOW = 29,
	BONE_L_THUMB = 30,

	BONE_L_HAND_ROOT_2 = 31,
	BONE_L_WRIST = 32,
	BONE_L_ARM_LOWER = 33,

	BONE_L_SHOULDER_2 = 34,

	BONE_L_ARM_TOP = 35,

	// -------------------------

	BONE_CHEST_TOP_1 = 36,

	// -------------------------

	BONE_CHEST_RIGHT = 37,

	BONE_R_ELBOW = 38,

	BONE_R_HAND_ROOT_1 = 39,

	BONE_R_FINGER_1_ROOT = 40,
	BONE_R_FINGER_1_LOW = 41,
	BONE_R_FINGER_1 = 42,
	BONE_R_FINGER_1_TOP = 43,

	BONE_R_FINGER_2_ROOT = 44,
	BONE_R_FINGER_2_LOW = 45,
	BONE_R_FINGER_2 = 46,
	BONE_R_FINGER_2_TOP = 47,

	BONE_R_FINGER_3_ROOT = 48,
	BONE_R_FINGER_3_LOW = 49,
	BONE_R_FINGER_3 = 50,
	BONE_R_FINGER_3_TOP = 51,

	BONE_R_FINGER_4_ROOT = 52,
	BONE_R_FINGER_4_LOW = 53,
	BONE_R_FINGER_4_ = 54,
	BONE_R_FINGER_4_TOP = 55,

	BONE_R_THUMB_ROOT = 56,
	BONE_R_THUMB_LOW = 57,
	BONE_R_THUMB = 58,

	BONE_R_HAND_ROOT = 59,
	BONE_R_WRIST = 60,
	BONE_R_ARM_LOWER = 61,

	BONE_R_SHOULDER = 62,

	BONE_R_ARM_TOP = 63,

	// -------------------------

	BONE_CHEST_TOP_2 = 64,

	BONE_NECK = 65,
	BONE_HEAD = 66,

	// -------------------------

	BONE_L_LEG_ROOT = 67,
	BONE_L_KNEE = 68,
	BONE_L_FOOT_ROOT = 69,
	BONE_L_SHIN = 70,
	BONE_L_FOOT_MID = 71,
	BONE_L_FOOT_LOW = 72,
	BONE_L_THIGH = 73,

	// -------------------------

	BONE_R_LEG_ROOT = 74,
	BONE_R_KNEE = 75,
	BONE_R_FOOT_ROOT = 76,
	BONE_R_SHIN = 77,
	BONE_R_FOOT_MID = 78,
	BONE_R_FOOT_LOW = 79,
	BONE_R_THIGH = 80,

	// -------------------------

	BONE_NULL_3 = 81,
	BONE_MISC_L_FOOT = 82,
	BONE_MISC_R_FOOT = 83,
	BONE_NULL_4 = 84,
	BONE_MISC_R_HAND_1 = 85,
	BONE_MISC_L_HAND = 86,
	BONE_MISC_R_HAND_2 = 87,
};
template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}

private:
	T* Data;
	int32_t Count;
	int32_t Max;
};


BOOL IsValid(DWORD64 address)
{
	if (!iat(IsBadReadPtr)((const void*)address, (UINT_PTR)8)) return TRUE;
	else return FALSE;
}

template<typename T>
T read(DWORD_PTR address, const T& def = T())
{
	if (IsValid(address))
		return *(T*)address;
	else
		return T();
}
class UClass {
public:
	BYTE _padding_0[0x40];
	UClass* SuperClass;
};

class UObject {
public:
	PVOID VTableObject;
	DWORD ObjectFlags;
	DWORD InternalIndex;
	UClass* Class;
	BYTE _padding_0[0x8];
	UObject* Outer;

	inline BOOLEAN IsA(PVOID parentClass) {
		for (auto super = this->Class; super; super = super->SuperClass) {
			if (super == parentClass) {
				return TRUE;
			}
		}

		return FALSE;
	}
};

class FUObjectItem {
public:
	UObject* Object;
	DWORD Flags;
	DWORD ClusterIndex;
	DWORD SerialNumber;
	DWORD SerialNumber2;
};

class TUObjectArray {
public:
	FUObjectItem* Objects[9];
};

class GObjects {
public:
	TUObjectArray* ObjectArray;
	BYTE _padding_0[0xC];
	DWORD ObjectCount;
};

struct FString : private TArray<wchar_t>
{
	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? std::wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

class FRotator
{
public:
	FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f)
	{

	}

	FRotator(float _Pitch, float _Yaw, float _Roll) : Pitch(_Pitch), Yaw(_Yaw), Roll(_Roll)
	{

	}
	~FRotator()
	{

	}

	float Pitch;
	float Yaw;
	float Roll;
	inline FRotator get() {
		return FRotator(Pitch, Yaw, Roll);
	}
	inline void set(float _Pitch, float _Yaw, float _Roll) {
		Pitch = _Pitch;
		Yaw = _Yaw;
		Roll = _Roll;
	}

	inline FRotator Clamp() {
		FRotator result = get();
		if (result.Pitch > 180)
			result.Pitch -= 360;
		else if (result.Pitch < -180)
			result.Pitch += 360;
		if (result.Yaw > 180)
			result.Yaw -= 360;
		else if (result.Yaw < -180)
			result.Yaw += 360;
		if (result.Pitch < -89)
			result.Pitch = -89;
		if (result.Pitch > 89)
			result.Pitch = 89;
		while (result.Yaw < -180.0f)
			result.Yaw += 360.0f;
		while (result.Yaw > 180.0f)
			result.Yaw -= 360.0f;

		result.Roll = 0;
		return result;

	}
	double Length() {
		return sqrt(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
	}

	FRotator operator+(FRotator angB) { return FRotator(Pitch + angB.Pitch, Yaw + angB.Yaw, Roll + angB.Roll); }
	FRotator operator-(FRotator angB) { return FRotator(Pitch - angB.Pitch, Yaw - angB.Yaw, Roll - angB.Roll); }
	FRotator operator/(float flNum) { return FRotator(Pitch / flNum, Yaw / flNum, Roll / flNum); }
	FRotator operator*(float flNum) { return FRotator(Pitch * flNum, Yaw * flNum, Roll * flNum); }
	bool operator==(FRotator angB) { return Pitch == angB.Pitch && Yaw == angB.Yaw && Yaw == angB.Yaw; }
	bool operator!=(FRotator angB) { return Pitch != angB.Pitch || Yaw != angB.Yaw || Yaw != angB.Yaw; }

};
namespace GetStructs {
	typedef struct {
		float Pitch;
		float Yaw;
		float Roll;
	} FRotator;

	typedef struct {
		float X, Y, Z;
	} FVector;

	typedef struct {
		FVector Location;
		FRotator Rotation;
		float FOV;
		float OrthoWidth;
		float OrthoNearClipPlane;
		float OrthoFarClipPlane;
		float AspectRatio;
	} FMinimalViewInfo;
}

FString(*GetObjectNameInternal)(PVOID) = nullptr;
class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline double Length() {
		return sqrt(x * x + y * y + z * z);
	}

	inline FRotator ToFRotator() {
		FRotator rot = FRotator();
		float RADPI = (float)(180 / M_PI);
		rot.Yaw = (float)atan2(y, x) * RADPI;
		rot.Pitch = (float)atan2(z, sqrt((x * x) + (y * y))) * RADPI;
		rot.Roll = 0;
		return rot;
	}
	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float flNum) { return Vector3(x * flNum, y * flNum, z * flNum); }
};

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

struct FBox
{
	Vector3  Min;
	Vector3  Max;
	unsigned char IsValid;
	unsigned char UnknownData00[0x3];
};

struct FMinimalViewInfo
{
	Vector3 Loc;
	Vector3 Rot;
	float FOV;
};

struct FMatrix
{
	float M[4][4];
};
PVOID TargetPawn = nullptr;
PVOID boatPawns = nullptr;
PVOID TargetBoat = nullptr;
PVOID LocalPlayerPawn = nullptr;
PVOID LocalPlayerController = nullptr;

uint64_t base_address;
DWORD_PTR Uworld;
DWORD_PTR LocalPawn;
DWORD_PTR LocalWeapon;
DWORD_PTR PlayerCameraManager;
DWORD_PTR Localplayer;
DWORD_PTR Rootcomp;
DWORD_PTR PawnMesh;
DWORD_PTR PlayerController;
DWORD_PTR Ulevel;
DWORD_PTR AActors;
DWORD_PTR Levels;

static auto Dummy_vTable = new uintptr_t[0x1001];
typedef uintptr_t(__fastcall* Cam)(uintptr_t, FMinimalViewInfo*);
Cam o_GetCameraInfo = NULL;
Vector3 CamLoc;
Vector3 CamRot;
D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

static FMatrix* myMatrix = new FMatrix();
D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}
typedef uintptr_t(__fastcall* Cam)(uintptr_t, FMinimalViewInfo*);
uintptr_t hkGetCameraInfo(uintptr_t a1, FMinimalViewInfo* a2)
{
	static float last_fire_ability_time = 0.f;

	uintptr_t ret = iat(game_rbx_jmp)(o_GetCameraInfo, a1, a2);

	Vector3 camera_location = a2->Loc;
	Vector3 camera_rotation = a2->Rot;

	CamLoc = camera_location;
	CamRot = camera_rotation;

	GlobalFOV = a2->FOV;


	return ret;
}
Vector3 GetBoneLocByIdx(uintptr_t mesh, int id)
{
	if (!mesh) return { 0,0,0 };

	auto fGetBoneMatrix = ((FMatrix * (__fastcall*)(uintptr_t, FMatrix*, int))(Offsets::fnGetBoneMatrix));
	iat(fGetBoneMatrix)(mesh, myMatrix, id);

	return Vector3(myMatrix->M[3][0], myMatrix->M[3][1], myMatrix->M[3][2]);
}

float GlobalFOV = 80.f;
Vector3 ProjectWorldToScreen(Vector3 WorldLocation, Vector3 camrot)
{
	Vector3 Screenlocation = Vector3(0, 0, 0);
	Vector3 Rotation = camrot;

	D3DMATRIX tempMatrix;

	Vector3 vAxisX, vAxisY, vAxisZ;

	tempMatrix = Matrix(Rotation);

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - CamLoc;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	float FovAngle = GlobalFOV;
	float ScreenCenterX = X / 2.0f;
	float ScreenCenterY = Y / 2.0f;

	if (vTransformed.z < 1.f || tanf(FovAngle * (float)M_PI / 360.f) == 0.f) return Vector3(0, 0, 0);

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return Screenlocation;
}
bool InstallCameraHook(uintptr_t PlayerCameraManager)
{
	uintptr_t vTable_address = *(uintptr_t*)(PlayerCameraManager);
	if ((uintptr_t)hkGetCameraInfo == read<uintptr_t>(vTable_address + (0xCC * 0x8))) return true;
	if (!vTable_address) return false;
	int num_virtual_methods = 0;
	int z = 0;
	while (read<uintptr_t>(vTable_address + (z * 0x8))) {
		num_virtual_methods += 1;
		z++;
	}
	for (int i = 0; i < num_virtual_methods; i++)
	{
		Dummy_vTable[i] = read<uintptr_t>(vTable_address + (i * 0x8));
	}
	o_GetCameraInfo = (Cam)(read<uintptr_t>(vTable_address + (0xCC * 8)));
	Dummy_vTable[0xCC] = (uintptr_t)hkGetCameraInfo;
	*(uintptr_t**)(PlayerCameraManager) = Dummy_vTable;
	return true;
}

void* SetHook_1(void* pSource, void* pDestination, int dwLen)
{
	DWORD MinLen = 14;

	if (dwLen < MinLen) return NULL;

	BYTE stub[] = {
	0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
	};

	static const void* pTrampoline = nullptr;
	if (!pTrampoline) {
		const auto ntdll = reinterpret_cast<const unsigned char*>(spoof_call(game_rbx_jmp, GetModuleHandleW, (LPCWSTR)NULL));
		const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(ntdll);
		const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(ntdll + dos->e_lfanew);
		const auto sections = IMAGE_FIRST_SECTION(nt);
		const auto num_sections = nt->FileHeader.NumberOfSections;

		constexpr char section_name[5]{ '.', 't', 'e', 'x', 't' };
		const auto     section = std::find_if(sections, sections + num_sections, [&](const auto& s) {
			return std::equal(s.Name, s.Name + 5, section_name);
			});

		constexpr unsigned char instr_bytes[2]{ 0xFF, 0x25 };
		const auto              va = ntdll + section->VirtualAddress;
		pTrampoline = std::search(va, va + section->Misc.VirtualSize, instr_bytes, instr_bytes + 2);
	}

	DWORD64 retto = (DWORD64)pSource + dwLen;

	// trampoline
	memcpy(stub + 6, &retto, 8);
	memcpy((void*)((DWORD_PTR)pTrampoline), pSource, dwLen);
	memcpy((void*)((DWORD_PTR)pTrampoline + dwLen), stub, sizeof(stub));

	// orig
	memcpy(stub + 6, &pDestination, 8);
	memcpy(pSource, stub, sizeof(stub));

	for (int i = MinLen; i < dwLen; i++)
	{
		*(BYTE*)((DWORD_PTR)pSource + i) = 0x90;
	}

	return (void*)((DWORD_PTR)pTrampoline);
}
FBox GetFBox(uintptr_t Actor)
{
	if (!Actor) return {};

	Vector3 Origin, BoxExtend;

	auto fGetActorBounds = reinterpret_cast<void(__fastcall*)(__int64, char, Vector3*, Vector3*)>(Offsets::fnGetBounds);

	iat(fGetActorBounds)( (__int64)Actor, (char)true, &Origin, &BoxExtend);

	FBox NewBox;
	NewBox.IsValid = 1;
	NewBox.Min = Origin - BoxExtend;
	NewBox.Max = Origin + BoxExtend;

	return NewBox;
}

VOID CalcAngle(float* src, float* dst, float* angles);
VOID ToMatrixWithScale(float* in, float out[4][4]);
VOID GetBoneLocation(float compMatrix[4][4], PVOID bones, DWORD index, float out[3]);

float Normalize(float angle) {
	float a = (float)fmod(fmod(angle, 360.0) + 360.0, 360.0);
	if (a > 180.0f) {
		a -= 360.0f;
	}
	return a;
}

VOID CalcAngle(float* src, float* dst, float* angles) {
	float rel[3] = {
		dst[0] - src[0],
		dst[1] - src[1],
		dst[2] - src[2],
	};

	auto dist = sqrtf(rel[0] * rel[0] + rel[1] * rel[1] + rel[2] * rel[2]);
	auto yaw = atan2f(rel[1], rel[0]) * (180.0f / 3.14159265358979323846264338327950288419716939937510);
	auto pitch = (-((acosf((rel[2] / dist)) * 180.0f / 3.14159265358979323846264338327950288419716939937510) - 90.0f));

	angles[0] = Normalize(pitch);
	angles[1] = Normalize(yaw);
}

VOID ToMatrixWithScale(float* in, float out[4][4])
{
	auto* rotation = &in[0];
	auto* translation = &in[4];
	auto* scale = &in[8];

	out[3][0] = translation[0];
	out[3][1] = translation[1];
	out[3][2] = translation[2];

	auto x2 = rotation[0] + rotation[0];
	auto y2 = rotation[1] + rotation[1];
	auto z2 = rotation[2] + rotation[2];

	auto xx2 = rotation[0] * x2;
	auto yy2 = rotation[1] * y2;
	auto zz2 = rotation[2] * z2;
	out[0][0] = (1.0f - (yy2 + zz2)) * scale[0];
	out[1][1] = (1.0f - (xx2 + zz2)) * scale[1];
	out[2][2] = (1.0f - (xx2 + yy2)) * scale[2];

	auto yz2 = rotation[1] * z2;
	auto wx2 = rotation[3] * x2;
	out[2][1] = (yz2 - wx2) * scale[2];
	out[1][2] = (yz2 + wx2) * scale[1];

	auto xy2 = rotation[0] * y2;
	auto wz2 = rotation[3] * z2;
	out[1][0] = (xy2 - wz2) * scale[1];
	out[0][1] = (xy2 + wz2) * scale[0];

	auto xz2 = rotation[0] * z2;
	auto wy2 = rotation[3] * y2;
	out[2][0] = (xz2 + wy2) * scale[2];
	out[0][2] = (xz2 - wy2) * scale[0];

	out[0][3] = 0.0f;
	out[1][3] = 0.0f;
	out[2][3] = 0.0f;
	out[3][3] = 1.0f;
}

VOID MultiplyMatrices(float a[4][4], float b[4][4], float out[4][4]) {
	for (auto r = 0; r < 4; ++r) {
		for (auto c = 0; c < 4; ++c) {
			auto sum = 0.0f;

			for (auto i = 0; i < 4; ++i) {
				sum += a[r][i] * b[i][c];
			}

			out[r][c] = sum;
		}
	}
}

VOID GetBoneLocation(float compMatrix[4][4], PVOID bones, DWORD index, float out[3]) {
	float boneMatrix[4][4];
	ToMatrixWithScale((float*)((PBYTE)bones + (index * 0x30)), boneMatrix);

	float result[4][4];
	MultiplyMatrices(boneMatrix, compMatrix, result);

	out[0] = result[3][0];
	out[1] = result[3][1];
	out[2] = result[3][2];
}

//if (!bones) bones = ReadPointer(mesh, 0x420 + 0x10);
BOOLEAN GetTarget(GetStructs::FVector& out) {
	if (!LocalPawn) {
		return FALSE;
	}
	if (!LocalPawn) {
		MessageBoxA(0, "pawna dead offset", 0, 0);
		return FALSE;
	}

	auto mesh = ReadPointer(LocalPawn, Offsets::Engine::Character::Mesh);
	if (!mesh) {
		MessageBoxA(0, "mesh dead offset", 0, 0);
		return FALSE;
	}

	auto bones = ReadPointer(mesh, 420);
	if (!bones) bones = ReadPointer(mesh, 420 + 0x10);
	if (!bones) {
		MessageBoxA(0, "bones dead offset", 0, 0);
		return FALSE;
	}

	float compMatrix[4][4] = { 0 };

	ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + 0x1C0), compMatrix);
	float kek[3];
	GetBoneLocation(compMatrix, bones, 66, kek);

	return TRUE;
}

namespace GetObjects {
	void FreeObjName(__int64 address)
	{
		if (!IsValid(address)) return;

		auto func = reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(data::OFFSET_FNFREE);

		iat(game_rbx_jmp)(func, address);
	}
	BOOL(*LineOfSightToInternal)(PVOID PlayerController, PVOID Actor, GetStructs::FVector* ViewPoint) = nullptr;
	BOOLEAN LineOfSightTo(PVOID PlayerController, PVOID Actor, GetStructs::FVector* ViewPoint);

	BOOLEAN LineOfSightTo(PVOID PlayerController, PVOID Actor, GetStructs::FVector* ViewPoint) {
		return iat(LineOfSightToInternal)(PlayerController, Actor, ViewPoint);
	}

	std::wstring GetObjectFirstName(UObject* object) {
		auto internalName = GetObjectNameInternal(object);
		if (!internalName.c_str()) {
			return L"";
		}

		std::wstring name(internalName.c_str());
		FreeObjName((__int64)internalName.c_str());

		return name;
	}

	std::wstring GetObjectName(UObject* object) {
		std::wstring name(L"");
		for (auto i = 0; object; object = object->Outer, ++i) {
			auto internalName = GetObjectNameInternal(object);
			if (!internalName.c_str()) {
				break;
			}

			name = internalName.c_str() + std::wstring(i > 0 ? L"." : L"") + name;
			FreeObjName((__int64)internalName.c_str());
		}

		return name;
	}

	PVOID FindObject(LPCWSTR name) {
		for (auto array : objects->ObjectArray->Objects) {
			auto fuObject = array;
			for (auto i = 0; i < 0x10000 && fuObject->Object; ++i, ++fuObject) {
				auto object = fuObject->Object;
				if (object->ObjectFlags != 0x41) {
					continue;
				}

				if (GetObjectName(object) == name) {
					return object;
				}
			}
		}

		return 0;
	}
}
PVOID(*ProcessEvent)(PVOID, PVOID, PVOID, PVOID) = nullptr;
PVOID ProcessEventHook(UObject* object, UObject* func, PVOID params, PVOID result) 
{

	return ProcessEvent(object, func, params, result);
}

BOOLEAN GetTargetHead(GetStructs::FVector& out) {
	if (!TargetPawn) {
		return FALSE;
	}

	auto mesh = ReadPointer(TargetPawn, 0x278);
	if (!mesh) {
		return FALSE;
	}

	auto bones = ReadPointer(mesh, 0x420);
	if (!bones) bones = ReadPointer(mesh, 0x420 + 0x10);
	if (!bones) {
		return FALSE;
	}

	float compMatrix[4][4] = { 0 };
	ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + 0x1C0), compMatrix);

	GetBoneLocation(compMatrix, bones, 66, &out.X);
	return TRUE;
}
uint64_t entityx;
Vector3 CalcAim()
{
	Vector3 RetVector = { 0,0,0 };

	if (!entityx) return { 0,0,0 };

	uint64_t currentactormesh = read<uint64_t>(entityx + Offsets::Engine::Character::Mesh);
	if (!currentactormesh) return { 0,0,0 };

	Vector3 rootHead = GetBoneLocByIdx(currentactormesh, 66);
	if (rootHead.x == 0 && rootHead.y == 0) return Vector3(0, 0, 0);

	Vector3 VectorPos = rootHead - CamLoc;

	float distance = VectorPos.Length();
	RetVector.x = -(((float)acos(VectorPos.z / distance) * (float)(180.0f / M_PI)) - 90.f);
	RetVector.y = (float)atan2(VectorPos.y, VectorPos.x) * (float)(180.0f / M_PI);

	return RetVector;
}
double GetCrossDistance(double x1, double y1, double x2, double y2)
{
	return iat(sqrtf)(iat(powf)((float)(x1 - x2), (float)2) + iat(powf)((float)(y1 - y2), (float)2));
}
static int AimFov = 80;
bool GetClosestPlayerToCrossHair(Vector3 Pos, float& max, DWORD_PTR entity)
{
	if (entity)
	{
		float Dist = GetCrossDistance(Pos.x, Pos.y, (X / 2), (Y / 2));

		if (Dist < max)
		{

			//GlobalFOV : X = NewFOV : NewSize
			//NewSize = NewFOV * X / GlobalFOV

			float Radius = (AimFov * X / GlobalFOV) / 2;

			if (Pos.x <= ((X / 2) + Radius) &&
				Pos.x >= ((X / 2) - Radius) &&
				Pos.y <= ((Y / 2) + Radius) &&
				Pos.y >= ((Y / 2) - Radius))
			{
				max = Dist;
				entityx = entity;
				return true;
			}

			return false;
		}
	}

	return false;
}

static int bVisible = 0; 
bool IsTargetVisible(uintptr_t entity)
{
	if (!entity || !LocalPawn || !LocalWeapon || !PawnMesh || !PlayerController) return false;

	Vector3 tmp = { 0,0,0 };

	auto fLineOfSight = ((BOOL(__fastcall*)(uintptr_t, uintptr_t, Vector3*))(Offsets::fnLineOfSightTo));
	return iat(fLineOfSight)(PlayerController, entity, &tmp);
}
void CheckClosestFOVEntity(DWORD_PTR entity, Vector3 Localcam, float& max)
{
	if (!entity || !LocalPawn || !LocalWeapon) return;

	uint64_t currentactormesh = read<uint64_t>(entity + Offsets::Engine::Character::Mesh);
	if (!currentactormesh) return;

	Vector3 rootHead = GetBoneLocByIdx(currentactormesh, 66);
	Vector3 rootHeadOut = ProjectWorldToScreen(rootHead, CamRot);

	if (rootHeadOut.x <= 0 || rootHeadOut.y <= 0) return;
	if (rootHeadOut.x >= X || rootHeadOut.y >= Y) return;

	if (bVisible && !IsTargetVisible(entity)) return;

	if (GetClosestPlayerToCrossHair(rootHeadOut, max, entity))
		entityx = entity;
}
static int AimDistance = 300;
static int AimSmooth = 0;
void CheckClosestDistEntity(DWORD_PTR entity, Vector3 Localcam, float& max)
{
	if (!entity) return;

	uint64_t currentactormesh = read<uint64_t>(entity + Offsets::Engine::Character::Mesh);
	if (!currentactormesh) return;

	Vector3 rootHead = GetBoneLocByIdx(currentactormesh, 66);

	if (rootHead.x == 0 && rootHead.y == 0) return;

	if (bVisible && !IsTargetVisible(entity)) return;

	Vector3 Delta = rootHead - CamLoc;

	float x0 = iat(powf)((Delta.x), (float)2);
	float x1 = iat(sqrtf)(x1);
	float x2 = iat(powf)(Delta.y, (float)2);
	float x3 = iat(powf)((float)(Delta.z, (float)2));

	float Dist = x1 + x2 + x3;

	if (AimDistance != 300)
	{
		if ((Dist * 0.01f) > (float)AimDistance) return;
	}

	if ((Dist * 0.01f) < max)
	{
		max = (Dist * 0.01f);
		entityx = entity;
		return;
	}
	return;
}
void Draw2DBoundingBox(Vector3 StartBoxLoc, float flWidth, float Height, nk_color color)
{
	StartBoxLoc.x = StartBoxLoc.x - (flWidth / 2);

	Engine->DrawLine(StartBoxLoc.x, StartBoxLoc.y, StartBoxLoc.x + flWidth, StartBoxLoc.y, 1, color); //bottom
	Engine->DrawLine(StartBoxLoc.x, StartBoxLoc.y, StartBoxLoc.x, StartBoxLoc.y + Height, 1, color); //left
	Engine->DrawLine(StartBoxLoc.x + flWidth, StartBoxLoc.y, StartBoxLoc.x + flWidth, StartBoxLoc.y + Height, 1, color); //right
	Engine->DrawLine(StartBoxLoc.x, StartBoxLoc.y + Height, StartBoxLoc.x + flWidth, StartBoxLoc.y + Height, 1, color); //up
}
void DrawSkeleton(DWORD_PTR mesh)
{
	std::list<int> upper_part = { 65,66 };
	std::list<int> right_arm = { 65, BONE_R_ARM_TOP, BONE_R_ARM_LOWER, BONE_MISC_R_HAND_1 };
	std::list<int> left_arm = { 65, BONE_L_ARM_TOP, BONE_L_ARM_LOWER, BONE_MISC_L_HAND };
	std::list<int> spine = { 65, BONE_PELVIS_1 };
	std::list<int> lower_right = { BONE_PELVIS_2, BONE_R_THIGH ,76 };
	std::list<int> lower_left = { BONE_PELVIS_2, BONE_L_THIGH ,69 };
	std::list<std::list<int>> Skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left };

	if (!mesh) return;

	nk_color col = { 102, 255, 204,255 };

	Vector3 neckpos = GetBoneLocByIdx(mesh, 65);
	Vector3 pelvispos = GetBoneLocByIdx(mesh, BONE_PELVIS_2);

	Vector3 previous(0, 0, 0);
	Vector3 current, p1, c1;

	for (auto a : Skeleton)
	{
		previous = Vector3(0, 0, 0);
		for (int bone : a)
		{
			current = bone == 65 ? neckpos : (bone == BONE_PELVIS_2 ? pelvispos : GetBoneLocByIdx(mesh, bone));
			if (previous.x == 0.f)
			{
				previous = current;
				continue;
			}

			p1 = ProjectWorldToScreen(previous, CamRot);
			c1 = ProjectWorldToScreen(current, CamRot);


			if (p1.x != 0 && p1.y != 0 && c1.x != 0 && c1.y != 0)
				Engine->DrawLine(p1.x, p1.y, c1.x, c1.y, 1, col);

			previous = current;
		}
	}
}
Vector3 Normalize(Vector3 vec)
{
	float a1 = vec.x;
	float a2 = vec.y;
	float a3 = vec.z;
	double length = vec.Length();

	if (length == 0.0) return { 0,0,0 };

	return Vector3(a1 / length, a2 / length, a3 / length);
}
Vector3 inline LimitRotation(Vector3 startRotation, Vector3 endRotation)
{
	Vector3 ret;
	auto scale = AimSmooth;
	auto currentRotation = startRotation;

	ret.x = (endRotation.x - startRotation.x) / scale + startRotation.x;
	ret.y = (endRotation.y - startRotation.y) / scale + startRotation.y;

	return ret;
}
int LevelsCount;
int actor_count;
int Actors[2] = { 0,0 };
int Bots[2] = { 0,0 };

void DoAimbot(Vector3 Localcam)
{

	if (!read<uint64_t>(entityx + Offsets::Engine::Actor::RootComponent))
	{
		entityx = 0;
		return;
	}
	if (!read<uint64_t>(entityx + Offsets::Engine::Pawn::PlayerState))
	{
		entityx = 0;
		return;
	}
	if (!read<uint64_t>(entityx + Offsets::Engine::Character::Mesh))
	{
		entityx = 0;
		return;
	}
	uint8_t bIsDying = *(uint8_t*)(entityx + Offsets::FortniteGame::FortPawn::bIsDying);
	if (BIT_CHECK(bIsDying, 3))
	{
		entityx = 0;
		return;
	}

	if (!PlayerController || !read<uintptr_t>(PlayerController))
	{
		entityx = 0;
		return;
	}

	Vector3 NewAngle = CalcAim();

	if (NewAngle.x == 0 && NewAngle.y == 0) return;

	if (AimSmooth > 0)
		NewAngle = LimitRotation(CamRot, NewAngle);

	NewAngle.z = 0;

	auto ClientSetRotation = (*(void(__fastcall**)(uint64_t, Vector3, char))(*(uint64_t*)PlayerController + 0x638));
	iat(ClientSetRotation)(PlayerController, NewAngle, (char)0);
}
bool GetAimKey()
{
	return (GetACheatLoverzKeyState((DWORD)VK_RBUTTON) & 0x8000);
	
}

VOID Free(PVOID buffer) {
	FreeInternal(buffer);
}

void FreeObjName(__int64 address)
{
	if (!IsValid(address)) return;

	auto func = reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(data::OFFSET_FNFREE);

	iat(func)(address);
}


std::string GetObjectName(uintptr_t Object) {
	if (Object == NULL)
		return skCrypt("");
	auto fGetObjName = reinterpret_cast<FString * (__fastcall*)(FString * name, uintptr_t entity)>(data::OFFSET_GETOBJECTNAMES);
	FString result;
	fGetObjName(&result, Object);
	if (result.c_str() == NULL)
		return skCrypt("");
	auto result_str = result.ToString();
	if (result.c_str() != NULL)
		FreeObjName((__int64)result.c_str());
	return result_str;
}

void OnlyActorsLoop()
{
	if (!IsValid(LocalPawn) || !IsValid(LocalWeapon)) return;

	float FOVmax = 9999.f;
	float DistanceMax = 9999999999.f;

	int MyTeamID = 0;
	int TeamID = 1;

	for (int i = 0; i < actor_count; i++)
	{
		uint64_t CurrentActor = read<uint64_t>(AActors + i * 0x8);
		if (!CurrentActor) continue;

		int curactorid = *(int*)(CurrentActor + 0x18);
		if (curactorid == 0) continue;

		//Enemy
		if (CurrentActor != LocalPawn && CurrentActor != Localplayer && CurrentActor != PlayerController)
		{
			if (Actors[0] == 0 || Actors[1] == 0 || Bots[0] == 0 || Bots[1] == 0)
			{
				if (curactorid != Actors[0] &&
					curactorid != Actors[1] &&
					curactorid != Bots[0] &&
					curactorid != Bots[1])
				{
					char* ObjName = (char*)malloc(200);
					strcpy(ObjName, (char*)GetObjectName(CurrentActor).c_str());
					if (strstr((const char*)ObjName, (const char*)skCrypt("PlayerPawn_Athena_C")))
						Actors[0] = curactorid;
					if (strstr((const char*)ObjName, (const char*)skCrypt("BP_PlayerPawn_Athena_Phoebe_C")))
						Actors[1] = curactorid;
					if (strstr((const char*)ObjName, (const char*)skCrypt("BP_MangPlayerPawn_Default_C")))
						Bots[0] = curactorid;
					if (strstr((const char*)ObjName, (const char*)skCrypt("BP_MangPlayerPawn_Boss_")))
						Bots[1] = curactorid;
					free(ObjName);
				}
			}

			if ((curactorid == Actors[0] || curactorid == Actors[1]) && curactorid != 0)
			{
				uintptr_t MyPlayerState = read<uint64_t>(LocalPawn + Offsets::Engine::Pawn::PlayerState);
				if (MyPlayerState) MyTeamID = *(int*)(MyPlayerState + Offsets::FortniteGame::FortPlayerStateAthena::TeamIndex);

				uint8_t bIsDying = *(uint8_t*)(CurrentActor + Offsets::FortniteGame::FortPawn::bIsDying);
				if (BIT_CHECK(bIsDying, 3)) continue;

				uintptr_t PlayerState = read<uint64_t>(CurrentActor + Offsets::Engine::Pawn::PlayerState);
				if (PlayerState) TeamID = *(int*)(PlayerState + Offsets::FortniteGame::FortPlayerStateAthena::TeamIndex);

				if (setting::EnableESP)
				{
					uint64_t currentactormesh = read<uint64_t>(CurrentActor + Offsets::Engine::Character::Mesh);
					if (!currentactormesh) continue;

					Vector3 Headpos = GetBoneLocByIdx(currentactormesh, 66);

					if (Headpos.x == 0 && Headpos.y == 0) continue;

					Vector3 bone0 = GetBoneLocByIdx(currentactormesh, 0);

					Vector3 HeadposW2s = ProjectWorldToScreen(Headpos, CamRot);
					Vector3 bottom = ProjectWorldToScreen(bone0, CamRot);
					Vector3 Headbox = ProjectWorldToScreen(Vector3(Headpos.x, Headpos.y, Headpos.z + 15), CamRot);

					if (HeadposW2s.x == 0 && HeadposW2s.y == 0) continue;
					if (bottom.x == 0 && bottom.y == 0) continue;
					if (Headbox.x == 0 && Headbox.y == 0) continue;

					if (setting::esp::skeleton) DrawSkeleton(currentactormesh);

					if (TeamID != MyTeamID )
					{
						float Height1 = Headbox.y - bottom.y;

						if (Height1 < 0)
							Height1 = Height1 * (-1.f);
						float Width1 = Height1 * 0.65;

						Draw2DBoundingBox(Headbox, Width1, Height1, { 255, 0, 0, 255 });
					}

				}

				}
				if ((setting::aimbot::aim_method == 1) && (TeamID != MyTeamID))
				{
					CheckClosestFOVEntity(CurrentActor, CamRot, FOVmax);
				}
			
			else
			{
				if ((curactorid == Bots[0] || (curactorid >= (Bots[1] - 5) && curactorid <= (Bots[1] + 5))) && curactorid != 0)
				{
					uint8_t bIsDying = *(uint8_t*)(CurrentActor + Offsets::FortniteGame::FortPawn::bIsDying);
					if (BIT_CHECK(bIsDying, 3)) continue;
					if (setting::EnableESP)
					{
						uint64_t currentactormesh = read<uint64_t>(CurrentActor + Offsets::Engine::Character::Mesh);
						if (!currentactormesh) continue;

						Vector3 Headpos = GetBoneLocByIdx(currentactormesh, 66);

						if (Headpos.x == 0 && Headpos.y == 0) continue;
						Vector3 HeadposW2s = ProjectWorldToScreen(Headpos, CamRot);
						Vector3 bone0 = GetBoneLocByIdx(currentactormesh, 0);
						Vector3 bottom = ProjectWorldToScreen(bone0, CamRot);
						Vector3 Headbox = ProjectWorldToScreen(Vector3(Headpos.x, Headpos.y, Headpos.z + 15), CamRot);

						if (HeadposW2s.x == 0 && HeadposW2s.y == 0) continue;
						if (bottom.x == 0 && bottom.y == 0) continue;
						if (Headbox.x == 0 && Headbox.y == 0) continue;

						if (setting::esp::skeleton) DrawSkeleton(currentactormesh);
						if (curactorid == Bots[0])
						{
							float Height1 = Headbox.y - bottom.y;

							if (Height1 < 0)
								Height1 = Height1 * (-1.f);
							float Width1 = Height1 * 0.65;

							Draw2DBoundingBox(Headbox, Width1, Height1, { 255, 0, 0, 255 });
						}
							
						
					}
					if ((setting::aimbot::aim_method == 2))
					{
						CheckClosestFOVEntity(CurrentActor, CamRot, FOVmax);
					}
				}
			}
		}
	}

	uintptr_t OldAimingActor = 0;
	if (!OldAimingActor && IsValid(entityx))
		if (GetAimKey())
			OldAimingActor = entityx;

	if (IsValid(OldAimingActor))
	{
		if (!read<uint64_t>(OldAimingActor + Offsets::Engine::Actor::RootComponent))
		{
			OldAimingActor = 0;
			return;
		}
		if (!read<uint64_t>(OldAimingActor + Offsets::Engine::Pawn::PlayerState))
		{
			OldAimingActor = 0;
			return;
		}
		if (!read<uint64_t>(OldAimingActor + Offsets::Engine::Character::Mesh))
		{
			OldAimingActor = 0;
			return;
		}
		uint8_t bIsDying = *(uint8_t*)(OldAimingActor + Offsets::FortniteGame::FortPawn::bIsDying);
		if (BIT_CHECK(bIsDying, 3))
		{
			OldAimingActor = 0;
			return;
		}

		if (GetAimKey())
			entityx = OldAimingActor;
		else
			OldAimingActor = NULL;
	}
}



bool MainAddress() {

	if (!IsValid(data::OFFSET_UWORLD)) return false;

	Uworld = read<DWORD_PTR>(data::OFFSET_UWORLD);
	if (!Uworld) return false;

	DWORD_PTR Gameinstance = read<DWORD_PTR>(Uworld + Offsets::Engine::World::OwningGameInstance);
	if (!Gameinstance) return false;

	DWORD_PTR LocalPlayers = read<DWORD_PTR>(Gameinstance + Offsets::Engine::GameInstance::LocalPlayers);
	if (!LocalPlayers) return false;

	Localplayer = read<DWORD_PTR>(LocalPlayers);
	if (!Localplayer) return false;

	PlayerController = read<DWORD_PTR>(Localplayer + Offsets::Engine::Player::PlayerController);
	if (!PlayerController) return false;

	LocalPawn = read<uint64_t>(PlayerController + Offsets::Engine::PlayerController::AcknowledgedPawn);
	if (!LocalPawn)
	{
		return false;
	}

	LocalWeapon = read<uint64_t>(LocalPawn + Offsets::FortniteGame::FortPawn::CurrentWeapon);
	if (!LocalWeapon) return false;

	PlayerCameraManager = read<uint64_t>(PlayerController + Offsets::Engine::PlayerController::PlayerCameraManager);
	if (!PlayerCameraManager) return false;

	Rootcomp = read<uint64_t>(LocalPawn + Offsets::Engine::Actor::RootComponent);
	if (!Rootcomp) return false;

	PawnMesh = read<uint64_t>(LocalPawn + Offsets::Engine::Character::Mesh);
	if (!PawnMesh) return false;

	Levels = read<DWORD_PTR>(Uworld + Offsets::Engine::World::Levels);
	if (!Levels) return false;

	LevelsCount = read<DWORD_PTR>(Uworld + Offsets::Engine::World::Levels + 0x8);
	if (!LevelsCount) return false;

	Ulevel = read<DWORD_PTR>(Uworld + Offsets::Engine::World::PersistentLevel);
	if (!Ulevel) return false;

	AActors = read<DWORD_PTR>(Ulevel + 0x98);
	actor_count = *(int*)(Ulevel + 0xA0);

	if (!AActors || !actor_count) return false;
	if (PlayerController && read<uintptr_t>(PlayerController))
	{
		auto SetIgnoreLookInput = (*(void(__fastcall**)(uint64_t, char bNewLookInput))(*(uint64_t*)PlayerController + 0x728));
		iat(SetIgnoreLookInput)(PlayerController, (char)0);

		if (hidden_window && !finished_window)
		{
			auto SetIgnoreLookInput = (*(void(__fastcall**)(uint64_t, char bNewLookInput))(*(uint64_t*)PlayerController + 0x738));
			iat(SetIgnoreLookInput)(PlayerController, (char)0);
			finished_window = true;
		}
	}
	uint8_t bIsDying = *(uint8_t*)(LocalPawn + Offsets::FortniteGame::FortPawn::bIsDying);
	if (BIT_CHECK(bIsDying, 3))
	{
		LocalPawn = NULL;
		return false;
	}
	return InstallCameraHook(PlayerCameraManager);
}