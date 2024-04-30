#pragma once

// Ό³Έν :
class UPhaseUnit
{
public:
	// constrcuter destructer
	UPhaseUnit();
	~UPhaseUnit();

	// delete Function
	UPhaseUnit(const UPhaseUnit& _Other) = delete;
	UPhaseUnit(UPhaseUnit&& _Other) noexcept = delete;
	UPhaseUnit& operator=(const UPhaseUnit& _Other) = delete;
	UPhaseUnit& operator=(UPhaseUnit&& _Other) noexcept = delete;

	inline bool GetIsPhaseEnd() const
	{
		return IsPhaseEnd;
	}

protected:
	inline void SetIsPhaseEnd(bool _Value)
	{
		IsPhaseEnd = _Value;
	}

private:
	bool IsPhaseEnd = false;
};

