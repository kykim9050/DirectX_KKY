#pragma once
#include "MoveUnit.h"
#include <EngineCore/StateManager.h>

// Ό³Έν :
class UDefaultSceneComponent;
class USpriteRenderer;
class ABossUnit : public UMoveUnit
{
	GENERATED_BODY(UMoveUnit)

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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	virtual void StateInit() {};

	UDefaultSceneComponent* Root;
	USpriteRenderer* Renderer;
	UStateManager State = UStateManager();

private:
};

