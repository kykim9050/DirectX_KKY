#pragma once

// Ό³Έν :
class UMath
{
public:


	// delete Function
	UMath(const UMath& _Other) = delete;
	UMath(UMath&& _Other) noexcept = delete;
	UMath& operator=(const UMath& _Other) = delete;
	UMath& operator=(UMath&& _Other) noexcept = delete;

	static UMath& GetInst()
	{
		static UMath Inst = UMath();
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
	UMath();
	~UMath();
};

