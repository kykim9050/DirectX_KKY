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
};

enum class ERenderingOrder
{
	None,
	CollisionLayer,
	BackLayer,
	Animation,
	StaticObject,
	Object,
	Dust,
	PlayerBullet,
	Player,
	FrontLayer,
	OldFilmEffect,
};

enum class EWorldPlayerDir
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

enum class EActorDir
{
	None,
	Left,
	Right,
};