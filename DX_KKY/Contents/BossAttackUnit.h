#pragma once
#include <EngineCore/Actor.h>

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

	UCollision* Collider = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UDefaultSceneComponent* Root = nullptr;
};

