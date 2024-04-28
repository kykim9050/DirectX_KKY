#pragma once
#include "MonsterUnit.h"
#include <EngineCore/StateManager.h>

// ���� :
class UDefaultSceneComponent;
class USpriteRenderer;
class UCollision;
class ACaptainBrineybeardPhase1 : public AMonsterUnit
{
	GENERATED_BODY(AMonsterUnit)
public:
	// constrcuter destructer
	ACaptainBrineybeardPhase1();
	~ACaptainBrineybeardPhase1();

	// delete Function
	ACaptainBrineybeardPhase1(const ACaptainBrineybeardPhase1& _Other) = delete;
	ACaptainBrineybeardPhase1(ACaptainBrineybeardPhase1&& _Other) noexcept = delete;
	ACaptainBrineybeardPhase1& operator=(const ACaptainBrineybeardPhase1& _Other) = delete;
	ACaptainBrineybeardPhase1& operator=(ACaptainBrineybeardPhase1&& _Other) noexcept = delete;

protected:

private:
	UStateManager State;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* ShipRenderer = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	//void DebugUpdate();

	void RendererInit();
	void AnimationInit();
	void CreateAnimation();
	//void SetAnimationCallback();
	//void ColliderInit();

	//void StateInit();
	//void StateCreate();
	//void StartFunctionSet();
	//void UpdateFunctionSet();
	//void EndFunctionSet();


};
