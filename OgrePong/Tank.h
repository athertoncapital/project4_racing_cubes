#ifndef __Tank_h_
#define __Tank_h_
#include "MotionObject.h"
#include "Ogre.h"
#include <string>
#include <iostream>
using namespace std;
namespace Ogre {
	class SceneNode;
	class SceneManager;
	class AxisAlignedBox;
	class Vector3;
}

class MotionObject;
class PongCamera;
class World;
class MovingObject;
class Tank : public MotionObject
{
public:
	//Tank(Ogre::SceneManager *sceneManager, World* world);
	int ky;

	~Tank(void);
	MovingObject *mObj1;
    MovingObject *mObj2;
	
    MovingObject *mObj3;
	MovingObject *mObj4;
	MovingObject *mObj5;
	MovingObject *mObj6;
	void Tank::Think(const Ogre::Real& mTime);
    MovingObject *mCrossHair;
	/* Node used to hold scene node for AI tank, bounding box, and next tank */
	typedef struct Node {
		Ogre::SceneNode *eTankNode;
		const Ogre::AxisAlignedBox *eAABB;
		MovingObject *ob;
		Node *next;
		bool destroyed;
	} mNode;
	Node *head;
	
	const Ogre::AxisAlignedBox *mo2ABB;
	void attachCamera(void);
	void createUserTank(void);
	void createEnemyTank(int i);
	void createEnemyshell(int i);
	void createsatellite(int i);
	void destroyshell(Node *node);
	void destroyTank(Node *node);
	void respawnEnemyTank(Node *node);

	/* Node for user tank */
	Ogre::SceneNode *mMainNode;
	const Ogre::AxisAlignedBox *mAABB;
	Ogre::SceneNode *oMainNode;
	void addCamera(PongCamera *c) { mCamera = c; }
	Ogre::SceneManager *SceneManager() { return mSceneManager; }
	//Ogre::Vector3 getPosition() const;
	Tank(Ogre::SceneManager* sceneManager, World *world, Ogre::Vector3 dimension);
	void load();
	void move(const Ogre::Real time);
	void reverseHorizontalvelocity();
	void reverseVerticalvelocity();
	void reset();
	//for AI computing
	Ogre::Vector3 vec;
private:
	Tank *mHumanPlayer;
	Ogre::SceneNode* mSceneNode;
	Ogre::Real mSpin;
protected:
	PongCamera *mCamera;
	World *mWorld;
	Ogre::SceneNode *mTankNode;
	Ogre::SceneNode *mCameraNode;
	Ogre::SceneManager *mSceneManager;
};

#endif
