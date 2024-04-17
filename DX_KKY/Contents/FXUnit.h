#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class UStateManager;
class AFXUnit : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AFXUnit();
	~AFXUnit();

	// delete Function
	AFXUnit(const AFXUnit& _Other) = delete;
	AFXUnit(AFXUnit&& _Other) noexcept = delete;
	AFXUnit& operator=(const AFXUnit& _Other) = delete;
	AFXUnit& operator=(AFXUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	virtual void StateInit() {};

	USpriteRenderer* Renderer;
	UStateManager State = UStateManager();

private:

};

