#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AGateUnit : public AActor
{

public:
	// constrcuter destructer
	AGateUnit();
	~AGateUnit();

	// delete Function
	AGateUnit(const AGateUnit& _Other) = delete;
	AGateUnit(AGateUnit&& _Other) noexcept = delete;
	AGateUnit& operator=(const AGateUnit& _Other) = delete;
	AGateUnit& operator=(AGateUnit&& _Other) noexcept = delete;

protected:

private:

};

