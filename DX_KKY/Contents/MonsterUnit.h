#pragma once
//#include <EngineCore/Actor.h>
#include "MoveUnit.h"

// Ό³Έν :
class AMonsterUnit : public UMoveUnit
{
	GENERATED_BODY(UMoveUnit)

public:
	// constrcuter destructer
	AMonsterUnit();
	~AMonsterUnit();

	// delete Function
	AMonsterUnit(const AMonsterUnit& _Other) = delete;
	AMonsterUnit(AMonsterUnit&& _Other) noexcept = delete;
	AMonsterUnit& operator=(const AMonsterUnit& _Other) = delete;
	AMonsterUnit& operator=(AMonsterUnit&& _Other) noexcept = delete;

	virtual void GetHit(int _DmgVal) {};

	inline void SetGetHitFunction(std::function<void()> _Function)
	{
		GetHitFunction = _Function;
		GetHitUse = true;
	}

	inline void SetHp(int _Hp)
	{
		Hp = _Hp;
	}
	inline int GetHp() const
	{
		return Hp;
	}
	inline void AddHp(int _Value)
	{
		Hp += _Value;
	}
	inline void SubHp(int _Value)
	{
		Hp -= _Value;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int Hp = 0;
	bool GetHitUse = false;

	std::function<void()> GetHitFunction = nullptr;
};

