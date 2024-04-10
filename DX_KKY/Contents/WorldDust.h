#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class AWorldDust : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AWorldDust();
	~AWorldDust();

	// delete Function
	AWorldDust(const AWorldDust& _Other) = delete;
	AWorldDust(AWorldDust&& _Other) noexcept = delete;
	AWorldDust& operator=(const AWorldDust& _Other) = delete;
	AWorldDust& operator=(AWorldDust&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

	USpriteRenderer* Renderer = nullptr;
};

