#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATutorialMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATutorialMode();
	~ATutorialMode();

	// delete Function
	ATutorialMode(const ATutorialMode& _Other) = delete;
	ATutorialMode(ATutorialMode&& _Other) noexcept = delete;
	ATutorialMode& operator=(const ATutorialMode& _Other) = delete;
	ATutorialMode& operator=(ATutorialMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private:

};

