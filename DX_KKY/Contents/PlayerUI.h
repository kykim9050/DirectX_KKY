#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UImage;
class APlayer;
//class UUICalculator;
class APlayerBullet;
class APlayerSSBullet;
class APlayerUI : public AActor
{
	friend APlayer;
	friend APlayerBullet;
	friend APlayerSSBullet;
	//friend UUICalculator;
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
	UImage* LifeUI = nullptr;
	static int PlayerLife;
	static bool LifeInfoChange;

	std::vector<UImage*> SuperMeters = std::vector<UImage*>();

	static bool SuperMeterInfoChange;
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
	void SuperMeterUpdate();
	void SubLife();
	
	static void SuperMeterChargeEnd();
	static void SuperMeterCharging();

	inline static void SetLifeInfoChange()
	{
		LifeInfoChange = true;
	}
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

