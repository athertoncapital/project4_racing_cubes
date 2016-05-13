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
class tensorflow;
class MotionObject;
class PongCamera;
class World;
class MovingObject;
class Tank : public MotionObject
{
public:
	int mean_ai1;
	int mean_ai2;
	int mean_ai3;
	void Tank::calculate_loss(int lab[6][5], int x[6][6401], float (&w1)[6401][66], float (&w2)[66][5], float *b1, float *b2);
	int Tank::prediction(int x[6][6401], float w1[6401][66], float w2[66][5], float b1[66], float b2[5]);
	void Tank::store(int c, int m, int i, int j);
	//Tank(Ogre::SceneManager *sceneManager, World* world);
    Tank(Ogre::SceneManager* sceneManager, World *world, Ogre::Vector3 dimension);
	void Tank::build_model(float w1[][66], float w2[], float b1[], float b2[], float z_2[], float reg_lambda, int nn_hdim, int num_passes, boolean print_loss);
	int ky;
	tensorflow *tf;
	~Tank(void);
	MovingObject *mObj1;
    MovingObject *mObj2;
	
    MovingObject *mObj3;
	MovingObject *mObj4;
	MovingObject *mObj5;
	MovingObject *mObj6;

    MovingObject *mSunObj;
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
	Ogre::SceneNode *mAI1;
	Ogre::SceneNode *mAI2;
	Ogre::SceneNode *mAI3;
	const Ogre::AxisAlignedBox *mAABB;
	Ogre::SceneNode *oMainNode;
	void addCamera(PongCamera *c,PongCamera *r, PongCamera *ai1, PongCamera *ai2, PongCamera *ai3) { mCamera = c, mCameraR = r, mCamera_ai1=ai1, mCamera_ai2=ai2, mCamera_ai3=ai3; }
	Ogre::SceneManager *SceneManager() { return mSceneManager; }
	//Ogre::Vector3 getPosition() const;
	
	void load();
	void move(const Ogre::Real time);
	void reverseHorizontalvelocity();
	void reverseVerticalvelocity();
	void reset();
	//for AI computing
	Ogre::Vector3 vec;
private:
	Ogre::Vector3 Tank::Normal(float u, float v);
	Ogre::Vector3 Tank::Tangent(float u, float v);
	Ogre::Vector3 Tank::Binormal(float u, float v);
	Ogre::Matrix3 Tank::Orientation(Ogre::Vector3 xBasis, Ogre::Vector3 yBasis, Ogre::Vector3 zBasis);
	Tank *mHumanPlayer;
	Ogre::SceneNode* mSceneNode;
	Ogre::Real mSpin;
protected:
	PongCamera *mCamera;
	PongCamera *mCameraR;
	PongCamera *mCamera_ai1;
	PongCamera *mCamera_ai2;
	PongCamera *mCamera_ai3;
	World *mWorld;
	Ogre::SceneNode *mTankNode;
	Ogre::SceneNode *mCameraNode;
	Ogre::SceneNode *mCameraNodeR;
	Ogre::SceneNode *mCameraNode_AI1;
	Ogre::SceneNode *mCameraNode_AI2;
	Ogre::SceneNode *mCameraNode_AI3;
	Ogre::SceneManager *mSceneManager;
	Ogre::SceneManager *mTempNode;
};

#endif
