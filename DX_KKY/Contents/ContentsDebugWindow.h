#pragma once
#include <EngineCore/EngineEditorWindow.h>

// Ό³Έν :
class UContentsDebugWindow : public UEngineEditorWindow
{
	GENERATED_BODY(UEngineEditorWindow)

public:
	// constrcuter destructer
	UContentsDebugWindow();
	~UContentsDebugWindow();

	// delete Function
	UContentsDebugWindow(const UContentsDebugWindow& _Other) = delete;
	UContentsDebugWindow(UContentsDebugWindow&& _Other) noexcept = delete;
	UContentsDebugWindow& operator=(const UContentsDebugWindow& _Other) = delete;
	UContentsDebugWindow& operator=(UContentsDebugWindow&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Tick(ULevel* Level, float _Delta) override;
	void OnGui(ULevel* Level, float _Delta) override;

private:

};

