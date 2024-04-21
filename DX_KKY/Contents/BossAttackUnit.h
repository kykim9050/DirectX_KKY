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

	void SetImgPivot(EPivot _Pivot);

	inline void SetChaseType(EChaseType _ChaseType, AActor* _Target)
	{
		ChaseType = _ChaseType;
		Target = _Target;
	}

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

