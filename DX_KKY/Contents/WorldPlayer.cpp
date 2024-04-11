#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "WorldPlayer.h"
#include "WorldDust.h"

std::shared_ptr<AWorldPlayer> AWorldPlayer:: MainPlayer = std::shared_ptr<AWorldPlayer>();

AWorldPlayer::AWorldPlayer()
	: Dir(EWorldPlayerDir::RightDown)
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("PlayerRenderer");
	InputOn();
}

AWorldPlayer::~AWorldPlayer()
{
}

void AWorldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetMainPlayer(shared_from_this());

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
	static std::shared_ptr<UEngineTexture> CheckTexture = UContentsValue::ColMapTexture;
	
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

void AWorldPlayer::MakeDust()
{
	std::shared_ptr<AWorldDust> Dust = GetWorld()->SpawnActor<AWorldDust>("WorldDust", static_cast<int>(EActorType::Dust));
	
	Dust->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 25.0f));
}