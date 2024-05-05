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

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CreatePeriscope();
	void CreateSeaDogs();
};

