#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class UStateManager;
class ABulletFX : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ABulletFX();
	~ABulletFX();

	// delete Function
	ABulletFX(const ABulletFX& _Other) = delete;
	ABulletFX(ABulletFX&& _Other) noexcept = delete;
	ABulletFX& operator=(const ABulletFX& _Other) = delete;
	ABulletFX& operator=(ABulletFX&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateInit();
	void Spawn() {};

	USpriteRenderer* Renderer;
	UStateManager State = UStateManager();
};

