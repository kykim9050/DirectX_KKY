#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UMoveUnit : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	UMoveUnit();
	~UMoveUnit();

	// delete Function
	UMoveUnit(const UMoveUnit& _Other) = delete;
	UMoveUnit(UMoveUnit&& _Other) noexcept = delete;
	UMoveUnit& operator=(const UMoveUnit& _Other) = delete;
	UMoveUnit& operator=(UMoveUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

