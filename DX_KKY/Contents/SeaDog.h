#pragma once
#include <EngineCore/StateManager.h>

#include "MonsterUnit.h"

// ���� :
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
	//UStateManager State;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* SeaDogRenderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	USpriteRenderer* ScopeRenderer = nullptr;
	UCollision* MainCollider = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void AnimationInit();
	void CreateAnimation();
	void SetAnimationCallback();
	void ColliderInit();


	// State
	void StateInit();
};
