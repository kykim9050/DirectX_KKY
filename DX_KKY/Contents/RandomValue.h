#pragma once

// Ό³Έν :
class URandomValue
{
public:


	// delete Function
	URandomValue(const URandomValue& _Other) = delete;
	URandomValue(URandomValue&& _Other) noexcept = delete;
	URandomValue& operator=(const URandomValue& _Other) = delete;
	URandomValue& operator=(URandomValue&& _Other) noexcept = delete;

	static URandomValue& GetInst()
	{
		static URandomValue Inst = URandomValue();
		return Inst;
	}


	template <typename ENumType>
	int RandomReturnInt(int _Min, ENumType _Max)
	{
		return RandomReturnInt(_Min, static_cast<int>(_Max));
	}

	int RandomReturnInt(int _Min, int _Max)
	{
		int RandomValue = UEngineRandom::MainRandom.RandomInt(_Min, _Max - 1);

		return RandomValue;
	}

protected:

private:
	// constrcuter destructer
	URandomValue();
	~URandomValue();
};

