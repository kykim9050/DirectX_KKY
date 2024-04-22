#pragma once

namespace GAniName
{
	// CUphead
	const std::string DashDust = "DashDust";
	const std::string LandDust = "LandDust";

	// flower boss
	const std::string Chomper_Chomp = "Chomper";
	const std::string Chomper_Death = "ChomperDeath";
}

namespace FlowerBossAniName
{
	const std::string Flower_Idle = "Flower_Idle";
	const std::string Flower_Intro = "FlowerIntro";

	const std::string Flower_FaceAttackHigh_Begin = "Flower_FaceAttackHigh_Begin";
	const std::string Flower_FaceAttackHigh_Idle= "Flower_FaceAttackHigh_Idle";
	const std::string Flower_FaceAttackHigh_End = "Flower_FaceAttackHigh_End";
	const std::string Flower_FaceAttackLow_Begin = "Flower_FaceAttackLow_Begin";
	const std::string Flower_FaceAttackLow_Idle = "Flower_FaceAttackLow_Idle";
	const std::string Flower_FaceAttackLow_End = "Flower_FaceAttackLow_End";

	const std::string Flower_Gatling_Begin = "Flower_Gatling_Begin";
	const std::string Flower_Gatling_Idle = "Flower_Gatling_Idle";
	const std::string Flower_Gatling_End = "Flower_Gatling_End";

	const std::string Flower_CreateObject_Begin = "Flower_CreateObject_Begin";
	const std::string Flower_CreateObject_Idle = "Flower_CreateObject_Idle";
	const std::string Flower_CreateObject_Release = "Flower_CreateObject_Release";
	const std::string Flower_CreateObject_ReleaseIdle = "Flower_CreateObject_ReleaseIdle";
	const std::string Flower_CreateObject_ReleaseRev = "Flower_CreateObject_ReleaseRev";
	const std::string Flower_CreateObject_End = "Flower_CreateObject_End";

	const std::string PurleMissile = "GatlingMissilePurple";
	const std::string BlueMissile = "GatlingMissilePurple";

	const std::string SeedFall = "Fall";
	const std::string SeedPlant = "Plant";
	const std::string SeedGrowUpBegin = "GrowUpBegin";

	const std::string VineGrowUp = "VineGrowUp";
	const std::string VineDisappear = "VineDisappear";

	const std::string Chomper_Chomp = "Chomper_Chomp";
	const std::string Chomper_Death = "Chomper_Death";

}

namespace FlowerBossState
{
	const std::string Intro = "Intro";
	const std::string Idle = "Idle";

	const std::string FaceAttackHigh_Begin = "FaceAttackHigh_Begin";
	const std::string FaceAttackHigh_Idle = "FaceAttackHigh_Idle";
	const std::string FaceAttackHigh_End = "FaceAttackHigh_End";

	const std::string FaceAttackLow_Begin = "FaceAttackLow_Begin";
	const std::string FaceAttackLow_Idle = "FaceAttackLow_Idle";
	const std::string FaceAttackLow_End = "FaceAttackLow_End";

	const std::string Gatling_Begin = "Gatling_Begin";
	const std::string Gatling_Idle = "Gatling_Idle";
	const std::string Gatling_End = "Gatling_End";

	const std::string CreateObject_Begin = "CreateObject_Begin";
	const std::string CreateObject_Idle = "CreateObject_Idle";
	const std::string CreateObject_Release = "CreateObject_Release";
	const std::string CreateObject_ReleaseIdle = "CreateObject_ReleaseIdle";
	const std::string CreateObject_ReleaseRev = "CreateObject_ReleaseRev";
	const std::string CreateObject_End = "CreateObject_End";

	const std::string Chomp = "Chomp";
	const std::string Chomp_Death = "Chomp_Death";
}

namespace FlowerBossStageValue
{
	const float4 SeedColliderScale = float4(20.0f, 40.0f, 1.0f);
}

namespace GColliderScale
{
	const float4 FlowerBoss_HeadColScale = float4(250.0f, 250.0f, 1.0f);
	const float4 FlowerBoss_FaceAttScale = float4(950.f, 280.f, 1.0f);

	const float4 Chomper_ColScale = float4(48.0f, 64.0f, 1.0f);
}

namespace GColliderPosInfo
{
	const float4 FlowerBoss_HeadColRelPos = float4(-300.f, 470.f, 1.0f);
	const float4 FlowerBoss_FaceAttHighPos = float4(-825.f, 430.f, 1.0f);
	const float4 FlowerBoss_FaceAttLowPos = float4(-825.f, 130.f, 1.0f);
}

namespace GRendererPos
{
	const float4 FlowerBoss_MissileInitPos = float4(1070.f, -100.f, 0.0f);
}


// Ό³Έν :
class UContentsValue
{
public:

	static const float WorldMapPlayerXInitValue;
	static const float WorldMapPlayerYInitValue;

	static const float CameraInitZValue;
	static const float4 WorldMapCameraInitValue;

	static const float4 ContentsCameraInitPos;
	static const float ContentsCameraInitXPos;
	static const float ContentsCameraInitYPos;

	static const float PlayerCheckPosOffSet;

	static std::shared_ptr<UEngineTexture> ColMapTexture;

	static const float4 Up_BulletInitPos;
	static const float4 RightUp_BulletInitPos;
	static const float4 DiagUp_BulletInitPos;
	static const float4 Straight_BulletInitPos;
	static const float4 DiagDown_BulletInitPos;
	static const float4 Down_BulletInitPos;
	static const float4 RightDown_BulletInitPos;
	static const float4 Duck_BulletInitPos;

	static const float4 Up_BulletInitRot;
	static const float4 RightUp_BulletInitRot;
	static const float4 Right_BulletInitRot;
	static const float4 RightDown_BulletInitRot;
	static const float4 Down_BulletInitRot;
	static const float4 LeftDown_BulletInitRot;
	static const float4 Left_BulletInitRot;
	static const float4 LeftUp_BulletInitRot;

	static const float4 PlayerBulletColSize;
	static const float4 PlayerSSBulletColSize;

protected:

private:
	UContentsValue();
	~UContentsValue();
};

