#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class AOldFilmEffect : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AOldFilmEffect();
	~AOldFilmEffect();

	// delete Function
	AOldFilmEffect(const AOldFilmEffect& _Other) = delete;
	AOldFilmEffect(AOldFilmEffect&& _Other) noexcept = delete;
	AOldFilmEffect& operator=(const AOldFilmEffect& _Other) = delete;
	AOldFilmEffect& operator=(AOldFilmEffect&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CreateOFEFAnimation();

private:
	USpriteRenderer* Renderer;
};

