#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>

#include "Player.h"
#include "MoveUnit.h"


void APlayer::StateInit()
{
	{

		State.CreateState("Idle");
		State.CreateState("Run");
		State.CreateState("Jump");
		State.CreateState("DuckIdle");
		State.CreateState("Duck");
		State.CreateState("Parry");
		State.CreateState("AfterParry");
		State.CreateState("Dash");
		State.CreateState("DashAir");
		State.CreateState("AfterDashAir");
		State.CreateState("DownJump");
		State.CreateState("FallDown");

		State.CreateState("Aim_Up");
		State.CreateState("Aim_DiagonalUp");
		State.CreateState("Aim_Straight");
		State.CreateState("Aim_DiagonalDown");
		State.CreateState("Aim_Down");

		State.CreateState("Shoot_Up");
		State.CreateState("Shoot_DiagonalUp");
		State.CreateState("Shoot_Straight");
		State.CreateState("Shoot_DiagonalDown");
		State.CreateState("Shoot_Down");
		State.CreateState("Shoot_Duck");

		State.CreateState("Run_Shoot_Straight");
		State.CreateState("Run_Shoot_DiagonalUp");

		State.CreateState("Ground_SS_Up");
		State.CreateState("Ground_SS_DiagonalUp");
		State.CreateState("Ground_SS_Straight");
		State.CreateState("Ground_SS_DiagonalDown");
		State.CreateState("Ground_SS_Down");

		State.CreateState(CupheadStateName::Player_SSAir_Straight);
		State.CreateState(CupheadStateName::Player_SSAir_Up);
		State.CreateState(CupheadStateName::Player_SSAir_Down);
		State.CreateState(CupheadStateName::Player_SSAir_DiagonalUp);
		State.CreateState(CupheadStateName::Player_SSAir_DiagonalDown);


		State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
		State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
		State.SetUpdateFunction("Jump", std::bind(&APlayer::Jump, this, std::placeholders::_1));
		State.SetUpdateFunction("DuckIdle", std::bind(&APlayer::DuckIdle, this, std::placeholders::_1));
		State.SetUpdateFunction("Duck", std::bind(&APlayer::Duck, this, std::placeholders::_1));
		State.SetUpdateFunction("Parry", std::bind(&APlayer::Parry, this, std::placeholders::_1));
		State.SetUpdateFunction("AfterParry", std::bind(&APlayer::AfterParry, this, std::placeholders::_1));
		State.SetUpdateFunction("Dash", std::bind(&APlayer::Dash, this, std::placeholders::_1));
		State.SetUpdateFunction("DashAir", std::bind(&APlayer::DashAir, this, std::placeholders::_1));
		State.SetUpdateFunction("AfterDashAir", std::bind(&APlayer::AfterDashAir, this, std::placeholders::_1));
		State.SetUpdateFunction("DownJump", std::bind(&APlayer::DownJump, this, std::placeholders::_1));
		State.SetUpdateFunction("FallDown", std::bind(&APlayer::FallDown, this, std::placeholders::_1));

		State.SetUpdateFunction("Aim_Up", std::bind(&APlayer::Aim_Up, this, std::placeholders::_1));
		State.SetUpdateFunction("Aim_DiagonalUp", std::bind(&APlayer::Aim_DiagonalUp, this, std::placeholders::_1));
		State.SetUpdateFunction("Aim_Straight", std::bind(&APlayer::Aim_Straight, this, std::placeholders::_1));
		State.SetUpdateFunction("Aim_DiagonalDown", std::bind(&APlayer::Aim_DiagonalDown, this, std::placeholders::_1));
		State.SetUpdateFunction("Aim_Down", std::bind(&APlayer::Aim_Down, this, std::placeholders::_1));

		State.SetUpdateFunction("Shoot_Up", std::bind(&APlayer::IdleShoot_Up, this, std::placeholders::_1));
		State.SetUpdateFunction("Shoot_DiagonalUp", std::bind(&APlayer::IdleShoot_DiagonalUp, this, std::placeholders::_1));
		State.SetUpdateFunction("Shoot_Straight", std::bind(&APlayer::IdleShoot_Straight, this, std::placeholders::_1));
		State.SetUpdateFunction("Shoot_DiagonalDown", std::bind(&APlayer::IdleShoot_DiagonalDown, this, std::placeholders::_1));
		State.SetUpdateFunction("Shoot_Down", std::bind(&APlayer::IdleShoot_Down, this, std::placeholders::_1));
		State.SetUpdateFunction("Shoot_Duck", std::bind(&APlayer::IdleShoot_Duck, this, std::placeholders::_1));

		State.SetUpdateFunction("Run_Shoot_Straight", std::bind(&APlayer::Run_Shoot_Straight, this, std::placeholders::_1));
		State.SetUpdateFunction("Run_Shoot_DiagonalUp", std::bind(&APlayer::Run_Shoot_DiagonalUp, this, std::placeholders::_1));

		State.SetUpdateFunction("Ground_SS_Up", std::bind(&APlayer::Ground_SS_Up, this, std::placeholders::_1));
		State.SetUpdateFunction("Ground_SS_DiagonalUp", std::bind(&APlayer::Ground_SS_DiagonalUp, this, std::placeholders::_1));
		State.SetUpdateFunction("Ground_SS_Straight", std::bind(&APlayer::Ground_SS_Straight, this, std::placeholders::_1));
		State.SetUpdateFunction("Ground_SS_DiagonalDown", std::bind(&APlayer::Ground_SS_DiagonalDown, this, std::placeholders::_1));
		State.SetUpdateFunction("Ground_SS_Down", std::bind(&APlayer::Ground_SS_Down, this, std::placeholders::_1));

		State.SetUpdateFunction(CupheadStateName::Player_SSAir_Up, std::bind(&APlayer::SSAir_Up, this, std::placeholders::_1));
		State.SetUpdateFunction(CupheadStateName::Player_SSAir_DiagonalUp, std::bind(&APlayer::SSAir_DiagonalUp, this, std::placeholders::_1));
		State.SetUpdateFunction(CupheadStateName::Player_SSAir_Straight, std::bind(&APlayer::SSAir_Straight, this, std::placeholders::_1));
		State.SetUpdateFunction(CupheadStateName::Player_SSAir_DiagonalDown, std::bind(&APlayer::SSAir_DiagonalDown, this, std::placeholders::_1));
		State.SetUpdateFunction(CupheadStateName::Player_SSAir_Down, std::bind(&APlayer::SSAir_Down, this, std::placeholders::_1));

		State.SetStartFunction("Idle", [this]
			{
				DirCheck();
				SetAvailableParry(true);
				SetAvailableAddJumpVec(false);
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Renderer->ChangeAnimation("Player_Idle");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("Run", [this]
			{
				DirCheck();
				SetAvailableParry(true);
				SetAvailableAddJumpVec(false);
				Renderer->ChangeAnimation("Player_Run");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("Jump", [this]
			{
				DirCheck();
				AddActorLocation(float4::Up * 10);
				SetJumpVec(float4::Up * GetJumpVal());
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			}
		);
		State.SetStartFunction("Duck", [this]
			{
				ColInfoChange(true);
				DirCheck();
				SetAvailableParry(true);
				SetAvailableAddJumpVec(false);
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Renderer->ChangeAnimation("Player_Duck");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("DuckIdle", [this]
			{
				ColInfoChange(true);
				DirCheck();
				SetAvailableParry(true);
				SetAvailableAddJumpVec(false);
				SetSpeedVec(float4::Zero);
				SetJumpVec(float4::Zero);
				Renderer->ChangeAnimation("Player_DuckIdle");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("Parry", [this]
			{
				DirCheck();
				SetJumpVec(GetPrevJumpVec());
				SetParrying(true);
				SetAvailableParry(false);
				SetAvailableAddJumpVec(false);
				Renderer->ChangeAnimation("Player_Parry");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			}
		);
		State.SetStartFunction("AfterParry", [this]
			{
				DirCheck();
				SetJumpVec(GetPrevJumpVec());
				SetAvailableAddJumpVec(false);
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			}
		);
		State.SetStartFunction("Dash", [this]
			{
				DirCheck();
				CreateDashFX(GetActorLocation());
				SetAvailableAddJumpVec(false);
				Renderer->ChangeAnimation("Player_Dash");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("DashAir", [this]
			{
				DirCheck();
				CreateDashFX(GetActorLocation());
				SetJumpVec(GetPrevJumpVec());
				Renderer->ChangeAnimation("Player_Dash_Air");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("AfterDashAir", [this]
			{
				DirCheck();
				SetAvailableAddJumpVec(false);
				SetJumpVec(GetPrevJumpVec());
				SetGravityVec(GetPrevGravityVec());
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			}
		);
		State.SetStartFunction("DownJump", [this]
			{
				DirCheck();
				AddActorLocation(float4::Down * 30.0f);
				SetAvailableAddJumpVec(false);
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			}
		);
		State.SetStartFunction("FallDown", [this]
			{
				DirCheck();
				SetAvailableAddJumpVec(false);
				Renderer->ChangeAnimation("Player_Jump");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			}
		);
		State.SetStartFunction("Aim_Up", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_Up");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("Aim_DiagonalUp", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_DiagonalUp");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("Aim_Straight", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_Straight");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("Aim_DiagonalDown", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_DiagonalDown");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);
		State.SetStartFunction("Aim_Down", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Aim_Down");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::None);
			}
		);

		State.SetStartFunction("Shoot_Up", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Shoot_Up");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::UpShoot);
			}
		);
		State.SetStartFunction("Shoot_DiagonalUp", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Shoot_DiagonalUp");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::DiagonalUpShoot);
			}
		);
		State.SetStartFunction("Shoot_Straight", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Shoot_Straight");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::StraightShoot);
			}
		);
		State.SetStartFunction("Shoot_DiagonalDown", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Shoot_DiagonalDown");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::DiagonalDownShoot);
			}
		);
		State.SetStartFunction("Shoot_Down", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Shoot_Down");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::DownShoot);
			}
		);
		State.SetStartFunction("Shoot_Duck", [this]
			{
				ColInfoChange(true);
				DirCheck();
				SetSpeedVec(float4::Zero);
				Renderer->ChangeAnimation("Player_Duck_Shoot");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::DuckShoot);
			}
		);

		State.SetStartFunction("Run_Shoot_Straight", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Run_Shoot_Straight");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::StraightShoot);
			}
		);
		State.SetStartFunction("Run_Shoot_DiagonalUp", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_Run_Shoot_DiagonalUp");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::DiagonalUpShoot);
			}
		);

		
		State.SetStartFunction("Ground_SS_Up", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_SSGround_Up");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::UpGSS);
			}
		);
		State.SetStartFunction("Ground_SS_DiagonalUp", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_SSGround_DiagonalUp");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::DiagonalUpGSS);
			}
		);
		State.SetStartFunction("Ground_SS_Straight", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_SSGround_Straight");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::StraightGSS);
			}
		);
		State.SetStartFunction("Ground_SS_DiagonalDown", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_SSGround_DiagonalDown");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::DiagonalDownGSS);
			}
		);
		State.SetStartFunction("Ground_SS_Down", [this]
			{
				DirCheck();
				Renderer->ChangeAnimation("Player_SSGround_Down");
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::DownGSS);
			}
		);

		State.SetStartFunction(CupheadStateName::Player_SSAir_Up, [this]
			{
				DirCheck();
				Renderer->ChangeAnimation(GAniName::Player_SSAir_Up);
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			});
		State.SetStartFunction(CupheadStateName::Player_SSAir_DiagonalUp, [this]
			{
				DirCheck();
				Renderer->ChangeAnimation(GAniName::Player_SSAir_DiagonalUp);
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			});
		State.SetStartFunction(CupheadStateName::Player_SSAir_Straight, [this]
			{
				DirCheck();
				Renderer->ChangeAnimation(GAniName::Player_SSAir_Straight);
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			});
		State.SetStartFunction(CupheadStateName::Player_SSAir_DiagonalDown, [this]
			{
				DirCheck();
				Renderer->ChangeAnimation(GAniName::Player_SSAir_DiagonalDown);
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			});
		State.SetStartFunction(CupheadStateName::Player_SSAir_Down, [this]
			{
				DirCheck();
				Renderer->ChangeAnimation(GAniName::Player_SSAir_Down);
				AnimationDirSet(Renderer, PlayerDir);
				SetShootType(EBulletShootType::JumpShoot);
			});
	}

	{
		State.SetEndFunction("Run", [this]()
			{
				SetSpeedVec(float4::Zero);
				ResetRunFXDelay();
			});
		State.SetEndFunction("Run_Shoot_DiagonalUp", [this]()
			{
				SetSpeedVec(float4::Zero);
				ResetRunFXDelay();
			});
		State.SetEndFunction("Run_Shoot_Straight", [this]()
			{
				SetSpeedVec(float4::Zero);
				ResetRunFXDelay();
			});
		State.SetEndFunction("Jump", [this]()
			{
				SetPrevJumpVec(GetJumpVec());
				SetJumpVec(float4::Zero);
			});
		State.SetEndFunction("Parry", [this]()
			{
				SetParrying(false);
			});
		State.SetEndFunction("Duck", [this]()
			{
				ColInfoChange(false);
			});
		State.SetEndFunction("DuckIdle", [this]()
			{
				ColInfoChange(false);
			});
		State.SetEndFunction("Shoot_Duck", [this]()
			{
				ColInfoChange(false);
			});
	}


	State.ChangeState("Idle");
}

bool APlayer::DirCheck()
{
	EActorDir ActorDir = PlayerDir;

	if (true == IsPress(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		ActorDir = EActorDir::Left;
	}

	if (true == IsPress(VK_RIGHT) && UEngineInput::IsFree(VK_LEFT))
	{
		ActorDir = EActorDir::Right;
	}

	if (ActorDir != PlayerDir)
	{
		PlayerDir = ActorDir;
		return false;
	}

	return true;
}

void APlayer::GetPlayerKeyDir()
{
	EPlayerKeyDir KeyDir = KeyDirCheck();
	
	if (ActorKeyDir != KeyDir)
	{
		ActorKeyDir = KeyDir;
		return;
	}
}

EPlayerKeyDir APlayer::KeyDirCheck()
{
	if (true == IsPress(VK_UP))
	{
		if (true == IsPress(VK_RIGHT))
		{
			return EPlayerKeyDir::RightUp;
		}

		if (true == IsPress(VK_LEFT))
		{
			return EPlayerKeyDir::LeftUp;
		}

		return EPlayerKeyDir::Up;;
	}

	if (true == IsPress(VK_DOWN))
	{
		if (true == IsPress(VK_RIGHT))
		{
			return EPlayerKeyDir::RightDown;
		}

		if (true == IsPress(VK_LEFT))
		{
			return EPlayerKeyDir::LeftDown;
		}

		return EPlayerKeyDir::Down;
	}

	if (true == IsPress(VK_RIGHT) || PlayerDir == EActorDir::Right)
	{
		return EPlayerKeyDir::Right;
	}

	if (true == IsPress(VK_LEFT) || PlayerDir == EActorDir::Left)
	{
		return EPlayerKeyDir::Left;
	}

	return EPlayerKeyDir::None;
}

void APlayer::Idle(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		if (true == IsPress(VK_DOWN))
		{
			State.ChangeState("Duck");
			return;
		}

		State.ChangeState("Run");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("Duck");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	if (true == IsPress('X'))
	{
		State.ChangeState("Shoot_Straight");
		return;
	}

	if (true == IsPress('C'))
	{
		State.ChangeState("Aim_Straight");
		return;
	}

	if (true == IsPress(VK_UP))
	{
		State.ChangeState("Aim_Up");
		return;
	}

	

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Run(float _DeltaTime)
{
	CreateRunFX(_DeltaTime);
	SuperShootCheck(_DeltaTime);

	if (true == FallDownCheck(GetActorLocation()))
	{
		return;
	}

	if (true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
	{
		if (true == IsPress(VK_UP))
		{
			State.ChangeState("Aim_Up");
			return;
		}

		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_DOWN))
	{
		State.ChangeState("Duck");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	if (true == IsPress('X'))
	{
		State.ChangeState("Run_Shoot_Straight");
		return;
	}


	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP) && true == IsDown('C'))
		{
			State.ChangeState("Aim_DiagonalUp");
			return;
		}

		if (true == IsPress('C'))
		{
			State.ChangeState("Aim_Straight");
			return;
		}
	}
	

	if (false == DirCheck())
	{
		AnimationDirSet(Renderer, PlayerDir);
	}

	SetSpeedVec(MoveDir(PlayerDir) * GetRunSpeed());
	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Jump(float _DeltaTime)
{
	JumpSuperShootCheck();
	ShootCheck(_DeltaTime);
	FootColOnOff();

	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == PixelCheck(Pos, Color8Bit::Black) || true == PixelCheck(Pos, Color8Bit::Blue))
	{
		if (true == IsPress(VK_DOWN))
		{
			if (true == IsPress('C'))
			{
				State.ChangeState("Aim_Straight");
				return;
			}
		}

		CreateLandFX(GetActorLocation());
		State.ChangeState("Idle");
		return;
	}

	if (true == GetAvailableParry() && true == IsDown('Z'))
	{
		State.ChangeState("Parry");
		return;
	}

	SetAvailableAddJumpVec(false);
	if (true == IsPress('Z') && 0.2f >= GetPressTime('Z'))
	{
		SetAvailableAddJumpVec(true);
	}

	if (true == IsDown(VK_SHIFT))
	{
		State.ChangeState("DashAir");
		return;
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		DirCheck();
		SetSpeedVec(MoveDir(PlayerDir) * GetRunSpeed());
		AnimationDirSet(Renderer, PlayerDir);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::DuckIdle(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);

	if (true == IsFree(VK_DOWN))
	{
		State.ChangeState("Idle");
		return;
	}
	

	if (true == IsPress(VK_DOWN))
	{
		if (true == IsDown('Z'))
		{
			if (true == DownJumpCheck())
			{
				State.ChangeState("DownJump");
				return;
			}
			State.ChangeState("Jump");
			return;
		}

		if (true == IsDown(VK_SHIFT))
		{
			SetPrevState(State.GetCurStateName());
			State.ChangeState("Dash");
			return;
		}

		if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
		{
			if (true == IsDown('C'))
			{
				State.ChangeState("Aim_DiagonalDown");
				return;
			}

			DirCheck();
			AnimationDirSet(Renderer, PlayerDir);
		}

		if (true == IsPress('X'))
		{
			State.ChangeState("Shoot_Duck");
			return;
		}

		if (true == IsPress('C'))
		{
			State.ChangeState("Aim_Down");
			return;
		}
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Duck(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);

	if (true == IsUp(VK_DOWN))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown(VK_LEFT) || true == IsDown(VK_RIGHT))
	{
		if (false == DirCheck())
		{
			State.ChangeState("DuckIdle");
			return;
		}
	}

	if (true == IsDown('Z'))
	{
		if (true == IsPress(VK_DOWN) && true == DownJumpCheck())
		{
			State.ChangeState("DownJump");
			return;
		}

		State.ChangeState("Jump");
		return;
	}

	if (true == IsPress('X'))
	{
		State.ChangeState("Shoot_Duck");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Parry(float _DeltaTime)
{
	ShootCheck(_DeltaTime);
	FootColOnOff();
	CollisionCheck();

	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == PixelCheck(Pos, Color8Bit::Black) || true == PixelCheck(Pos, Color8Bit::Blue))
	{
		CreateLandFX(GetActorLocation());
		State.ChangeState("Idle");
		return;
	}

	if (true == GetAvailableParry() && true == IsDown('Z'))
	{
		State.ChangeState("Parry");
		return;
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		DirCheck();
		SetSpeedVec(MoveDir(PlayerDir) * GetRunSpeed());
		AnimationDirSet(Renderer, PlayerDir);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::AfterParry(float _DeltaTime)
{
	ShootCheck(_DeltaTime);
	FootColOnOff();

	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == PixelCheck(Pos, Color8Bit::Black) || true == PixelCheck(Pos, Color8Bit::Blue))
	{
		CreateLandFX(GetActorLocation());
		State.ChangeState("Idle");
		return;
	}

	if (true == GetAvailableParry() && true == IsDown('Z'))
	{
		State.ChangeState("Parry");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		State.ChangeState("DashAir");
		return;
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		DirCheck();
		SetSpeedVec(MoveDir(PlayerDir) * GetRunSpeed());
		AnimationDirSet(Renderer, PlayerDir);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Dash(float _DeltaTime)
{
	float Speed = 0;

	if (true == WallCheck())
	{
		Speed = 0;
	}
	else
	{
		Speed = GetDashSpeed();
	}

	AddActorLocation(MoveDir(PlayerDir) * Speed * _DeltaTime);
}

void APlayer::DashAir(float _DeltaTime)
{
	float Speed = 0;

	if (true == WallCheck())
	{
		Speed = 0;
	}
	else
	{
		Speed = GetDashSpeed();
	}

	AddGravityVec(0.4f, _DeltaTime);
	AddActorLocation(MoveDir(PlayerDir) * Speed * _DeltaTime);
}

void APlayer::AfterDashAir(float _DeltaTime)
{
	ShootCheck(_DeltaTime);
	FootColOnOff();

	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == PixelCheck(Pos, Color8Bit::Black) || true == PixelCheck(Pos, Color8Bit::Blue))
	{
		CreateLandFX(GetActorLocation());
		State.ChangeState("Idle");
		return;
	}

	if (true == GetAvailableParry() && true == IsDown('Z'))
	{
		State.ChangeState("Parry");
		return;
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		DirCheck();
		SetSpeedVec(MoveDir(PlayerDir) * GetRunSpeed());
		AnimationDirSet(Renderer, PlayerDir);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Aim_Up(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);

	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if ((true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			if (true == IsPress(VK_UP))
			{
				State.ChangeState("Aim_DiagonalUp");
				return;
			}
		}

		if (true == IsUp(VK_UP))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		if (true == IsPress('X'))
		{
			State.ChangeState("Shoot_Up");
			return;
		}
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}


	if (true == IsFree('C'))
	{
		if ((true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			State.ChangeState("Run");
			return;
		}

		if (true == IsUp(VK_UP))
		{
			State.ChangeState("Idle");
			return;
		}

		if (true == IsPress('X'))
		{
			State.ChangeState("Shoot_Up");
			return;
		}
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Aim_DiagonalUp(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);

	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsUp(VK_UP))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		if (true == IsPress(VK_UP) && (IsFree(VK_RIGHT) && true == IsFree(VK_LEFT)))
		{
			State.ChangeState("Aim_Up");
			return;
		}
	}

	if (true == IsPress('X'))
	{
		State.ChangeState("Shoot_DiagonalUp");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP) && true == IsUp('C'))
		{
			State.ChangeState("Run");
			return;
		}

		DirCheck();
		AnimationDirSet(Renderer, PlayerDir);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Aim_Straight(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);
	
	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsPress(VK_DOWN) && (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			State.ChangeState("Aim_DiagonalDown");
			return;
		}

		if (true == IsPress(VK_UP) && (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			State.ChangeState("Aim_DiagonalUp");
			return;
		}

		if (true == IsPress(VK_DOWN))
		{
			State.ChangeState("Aim_Down");
			return;
		}

		if (true == IsPress(VK_UP))
		{
			State.ChangeState("Aim_Up");
			return;
		}
	}

	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		if (true == IsUp('C'))
		{
			State.ChangeState("Run");
			return;
		}

		DirCheck();
		AnimationDirSet(Renderer, PlayerDir);
	}

	if (true == IsUp('C'))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsPress('X'))
	{
		State.ChangeState("Shoot_Straight");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}


	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Aim_DiagonalDown(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsUp(VK_DOWN) && (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		if (true == IsPress(VK_DOWN) && (true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT)))
		{
			State.ChangeState("Aim_Down");
			return;
		}
	}

	if (true == IsPress('X'))
	{
		State.ChangeState("Shoot_DiagonalDown");
		return;
	}

	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_DOWN) && true == IsUp('C'))
		{
			State.ChangeState("DuckIdle");
			return;
		}

		DirCheck();
		AnimationDirSet(Renderer, PlayerDir);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Aim_Down(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	// Aim 끼리 상태 변화
	if (true == IsPress('C'))
	{
		if (true == IsFree(VK_DOWN))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		if (true == IsPress(VK_DOWN) && (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT)))
		{
			State.ChangeState("Aim_DiagonalDown");
			return;
		}

		if (true == IsPress('X'))
		{
			State.ChangeState("Shoot_Down");
			return;
		}


	}


	if (true == IsFree('C'))
	{
		if (true == IsPress(VK_DOWN))
		{
			State.ChangeState("DuckIdle");
			return;
		}
	}

	ResultMovementUpdate(_DeltaTime);
}





void APlayer::IdleShoot_Up(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);
	ShootCheck(_DeltaTime);

	if (true == IsUp('X'))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsPress('C'))
	{
		if (true == IsDown(VK_RIGHT) || true == IsDown(VK_LEFT))
		{
			State.ChangeState("Shoot_DiagonalUp");
			return;
		}
	}

	if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		State.ChangeState("Run_Shoot_DiagonalUp");
		return;
	}

	if (true == IsUp(VK_UP))
	{
		State.ChangeState("Shoot_Straight");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::IdleShoot_DiagonalUp(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);
	ShootCheck(_DeltaTime);

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsPress('C'))
	{
		if (true == IsUp('X'))
		{
			State.ChangeState("Aim_DiagonalUp");
			return;
		}

		if (true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
		{
			State.ChangeState("Shoot_Up");
			return;
		}

		if (true == IsFree(VK_UP))
		{
			State.ChangeState("Shoot_Straight");
			return;
		}
	}

	if (true == IsFree('C'))
	{
		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			State.ChangeState("Run_Shoot_DiagonalUp");
			return;
		}
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::IdleShoot_Straight(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);
	ShootCheck(_DeltaTime);

	if (true == IsUp('X'))
	{
		if (true == IsPress('C'))
		{
			State.ChangeState("Aim_Straight");
			return;
		}

		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}


	if (true == IsFree('C'))
	{
		if (true == IsPress(VK_UP))
		{
			State.ChangeState("Shoot_Up");
			return;
		}

		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			State.ChangeState("Run_Shoot_Straight");
			return;
		}
	}


	if (true == IsPress('C'))
	{

		if (true == IsPress(VK_UP))
		{
			if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
			{
				State.ChangeState("Shoot_DiagonalUp");
				return;
			}
			State.ChangeState("Shoot_Up");
			return;
		}

		if (true == IsPress(VK_DOWN))
		{
			if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
			{
				State.ChangeState("Shoot_DiagonalDown");
				return;
			}
			State.ChangeState("Shoot_Down");
			return;
		}

		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			DirCheck();
			AnimationDirSet(Renderer, PlayerDir);
		}
	}

	if (true == IsPress(VK_DOWN))
	{
		State.ChangeState("Shoot_Duck");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::IdleShoot_DiagonalDown(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);
	ShootCheck(_DeltaTime);

	if (true == IsFree('X'))
	{
		State.ChangeState("Aim_DiagonalDown");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsPress('C'))
	{
		if (true == IsUp(VK_DOWN))
		{
			State.ChangeState("Shoot_Straight");
			return;
		}

		if (true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
		{
			State.ChangeState("Shoot_Down");
			return;
		}
	}

	if (true == IsFree('C'))
	{
		State.ChangeState("Shoot_Duck");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::IdleShoot_Down(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);
	ShootCheck(_DeltaTime);

	if (true == IsUp('X'))
	{
		State.ChangeState("Aim_Down");
		return;
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsPress('C'))
	{
		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			State.ChangeState("Shoot_DiagonalDown");
			return;
		}
	}

	if (true == IsFree('C'))
	{
		State.ChangeState("Shoot_Duck");
		return;

	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::IdleShoot_Duck(float _DeltaTime)
{
	SuperShootCheck(_DeltaTime);
	ShootCheck(_DeltaTime);

	if (true == IsPress(VK_DOWN))
	{
		if (true == IsUp('X'))
		{
			State.ChangeState("DuckIdle");
			return;
		}

		if (true == IsDown('Z'))
		{
			if (true == DownJumpCheck())
			{
				State.ChangeState("DownJump");
				return;
			}
			State.ChangeState("Jump");
			return;
		}

		if (true == IsDown(VK_SHIFT))
		{
			SetPrevState(State.GetCurStateName());
			State.ChangeState("Dash");
			return;
		}

		if (true == IsPress('C'))
		{
			State.ChangeState("Shoot_Down");
			return;
		}

		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			DirCheck();
			AnimationDirSet(Renderer, PlayerDir);
		}
	}

	if (true == IsFree(VK_DOWN))
	{
		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			State.ChangeState("Run_Shoot_Straight");
			return;
		}

		State.ChangeState("Shoot_Straight");
		return;
	}
	
	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Run_Shoot_DiagonalUp(float _DeltaTime)
{
	CreateRunFX(_DeltaTime);
	SuperShootCheck(_DeltaTime);
	ShootCheck(_DeltaTime);


	if (true == FallDownCheck(GetActorLocation()))
	{
		return;
	}

	if (true == IsFree('X'))
	{
		State.ChangeState("Run");
		return;
	}

	if (true == IsPress('X'))
	{
		if (true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
		{
			State.ChangeState("Shoot_Up");
			return;
		}

		if (true == IsPress('C'))
		{
			State.ChangeState("Shoot_DiagonalUp");
			return;
		}

		if (true == IsFree(VK_UP))
		{
			State.ChangeState("Run_Shoot_Straight");
			return;
		}
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	if (false == DirCheck())
	{
		AnimationDirSet(Renderer, PlayerDir);
	}

	SetSpeedVec(MoveDir(PlayerDir) * GetRunSpeed());
	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Run_Shoot_Straight(float _DeltaTime)
{
	CreateRunFX(_DeltaTime);
	SuperShootCheck(_DeltaTime);
	ShootCheck(_DeltaTime);

	if (true == FallDownCheck(GetActorLocation()))
	{
		return;
	}

	if (true == IsFree('X'))
	{
		State.ChangeState("Run");
		return;
	}

	if (true == IsPress('X'))
	{
		if ((true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT)) || true == IsDown('C'))
		{
			State.ChangeState("Shoot_Straight");
			return;
		}

		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			if (true == IsPress(VK_UP))
			{
				State.ChangeState("Run_Shoot_DiagonalUp");
				return;
			}
		}

		if (true == IsDown(VK_DOWN))
		{
			State.ChangeState("Shoot_Duck");
			return;
		}
	}

	if (true == IsDown('Z'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		SetPrevState(State.GetCurStateName());
		State.ChangeState("Dash");
		return;
	}

	if (false == DirCheck())
	{
		AnimationDirSet(Renderer, PlayerDir);
	}

	SetSpeedVec(MoveDir(PlayerDir) * GetRunSpeed());
	ResultMovementUpdate(_DeltaTime);
}

void APlayer::DownJump(float _DeltaTime)
{
	ShootCheck(_DeltaTime);

	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == PixelCheck(Pos, Color8Bit::Black))
	{
		CreateLandFX(GetActorLocation());
		State.ChangeState("Idle");
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::FallDown(float _DeltaTime)
{
	ShootCheck(_DeltaTime);

	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y;

	if (true == PixelCheck(Pos, Color8Bit::Black) || true == PixelCheck(Pos, Color8Bit::Blue))
	{
		CreateLandFX(GetActorLocation());
		State.ChangeState("Idle");
		return;
	}

	if (true == GetAvailableParry() && true == IsDown('Z'))
	{
		State.ChangeState("Parry");
		return;
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT))
	{
		DirCheck();
		SetSpeedVec(MoveDir(PlayerDir) * GetRunSpeed());
		AnimationDirSet(Renderer, PlayerDir);
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT))
	{
		SetSpeedVec(float4::Zero);
	}

	ResultMovementUpdate(_DeltaTime);
}

void APlayer::Ground_SS_Up(float _DeltaTime)
{

}

void APlayer::Ground_SS_DiagonalUp(float _DeltaTime)
{
	DirCheck();
	AddActorLocation(-MoveDir(PlayerDir) * _DeltaTime * SSReboundSpeed);
}

void APlayer::Ground_SS_Straight(float _DeltaTime)
{
	DirCheck();
	AddActorLocation(-MoveDir(PlayerDir) * _DeltaTime * SSReboundSpeed);
}

void APlayer::Ground_SS_DiagonalDown(float _DeltaTime)
{
	DirCheck();
	AddActorLocation(-MoveDir(PlayerDir) * _DeltaTime * SSReboundSpeed);
}

void APlayer::Ground_SS_Down(float _DeltaTime)
{

}

void APlayer::SSAir_Up(float _DeltaTime)
{

}

void APlayer::SSAir_DiagonalUp(float _DeltaTime)
{

}

void APlayer::SSAir_Straight(float _DeltaTime)
{

}

void APlayer::SSAir_DiagonalDown(float _DeltaTime)
{

}

void APlayer::SSAir_Down(float _DeltaTime)
{

}