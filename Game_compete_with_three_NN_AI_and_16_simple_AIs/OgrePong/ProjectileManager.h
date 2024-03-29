#ifndef __ProjectileManager_h_
#define __ProjectileManager_h_

#include "Tank.h"

using namespace std;
namespace Ogre {
	class SceneNode;
    class SceneManager;
	class AxisAlignedBox;
}

class InputHandler;
class Tank;
class World;

class ProjectileManager
{
public:
	
	ProjectileManager(Ogre::SceneManager *sceneManager, InputHandler *input, World *world);
	~ProjectileManager(void);

	void spawnProjectile(void);
	void spawnProjectile2(void);
	void shootProjectile(const Ogre::Real& mTime);
	void shootProjectile2(const Ogre::Real& mTime);
	void despawnProjectile(void);
	void despawnProjectile2(void);
	void Think(const Ogre::Real& mTime);
	void setIterator(void);

	void addTank(Tank *t) {mTank = t;}

	Ogre::SceneManager *SceneManager() { return mSceneManager; }

protected:

	Ogre::SceneManager *mSceneManager;
	Ogre::SceneNode *mProjectileNode;
	const Ogre::AxisAlignedBox *mAABB;

	InputHandler *mInputHandler;
	Tank *mTank;
	World *mWorld;

	Tank::Node *iterator;

	bool comeDown;
	bool spawnedProjectile;
	bool shotProjectile;
};

#endif
