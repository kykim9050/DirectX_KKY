#pragma once
#include <EngineCore/StateManager.h>
#include <EngineCore/Actor.h>
#include "MonsterUnit.h"

// Ό³Έν :
class UDefaultSceneComponent;
class USpriteRenderer;
class ABossUnit : public AActor, public UMonsterUnit
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ABossUnit();
	~ABossUnit();

	// delete Function
	ABossUnit(const ABossUnit& _Other) = delete;
	ABossUnit(ABossUnit&& _Other) noexcept = delete;
	ABossUnit& operator=(const ABossUnit& _Other) = delete;
	ABossUnit& operator=(ABossUnit&& _Other) noexcept = delete;



protected:
	UDefaultSceneComponent* Root;
	USpriteRenderer* Renderer;
	UStateManager State = UStateManager();

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	virtual void StateInit() = 0;

private:
	

};

