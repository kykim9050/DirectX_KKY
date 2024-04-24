#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class APlatformShadow : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	APlatformShadow();
	~APlatformShadow();

	// delete Function
	APlatformShadow(const APlatformShadow& _Other) = delete;
	APlatformShadow(APlatformShadow&& _Other) noexcept = delete;
	APlatformShadow& operator=(const APlatformShadow& _Other) = delete;
	APlatformShadow& operator=(APlatformShadow&& _Other) noexcept = delete;

protected:

private:
	USpriteRenderer* Renderer = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

