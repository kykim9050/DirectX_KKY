#pragma once
#include "MonsterUnit.h"
#include "ParryUnit.h"

enum class EChaseType
{
	None,
	Temporal,
	Permanent,
};

// Ό³Έν :
class UCollision;
class USpriteRenderer;
class UDefaultSceneComponent;
class ABossAttackUnit : public AMonsterUnit, public UParryUnit
{
	GENERATED_BODY(AMonsterUnit)

public:
	// constrcuter destructer
	ABossAttackUnit();
	~ABossAttackUnit();

	// delete Function
	ABossAttackUnit(const ABossAttackUnit& _Other) = delete;
	ABossAttackUnit(ABossAttackUnit&& _Other) noexcept = delete;
	ABossAttackUnit& operator=(const ABossAttackUnit& _Other) = delete;
	ABossAttackUnit& operator=(ABossAttackUnit&& _Other) noexcept = delete;

	inline void SetChaseType(EChaseType _ChaseType, AActor* _Target)
	{
		ChaseType = _ChaseType;
		Target = _Target;
		Move = true;
	}
	inline void SetRendererAutoSize()
	{
		Renderer->SetAutoSize(1.0f, true);
	}
	template <typename EnumType>
	inline void SetRendererOrder(EnumType _Order)
	{
		Renderer->SetOrder(_Order);
	}
	inline void SetColScale(float4 _Scale)
	{
		Collider->SetScale(_Scale);
	}
	inline void SetColPosition(float4 _Pos)
	{
		Collider->SetPosition(_Pos);
	}
	template<typename EnumType>
	inline void SetColGroup(EnumType _Group)
	{
		Collider->SetCollisionGroup(_Group);
	}
	template<typename EnumType>
	inline void SetColType(EnumType _Type)
	{
		Collider->SetCollisionType(_Type);
	}
	inline USpriteRenderer* GetRenderer() const
	{
		return Renderer;
	}
	inline UCollision* GetCollider() const
	{
		return Collider;
	}
	inline void SetRendererFrameCallback(std::string_view _AnimationName, int _Index, std::function<void()> _Function)
	{
		Renderer->SetFrameCallback(_AnimationName, _Index, _Function);
	}
	inline void SetVelocityGenerator(std::function<float4()> _VelocityGenerator)
	{
		VelocityGenerator = _VelocityGenerator;
	}

	void SetRendererPivot(EPivot _Pivot);
	void CreateAnimation(FAniInfo _Info, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName);
	void CreateRevAnimation(FAniInfo _Info, bool _Loop, int _Start, int _End);

	virtual void StateInit() {};
	virtual void RendererInit() {};
	virtual void ColliderInit() {};
	virtual void AnimationInit() {};
	bool BoundaryCheck(float4 _Boundary, float OffsetX = 0.0f, float OffsetY = 0.0f);
	

protected:
	UCollision* Collider = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	EChaseType ChaseType = EChaseType::None;
	AActor* Target = nullptr;
	float4 BoundaryValue = float4::Zero;

	float4 Velocity = FVector::Zero;
	std::function<float4()> VelocityGenerator;
	bool Loop = false;
	bool Move = false;
	bool IsSetTargetDir = false;
};

