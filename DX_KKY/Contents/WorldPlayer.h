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

	void UpIdle(float _DeltaTime);
	//void RightUpIdle(float _DeltaTime);
	void RightIdle(float _DeltaTime);
	void RightDownIdle(float _DeltaTime);
	void DownIdle(float _DeltaTime);
	//void LeftDownIdle(float _DeltaTime);
	void LeftIdle(float _DeltaTime);
	//void LeftUpIdle(float _DeltaTime);

	//void UpWalk(float _DeltaTime);
	//void RightUpWalk(float _DeltaTime);
	//void RightWalk(float _DeltaTime);
	//void RightDownWalk(float _DeltaTime);
	//void DownWalk(float _DeltaTime);
	//void LeftDownWalk(float _DeltaTime);
	//void LeftWalk(float _DeltaTime);
	//void LeftUpWalk(float _DeltaTime);


	inline float GetSpeed() const
	{
		return Speed;
	}

	UStateManager State = UStateManager();
	USpriteRenderer* Renderer;
	float Speed = 200.0f;

	EWorldPlayerDir Dir = EWorldPlayerDir::None;
};

