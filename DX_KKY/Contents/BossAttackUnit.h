#pragma once
#include <EngineCore/Actor.h>
#include "MonsterUnit.h"

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
class ABossAttackUnit : public AActor , public UMonsterUnit
{
	GENERATED_BODY(AActor)

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

	void SetRendererPivot(EPivot _Pivot);
	void CreateAnimation(FAniInfo _Info, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName);


protected:
	UCollision* Collider = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

	EChaseType ChaseType = EChaseType::None;
	AActor* Target = nullptr;

	bool Loop = false;
};

