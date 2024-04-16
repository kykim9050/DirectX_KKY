#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class UContentsCamera : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	UContentsCamera();
	~UContentsCamera();

	// delete Function
	UContentsCamera(const UContentsCamera& _Other) = delete;
	UContentsCamera(UContentsCamera&& _Other) noexcept = delete;
	UContentsCamera& operator=(const UContentsCamera& _Other) = delete;
	UContentsCamera& operator=(UContentsCamera&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void End() override;

	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;


private:

};

