#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class UDefaultSceneComponent;
class ACallSeaDogs : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ACallSeaDogs();
	~ACallSeaDogs();

	// delete Function
	ACallSeaDogs(const ACallSeaDogs& _Other) = delete;
	ACallSeaDogs(ACallSeaDogs&& _Other) noexcept = delete;
	ACallSeaDogs& operator=(const ACallSeaDogs& _Other) = delete;
	ACallSeaDogs& operator=(ACallSeaDogs&& _Other) noexcept = delete;

protected:

private:
	UDefaultSceneComponent* Root = nullptr;
	int SeaDogsNum = 4;
	float SeaDogInitDelay = 1.0f;
	float SeaDogAppearDelay = 1.5f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CreatePeriscope();
	void CreateSeaDogs();
};

