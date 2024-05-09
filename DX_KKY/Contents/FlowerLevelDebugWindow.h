#pragma once
#include <EngineCore/EngineEditorWindow.h>

// Ό³Έν :
class UFlowerLevelDebugWindow : public UEngineEditorWindow
{
	GENERATED_BODY(UEngineEditorWindow)

public:
	// constrcuter destructer
	UFlowerLevelDebugWindow();
	~UFlowerLevelDebugWindow();

	// delete Function
	UFlowerLevelDebugWindow(const UFlowerLevelDebugWindow& _Other) = delete;
	UFlowerLevelDebugWindow(UFlowerLevelDebugWindow&& _Other) noexcept = delete;
	UFlowerLevelDebugWindow& operator=(const UFlowerLevelDebugWindow& _Other) = delete;
	UFlowerLevelDebugWindow& operator=(UFlowerLevelDebugWindow&& _Other) noexcept = delete;

	inline void ResetIsPhase2()
	{
		IsPhase2 = false;
	}
	inline void SetFunction(std::function<void(int)> _Function)
	{
		PhaseSetFunction = _Function;
	}

protected:

private:
	void Init() override;
	void Tick(ULevel* Level, float _Delta) override;
	void OnGui(ULevel* Level, float _Delta) override;

	bool IsPhase2 = false;

	std::function<void(int)> PhaseSetFunction = nullptr;
};

