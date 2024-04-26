#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineCore/Collision.h>

#include "Player.h"
#include "PlayerBullet.h"
#include "BulletFX.h"
#include "PlayerSSBullet.h"
#include "SSBulletFX.h"
#include "FXBase.h"
#include "FlowerPlatform.h"
#include "BossAttackUnit.h"
#include "TimeScaleControlUnit.h"

std::shared_ptr<APlayer> APlayer::MainPlayer = std::shared_ptr<APlayer>();

APlayer::APlayer() 
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("PlayerRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);
	
	FootCollider = CreateDefaultSubObject<UCollision>("FootCollider");
	FootCollider->SetupAttachment(Root);

	BodyCollider = CreateDefaultSubObject<UCollision>("BodyCollider");
	BodyCollider->SetupAttachment(Root);

	InputOn();
}

APlayer::~APlayer() 
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetMainPlayer(shared_from_this());

	CreatePlayerAnimation();
	
	Renderer->ChangeAnimation("Player_Idle");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Player);

	FootCollider->SetScale(GColliderScale::PlayerFoot_ColScale);
	FootCollider->SetCollisionGroup(ECollisionGroup::PlayerFoot);
	FootCollider->SetCollisionType(ECollisionType::Rect);
	FootCollider->SetPosition(GColliderPosInfo::PlayerFootCol_RelativePos);

	BodyCollider->SetScale(GColliderScale::PlayerBody_ColScale);
	BodyCollider->SetCollisionGroup(ECollisionGroup::Player);
	BodyCollider->SetCollisionType(ECollisionType::Rect);
	BodyCollider->SetPosition(GColliderPosInfo::PlayerBodyCol_RelativePos);

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	
	MakeDebugMSG();
}

void APlayer::CreatePlayerAnimation()
{
	{
		Renderer->CreateAnimation("Player_Idle", "Cuphead_Idle", 0.04f);
		Renderer->CreateAnimation("Player_Run", "CupHead_Run", 0.033f);
		Renderer->CreateAnimation("Player_Jump", "CupHead_Jump", 0.033f);
		Renderer->CreateAnimation("Player_Parry", "CupHead_Parry", 0.033f, false);

		Renderer->CreateAnimation("Player_Aim_Straight", "CupHead_Aim_Straight", 0.04f);
		Renderer->CreateAnimation("Player_Aim_Up", "CupHead_Aim_Up", 0.04f);
		Renderer->CreateAnimation("Player_Aim_Down", "CupHead_Aim_Down", 0.04f);
		Renderer->CreateAnimation("Player_Aim_DiagonalUp", "CupHead_Aim_DiagonalUp", 0.04f);
		Renderer->CreateAnimation("Player_Aim_DiagonalDown", "CupHead_Aim_DiagonalDown", 0.04f);

		Renderer->CreateAnimation("Player_Duck", "CupHead_Duck", 0.033f, false);
		Renderer->CreateAnimation("Player_DuckIdle", "CupHead_DuckIdle", 0.04f);

		Renderer->CreateAnimation("Player_Dash", "CupHead_Dash", 0.044f, false);
		Renderer->CreateAnimation("Player_Dash_Air", "CupHead_Dash_Air", 0.044f, false);

		Renderer->CreateAnimation("Player_Run_Shoot_Straight", "CupHead_Run_Shoot_Straight", 0.033f);
		Renderer->CreateAnimation("Player_Run_Shoot_DiagonalUp", "CupHead_Run_Shoot_DiagonalUp", 0.033f);

		Renderer->CreateAnimation("Player_Shoot_Straight", "CupHead_Shoot_Straight", 0.033f);
		Renderer->CreateAnimation("Player_Shoot_Up", "CupHead_Shoot_Up", 0.033f);
		Renderer->CreateAnimation("Player_Shoot_Down", "CupHead_Shoot_Down", 0.033f);
		Renderer->CreateAnimation("Player_Shoot_DiagonalUp", "CupHead_Shoot_DiagonalUp", 0.033f);
		Renderer->CreateAnimation("Player_Shoot_DiagonalDown", "CupHead_Shoot_DiagonalDown", 0.033f);
		Renderer->CreateAnimation("Player_Duck_Shoot", "CupHead_Duck_Shoot", 0.033f);

		Renderer->CreateAnimation("Player_SSAir_Straight", "CupHead_SSAir_Straight", 0.0416f, false);
		Renderer->CreateAnimation("Player_SSAir_Up", "CupHead_SSAir_Up", 0.0416f, false);
		Renderer->CreateAnimation("Player_SSAir_Down", "CupHead_SSAir_Down", 0.0416f, false);
		Renderer->CreateAnimation("Player_SSAir_DiagonalUp", "CupHead_SSAir_DiagonalUp", 0.0416f, false);
		Renderer->CreateAnimation("Player_SSAir_DiagonalDown", "CupHead_SSAir_DiagonalDown", 0.0416f, false);

		Renderer->CreateAnimation("Player_SSGround_Straight", "CupHead_SSGround_Straight", 0.0416f, false);
		Renderer->CreateAnimation("Player_SSGround_Up", "CupHead_SSGround_Up", 0.0416f, false);
		Renderer->CreateAnimation("Player_SSGround_Down", "CupHead_SSGround_Down", 0.0416f, false);
		Renderer->CreateAnimation("Player_SSGround_DiagonalUp", "CupHead_SSGround_DiagonalUp", 0.0416f, false);
		Renderer->CreateAnimation("Player_SSGround_DiagonalDown", "CupHead_SSGround_DiagonalDown", 0.0416f, false);

		Renderer->CreateAnimation("Player_Hit_Ground", "CupHead_Hit_Ground", 0.05f, false);

		Renderer->CreateAnimation("Player_Scared", "CupHead_Scared", 0.034f, false);
	}

	{
		Renderer->SetFrameCallback("Player_Duck", 7, [this]()
			{
				State.ChangeState("DuckIdle");
			}
		);
		Renderer->SetFrameCallback("Player_Parry", 8, [this]()
			{
				SetPrevJumpVec(GetJumpVec());
				State.ChangeState("AfterParry");
			}
		);
		Renderer->SetFrameCallback("Player_Dash", 8, [this]()
			{
				AddActorLocation(MoveDir(PlayerDir) * 10.0f);
				State.ChangeState("FallDown");
			}
		);
		Renderer->SetFrameCallback("Player_Dash_Air", 8, [this]()
			{
				SetPrevJumpVec(GetJumpVec());
				SetPrevGravityVec(GetGravityVec());
				AddActorLocation(MoveDir(PlayerDir) * 10.0f);
				State.ChangeState("AfterDashAir");
			}
		);
		Renderer->SetFrameCallback("Player_SSGround_Up", 15, [this]()
			{
				State.ChangeState("Idle");
			}
		);
		Renderer->SetFrameCallback("Player_SSGround_DiagonalUp", 15, [this]()
			{
				State.ChangeState("Idle");
			}
		);
		Renderer->SetFrameCallback("Player_SSGround_Straight", 15, [this]()
			{
				State.ChangeState("Idle");
			}
		);
		Renderer->SetFrameCallback("Player_SSGround_DiagonalDown", 15, [this]()
			{
				State.ChangeState("Idle");
			}
		);
		Renderer->SetFrameCallback("Player_SSGround_Down", 15, [this]()
			{
				State.ChangeState("Idle");
			}
		);
	}
}

void APlayer::MakeDebugMSG()
{
	{
		std::string Msg = std::format("PlayerPos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("MousePos(In Screen) : {}\n", GEngine->EngineWindow.GetScreenMousePos().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("JumpVal : {}\n", std::to_string(GetJumpVec().Y));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("GravityVal : {}\n", std::to_string(GetGravityVec().Y));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("OnTreadableObjectValue : {}\n", std::to_string(GetOnTreadableObject()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

std::string APlayer::ChangeStringName(const std::string& _MainName)
{
	std::string ActorDir = "";
	std::string CurAnimationName = _MainName;

	switch (PlayerDir)
	{
	case EActorDir::Left:
		ActorDir = "_Left";
		break;
	case EActorDir::Right:
		ActorDir = "_Right";
		break;
	default:
		break;
	}

	return CurAnimationName + ActorDir;
}

void APlayer::AnimationDirSet(USpriteRenderer* _Renderer, EActorDir _Dir)
{
	switch (_Dir)
	{
	case EActorDir::Left:
		_Renderer->SetDir(EEngineDir::Left);
		break;
	case EActorDir::Right:
		_Renderer->SetDir(EEngineDir::Right);
		break;
	default:
		MsgBoxAssert("등록되지 않은 EEngineDir 형식 입니다.")
		break;
	}
}

void APlayer::ResultMovementUpdate(float _DeltaTime)
{
	CalGravityVec(_DeltaTime);
	CalJumpVec(_DeltaTime);
	WallCheck(_DeltaTime);

	Super::ResultMovementUpdate(_DeltaTime);
}

void APlayer::CalGravityVec(float _DeltaTime)
{
	Super::CalGravityVec(_DeltaTime);

	TreadableCheck();
}

void APlayer::CalJumpVec(float _DeltaTime)
{
	Super::CalJumpVec(_DeltaTime);
}

void APlayer::WallCheck(float _DeltaTime)
{
	float4 CheckPos = GetActorLocation();
	CheckPos.Y = -(CheckPos.Y + UContentsValue::PlayerCheckPosOffSet);

	switch (PlayerDir)
	{
	case EActorDir::Right:
		CheckPos.X += UContentsValue::PlayerCheckPosOffSet;
		break;
	case EActorDir::Left:
		CheckPos.X -= UContentsValue::PlayerCheckPosOffSet;
		break;
	default:
		break;
	}

	if (true == PixelCheck(CheckPos, Color8Bit::Black))
	{
		SetSpeedVec(float4::Zero);
		return;
	}
}

void APlayer::ShootBullet(float _DeltaTime)
{
	ShootDelayTime -= _DeltaTime;

	if (0.0f >= ShootDelayTime)
	{
		ShootDelayTime += ShootDelayInitTime + ShootDelayTime;

		std::shared_ptr<APlayerBullet> NewBullet = GetWorld()->SpawnActor<APlayerBullet>("Bullet", EActorType::Bullet);
		std::shared_ptr<ABulletFX> BulletFX = GetWorld()->SpawnActor<ABulletFX>("BulletFX", EActorType::FX);

		FVector InitPos = FVector::Zero;
		FVector InitRot = FVector::Zero;
		float FXRandomRot = UMath::GetInst().RandomReturnFloat(0.0f, 360.f);

		GetBulletInitPosAndRot(InitPos, InitRot, NewBullet);

		NewBullet->SetActorLocation(InitPos);
		NewBullet->SetActorRotation(InitRot);
		BulletFX->SetActorLocation(InitPos);
		BulletFX->SetActorRotation(float4(0.0f, 0.0f, FXRandomRot));
	}

}

void APlayer::SuperShoot(float _DeltaTime)
{
	GetPlayerKeyDir();

	std::shared_ptr<APlayerSSBullet> NewBullet = GetWorld()->SpawnActor<APlayerSSBullet>("Bullet", EActorType::Bullet);
	std::shared_ptr<ASSBulletFX> BulletFX = GetWorld()->SpawnActor<ASSBulletFX>("BulletFX", EActorType::FX);

	FVector InitPos = FVector::Zero;
	FVector InitRot = FVector::Zero;

	switch (ActorKeyDir)
	{
	case EPlayerKeyDir::Up:
		InitPos = UContentsValue::Up_BulletInitPos;
		InitRot = UContentsValue::Up_BulletInitRot;
		NewBullet->SetVerticalDir(float4::Up);
		break;
	case EPlayerKeyDir::RightUp:
		InitPos = UContentsValue::RightUp_BulletInitPos;
		InitRot = UContentsValue::RightUp_BulletInitRot;
		NewBullet->SetVerticalDir(float4::Up);
		NewBullet->SetHorizontalDir(float4::Right);
		break;
	case EPlayerKeyDir::Right:
		InitPos = UContentsValue::Straight_BulletInitPos;
		InitRot = UContentsValue::Right_BulletInitRot;
		NewBullet->SetHorizontalDir(float4::Right);
		break;
	case EPlayerKeyDir::RightDown:
		InitPos = UContentsValue::RightDown_BulletInitPos;
		InitRot = UContentsValue::RightDown_BulletInitRot;
		NewBullet->SetVerticalDir(float4::Down);
		NewBullet->SetHorizontalDir(float4::Right);
		break;
	case EPlayerKeyDir::Down:
		InitPos = UContentsValue::Down_BulletInitPos;
		InitRot = UContentsValue::Down_BulletInitRot;
		NewBullet->SetVerticalDir(float4::Down);
		break;
	case EPlayerKeyDir::LeftDown:
		InitPos = UContentsValue::RightDown_BulletInitPos;
		InitPos.X = -InitPos.X;
		InitRot = UContentsValue::LeftDown_BulletInitRot;
		NewBullet->SetVerticalDir(float4::Down);
		NewBullet->SetHorizontalDir(float4::Left);
		break;
	case EPlayerKeyDir::Left:
		InitPos = UContentsValue::Straight_BulletInitPos;
		InitPos.X = -InitPos.X;
		InitRot = UContentsValue::Left_BulletInitRot;
		NewBullet->SetHorizontalDir(float4::Left);
		break;
	case EPlayerKeyDir::LeftUp:
		InitPos = UContentsValue::Up_BulletInitPos;
		InitPos.X = -InitPos.X;
		InitRot = UContentsValue::LeftUp_BulletInitRot;
		NewBullet->SetVerticalDir(float4::Up);
		NewBullet->SetHorizontalDir(float4::Left);
		break;
	default:
		break;
	}



	NewBullet->SetActorLocation(GetActorLocation() + InitPos);
	NewBullet->SetActorRotation(InitRot);
	BulletFX->SetActorLocation(GetActorLocation() + InitPos);
	BulletFX->SetActorRotation(InitRot);
}

void APlayer::ChangeSuperShootState()
{
	GetPlayerKeyDir();

	switch (ActorKeyDir)
	{
	case EPlayerKeyDir::Up:
		State.ChangeState("Ground_SS_Up");
		break;
	case EPlayerKeyDir::RightUp:
	case EPlayerKeyDir::LeftUp:
		State.ChangeState("Ground_SS_DiagonalUp");
		break;
	case EPlayerKeyDir::Right:
	case EPlayerKeyDir::Left:
		State.ChangeState("Ground_SS_Straight");
		break;
	case EPlayerKeyDir::RightDown:
	case EPlayerKeyDir::LeftDown:
		State.ChangeState("Ground_SS_DiagonalDown");
		break;
	case EPlayerKeyDir::Down:
		State.ChangeState("Ground_SS_Down");
		break;
	default:
		break;
	}
}

void APlayer::ShootCheck(float _DeltaTime)
{
	if (true == IsPress('X'))
	{
		ShootBullet(_DeltaTime);
	}
	else
	{
		ShootDelayTime = 0.0f;
	}
}

void APlayer::SuperShootCheck(float _DeltaTime)
{
	if (true == IsDown('V'))
	{
		ChangeSuperShootState();
		SuperShoot(_DeltaTime);
	}
}

void APlayer::GetBulletInitPosAndRot(FVector& _Pos, FVector& _Rot, std::shared_ptr<APlayerBullet>& _Bullet)
{
	DirCheck();

	FVector PlayerPos = GetActorLocation();
	FVector& ResultPos = _Pos;
	FVector& ResultRot = _Rot;
	FVector PlusPos = FVector::Zero;
	std::shared_ptr<APlayerBullet>& Bullet = _Bullet;

	switch (ShootType)
	{
	case EBulletShootType::JumpShoot:
		JumpShootInit(_Pos, _Rot, _Bullet);
		break;
	case EBulletShootType::UpShoot:
		PlusPos = UContentsValue::RightUp_BulletInitPos;
		ResultRot = { 0.0f, 0.0f, 90.0f };
		Bullet->SetVerticalDir(float4::Up);
		break;
	case EBulletShootType::DiagonalUpShoot:
		PlusPos = UContentsValue::DiagUp_BulletInitPos;
		ResultRot = { 0.0f, 0.0f, 45.0f };
		Bullet->SetVerticalDir(float4::Up);
		Bullet->SetHorizontalDir(float4::Right);
		break;
	case EBulletShootType::StraightShoot:
	{
		if (BulletYOffsetIdx >= BulletYOffest.size())
		{
			BulletYOffsetIdx = 0;
		}
		PlusPos = UContentsValue::Straight_BulletInitPos + float4(0.0f, BulletYOffest[BulletYOffsetIdx++], 0.0f);
		ResultRot = { 0.0f, 0.0f, 0.0f };
		Bullet->SetHorizontalDir(float4::Right);
		break;
	}
	case EBulletShootType::DiagonalDownShoot:
		PlusPos = UContentsValue::DiagDown_BulletInitPos;
		ResultRot = { 0.0f, 0.0f, -45.0f };
		Bullet->SetVerticalDir(float4::Down);
		Bullet->SetHorizontalDir(float4::Right);
		break;
	case EBulletShootType::DownShoot:
		PlusPos = UContentsValue::RightDown_BulletInitPos;
		ResultRot = { 0.0f, 0.0f, -90.0f };
		Bullet->SetVerticalDir(float4::Down);
		break;
	case EBulletShootType::DuckShoot:
		PlusPos = UContentsValue::Duck_BulletInitPos;
		ResultRot = { 0.0f, 0.0f, 0.0f };
		Bullet->SetHorizontalDir(float4::Right);
		break;
	default:
		break;
	}



	switch (PlayerDir)
	{
	case EActorDir::Left:
	{
		switch (ShootType)
		{
		case EBulletShootType::JumpShoot:
			PlusPos.X = -PlusPos.X;
			break;
		case EBulletShootType::UpShoot:
			PlusPos.X = -PlusPos.X;
			break;
		case EBulletShootType::DownShoot:
			PlusPos.X = -PlusPos.X;
			break;
		case EBulletShootType::DiagonalUpShoot:
			PlusPos.X = -PlusPos.X;
			ResultRot.Z += 90.0f;
			Bullet->SetHorizontalDir(float4::Left);
			break;
		case EBulletShootType::StraightShoot:
			PlusPos.X = -PlusPos.X;
			ResultRot.Y = 180.0f;
			Bullet->SetHorizontalDir(float4::Left);
			break;
		case EBulletShootType::DiagonalDownShoot:
			PlusPos.X = -PlusPos.X;
			ResultRot.Z -= 90.0f;
			Bullet->SetHorizontalDir(float4::Left);
			break;
		case EBulletShootType::DuckShoot:
			PlusPos.X = -PlusPos.X;
			ResultRot.Y = 180.0f;
			Bullet->SetHorizontalDir(float4::Left);
			break;
		default:
			break;
		}
		break;
	}
	case EActorDir::Right:
	default:
		break;
	}

	ResultPos = PlayerPos + PlusPos;
}

void APlayer::JumpShootInit(FVector& _Pos, FVector& _Rot, std::shared_ptr<APlayerBullet>& _Bullet)
{
	std::shared_ptr<APlayerBullet>& Bullet = _Bullet;
	FVector& Pos = _Pos;
	FVector& Rot = _Rot;

	if (true == IsPress(VK_UP))
	{
		if (true == IsPress(VK_RIGHT))
		{
			Bullet->SetHorizontalDir(float4::Right);
			Bullet->SetVerticalDir(float4::Up);
			Pos = UContentsValue::DiagUp_BulletInitPos;
			Rot = { 0.0f, 0.0f, 45.0f };
			return;
		}

		if (true == IsPress(VK_LEFT))
		{
			Bullet->SetHorizontalDir(float4::Left);
			Bullet->SetVerticalDir(float4::Up);
			Pos = UContentsValue::DiagUp_BulletInitPos;
			Rot = { 0.0f, 0.0f, 135.0f };
			return;
		}

		Bullet->SetVerticalDir(float4::Up);
		Pos = UContentsValue::Up_BulletInitPos;
		Rot = { 0.0f, 0.0f, 90.0f };
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		if (true == IsPress(VK_RIGHT))
		{
			Bullet->SetHorizontalDir(float4::Right);
			Bullet->SetVerticalDir(float4::Down);
			Pos = UContentsValue::DiagDown_BulletInitPos;
			Rot = { 0.0f, 0.0f, -45.0f };
			return;
		}

		if (true == IsPress(VK_LEFT))
		{
			Bullet->SetHorizontalDir(float4::Left);
			Bullet->SetVerticalDir(float4::Down);
			Pos = UContentsValue::DiagDown_BulletInitPos;
			Rot = { 0.0f, 0.0f, -135.0f };
			return;
		}

		Bullet->SetVerticalDir(float4::Down);
		Pos = UContentsValue::Down_BulletInitPos;
		Rot = { 0.0f, 0.0f, -90.0f };
		return;
	}

	if (true == IsPress(VK_RIGHT) || PlayerDir == EActorDir::Right)
	{
		Bullet->SetHorizontalDir(float4::Right);
		Pos = UContentsValue::Straight_BulletInitPos;
		Rot = { 0.0f, 0.0f, 0.0f };
		return;
	}

	if (true == IsPress(VK_LEFT) || PlayerDir == EActorDir::Left)
	{
		Bullet->SetHorizontalDir(float4::Left);
		Pos = UContentsValue::Straight_BulletInitPos;
		Rot = { 0.0f, 0.0f, 180.0f };
		return;
	}

	return;
}

bool APlayer::DownJumpCheck()
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == PixelCheck(Pos, Color8Bit::Blue))
	{
		return true;
	}

	return false;
}

void APlayer::CreateDashFX(float4 _Pos)
{
	float4 Pos = _Pos;
	Pos.Y += DashFXOffset;

	DirCheck();
	EEngineDir ImgDir = EEngineDir::MAX;
	
	std::shared_ptr<AFXBase> DashFX = GetWorld()->SpawnActor<AFXBase>("DashFX");
	DashFX->FXInit(ERenderingOrder::FrontFX, FAniInfo(GAniName::DashDust, "DashDust",  0.0416f));
	DashFX->SetActorLocation(Pos);

	switch (PlayerDir)
	{
	case EActorDir::Left:
		ImgDir = EEngineDir::Left;
		break;
	case EActorDir::Right:
		ImgDir = EEngineDir::Right;
		break;
	default:
		break;
	}
	DashFX->SetImgDir(ImgDir);

}

void APlayer::CreateLandFX(float4 _Pos)
{
	float4 Pos = _Pos;
	Pos.Y += LandFXOffset;

	DirCheck();
	std::shared_ptr<AFXBase> LandingFX= GetWorld()->SpawnActor<AFXBase>("DashFX");
	LandingFX->FXInit(ERenderingOrder::BackFX, FAniInfo(GAniName::LandDust, "LandDust", 0.0416f));
	LandingFX->SetActorLocation(Pos);
}

void APlayer::FootColOnOff()
{
	float JumpVal = GetJumpVec().Y;
	float GravityVal = GetGravityVec().Y;
	GravityVal *= -1;

	if (JumpVal > GravityVal)
	{
		FootColSetActive(false);
	}
	else if (JumpVal <= GravityVal)
	{
		FootColSetActive(true);
	}
}

void APlayer::TreadableCheck()
{
	FootCollider->CollisionEnter(ECollisionGroup::Platform, [this](std::shared_ptr<UCollision> _Collision)
		{
			AFlowerPlatform* Platform = dynamic_cast<AFlowerPlatform*>(_Collision->GetActor());

			if (nullptr == Platform)
			{
				MsgBoxAssert("충돌 대상이 Platform가 아닙니다.");
				return;
			}

			Platform->SetPressed();

			if ("Idle" != State.GetCurStateName())
			{
				SetOnTreadableObject(true);
				CreateLandFX(GetActorLocation());
				State.ChangeState("Idle");
				return;
			}
		});

	FootCollider->CollisionExit(ECollisionGroup::Platform, [this](std::shared_ptr<UCollision> _Collision)
		{
			AFlowerPlatform* Platform = dynamic_cast<AFlowerPlatform*>(_Collision->GetActor());

			if (nullptr == Platform)
			{
				MsgBoxAssert("충돌 대상이 Platform가 아닙니다.");
				return;
			}

			if (false == Platform->GetIsPressed())
			{
				Platform->PressedOver();

				SetOnTreadableObject(false);
				return;
			}
		});

	FootCollider->CollisionStay(ECollisionGroup::Platform, [this](std::shared_ptr<UCollision> _Collision)
		{
			AFlowerPlatform* Platform = dynamic_cast<AFlowerPlatform*>(_Collision->GetActor());

			if (nullptr == Platform)
			{
				MsgBoxAssert("충돌 대상이 Platform가 아닙니다.");
				return;
			}

			SetOnTreadableObject(true);
			SetJumpVec(float4::Zero);
			SetGravityVec(float4::Zero);
		});

	
}

bool APlayer::FallDownCheck(float4 _Pos)
{
	float4 Pos = _Pos;

	Pos.Y = -Pos.Y;

	if (false == PixelCheck(Pos, Color8Bit::Black)
		&& false == PixelCheck(Pos, Color8Bit::Blue)
		&& false == GetOnTreadableObject()
		)
	{
		State.ChangeState("FallDown");
		return true;
	}

	return false;
}


void APlayer::CollisionCheck()
{
	BodyCollider->CollisionStay(ECollisionGroup::MonsterBullet, [this](std::shared_ptr<UCollision> _Collision)
		{
			ABulletUnit* Bullet = dynamic_cast<ABulletUnit*>(_Collision->GetActor());

			if (nullptr == Bullet)
			{
				MsgBoxAssert("충돌 대상이 Monster Bullet이 아닙니다.");
				return;
			}

			if (true == GetParrying() && true == Bullet->GetParryableObject())
			{
				Bullet->Destroy();
				
				AfterSuccessParrySetting();
			}
			
		});

	BodyCollider->CollisionStay(ECollisionGroup::Monster, [this](std::shared_ptr<UCollision> _Collision)
		{
			ABossAttackUnit* Monster = dynamic_cast<ABossAttackUnit*>(_Collision->GetActor());

			if (nullptr == Monster)
			{
				MsgBoxAssert("충돌 대상이 Monster가 아닙니다.");
				return;
			}

			if (true == GetParrying() && true == Monster->GetParryableObject())
			{
				Monster->Destroy();

				AfterSuccessParrySetting();
			}

		});
}

void APlayer::AfterSuccessParrySetting()
{
	float RandomAngleValue = UMath::GetInst().RandomReturnFloat(0.0f, 360.0f);

	std::shared_ptr<AFXBase> ParryEffect = GetWorld()->SpawnActor<AFXBase>("AFXBase", EActorType::FX);
	ParryEffect->FXInit(ERenderingOrder::BackFX, FAniInfo(GAniName::ParryEffect, GSpriteName::ParryEffect, 0.034f), false);
	ParryEffect->SetActorLocation(GetActorLocation());
	ParryEffect->SetActorRotation(float4(0.0f, 0.0f, RandomAngleValue));

	SetAvailableParry(true);

	SetJumpVec(float4::Up * ParrySuccessJumpSpeed);
	SetGravityVec(float4::Zero);

	UTimeScaleControlUnit::GetTimeController()->RecoveryTimeScale();

	SetStopTimeScale();
}

void APlayer::SetStopTimeScale()
{
	for (int i = 0; i < static_cast<int>(EActorType::Max); i++)
	{
		if (static_cast<int>(EActorType::FilmEffect) == i
			|| static_cast<int>(EActorType::TimeScaleController) == i
			)
		{
			continue;
		}
		GEngine->SetOrderTimeScale(i, 0.0f);
	}
}