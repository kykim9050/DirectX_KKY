#pragma once
#include <EngineCore/Actor.h>


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
class ABossAttackUnit : public AActor
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

	inline void SetAutoSize()
	{
		Renderer->SetAutoSize(1.0f, true);
	}

	template <typename EnumType>
	inline void SetOrder(EnumType _Order)
	{
		Renderer->SetOrder(_Order);
	}

	void SetImgPivot(EPivot _Pivot);
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

