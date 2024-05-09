#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

// Ό³Έν :
class USpriteRenderer;
class UCollision;
class AWorldPlayer : public AActor, public std::enable_shared_from_this<AWorldPlayer>
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AWorldPlayer();
	~AWorldPlayer();

	// delete Function
	AWorldPlayer(const AWorldPlayer& _Other) = delete;
	AWorldPlayer(AWorldPlayer&& _Other) noexcept = delete;
	AWorldPlayer& operator=(const AWorldPlayer& _Other) = delete;
	AWorldPlayer& operator=(AWorldPlayer&& _Other) noexcept = delete;

	inline static std::shared_ptr<AWorldPlayer> GetMainPlayer()
	{
		return MainPlayer;
	}
		
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State = UStateManager();
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* ButtonRenderer = nullptr;
	UCollision* Collider = nullptr;

	float Speed = 230.0f;
	float DiagonalSpeed = 170.0f;

	EPlayerKeyDir Dir = EPlayerKeyDir::None;

	float DustInitXOffset = -15.0f;
	float DustDelayTime = 1.0f;
	float DustDelayTimeInit = 0.3f;
	float WalkDelayTime = 0.0f;
	float WalkDelayTimeInit = 0.25f;

	static std::shared_ptr<AWorldPlayer> MainPlayer;


private:
	void UpIdle(float _DeltaTime);
	void RightUpIdle(float _DeltaTime);
	void RightIdle(float _DeltaTime);
	void RightDownIdle(float _DeltaTime);
	void DownIdle(float _DeltaTime);
	void LeftDownIdle(float _DeltaTime);
	void LeftIdle(float _DeltaTime);
	void LeftUpIdle(float _DeltaTime);
	void UpWalk(float _DeltaTime);
	void RightUpWalk(float _DeltaTime);
	void RightWalk(float _DeltaTime);
	void RightDownWalk(float _DeltaTime);
	void DownWalk(float _DeltaTime);
	void LeftDownWalk(float _DeltaTime);
	void LeftWalk(float _DeltaTime);
	void LeftUpWalk(float _DeltaTime);
	bool MapCollisionCheck();
	void MakeDust(float _DeltaTime);
	void ResetDustDelayTime();
	void CameraMove(float _DeltaTime);

	void CreatePlayerAnimation();
	void ColliderInit();
	void StateInit();
	void CollisionCheck();
	void WalkCheck(float _DeltaTime);
	void WalkSoundPlay();
	void RendererInit();

	inline float GetSpeed() const
	{
		return Speed;
	}
	inline float GetDiagonalSpeed() const
	{
		return DiagonalSpeed;
	}
	inline void SetMainPlayer(std::shared_ptr<AWorldPlayer> _Player)
	{
		MainPlayer = _Player;
	}
};

