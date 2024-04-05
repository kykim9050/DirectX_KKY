#pragma once
#include <EngineCore/Actor.h>


class USpriteRenderer;
// Ό³Έν :
class AEndingAnimation : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AEndingAnimation();
	~AEndingAnimation();

	// delete Function
	AEndingAnimation(const AEndingAnimation& _Other) = delete;
	AEndingAnimation(AEndingAnimation&& _Other) noexcept = delete;
	AEndingAnimation& operator=(const AEndingAnimation& _Other) = delete;
	AEndingAnimation& operator=(AEndingAnimation&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;

};

