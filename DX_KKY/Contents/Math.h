#pragma once

// ���� :
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


	/// <summary>
	/// ������ Max���� Enum�� Max ���� �ش�.
	/// ���ο��� �ڵ������� Max-1������ ������ �����
	/// </summary>
	/// <typeparam name="ENumType"></typeparam>
	/// <param name="_Min"></param>
	/// <param name="_Max"></param>
	/// <returns></returns>
	template <typename ENumType>
	int RandomReturnIntEnum(int _Min, ENumType _Max)
	{
		return RandomReturnInt(_Min, static_cast<int>(_Max) - 1);
	}

	int RandomReturnInt(int _Min, int _Max)
	{
		int RandomValue = UEngineRandom::MainRandom.RandomInt(_Min, _Max);

		return RandomValue;
	}

protected:

private:
	// constrcuter destructer
	UMath();
	~UMath();
};
