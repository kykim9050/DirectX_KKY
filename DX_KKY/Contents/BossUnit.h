#pragma once
#include <EngineCore/StateManager.h>
#include "MonsterUnit.h"

// ���� :
class UDefaultSceneComponent;
class USpriteRenderer;
class ABossUnit : public AMonsterUnit
{
	GENERATED_BODY(AMonsterUnit)

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

