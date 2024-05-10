#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UImage;
class APlayer;
class APlayerUI : public AActor
{
	friend APlayer;
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
	static UImage* LifeUI;
	static int PlayerLife;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void UIInit();
	static void SubLife();
};

