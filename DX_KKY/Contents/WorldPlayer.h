#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
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

	void CreatePlayerAnimation();

	void StateInit();
	void Idle(float _DeltaTime);

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

	inline float GetSpeed() const
	{
		return Speed;
	}
	inline float GetDiagonalSpeed() const
	{
		return DiagonalSpeed;
	}

	static std::shared_ptr<AWorldPlayer> MainPlayer;
	inline void SetMainPlayer(std::shared_ptr<AWorldPlayer> _Player)
	{
		MainPlayer = _Player;
	}

	UStateManager State = UStateManager();
	USpriteRenderer* Renderer;
	float Speed = 230.0f;
	float DiagonalSpeed = 170.0f;

	EWorldPlayerDir Dir = EWorldPlayerDir::None;
};

