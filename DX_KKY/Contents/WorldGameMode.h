#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class UCamera;
class AWorldPlayer;
class AMapBase;
class UImage;
class AWorldGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	AWorldGameMode();
	~AWorldGameMode();

	// delete Function
	AWorldGameMode(const AWorldGameMode& _Other) = delete;
	AWorldGameMode(AWorldGameMode&& _Other) noexcept = delete;
	AWorldGameMode& operator=(const AWorldGameMode& _Other) = delete;
	AWorldGameMode& operator=(AWorldGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private:
	UImage* OldFilm = nullptr;
	UImage* Iris = nullptr;

	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<AWorldPlayer> WPlayer;
	std::shared_ptr<AMapBase> MapLayer;
	std::shared_ptr<AMapBase> WorldMap;
	std::shared_ptr<AMapBase> WorldCollisionMap;

private:
	void WidgetInit();
	void WidgetStart();
	void CreateObject();
	void ObjectInit();
	void DeleteObject();
};

