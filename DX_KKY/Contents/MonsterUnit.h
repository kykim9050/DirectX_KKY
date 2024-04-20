#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AMonsterUnit : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AMonsterUnit();
	~AMonsterUnit();

	// delete Function
	AMonsterUnit(const AMonsterUnit& _Other) = delete;
	AMonsterUnit(AMonsterUnit&& _Other) noexcept = delete;
	AMonsterUnit& operator=(const AMonsterUnit& _Other) = delete;
	AMonsterUnit& operator=(AMonsterUnit&& _Other) noexcept = delete;

	virtual void GetHit(int _DmgVal) = 0;

protected:
	int Hp = 0;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	inline void SetHp(int _Hp)
	{
		Hp = _Hp;
	}

private:
};

