#pragma once
#include <EngineCore/Actor.h>

struct FFXAniInfo
{
public:
	FFXAniInfo(std::string_view _AnimationName, std::string_view _SpriteName, float _InterTime)
		: AnimationName(_AnimationName)
		, SpriteName(_SpriteName)
		, InterTime(_InterTime)
	{

	}

	std::string AnimationName;
	std::string SpriteName;
	float InterTime;
};

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

	void FXInit(ERenderingOrder _Order, FFXAniInfo _Info, bool _Loop = false);
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

