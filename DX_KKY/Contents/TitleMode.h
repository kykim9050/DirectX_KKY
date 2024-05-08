#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class UCamera;
class ATitleAnimation;
class ATitleLogo;
class UImage;
class ATitleMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATitleMode();
	~ATitleMode();

	// delete Function
	ATitleMode(const ATitleMode& _Other) = delete;
	ATitleMode(ATitleMode&& _Other) noexcept = delete;
	ATitleMode& operator=(const ATitleMode& _Other) = delete;
	ATitleMode& operator=(ATitleMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

private:
	std::shared_ptr<UCamera> Camera;
	std::shared_ptr<ATitleAnimation> TitleAni;
	std::shared_ptr<ATitleLogo> TitleLogo;
	
	UImage* OldFilm = nullptr;
	UImage* Iris = nullptr;

private:
	void WidgetInit();
	void WidgetStart();
	void CreateObject();
	void DeleteObject();
};

