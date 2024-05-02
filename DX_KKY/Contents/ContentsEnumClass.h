#pragma once

enum class EActorType
{
	None,
	ContentsCamera,
	FilmEffect,
	BackGroundAnimation,
	BackGroundSubStaticObject,
	Map,
	Player,
	Dust,
	Bullet,
	MonsterBullet,
	FX,
	Monster,
	BossMonster,
	Object,
	ScreenMsg,
	TimeScaleController,
	Max,
};

enum class ERenderingOrder
{
	None,
	CollisionLayer,
	BackLayer4,
	BackLayer3,
	BackLayer2,
	BackLayer1,
	Wave4,
	Wave3,
	Wave2,
	Animation,
	StaticObject,
	Object3,
	Object2,
	Object1,
	Monster2,
	Monster1,
	BossMonsterBackFX1,
	BossMonsterBackFX2,
	BossMonster,
	BossMonsterFrontFX1,
	BossMonsterFrontLayer1,
	BossMonsterObject1,
	BossMonsterObject2,
	MonsterBullet,
	MonsterBulletFX,
	Dust,
	PlayerBullet,
	PlayerBulletFx,
	BackFX,
	Player,
	FrontFX,
	FrontLayer,
	DockLog,
	Wave1,
	Message,
	Iris,
	OldFilmEffect,
};

enum class EPlayerKeyDir
{
	None,
	Up,
	RightUp,
	Right,
	RightDown,
	Down,
	LeftDown,
	Left,
	LeftUp,
};

enum class ECollisionGroup
{
	Player,
	PlayerBullet,
	Monster,
	MonsterBullet,
	Platform,
	PlayerFoot,
	Trap,
};

enum class EActorDir
{
	None,
	Left,
	Right,
};

enum class EBulletShootType
{
	None,
	JumpShoot,
	UpShoot,
	DiagonalUpShoot,
	StraightShoot,
	DiagonalDownShoot,
	DownShoot,
	DuckShoot,
	UpGSS,
	DiagonalUpGSS,
	StraightGSS,
	DiagonalDownGSS,
	DownGSS,
	AirSuperShoot
};

enum class ESeedColor
{
	None,
	Blue,
	Purple,
	Pink,
};