#pragma once

enum class eSceneType
{
	Title,
	MainHall,
	Romm1,
	Boss,
	MantisLordsBoss,
	FalseKnightBoss,
	Ending,
	End
};

enum class eLayerType	
{
	Manager,
	BG,
	BGObject,
	Object,
	Ground,
	Wall,
	BackEffect,
	Monster,
	Player,
	NeilEffect,
	SpellEffect,
	Effect,
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