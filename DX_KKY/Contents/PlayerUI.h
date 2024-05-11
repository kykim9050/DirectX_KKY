#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UImage;
class APlayer;
class UUICalculator;
class APlayerUI : public AActor
{
	friend APlayer;
	friend UUICalculator;
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	APlayerUI();
	~APlayerUI();

	// delete Function
	APlayerUI(const APlayerUI& _Other) = delete;
	APlayerUI(APlayerUI&& _Other) noexcept = delete;
	APlayerUI& operator=(const APlayerUI& _Other) = delete;
	APlayerUI& operator=(APlayerUI&& _Other) noexcept = delete;


protected:

private:
	static UImage* LifeUI;
	static int PlayerLife;

	static std::vector<UImage*> SuperMeters;
	static int CurSuperMeterIdx;
	static int SuperMeterNum;
	static int ChargingCount;
	static int ChargingMaxCount;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;


	void UIInit();
	void LifeUIInit();
	void SuperMetersUIInit();
	void ResetSuperMeterInfo();
	
	static void SubLife();
	static void SuperMeterChargeEnd();

	inline static void AddChargingCount()
	{
		++ChargingCount;
	}
	inline static int GetChargingCount()
	{
		return ChargingCount;
	}
	inline static int GetChargingMaxCount()
	{
		return ChargingMaxCount;
	}
	inline static void ResetChargingCount()
	{
		ChargingCount = 0;
	}
};

