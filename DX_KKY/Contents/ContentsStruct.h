#pragma once
#include <string>


struct FAniInfo
{
public:
	FAniInfo(std::string_view _AnimationName, std::string_view _SpriteName, float _InterTime)
		: AnimationName(_AnimationName)
		, SpriteName(_SpriteName)
		, InterTime(_InterTime)
	{

	}

	std::string AnimationName;
	std::string SpriteName;
	float InterTime;
};