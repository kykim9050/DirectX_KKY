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
	DisplayEffect,
};

enum class ETitleRenderingOrder
{
	None,
	BackGroundImg,
	Animation,
	OldFilmEffect,
};

enum class EEndingRenderingOrder
{
	None,
	Animation,
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