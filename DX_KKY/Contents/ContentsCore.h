#pragma once
#include <EngineCore/EngineCore.h>

// Ό³Έν :
class UContentsDebugWindow;
class UContentsCore : public UserCore
{
public:
	// constrcuter destructer
	UContentsCore();
	~UContentsCore();

	// delete Function
	UContentsCore(const UContentsCore& _Other) = delete;
	UContentsCore(UContentsCore&& _Other) noexcept = delete;
	UContentsCore& operator=(const UContentsCore& _Other) = delete;
	UContentsCore& operator=(UContentsCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;

private:
	std::shared_ptr<UContentsDebugWindow> DebugWindow;

	void CreateDebugWindow();
	void LoadingLevelStart();
};

