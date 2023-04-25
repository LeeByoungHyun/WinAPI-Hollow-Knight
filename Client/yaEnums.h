#pragma once

enum class eSceneType
{
	Title,
	Tutorial,
	MainHall,
	Romm1,
	Boss,
	MantisLordsBoss,
	FalseKnightBoss,
	HornetBoss,
	Ending,
	End
};

enum class eLayerType	
{
	Manager,
	BG,
	BGObject,
	Object,
	Spike,
	Ground,
	Platform,
	BackEffect,
	Monster,
	Player,
	Hornet,
	FalseKnight,
	NeilEffect,
	SpellEffect,
	Effect,
	Wall,
	UI, 
	Fade,
	End
};

enum class eComponentType
{
	Transform,
	Collider,
	RigidBody,
	SpriteRenderer,
	Animator,
	Audio,
	End
};

enum class eDirection
{
	Left,
	Right
};