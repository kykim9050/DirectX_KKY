#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class UDefaultSceneComponent;
class APirateLevelMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	APirateLevelMap();
	~APirateLevelMap();

	// delete Function
	APirateLevelMap(const APirateLevelMap& _Other) = delete;
	APirateLevelMap(APirateLevelMap&& _Other) noexcept = delete;
	APirateLevelMap& operator=(const APirateLevelMap& _Other) = delete;
	APirateLevelMap& operator=(APirateLevelMap&& _Other) noexcept = delete;

protected:

private:
	USpriteRenderer* Wave1 = nullptr;
	USpriteRenderer* Wave2 = nullptr;
	USpriteRenderer* Wave3 = nullptr;
	USpriteRenderer* Wave4 = nullptr;
	USpriteRenderer* Dock = nullptr;
	USpriteRenderer* DockLog = nullptr;

	UDefaultSceneComponent* Root = nullptr;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void AnimationInit();

};

