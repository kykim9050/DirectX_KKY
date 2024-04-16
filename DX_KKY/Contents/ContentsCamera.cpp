#include "PreCompile.h"
#include <EngineCore/Camera.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "ContentsCamera.h"
#include "OldFilmEffect.h"

UContentsCamera::UContentsCamera()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("CameraRoot");
	SetRoot(Root);
}

UContentsCamera::~UContentsCamera()
{
}

void UContentsCamera::BeginPlay()
{
	Super::BeginPlay();

	Camera = GetWorld()->GetMainCamera();
	OldFilm = GetWorld()->SpawnActor<AOldFilmEffect>("OldFilmEffect", static_cast<int>(EActorType::FilmEffect));

	Camera->SetActorLocation(UContentsValue::ContentsCameraInitPos);
	OldFilm->SetActorLocation(FVector{ UContentsValue::ContentsCameraInitXPos, UContentsValue::ContentsCameraInitYPos, 0.0f });
}

void UContentsCamera::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == GetisCameraMove())
	{
		CameraMove(_DeltaTime);
	}
}

void UContentsCamera::End()
{
	Super::End();
}

void UContentsCamera::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void UContentsCamera::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void UContentsCamera::CameraMove(float _DeltaTime)
{
	float4 PlayerPos = UContentsFunction::GetStagePlayer()->GetActorLocation();
	float4 CameraPos = Camera->GetActorLocation();
	PlayerPos.Y = 0.0f;
	PlayerPos.Z = 0.0f;
	CameraPos.Y = 0.0f;
	CameraPos.Z = 0.0f;


	float4 ChasePlayerVector = PlayerPos - CameraPos;

	if (1.0f >= ChasePlayerVector.Size3D())
	{
		return;
	}

	Camera->AddActorLocation(ChasePlayerVector.Normalize3DReturn() * _DeltaTime * 300.0f);
	OldFilm->AddActorLocation(ChasePlayerVector.Normalize3DReturn() * _DeltaTime * 300.0f);
}