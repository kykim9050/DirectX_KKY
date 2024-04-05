#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;

class ATitleAnimation : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATitleAnimation();
	~ATitleAnimation();

	// delete Function
	ATitleAnimation(const ATitleAnimation& _Other) = delete;
	ATitleAnimation(ATitleAnimation&& _Other) noexcept = delete;
	ATitleAnimation& operator=(const ATitleAnimation& _Other) = delete;
	ATitleAnimation& operator=(ATitleAnimation&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;

};

