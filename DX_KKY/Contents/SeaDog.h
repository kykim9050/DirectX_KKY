#pragma once
#include <EngineCore/StateManager.h>

#include "MonsterUnit.h"

// Ό³Έν :
class USpriteRenderer;
class UCollision;
class UDefaultSceneComponent;
class ASeaDog : public AMonsterUnit
{
	GENERATED_BODY(AMonsterUnit)
public:
	// constrcuter destructer
	ASeaDog();
	~ASeaDog();

	// delete Function
	ASeaDog(const ASeaDog& _Other) = delete;
	ASeaDog(ASeaDog&& _Other) noexcept = delete;
	ASeaDog& operator=(const ASeaDog& _Other) = delete;
	ASeaDog& operator=(ASeaDog&& _Other) noexcept = delete;

protected:

private:
	UStateManager State;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* SeaDogRenderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	USpriteRenderer* ScopeRenderer = nullptr;
	UCollision* MainCollider = nullptr;
	
	float JumpSpeed = 1600.0f;
	float Appear1Speed = 550.0f;
	float Appear2Speed = 1000.0f;
	float PixelCheckOffset = 75.0f;
	float FirstAppearXBoundary = 800.0f;
	float MoveSpeed = 600.0f;
	float DestroyBoundaryXValue = -200.0f;
	float DestroyBoundaryYValue = -100.0f;
	float UpSpeed = 500.0f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();
	void ColliderInit();

	void CalGravityVec(float _DeltaTime) override;

	// State
	void StateInit();
	void Appear_Step1(float _DeltaTime);
	void Appear_Step2(float _DeltaTime);
	void Move(float _DeltaTime);
	void Death(float _DeltaTime);
};

