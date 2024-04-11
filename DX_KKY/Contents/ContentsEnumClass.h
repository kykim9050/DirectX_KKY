#pragma once

enum class EActorType
{
	None,
	FilmEffect,
	BackGroundAnimation,
	BackGroundSubStaticObject,
	Map,
	Player,
	Dust,
};

enum class ERenderingOrder
{
	None,
	CollisionLayer,
	BackLayer,
	Animation,
	StaticObject,
	Object,
	Player,
	Dust,
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