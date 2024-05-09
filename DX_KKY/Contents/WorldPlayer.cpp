#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/Collision.h>

#include "WorldPlayer.h"
#include "WorldDust.h"
#include "WorldGameMode.h"
#include "GateUnit.h"

std::shared_ptr<AWorldPlayer> AWorldPlayer:: MainPlayer = std::shared_ptr<AWorldPlayer>();

AWorldPlayer::AWorldPlayer()
	: Dir(EPlayerKeyDir::RightDown)
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("WPlayerRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("WPlayerRenderer");
	Renderer->SetupAttachment(Root);

	ButtonRenderer = CreateDefaultSubObject<USpriteRenderer>("ButtonRenderer");
	ButtonRenderer->SetupAttachment(Root);

	Collider = CreateDefaultSubObject<UCollision>("WPlayerCollider");
	Collider->SetupAttachment(Root);

	InputOn();
}

AWorldPlayer::~AWorldPlayer()
{
}

void AWorldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetMainPlayer(shared_from_this());
	RendererInit();
	CreatePlayerAnimation();
	ColliderInit();
	StateInit();
}

void AWorldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	CollisionCheck();
	WalkCheck(_DeltaTime);
}

void AWorldPlayer::CreatePlayerAnimation()
{
	Renderer->CreateAnimation("WPlayer_UpIdle", "UpIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_DownIdle", "DownIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_DiagonalUpIdle", "DiagonalUpIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_DiagonalDownIdle", "DiagonalDownIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_StraightIdle", "StraightIdle", 0.067f);
	Renderer->CreateAnimation("WPlayer_UpWalk", "UpWalk", 0.037f);
	Renderer->CreateAnimation("WPlayer_DownWalk", "DownWalk", 0.037f);
	Renderer->CreateAnimation("WPlayer_DiagonalUpWalk", "DiagonalUpWalk", 0.037f);
	Renderer->CreateAnimation("WPlayer_DiagonalDownWalk", "DiagonalDownWalk", 0.037f);
	Renderer->CreateAnimation("WPlayer_StraightWalk", "StraightWalk", 0.037f);
}

bool AWorldPlayer::MapCollisionCheck()
{
	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;
	std::shared_ptr<UEngineTexture> CheckTexture = UContentsValue::ColMapTexture;
	
	float CheckOffset = 10.0f;

	switch (Dir)
	{
	case EPlayerKeyDir::Up:
		Pos.Y = Pos.Y - CheckOffset;
		break;
	case EPlayerKeyDir::RightUp:
		Pos.X = Pos.X + CheckOffset;
		Pos.Y = Pos.Y - CheckOffset;
		break;
	case EPlayerKeyDir::Right:
		Pos.X = Pos.X + CheckOffset;
		break;
	case EPlayerKeyDir::RightDown:
		Pos.X = Pos.X + CheckOffset;
		Pos.Y = Pos.Y + CheckOffset;
		break;
	case EPlayerKeyDir::Down:
		Pos.Y = Pos.Y + CheckOffset;
		break;
	case EPlayerKeyDir::LeftDown:
		Pos.X = Pos.X - CheckOffset;
		Pos.Y = Pos.Y + CheckOffset;
		break;
	case EPlayerKeyDir::Left:
		Pos.X = Pos.X - CheckOffset;
		break;
	case EPlayerKeyDir::LeftUp:
		Pos.X = Pos.X - CheckOffset;
		Pos.Y = Pos.Y - CheckOffset;
		break;
	default:
		break;
	}

	Color8Bit Color = CheckTexture->GetColor(Pos, Color8Bit::Black);

	if (Color != Color8Bit::Black)
	{
		return false;
	}

	return true;
}

void AWorldPlayer::MakeDust(float _DeltaTime)
{
	{
		DustDelayTime -= _DeltaTime;

		if (0.0f >= DustDelayTime)
		{
			DustDelayTime = DustDelayTimeInit + DustDelayTime;
			std::shared_ptr<AWorldDust> Dust = GetWorld()->SpawnActor<AWorldDust>("WorldDust", static_cast<int>(EActorType::Dust));

			DustInitXOffset *= -1;
			Dust->SetActorLocation(FVector(GetActorLocation().X + DustInitXOffset, GetActorLocation().Y, 25.0f));
		}
	}
}

void AWorldPlayer::ResetDustDelayTime()
{
	DustDelayTime = 1.0f;
}

void AWorldPlayer::CameraMove(float _DeltaTime)
{
	FVector PlayerPos = GetActorLocation();
	PlayerPos.Z = 0.0f;
	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	CameraPos.Z = 0.0f;

	FVector ChasePlayerVector = PlayerPos - CameraPos;

	if (1.0f >= ChasePlayerVector.Size3D())
	{
		return;
	}

	GetWorld()->GetMainCamera()->AddActorLocation(ChasePlayerVector.Normalize3DReturn() * _DeltaTime * 300.0f);
}

void AWorldPlayer::ColliderInit()
{
	Collider->SetScale(GColliderScale::WorldPlayer_ColScale);
	Collider->SetCollisionGroup(ECollisionGroup::Player);
	Collider->SetCollisionType(ECollisionType::Rect);
}

void AWorldPlayer::CollisionCheck()
{
	Collider->CollisionEnter(ECollisionGroup::Gate, [=](std::shared_ptr<UCollision> _Collision)
		{
			AGateUnit* Gate = dynamic_cast<AGateUnit*>(_Collision->GetActor());

			if (nullptr == Gate)
			{
				MsgBoxAssert("충돌 대상이 Gate가 아닙니다.");
				return;
			}
			
			ButtonRenderer->SetActive(true);
			UEngineSound::SoundPlay("sfx_WorldMap_LevelSelect_BubbleAppear.wav");
		});


	Collider->CollisionStay(ECollisionGroup::Gate, [=](std::shared_ptr<UCollision> _Collision)
		{
			AGateUnit* Gate = dynamic_cast<AGateUnit*>(_Collision->GetActor());

			if (nullptr == Gate)
			{
				MsgBoxAssert("충돌 대상이 Gate가 아닙니다.");
				return;
			}

			if (true == IsDown('Z'))
			{
				Gate->SetIsGateOpen(true);
				return;
			}
		});

	Collider->CollisionExit(ECollisionGroup::Gate, [=](std::shared_ptr<UCollision> _Collision)
		{
			AGateUnit* Gate = dynamic_cast<AGateUnit*>(_Collision->GetActor());

			if (nullptr == Gate)
			{
				MsgBoxAssert("충돌 대상이 Gate가 아닙니다.");
				return;
			}

			ButtonRenderer->SetActive(false);

			UEngineSound::SoundPlay("sfx_WorldMap_LevelSelect_BubbleDisappear.wav");
			Gate->SetIsGateOpen(false);
		});
}

void AWorldPlayer::WalkSoundPlay()
{
	int Random = UMath::RandomReturnInt(1, 5);
	UEngineSound::SoundPlay("sfx_WorldMap_Footstep_00" + std::to_string(Random) + ".wav");
}

void AWorldPlayer::WalkCheck(float _DeltaTime)
{
	if (true == IsPress(VK_UP)
		|| true == IsPress(VK_DOWN)
		|| true == IsPress(VK_LEFT)
		|| true == IsPress(VK_RIGHT)
		)
	{
		WalkDelayTime -= _DeltaTime;

		if (0.0f >= WalkDelayTime)
		{
			WalkDelayTime = WalkDelayTimeInit + WalkDelayTime;
			WalkSoundPlay();
		}
	}
	else
	{
		WalkDelayTime = 0.0f;
	}
}

void AWorldPlayer::RendererInit()
{
	Renderer->SetOrder(ERenderingOrder::Player);
	
	ButtonRenderer->SetSprite("overworld_zbutton.png");
	ButtonRenderer->SetAutoSize(1.0f, true);
	ButtonRenderer->SetOrder(ERenderingOrder::FrontFX);
	ButtonRenderer->SetPivot(EPivot::BOT);
	ButtonRenderer->SetPosition(float4(0.0f, 60.0f, 0.0f));
	ButtonRenderer->SetActive(false);
}