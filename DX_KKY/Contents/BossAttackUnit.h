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

	void Init(ERenderingOrder _Order, FAniInfo _Info, bool _Loop = false);
	void SetImgPivot(EPivot _Pivot);

	inline void SetChaseType(EChaseType _ChaseType, AActor* _Target)
	{
		ChaseType = _ChaseType;
		Target = _Target;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collider = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	EChaseType ChaseType = EChaseType::None;
	AActor* Target = nullptr;

	bool Loop = false;
};

