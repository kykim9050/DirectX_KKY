#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class UDefaultSceneComponent;
class AFXBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AFXBase();
	~AFXBase();

	// delete Function
	AFXBase(const AFXBase& _Other) = delete;
	AFXBase(AFXBase&& _Other) noexcept = delete;
	AFXBase& operator=(const AFXBase& _Other) = delete;
	AFXBase& operator=(AFXBase&& _Other) noexcept = delete;

	void FXInit(ERenderingOrder _Order, FAniInfo _Info, bool _Loop = false);
	void SetImgDir(EEngineDir _ImgDir);
	void FXDestroy();
	void SetImgPivot(EPivot _Pivot);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void FXDestroyCheck();

	UDefaultSceneComponent* Root;
	USpriteRenderer* Renderer;

private:
	bool Loop = false;

};

