#pragma once

// Ό³Έν :
class UParryUnit
{
public:
	// constrcuter destructer
	UParryUnit();
	~UParryUnit();

	// delete Function
	UParryUnit(const UParryUnit& _Other) = delete;
	UParryUnit(UParryUnit&& _Other) noexcept = delete;
	UParryUnit& operator=(const UParryUnit& _Other) = delete;
	UParryUnit& operator=(UParryUnit&& _Other) noexcept = delete;

	inline bool GetParryableObject() const
	{
		return ParryableObject;
	}

protected:
	inline void SetParryableObject()
	{
		ParryableObject = true;
	}

private:
	bool ParryableObject = false;
};

