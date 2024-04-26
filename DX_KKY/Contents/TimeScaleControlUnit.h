#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UTimeScaleControlUnit : public AActor, public std::enable_shared_from_this<UTimeScaleControlUnit>
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	UTimeScaleControlUnit();
	~UTimeScaleControlUnit();

	// delete Function
	UTimeScaleControlUnit(const UTimeScaleControlUnit& _Other) = delete;
	UTimeScaleControlUnit(UTimeScaleControlUnit&& _Other) noexcept = delete;
	UTimeScaleControlUnit& operator=(const UTimeScaleControlUnit& _Other) = delete;
	UTimeScaleControlUnit& operator=(UTimeScaleControlUnit&& _Other) noexcept = delete;

	inline static std::shared_ptr<UTimeScaleControlUnit> GetTimeController()
	{
		return TimeController;
	}
	inline void RecoveryTimeScale()
	{
		DelayCallBack(0.5f, []()
			{
				for (int i = 0; i < static_cast<int>(EActorType::Max); i++)
				{
					GEngine->SetOrderTimeScale(i, 1.0f);
				}
			});
	}

protected:


private:
	static std::shared_ptr<UTimeScaleControlUnit> TimeController;

	inline void SetTimeController(std::shared_ptr<UTimeScaleControlUnit> _TimeController)
	{
		TimeController = _TimeController;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

