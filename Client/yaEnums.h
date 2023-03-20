#pragma once

enum class eSceneType
{
	Title,
	MainHall,
	Romm1,
	Boss,
	MantisLordsBoss,
	Ending,
	End
};

enum class eLayerType	
{
	BG,
	BGObject,
	Ground,
	BackEffect,
	Monster,
	Player,
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