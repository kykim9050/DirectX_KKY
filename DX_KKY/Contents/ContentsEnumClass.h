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
	FX,
	BossMonster,
};

enum class ERenderingOrder
{
	None,
	CollisionLayer,
	BackLayer3,
	BackLayer2,
	BackLayer,
	Animation,
	StaticObject,
	Object,
	BossMonster,
	Dust,
	PlayerBullet,
	PlayerBulletFx,
	Player,
	FrontLayer,
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

enum class ECollisionOrder
{
	Player,
	PlayerBullet,
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

