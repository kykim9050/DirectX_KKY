#pragma once
#include "MapBase.h"

// Ό³Έν :
class AMapSubObject : public AMapBase
{
	GENERATED_BODY(AMapBase)

public:
	// constrcuter destructer
	AMapSubObject();
	~AMapSubObject();

	// delete Function
	AMapSubObject(const AMapSubObject& _Other) = delete;
	AMapSubObject(AMapSubObject&& _Other) noexcept = delete;
	AMapSubObject& operator=(const AMapSubObject& _Other) = delete;
	AMapSubObject& operator=(AMapSubObject&& _Other) noexcept = delete;
	
	inline void SetMapSubObject(std::string_view _Filename)
	{
		SetMapFile(_Filename);
	}

	inline void SetMapSubObjectScale(FVector _Scale)
	{
		SetMapScale(_Scale);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

