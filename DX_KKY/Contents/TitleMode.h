#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/StateManager.h>

// 설명 :
class UCamera;
class ATitleAnimation;
class ATitleLogo;
class UImage;
class UContentsDebugWindow;
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
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<ATitleAnimation> TitleAni = nullptr;
	std::shared_ptr<ATitleLogo> TitleLogo = nullptr;
	
	UImage* OldFilm = nullptr;
	UImage* Iris = nullptr;

	UStateManager ModeState = UStateManager();

	std::shared_ptr<UContentsDebugWindow> DebugWindow;

private:
	void WidgetInit();
	void WidgetStart();
	void CreateObject();
	void DeleteObject();
	void CreateDebugWindow();

	// State 관련
	void StateInit();
	void Idle(float _DeltaTime);
};

