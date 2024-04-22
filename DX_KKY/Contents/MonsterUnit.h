#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UMonsterUnit
{
public:
	// constrcuter destructer
	UMonsterUnit();
	~UMonsterUnit();

	// delete Function
	UMonsterUnit(const UMonsterUnit& _Other) = delete;
	UMonsterUnit(UMonsterUnit&& _Other) noexcept = delete;
	UMonsterUnit& operator=(const UMonsterUnit& _Other) = delete;
	UMonsterUnit& operator=(UMonsterUnit&& _Other) noexcept = delete;

	virtual void GetHit(int _DmgVal) {};

protected:

	int Hp = 0;
	inline void SetHp(int _Hp)
	{
		Hp = _Hp;
	}

private:
};

