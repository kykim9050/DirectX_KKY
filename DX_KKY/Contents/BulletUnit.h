#pragma once
#include "MoveUnit.h"
#include <EngineCore/StateManager.h>
#include "ParryUnit.h"

// Ό³Έν :
class UCollision;
class USpriteRenderer;
class UDefaultSceneComponent;
class ABulletUnit : public UMoveUnit ,public UParryUnit
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
	bool BoundaryCheck(float4 _Boundary, float OffsetX = 0.0f, float OffsetY = 0.0f);

	virtual void StateInit() {};
	virtual void RendererInit() {};
	virtual void ColliderInit() {};
	virtual void AnimationInit() {};
	
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

	UDefaultSceneComponent* Root;
	USpriteRenderer* Renderer;
	UCollision* Collision;
	UStateManager State = UStateManager();
	float4 BoundaryValue = float4::Zero;

private:
	int Damage = 0;
	float4 HorizontalDir = float4::Zero;
	float4 VerticalDir = float4::Zero;
	float HorizontalSpeed = 0.0f;
	float VerticalSpeed = 0.0f;
	
};

