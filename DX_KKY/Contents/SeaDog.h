#pragma once
#include <EngineCore/StateManager.h>

#include "MonsterUnit.h"

// Ό³Έν :
class ASeaDog
{
public:
	// constrcuter destructer
	ASeaDog();
	~ASeaDog();

	// delete Function
	ASeaDog(const ASeaDog& _Other) = delete;
	ASeaDog(ASeaDog&& _Other) noexcept = delete;
	ASeaDog& operator=(const ASeaDog& _Other) = delete;
	ASeaDog& operator=(ASeaDog&& _Other) noexcept = delete;

protected:

private:

};

