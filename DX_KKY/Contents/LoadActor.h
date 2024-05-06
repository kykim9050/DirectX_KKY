#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UDefaultSceneComponent;
class USpriteRenderer;
class ALoadActor : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ALoadActor();
	~ALoadActor();

	// delete Function
	ALoadActor(const ALoadActor& _Other) = delete;
	ALoadActor(ALoadActor&& _Other) noexcept = delete;
	ALoadActor& operator=(const ALoadActor& _Other) = delete;
	ALoadActor& operator=(ALoadActor&& _Other) noexcept = delete;

protected:

private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* HourglassRenderer = nullptr;
	USpriteRenderer* BackGroundRenderer = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CreateObject();
	void RendererInit();
	void AnimationInit();
};

