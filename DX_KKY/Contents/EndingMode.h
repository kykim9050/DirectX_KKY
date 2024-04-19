#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class UCamera;
class AOldFilmEffect;
class AEndingAnimation;
class AEndingMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private:
	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<AOldFilmEffect> OldFilm;
	std::shared_ptr<AEndingAnimation> EndingAni;
};

