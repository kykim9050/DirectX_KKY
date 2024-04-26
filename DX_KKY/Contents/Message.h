#pragma once
#include <EngineCore/Image.h>
#include <EngineCore/Actor.h>


// Ό³Έν :
class UImage;
class UStateManager;
class AMessage : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AMessage();
	~AMessage();

	// delete Function
	AMessage(const AMessage& _Other) = delete;
	AMessage(AMessage&& _Other) noexcept = delete;
	AMessage& operator=(const AMessage& _Other) = delete;
	AMessage& operator=(AMessage&& _Other) noexcept = delete;

protected:

private:
	UImage* Message = nullptr;
	UStateManager State;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void ImageInit();
	void AnimationInit();
	void StateInit();
};

