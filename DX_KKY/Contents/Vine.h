#pragma once
#include "BossAttackUnit.h"
#include <EngineCore/StateManager.h>
#include <EnginePlatform/EngineSound.h>

enum class EVineAttackStep
{
	None,
	Grow,
	Attack,
	Retract,
};

// 설명 :
class USpriteRenderer;
class UCollision;
class AVine : public ABossAttackUnit
{
	GENERATED_BODY(ABossAttackUnit)
public:
	// constrcuter destructer
	AVine();
	~AVine();

	// delete Function
	AVine(const AVine& _Other) = delete;
	AVine(AVine&& _Other) noexcept = delete;
	AVine& operator=(const AVine& _Other) = delete;
	AVine& operator=(AVine&& _Other) noexcept = delete;

	inline void GrowUp()
	{
		State.ChangeState(FlowerBossState::Vine_GrowUp);
		return;
	}
	inline bool IsWait() const
	{
		if (FlowerBossState::Vine_Wait == State.GetCurStateName())
		{
			return true;
		}

		return false;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;
	USpriteRenderer* BackVineRenderer;
	UCollision* StemCollider;

	float AttackDelay = 0.0f;

	void StateInit() override;
	void RendererInit() override;
	void ColliderInit() override;
	void AnimationInit() override;

	void WaitAttack(float _DeltaTime);

	template <typename EnumType>
	void PlayVineAttackSound(EnumType _Type)
	{
		int Type = static_cast<int>(_Type);
		UEngineSoundPlayer Sound = UEngineSoundPlayer();
		int RandomVal = 0;

		switch (Type)
		{
		case static_cast<int>(EVineAttackStep::Grow):
		{
			RandomVal = UMath::RandomReturnInt(1, 4);
			Sound = UEngineSound::SoundPlay("sfx_level_flower_vinehand_grow_0" + std::to_string(RandomVal) + ".wav");
			break;
		}
		case static_cast<int>(EVineAttackStep::Attack):
		{
			RandomVal = UMath::RandomReturnInt(1, 2);
			Sound = UEngineSound::SoundPlay("sfx_level_flower_vinehand_grow_continue_0" + std::to_string(RandomVal) + ".wav");
			break;
		}
		case static_cast<int>(EVineAttackStep::Retract):
		{
			RandomVal = UMath::RandomReturnInt(1, 2);
			Sound = UEngineSound::SoundPlay("sfx_level_flower_vinehand_grow_retract_0" + std::to_string(RandomVal) + ".wav");
			break;
		}
		default:
			MsgBoxAssert("지정되지 않은 공격 Step입니다.");
			return;
		}

		Sound.SetVolume(0.3f);
	}
};

