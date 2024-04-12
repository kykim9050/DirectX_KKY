#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "WorldPlayer.h"
#include "WorldDust.h"
#include "WorldGameMode.h"
#include "OldFilmEffect.h"

std::shared_ptr<AWorldPlayer> AWorldPlayer:: MainPlayer = std::shared_ptr<AWorldPlayer>();

AWorldPlayer::AWorldPlayer()
	: Dir(EWorldPlayerDir::RightDown)
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("PlayerRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
	Renderer->SetupAttachment(Root);

	InputOn();
}

AWorldPlayer::~AWorldPlayer()
{
}

void AWorldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetMainPlayer(shared_from_this());
	Renderer->SetOrder(ERenderingOrder::Player);

	CreatePlayerAnimation();
	StateInit();
}

void AWorldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
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
	case EWorldPlayerDir::Up:
		Pos.Y = Pos.Y - CheckOffset;
		break;
	case EWorldPlayerDir::RightUp:
		Pos.X = Pos.X + CheckOffset;
		Pos.Y = Pos.Y - CheckOffset;
		break;
	case EWorldPlayerDir::Right:
		Pos.X = Pos.X + CheckOffset;
		break;
	case EWorldPlayerDir::RightDown:
		Pos.X = Pos.X + CheckOffset;
		Pos.Y = Pos.Y + CheckOffset;
		break;
	case EWorldPlayerDir::Down:
		Pos.Y = Pos.Y + CheckOffset;
		break;
	case EWorldPlayerDir::LeftDown:
		Pos.X = Pos.X - CheckOffset;
		Pos.Y = Pos.Y + CheckOffset;
		break;
	case EWorldPlayerDir::Left:
		Pos.X = Pos.X - CheckOffset;
		break;
	case EWorldPlayerDir::LeftUp:
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
	AWorldGameMode::GetOldFilm()->AddActorLocation(ChasePlayerVector.Normalize3DReturn() * _DeltaTime * 300.0f);
}