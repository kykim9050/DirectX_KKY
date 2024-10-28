#pragma once

// ���� :
class UMath
{
public:
	/// <summary>
	/// ������ Max���� Enum�� Max ���� �ش�.
	/// ���ο��� �ڵ������� Max-1������ ������ �����
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

