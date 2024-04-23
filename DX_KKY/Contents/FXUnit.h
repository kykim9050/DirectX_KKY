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

	inline void SetRendererAutoSize()
	{
		Renderer->SetAutoSize(1.0f, true);
	}
	template <typename EnumType>
	inline void SetRendererOrder(EnumType _Order)
	{
		Renderer->SetOrder(_Order);
	}
	inline void SetRendererFrameCallback(std::string_view _AnimationName, int _Index, std::function<void()> _Function)
	{
		Renderer->SetFrameCallback(_AnimationName, _Index, _Function);
	}

	void SetRendererPivot(EPivot _Pivot);
	void CreateAnimation(FAniInfo _Info, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	virtual void StateInit() {};


	USpriteRenderer* Renderer;
	UStateManager State = UStateManager();
private:

};

