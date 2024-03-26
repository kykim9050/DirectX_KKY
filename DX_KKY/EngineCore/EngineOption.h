#pragma once
#include <EngineBase/EngineSerializer.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>
#include <sstream>
#include <iostream>
#include <format>

struct FEngineOption : public UEngineSerializeObject
{
public:
	FVector WindowScale = FVector::Zero;
	bool IsDebug = false;

	void Serialize(UEngineSerializer& _Ser) override
	{
		{
			std::string DebugOptionText;

			DebugOptionText += std::format("WindowScale : {}, {}\n", WindowScale.iX(), WindowScale.iY());
			DebugOptionText += std::format("IsDebug : {}\n", IsDebug);

			_Ser.WriteText(DebugOptionText);
		}
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		std::string OptionText = _Ser.ToString();
	}

};

