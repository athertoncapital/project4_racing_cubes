#include "ProjectileManager.h"
#include "InputHandler.h"
#include "Tank.h"
#include "World.h"
#include "PongObject.h"
#include "Ogre.h"
#include "OgreSceneManager.h"
#include "OgreAxisAlignedBox.h"
#include <string>
#include <iostream>


ProjectileManager::ProjectileManager(Ogre::SceneManager *sceneManager, InputHandler *input, World *world) : mSceneManager(sceneManager), mInputHandler(input), mWorld(world)
{
	comeDown = false;
	shotProjectile = false;
	spawnedProjectile = false;
	mWorld->PROJECTILE_SPEED_H=100;
	mWorld->PROJECTILE_SPEED_V=100;
}


ProjectileManager::~ProjectileManager(void)
{
}
string pID = "s";
int pi = 0;
/* Spawn projectile when user wants to shoot it */
void
ProjectileManager::spawnProjectile(void)
{
	pi++;
	int Number = pi;       // number to be converted to a string
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	pID.append(Result);
	/* If there is no current projectile that was shot */
	if (!shotProjectile) {
		Ogre::Entity *projectile = SceneManager()->createEntity("Sphere.mesh");
		
		///* Projectile is child of tank, so that it spawns wherever the tank is */
		//mProjectileNode = mTank->mMainNode->createChildSceneNode(pID);
		//mProjectileNode->attachObject(projectile);

		//mProjectileNode->scale(2,2,4);

		//// Debugging purposes 
		//mProjectileNode->showBoundingBox(false);
		//
		//mAABB = &projectile->getWorldBoundingBox();
	}
}

string cID = "c";
int ci = 0;

void
ProjectileManager::spawnProjectile2(void)
{
	ci++;
	int Number = ci;       // number to be converted to a string
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	cID.append(Result);
	/* If there is no current projectile that was shot */
	if (!shotProjectile) {
		Ogre::Entity *projectile = SceneManager()->createEntity("Cube.mesh");//Missle
		
		/* Projectile is child of tank, so that it spawns wherever the tank is */
		//mProjectileNode = mTank->mMainNode->createChildSceneNode(cID);
		mProjectileNode->attachObject(projectile);

		mProjectileNode->scale(2,2,10);

		// Debugging purposes 
		mProjectileNode->showBoundingBox(false);
		
		mAABB = &projectile->getWorldBoundingBox();
	}
}

void
ProjectileManager::shootProjectile(const Ogre::Real& mTime)
{
	

	/* User just shot the projectile */
	shotProjectile = true;

	/* Projectile going up */
	if (mProjectileNode->getPosition().y < 30 && comeDown == false)
	{
		mProjectileNode->translate(0, mTime * mWorld->PROJECTILE_SPEED_V, 0, Ogre::Node::TS_LOCAL);
		mProjectileNode->translate(0, 0, mTime * 8 * mWorld->PROJECTILE_SPEED_H, Ogre::Node::TS_LOCAL);
	}





	/* Projectile hit peak */
	else if (mProjectileNode->getPosition().y >= 30 && comeDown == false)
	{
		comeDown = true;
	}

	/* Projectile going down */
	else if (comeDown == true && mProjectileNode->getPosition().y > 0)
	{
		mProjectileNode->translate(0, -mTime * mWorld->PROJECTILE_SPEED_V, 0, Ogre::Node::TS_LOCAL);
		mProjectileNode->translate(0, 0, mTime * 8 * mWorld->PROJECTILE_SPEED_H, Ogre::Node::TS_LOCAL);
	}

	/* Projectile hit the ground */
	if (mProjectileNode->getPosition().y <= 0 && comeDown == true)
	{
		comeDown = false;
		shotProjectile = false;
		despawnProjectile();
	}
}
void
ProjectileManager::shootProjectile2(const Ogre::Real& mTime)
{
	const float PROJECTILE_SPEED = 10;

	/* User just shot the projectile */
	shotProjectile = true;

	/* Projectile going up */
	if (mProjectileNode->getPosition().y < 1000 && comeDown == false)
	{
		mProjectileNode->translate(0, mTime * mWorld->PROJECTILE_SPEED_V, 0, Ogre::Node::TS_LOCAL);
		mProjectileNode->translate(0, 0, mTime * 9.8F * mWorld->PROJECTILE_SPEED_H, Ogre::Node::TS_LOCAL);
	}

	/* Projectile hit peak */
	else if (mProjectileNode->getPosition().y >= 1000 && comeDown == false)
	{
		comeDown = true;
	}

	/* Projectile going down */
	else if (comeDown == true && mProjectileNode->getPosition().y > 0)
	{
		mProjectileNode->translate(0, -mTime * mWorld->PROJECTILE_SPEED_V*0.5F, 0, Ogre::Node::TS_LOCAL);
		mProjectileNode->translate(0, 0, mTime * 9.8F * mWorld->PROJECTILE_SPEED_H, Ogre::Node::TS_LOCAL);
	}

	/* Projectile hit the ground */
	if (mProjectileNode->getPosition().y <= 0 && comeDown == true)
	{
		comeDown = false;
		shotProjectile = false;
		despawnProjectile2();
	}
}
/* Make projectile disappear */
void
ProjectileManager::despawnProjectile()
{
	mProjectileNode->detachAllObjects();
}
void
ProjectileManager::despawnProjectile2()
{
	mProjectileNode->detachAllObjects();
}

/* Initialize iterator to head of AI tank list */
void
ProjectileManager::setIterator(void)
{
	iterator = mWorld->tanks->head;
}

void
ProjectileManager::Think(const Ogre::Real& mTime)
{
	//if (mInputHandler->IsKeyDown(OIS::KC_H))
	//{
	//	mWorld->PROJECTILE_SPEED_H+=5;
	//}
	//if (mInputHandler->IsKeyDown(OIS::KC_G))
	//{
	//	mWorld->PROJECTILE_SPEED_H-=5;
	//}
	//if (mInputHandler->IsKeyDown(OIS::KC_V))
	//{
	//	mWorld->PROJECTILE_SPEED_V+=5;
	//}
	//if (mInputHandler->IsKeyDown(OIS::KC_C))
	//{
	//	mWorld->PROJECTILE_SPEED_V-=5;
	//}

}