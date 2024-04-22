#pragma once

// 설명 :
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
	/// 인자의 Max값은 Enum의 Max 값에 해당.
	/// 내부에서 자동적으로 Max-1까지의 값만을 출력함
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

	float RandomReturnFloat(float _Min, float _Max)
	{
		float RandomValue = UEngineRandom::MainRandom.RandomFloat(_Min, _Max);
		return RandomValue;
	}

	float DirectionToDeg(const float4& _Direction);
	float DirectionToRad(const float4& _Direction);

public:
	float PI = static_cast<float>(std::atan(1) * 4);

protected:

private:
	// constrcuter destructer
	UMath();
	~UMath();
};

