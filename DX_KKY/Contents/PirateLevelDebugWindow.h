#pragma once
#include <EngineCore/EngineEditorWindow.h>

// Ό³Έν :
class AShark;
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

protected:

private:
	void Init() override;
	void Tick(ULevel* Level, float _Delta) override;
	void OnGui(ULevel* Level, float _Delta) override;

	AShark* Shark = nullptr;
};

