#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class UEngineRandom;


class APlatformShadow;
class AFlowerPlatform;
class UCamera;
class AOldFilmEffect;
class APlayer;
class ACagneyCarnation;
class AMapBase;
class AFlowerLevelMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	AFlowerLevelMode();
	~AFlowerLevelMode();

	// delete Function
	AFlowerLevelMode(const AFlowerLevelMode& _Other) = delete;
	AFlowerLevelMode(AFlowerLevelMode&& _Other) noexcept = delete;
	AFlowerLevelMode& operator=(const AFlowerLevelMode& _Other) = delete;
	AFlowerLevelMode& operator=(AFlowerLevelMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private:
	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<AOldFilmEffect> OldFilm;
	std::shared_ptr<APlayer> Player;
	std::shared_ptr<ACagneyCarnation> BossMonster;
	std::shared_ptr<AMapBase> MapFrontObject;
	std::shared_ptr<AMapBase> Map;
	std::shared_ptr<AMapBase> BackGroundObject;
	std::shared_ptr<AMapBase> ColMap;

	std::shared_ptr<AFlowerPlatform> Platform1;
	std::shared_ptr<AFlowerPlatform> Platform2;
	std::shared_ptr<AFlowerPlatform> Platform3;
	std::vector<std::shared_ptr<APlatformShadow>> Shadows;

	std::shared_ptr<UEngineRandom> Random;

	int ShadowNum = 3;
};

