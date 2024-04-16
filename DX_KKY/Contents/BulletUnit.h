#pragma once
#include "MoveUnit.h"

// Ό³Έν :
class ABulletUnit : public UMoveUnit
{
	GENERATED_BODY(UMoveUnit)

public:
	// constrcuter destructer
	ABulletUnit();
	~ABulletUnit();

	// delete Function
	ABulletUnit(const ABulletUnit& _Other) = delete;
	ABulletUnit(ABulletUnit&& _Other) noexcept = delete;
	ABulletUnit& operator=(const ABulletUnit& _Other) = delete;
	ABulletUnit& operator=(ABulletUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:


};

