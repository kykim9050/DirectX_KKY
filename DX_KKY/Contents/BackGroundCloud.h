#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class  ABackGroundCloud : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABackGroundCloud();
	~ABackGroundCloud();

	// delete Function
	ABackGroundCloud(const ABackGroundCloud& _Other) = delete;
	ABackGroundCloud(ABackGroundCloud&& _Other) noexcept = delete;
	ABackGroundCloud& operator=(const ABackGroundCloud& _Other) = delete;
	ABackGroundCloud& operator=(ABackGroundCloud&& _Other) noexcept = delete;

	void CloudMoving(float _DeltaTime);

protected:


private:
	USpriteRenderer* CloudRenderer = nullptr;
	float AccTime = 0.0f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();

};

