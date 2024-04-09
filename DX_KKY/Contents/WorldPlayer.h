#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class AWorldPlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AWorldPlayer();
	~AWorldPlayer();

	// delete Function
	AWorldPlayer(const AWorldPlayer& _Other) = delete;
	AWorldPlayer(AWorldPlayer&& _Other) noexcept = delete;
	AWorldPlayer& operator=(const AWorldPlayer& _Other) = delete;
	AWorldPlayer& operator=(AWorldPlayer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CreatePlayerAnimation();

	void StateInit();
	void Idle(float _DeltaTime);

private:
	void KeyCheck(float _DeltaTime);

	inline float GetSpeed() const
	{
		return Speed;
	}

	UStateManager State = UStateManager();
	USpriteRenderer* Renderer;
	float Speed = 200.0f;

	EWorldPlayerDir Dir = EWorldPlayerDir::None;
};

