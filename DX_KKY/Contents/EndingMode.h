#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class AEndingMode : public AGameMode
{
public:
	// constrcuter destructer
	AEndingMode();
	~AEndingMode();

	// delete Function
	AEndingMode(const AEndingMode& _Other) = delete;
	AEndingMode(AEndingMode&& _Other) noexcept = delete;
	AEndingMode& operator=(const AEndingMode& _Other) = delete;
	AEndingMode& operator=(AEndingMode&& _Other) noexcept = delete;

protected:

private:

};

