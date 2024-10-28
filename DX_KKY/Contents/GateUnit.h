#pragma once
#include <EngineCore/Actor.h>

// ���� :
class AGateUnit : public AActor
{

public:
	// constrcuter destructer
	AGateUnit();
	~AGateUnit();

	// delete Function
	AGateUnit(const AGateUnit& _Other) = delete;
	AGateUnit(AGateUnit&& _Other) noexcept = delete;
	AGateUnit& operator=(const AGateUnit& _Other) = delete;
	AGateUnit& operator=(AGateUnit&& _Other) noexcept = delete;

	inline void SetIsGateOpen(bool _Value)
	{
		IsGateOpen = _Value;
	}
	inline bool GetIsGateOpen() const
	{
		return IsGateOpen;
	}

protected:

private:
	bool IsGateOpen = false;
};

