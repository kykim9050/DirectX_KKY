#include "PreCompile.h"

#include "Acorn.h"
#include "FXUnit.h"

AAcorn::AAcorn()
{
}

AAcorn::~AAcorn()
{
}

void AAcorn::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AAcorn::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AAcorn::StateInit()
{
	State.CreateState(FlowerBossState::Acorn_Init);
	State.CreateState(FlowerBossState::Acorn_Spawn);
	State.CreateState(FlowerBossState::Acorn_Fly);
	State.CreateState(FlowerBossState::Acorn_Death);

	State.SetStartFunction(FlowerBossState::Acorn_Init, []() {});
	State.SetStartFunction(FlowerBossState::Acorn_Spawn, [this]()
		{
			Renderer->ChangeAnimation(FlowerBossAniName::Acorn_Spawn);
		});
	State.SetStartFunction(FlowerBossState::Acorn_Fly, [this]()
		{
			AFXUnit* FlyEffect = GetWorld()->SpawnActor<AFXUnit>("FlyEffect").get();
			FlyEffect->CreateAnimation(FAniInfo(FlowerBossAniName::Acorn_Effect, GSpriteName::Acorn_Effect, 0.0416f), false);
			FlyEffect->SetRendererFrameCallback(FlowerBossAniName::Acorn_Effect, 8, [FlyEffect]()
				{
					FlyEffect->Destroy();
				});
			FlyEffect->SetActorLocation(GetActorLocation());
			FlyEffect->SetRendererAutoSize();
			FlyEffect->SetRendererOrder(ERenderingOrder::MonsterBulletFX);
			// Pivot Left로 바꾸어 주어야 함
			//FlyEffect->SetRendererPivot(EPivot::RIGHT);
			FlyEffect->ChangeAnimation(FlowerBossAniName::Acorn_Effect);


			BoundaryValue = GEngine->EngineWindow.GetWindowScale();

			float4 PlayerPos = UContentsFunction::GetStagePlayer()->GetActorLocation();
			float4 BulletPos = GetActorLocation();
			float4 TargetDir = (PlayerPos - BulletPos).Normalize2DReturn();

			ResVelocity = TargetDir * BulletSpeed;
			SetSpeedVec(ResVelocity);

			float Theta = UMath::DirectionToDeg(TargetDir);
			SetActorRotation(float4(0.0f, 0.0f, Theta + 180.0f));
			FlyEffect->SetActorRotation(float4(0.0f, 0.0f, Theta + 180.0f));

			Renderer->ChangeAnimation(FlowerBossAniName::Acorn_Fly);
		});
	State.SetStartFunction(FlowerBossState::Acorn_Death, [this]()
		{
			UEngineSoundPlayer Sound = UEngineSound::SoundPlay("sfx_flower_bullet_seed_poof.wav");
			Sound.SetVolume(0.5f);

			Collision->SetActive(false);
			Renderer->ChangeAnimation(FlowerBossAniName::Acorn_Death);
		});
	


	State.SetUpdateFunction(FlowerBossState::Acorn_Init, [this](float)
		{
			State.ChangeState(FlowerBossState::Acorn_Spawn);
			return;
		});
	State.SetUpdateFunction(FlowerBossState::Acorn_Spawn, [](float) {});
	State.SetUpdateFunction(FlowerBossState::Acorn_Fly, std::bind(&AAcorn::Flying, this, std::placeholders::_1));
	State.SetUpdateFunction(FlowerBossState::Acorn_Death, [](float) {});

	State.ChangeState(FlowerBossState::Acorn_Init);
}

void AAcorn::RendererInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterBullet);
}

void AAcorn::ColliderInit()
{
	Collision->SetScale(GColliderScale::Acorn_ColScale);
	Collision->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->SetPosition(float4(0.0f, 0.0f, 0.0f));
}

void AAcorn::AnimationInit()
{
	Renderer->CreateAnimation(FlowerBossAniName::Acorn_Spawn, GSpriteName::Acorn_Spawn, 0.034f);
	Renderer->CreateAnimation(FlowerBossAniName::Acorn_Fly, GSpriteName::Acorn_Fly, 0.034f);
	Renderer->CreateAnimation(FlowerBossAniName::Acorn_Death, GSpriteName::Acorn_Death, 0.0416f, false);

	Renderer->SetFrameCallback(FlowerBossAniName::Acorn_Death, 9, [this]()
		{
			Destroy();
		});
}

void AAcorn::Flying(float _DeltaTime)
{
	if (BoundaryCheck(BoundaryValue))
	{
		State.ChangeState(FlowerBossState::Acorn_Death);
		return;
	}
	
	ResultMovementUpdate(_DeltaTime);
}