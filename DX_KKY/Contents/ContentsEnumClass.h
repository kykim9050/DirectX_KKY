#pragma once

enum class EActorType
{
	None,
	FilmEffect,
	BackGroundAnimation,
	BackGroundSubStaticObject,
	Map,
	Player,
};

enum class ERenderingOrder
{
	None,
	DisplayEffect,
};

enum class ETitleRenderingOrder
{
	None,

};

enum class EEndingRenderingOrder
{
	None,
	Animation,
	DisplayEffect,
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