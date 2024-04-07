#pragma once
#include "MapBase.h"

// Ό³Έν :
class ATutorialMap : public AMapBase
{
	GENERATED_BODY(AMapBase)

public:
	// constrcuter destructer
	ATutorialMap();
	~ATutorialMap();

	// delete Function
	ATutorialMap(const ATutorialMap& _Other) = delete;
	ATutorialMap(ATutorialMap&& _Other) noexcept = delete;
	ATutorialMap& operator=(const ATutorialMap& _Other) = delete;
	ATutorialMap& operator=(ATutorialMap&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

