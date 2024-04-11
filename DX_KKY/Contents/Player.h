#pragma once
#include <EngineCore/Actor.h>

// ���� :
class UStateManager;
class USpriteRenderer;
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	inline USpriteRenderer* GetRenderer() const
	{
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	UStateManager State = UStateManager();

	float RunSpeed = 500.0f;

	void StateInit();
	void CreatePlayerAnimation();

	void IdleLeft(float _DeltaTime);
	void IdleRight(float _DeltaTime);
	void RunLeft(float _DeltaTime);
	void RunRight(float _DeltaTime);
		
	inline float GetRunSpeed() const
	{
		return RunSpeed;
	}
};

