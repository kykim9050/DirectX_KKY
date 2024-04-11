#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class AMapBase : public AActor , public UNameObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AMapBase();
	~AMapBase();

	// delete Function
	AMapBase(const AMapBase& _Other) = delete;
	AMapBase(AMapBase&& _Other) noexcept = delete;
	AMapBase& operator=(const AMapBase& _Other) = delete;
	AMapBase& operator=(AMapBase&& _Other) noexcept = delete;

	inline FVector GetMapScale()
	{
		return GetActorTransform().GetScale();
	}

	void SetMapFile(std::string_view _MapFileName);
	void SetMapScale(FVector _Scale);

	void SetAutoScale();

	template<typename EnumType>
	void SetOrdering(EnumType _Order)
	{
		SetOrdering(static_cast<int>(_Order));
	}

	void SetOrdering(int _Order);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
};

