#pragma once
#include "MoveUnit.h"
#include <EngineCore/StateManager.h>

// ���� :
class UCollision;
class USpriteRenderer;
class ABulletUnit : public UMoveUnit
{
	GENERATED_BODY(UMoveUnit)

public:
	// constrcuter destructer
	ABulletUnit();
	~ABulletUnit();

	// delete Function
	ABulletUnit(const ABulletUnit& _Other) = delete;
	ABulletUnit(ABulletUnit&& _Other) noexcept = delete;
	ABulletUnit& operator=(const ABulletUnit& _Other) = delete;
	ABulletUnit& operator=(ABulletUnit&& _Other) noexcept = delete;

	inline float4 GetHorizontalDir() const
	{
		return HorizontalDir;
	}
	inline void SetHorizontalDir(float4 _Dir)
	{
		HorizontalDir = _Dir;
	}
	inline float4 GetVerticalDir() const
	{
		return VerticalDir;
	}
	inline void SetVerticalDir(float4 _Dir)
	{
		VerticalDir = _Dir;
	}
	inline int GetDamage() const
	{
		return Damage;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void StateInit() {};
	
	inline float GetHorizontalSpeed() const
	{
		return HorizontalSpeed;
	}
	inline void SetHorizontalSpeed(float _Speed)
	{
		HorizontalSpeed = _Speed;
	}
	inline float GetVerticalSpeed() const
	{
		return VerticalSpeed;
	}
	inline void SetVerticalSpeed(float _Speed)
	{
		VerticalSpeed = _Speed;
	}

	inline void SetDamage(int _DmgVal)
	{
		Damage = _DmgVal;
	}

	USpriteRenderer* Renderer;
	UCollision* Collision;
	UStateManager State = UStateManager();

private:
	int Damage = 0;
	float4 HorizontalDir = float4::Zero;
	float4 VerticalDir = float4::Zero;
	float HorizontalSpeed = 0.0f;
	float VerticalSpeed = 0.0f;
};

