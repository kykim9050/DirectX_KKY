#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UImage;
class APlayerUI : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayerUI();
	~APlayerUI();

	// delete Function
	APlayerUI(const APlayerUI& _Other) = delete;
	APlayerUI(APlayerUI&& _Other) noexcept = delete;
	APlayerUI& operator=(const APlayerUI& _Other) = delete;
	APlayerUI& operator=(APlayerUI&& _Other) noexcept = delete;

protected:

private:
	UImage* LifeUI = nullptr;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void UIInit();
};

