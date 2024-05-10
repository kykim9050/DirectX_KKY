#pragma once
#include <EngineCore/EngineEditorWindow.h>

// Ό³Έν :
class UPirateLevelDebugWindow : public UEngineEditorWindow
{
	GENERATED_BODY(UEngineEditorWindow)

public:
	// constrcuter destructer
	UPirateLevelDebugWindow();
	~UPirateLevelDebugWindow();

	// delete Function
	UPirateLevelDebugWindow(const UPirateLevelDebugWindow& _Other) = delete;
	UPirateLevelDebugWindow(UPirateLevelDebugWindow&& _Other) noexcept = delete;
	UPirateLevelDebugWindow& operator=(const UPirateLevelDebugWindow& _Other) = delete;
	UPirateLevelDebugWindow& operator=(UPirateLevelDebugWindow&& _Other) noexcept = delete;


	inline void ResetIsPhase2()
	{
		IsPhase2 = false;
	}
	inline void SetSharkAppearFunction(std::function<void()> _Function)
	{
		SharkAppearFunction = _Function;
	}
	inline void SetSeaDogAppearFunction(std::function<void()> _Function)
	{
		SeaDogAppearFunction = _Function;
	}
	inline void SetOtherSetFunction(std::function<void(int)> _Function)
	{
		OtherSetFunction = _Function;
	}


protected:

private:
	std::function<void()> SharkAppearFunction = nullptr;
	std::function<void()> SeaDogAppearFunction = nullptr;
	std::function<void(int)> OtherSetFunction = nullptr;

	bool IsPhase2 = false;

private:
	void Init() override;
	void Tick(ULevel* Level, float _Delta) override;
	void OnGui(ULevel* Level, float _Delta) override;

};

