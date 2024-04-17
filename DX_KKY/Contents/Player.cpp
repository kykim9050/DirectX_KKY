#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineDebugMsgWindow.h>

#include "Player.h"
#include "PlayerBullet.h"
#include "BulletFX.h"

std::shared_ptr<APlayer> APlayer::MainPlayer = std::shared_ptr<APlayer>();

APlayer::APlayer() 
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("PlayerRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);
	

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
				AddActorLocation(MoveDir(Dir) * 10.0f);
				State.ChangeState("FallDown");
			}
		);
		Renderer->SetFrameCallback("Player_Dash_Air", 8, [this]()
			{
				SetPrevJumpVec(GetJumpVec());
				SetPrevGravityVec(GetGravityVec());
				AddActorLocation(MoveDir(Dir) * 10.0f);
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
}

std::string APlayer::ChangeStringName(const std::string& _MainName)
{
	std::string ActorDir = "";
	std::string CurAnimationName = _MainName;

	switch (Dir)
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
}

void APlayer::CalJumpVec(float _DeltaTime)
{
	Super::CalJumpVec(_DeltaTime);
}

void APlayer::WallCheck(float _DeltaTime)
{
	float4 CheckPos = GetActorLocation();
	CheckPos.Y = -(CheckPos.Y + UContentsValue::PlayerCheckPosOffSet);

	switch (Dir)
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

		GetBulletInitPosAndRot(InitPos, InitRot, NewBullet);
		NewBullet->SetActorLocation(InitPos);
		NewBullet->SetActorRotation(InitRot);
		BulletFX->SetActorLocation(InitPos);
	}

}

void APlayer::ShootCheck(float _DeltaTime)
{
	if (true == IsPress('X'))
	{
		ShootBullet(_DeltaTime);
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
		PlusPos = UContentsValue::Straight_BulletInitPos;
		ResultRot = { 0.0f, 0.0f, 0.0f };
		Bullet->SetHorizontalDir(float4::Right);
		break;
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



	switch (Dir)
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

	if (true == IsPress(VK_RIGHT) || Dir == EActorDir::Right)
	{
		Bullet->SetHorizontalDir(float4::Right);
		Pos = UContentsValue::Straight_BulletInitPos;
		Rot = { 0.0f, 0.0f, 0.0f };
		return;
	}

	if (true == IsPress(VK_LEFT) || Dir == EActorDir::Left)
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
	if (true == PixelCheck(GetActorLocation(), Color8Bit::Blue))
	{
		return true;
	}

	return false;
}