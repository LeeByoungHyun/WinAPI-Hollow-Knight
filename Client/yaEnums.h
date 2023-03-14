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
	Monster,
	Player,
	Effect,
	UI, 
	End
};

enum class eComponentType
{
	Transform,
	Collider,
	SpriteRenderer,
	Animator,
	Audio,
	End
};