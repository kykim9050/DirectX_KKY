#pragma once

// Ό³Έν :
class APlayer;
class APlayerSSBullet;
class APlayerBullet;
class UUICalculator
{
	friend APlayer;
	friend APlayerBullet;
	friend APlayerSSBullet;
public:

protected:

private:

private:
	// constrcuter destructer
	UUICalculator();
	~UUICalculator();

	static void SuperMeterChargingCheck();
	static void SuperMeterCharging();

};

