#pragma once

// 설명 :
class UMath
{
public:
	/// <summary>
	/// 인자의 Max값은 Enum의 Max 값에 해당.
	/// 내부에서 자동적으로 Max-1까지의 값만을 출력함
	/// </summary>
	/// <typeparam name="ENumType"></typeparam>
	/// <param name="_Min"></param>
	/// <param name="_Max"></param>
	/// <returns></returns>
	template <typename ENumType>
	static int RandomReturnIntEnum(int _Min, ENumType _Max)
	{
		return RandomReturnInt(_Min, static_cast<int>(_Max) - 1);
	}

	static int RandomReturnInt(int _Min, int _Max)
	{
		int RandomValue = UEngineRandom::MainRandom.RandomInt(_Min, _Max);

		return RandomValue;
	}

	static float RandomReturnFloat(float _Min, float _Max)
	{
		float RandomValue = UEngineRandom::MainRandom.RandomFloat(_Min, _Max);
		return RandomValue;
	}

	static float DirectionToDeg(const float4& _Direction);
	static float DirectionToRad(const float4& _Direction);

public:

protected:

private:
	static float PI;
	// constrcuter destructer
	UMath();
	~UMath();
};

