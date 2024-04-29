#include "PreCompile.h"

#include "OctopusBullet.h"

AOctopusBullet::AOctopusBullet()
{
	DefineParryableUnit();
}

AOctopusBullet::~AOctopusBullet()
{
}

void AOctopusBullet::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	RendererInit();
	ColliderInit();
	StateInit();
}

void AOctopusBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AOctopusBullet::StateInit()
{
	{
		State.CreateState("Init");
		State.CreateState("Fire");
		State.CreateState("Death");
	}

	{
		State.SetStartFunction("Init", [this]() {});
		State.SetStartFunction("Fire", [this]()
			{
				float4 PlayerPos = UContentsFunction::GetStagePlayer()->GetActorLocation();
				float4 BulletPos = GetActorLocation();
				float4 TargetDir = (PlayerPos - BulletPos).Normalize2DReturn();

				ResVelocity = TargetDir * BulletSpeed;
				SetSpeedVec(ResVelocity);

				float Theta = UMath::GetInst().DirectionToDeg(TargetDir);
				SetActorRotation(float4(0.0f, 0.0f, Theta + 180.0f));

				Renderer->ChangeAnimation(PirateBossAniName::OctoBullet + Color);
			});
	}	State.SetStartFunction("Death", [this]()
		{
			SetSpeedVec(float4::Zero);
			Renderer->ChangeAnimation(PirateBossAniName::OctoBullet_Effect + Color);
		});

	{
		State.SetUpdateFunction("Init", [this](float)
			{
				State.ChangeState("Fire");
			});
		State.SetUpdateFunction("Fire", std::bind(&AOctopusBullet::Fire, this, std::placeholders::_1));
		State.SetUpdateFunction("Death", [this](float) {});
	}

	State.ChangeState("Init");
}

void AOctopusBullet::RendererInit()
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterBullet);
}

void AOctopusBullet::ColliderInit()
{
	Collision->SetScale(float4(32.0f, 32.0f, 1.0f));
	Collision->SetCollisionGroup(ECollisionGroup::MonsterBullet);
	Collision->SetCollisionType(ECollisionType::Rect);
}

void AOctopusBullet::AnimationInit()
{
	Renderer->CreateAnimation(PirateBossAniName::OctoBullet + Color, "OctoBullet" + Color, 0.0678f);
	Renderer->CreateAnimation(PirateBossAniName::OctoBullet_Effect + Color, "OctoBullet_Effect" + Color, 0.0416f, false);

	Renderer->SetLastFrameCallback(PirateBossAniName::OctoBullet_Effect + Color, [this]()
		{
			Destroy();
		});
}

void AOctopusBullet::DefineParryableUnit()
{
	// 75% 확률로 Parryable 이 된다
	RandomValue = UMath::GetInst().RandomReturnInt(0, 3);

	if (NOT_DEFINE == RandomValue)
	{
		MsgBoxAssert("OctopusBullet의 색이 정상적으로 지정되지 않았습니다.");
		return;
	}

	if (UNPARRYABLE_VALUE == RandomValue)
	{
		Color = "_Yellow";
		return;
	}
	else
	{
		Color = "_Pink";
		SetParryableObject();
		return;
	}
}

void AOctopusBullet::Fire(float _DeltaTime)
{
	if (true == BoundaryCheck(BoundaryValue))
	{
		State.ChangeState("Death");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}