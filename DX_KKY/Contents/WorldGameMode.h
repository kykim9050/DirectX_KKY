#pragma once
#include <EngineCore/GameMode.h>

// ���� :
class UCamera;
class AWorldPlayer;
class AMapBase;
class UImage;
class AFlowerLevelGate;
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

	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<AWorldPlayer> WPlayer = nullptr;
	std::shared_ptr<AMapBase> MapLayer = nullptr;
	std::shared_ptr<AMapBase> WorldMap = nullptr;
	std::shared_ptr<AMapBase> WorldCollisionMap = nullptr;
	std::shared_ptr<AFlowerLevelGate> FlowerLevelGate = nullptr;

private:
	void WidgetInit();
	void WidgetStart();
	void CreateObject();
	void ObjectInit();
	void DeleteObject();
	void PermanentObjectCreate();
};

