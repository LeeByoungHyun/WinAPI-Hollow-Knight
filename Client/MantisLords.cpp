#include "MantisLords.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObject.h"
#include "yaResourceManager.h"
#include "yaSceneManager.h"

namespace ya
{
	MantisLords::MantisLords()
	{

	}
	MantisLords::~MantisLords()
	{

	}
	void MantisLords::Initialize()
	{
		Transform* tr = GetComponent<Transform>();

		hp = 100;

		mAnimator = AddComponent<Animator>();
	}
	void MantisLords::Update()
	{

	}
	void MantisLords::Render(HDC hdc)
	{

	}
	void MantisLords::Release()
	{

	}
	void MantisLords::OnCollisionEnter(Collider* other)
	{

	}
	void MantisLords::OnCollisionStay(Collider* other)
	{

	}
	void MantisLords::OnCollisionExit(Collider* other)
	{

	}

	void MantisLords::throneIdle()
	{
	}

	void MantisLords::throneBow()
	{
	}

	void MantisLords::throneStand()
	{
	}

	void MantisLords::throneLeave()
	{
	}

	void MantisLords::throneWounded()
	{
	}

	void MantisLords::dashArrive()
	{
	}

	void MantisLords::dashAnticipate()
	{
	}

	void MantisLords::dash()
	{
	}

	void MantisLords::dashRecover()
	{
	}

	void MantisLords::dashLeave()
	{
	}

	void MantisLords::wallArrive()
	{
	}

	void MantisLords::wallReady()
	{
	}

	void MantisLords::wallThrow()
	{
	}

	void MantisLords::wallLeave1()
	{
	}

	void MantisLords::wallLeave2()
	{
	}

	void MantisLords::death()
	{
	}

	void MantisLords::deathLeave()
	{
	}
	

}