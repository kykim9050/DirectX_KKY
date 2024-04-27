#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APirateLevelMode;
class USpriteRenderer;
class UDefaultSceneComponent;
class APirateLevelMap : public AActor
{
	GENERATED_BODY(AActor)

	friend APirateLevelMode;
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
	float AccTime = 0.0f;

	USpriteRenderer* Wave1 = nullptr;
	USpriteRenderer* Wave2 = nullptr;
	USpriteRenderer* Wave3 = nullptr;
	USpriteRenderer* Wave4 = nullptr;
	USpriteRenderer* Dock = nullptr;
	USpriteRenderer* DockLog = nullptr;
	USpriteRenderer* DefaultSky = nullptr;
	USpriteRenderer* MovingCloud1 = nullptr;
	USpriteRenderer* MovingCloud2 = nullptr;
	USpriteRenderer* MovingCloud3 = nullptr;
	USpriteRenderer* ColMap = nullptr;

	UDefaultSceneComponent* Root = nullptr;


	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void AnimationInit();

	void CloudMoving(float _DeltaTime);

	inline void ReleaseColMapTexInfo() const
	{
		UContentsValue::ColMapTexture = nullptr;
	}
};

