#include "Tank.h"
#include "Camera.h"
#include "World.h"
#include "PongObject.h"
#include "MotionObject.h"
#include "MovingObject.h"
#include "Properties.h"
#include "OgreVector3.h"
#include "Ogre.h"
#include "OgreAxisAlignedBox.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "SdkSample.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h> 


int id=0;
string ID = "AItank";


Tank::Tank(Ogre::SceneManager *sceneManager, World *world, Ogre::Vector3 dimension) :  MotionObject(sceneManager, dimension, 
																				   pong_0_SPEED, pong_MOVE_User_BOTTOM), mSceneManager(sceneManager), mWorld(world)
{
	mMainNode = SceneManager()->getRootSceneNode()->createChildSceneNode("U");
	mSpin = 1000;
	/* Create 1 user tank */
	createUserTank();
	mWorld->SceneManager()->getSceneNode("U")->setPosition(0,0,0);
	Ogre::Vector3 vUser=mWorld->SceneManager()->getSceneNode("U")->getPosition();
	//mWorld->Hpoint_y=mMainNode->getPosition().y;
	//mWorld->Hpoint_z=mMainNode->getPosition().z;
	/* Generate random seed to be used for spawn points */
	//srand ((unsigned)time(0));
	ky=3;
	//////////////////////////////////////////////////////////////////////////
	int Number = 0;       // number to be converted to a string
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	Node *node = new Node();
	Ogre::SceneNode *eTankNode;
	Ogre::Entity *tank = SceneManager()->createEntity("AItank0","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank0");
	eTankNode->setPosition(mWorld->spawnPoints[0]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);

	Ogre::Vector3 XBasis = Ogre::Vector3(-1,0, 0);
    Ogre::Vector3 YBasis = Ogre::Vector3(0,-1 ,0);
    Ogre::Vector3 ZBasis = Ogre::Vector3(0,0,1);
    Ogre::Matrix3 R;
    R.FromAxes(XBasis, YBasis, ZBasis);
	eTankNode->setOrientation(R);

	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	Ogre::Real time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
    Number = 1;       // number to be converted to a string
	Result;          // string which will contain the result  
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	node = new Node();
	
	tank = SceneManager()->createEntity("AItank1","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank1");
	eTankNode->setPosition(mWorld->spawnPoints[1]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	/*XBasis = Ogre::Vector3(-1,0, 0);
    YBasis = Ogre::Vector3(0,-1 ,0);
    ZBasis = Ogre::Vector3(0,0,1);
    R.FromAxes(XBasis, YBasis, ZBasis);
	eTankNode->setOrientation(R);*/
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	Number = 2;       // number to be converted to a string
	Result;          // string which will contain the result
	convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	node = new Node();
	eTankNode;
	tank = SceneManager()->createEntity("AItank2","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank2");
	eTankNode->setPosition(mWorld->spawnPoints[2]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	Number = 3;       // number to be converted to a string
	Result;          // string which will contain the result
	convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	node = new Node();
	eTankNode;
	tank = SceneManager()->createEntity("AItank3","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank3");
	eTankNode->setPosition(mWorld->spawnPoints[3]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);

	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank4","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank4");
	eTankNode->setPosition(mWorld->spawnPoints[4]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank5","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank5");
	eTankNode->setPosition(mWorld->spawnPoints[5]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank6","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank6");
	eTankNode->setPosition(mWorld->spawnPoints[6]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank7","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank7");
	eTankNode->setPosition(mWorld->spawnPoints[7]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank8","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank8");
	eTankNode->setPosition(mWorld->spawnPoints[8]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank9","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank9");
	eTankNode->setPosition(mWorld->spawnPoints[9]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank10","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank10");
	eTankNode->setPosition(mWorld->spawnPoints[10]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank11","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank11");
	eTankNode->setPosition(mWorld->spawnPoints[11]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);

	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank12","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank12");
	eTankNode->setPosition(mWorld->spawnPoints[12]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank13","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank13");
	eTankNode->setPosition(mWorld->spawnPoints[13]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank14","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank14");
	eTankNode->setPosition(mWorld->spawnPoints[14]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank15","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank15");
	eTankNode->setPosition(mWorld->spawnPoints[15]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank16","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank16");
	eTankNode->setPosition(mWorld->spawnPoints[16]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank17","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank17");
	eTankNode->setPosition(mWorld->spawnPoints[17]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank18","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank18");
	eTankNode->setPosition(mWorld->spawnPoints[18]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank19","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank19");
	eTankNode->setPosition(mWorld->spawnPoints[19]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank20","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank20");
	eTankNode->setPosition(mWorld->spawnPoints[20]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	time=mWorld->t;
	mWorld->Push(node);
	/*for (int i = 10; i < 50; i++) {
		createEnemyshell(i);
	}*/
	/*for (int i = 0; i < 5; i++) {
		createsatellite(i);
	}*/
	node = new Node();
	mObj1 = new MovingObject(mSceneManager, "ogrehead.mesh", NULL);
	mObj1->setPosition(mWorld->spawnPoints[1]);
	node->eTankNode = mObj1->mObjectSceneNode;
	node->eAABB = &mObj1->ent1->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);
	
	mObj2 = new MovingObject(mSceneManager, "MyCube.mesh", mObj1);
    mObj3 = new MovingObject(mSceneManager, "MyCube.mesh", mObj2);
	mObj4 = new MovingObject(mSceneManager, "MyCube.mesh", NULL);
	//mObj5 = new MovingObject(mSceneManager, "Ground.mesh", NULL);
	mObj5 = new MovingObject(mSceneManager, "XYZ_Function.mesh", NULL);

    mCrossHair = new MovingObject(mSceneManager, "Crosshair.mesh", NULL);
    mCrossHair->setScale(Ogre::Vector3(0.5F,1,1));
	mObj1->setScale(Ogre::Vector3(1.1F,1.1F,1.1F));
	//mObj5->setScale(Ogre::Vector3(30000,1.1F,30000));
	mObj5->setScale(Ogre::Vector3(1000,1000,1000));
    mObj1->setPosition(Ogre::Vector3(500, 20, 300));
    mObj2->setPosition(Ogre::Vector3(20, 0, 0));
    mObj3->setPosition(Ogre::Vector3(0, 20, 0));
	mObj4->setPosition(Ogre::Vector3(0, 0, 200));
	mObj5->setPosition(Ogre::Vector3(0, 0, 0));
	Ogre::Vector3 xBasis = Ogre::Vector3(1,0, 0);
    Ogre::Vector3 yBasis = Ogre::Vector3(0,0 ,1);
    Ogre::Vector3 zBasis = Ogre::Vector3(0,-1,0);
    Ogre::Matrix3 rotate;
    rotate.FromAxes(xBasis, yBasis, zBasis);
	mObj5->setOrientation(rotate);
    mCrossHair->setPosition(Ogre::Vector3(0,-20,0));
	Ogre::Vector3 pos;
    Ogre::Matrix3 orientation;

    mCrossHair->yaw(Ogre::Radian(Ogre::Math::PI / 2));

			

	Ogre::SceneNode *oMainNode;
	Ogre::Entity *mObj20 = SceneManager()->createEntity("ogrehead.mesh");
	oMainNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
	oMainNode->setPosition(Ogre::Vector3(250, 3, 0));
	oMainNode->attachObject(mObj20);
	oMainNode->scale(1, 1, 1);
	mo2ABB = &mObj20->getWorldBoundingBox();
	
	
}


Tank::~Tank(void)
{
}

/* Attach camera to the main user node */
void
Tank::attachCamera(void)
{
	mCameraNode = mMainNode->createChildSceneNode();
	mCameraNode->attachObject(mCamera->getCamera());
}
void Tank::Think(const Ogre::Real& mTime)
{
	mObj1->yaw(Ogre::Radian(0.5f * mTime));
    mObj2->pitch(Ogre::Radian(0.6f * mTime));
    mObj3->roll(Ogre::Radian(0.5f * mTime));
	mObj4->translate(mTime * Ogre::Vector3(-1, 0,0));
}

/* Creates user tank entity and node */
void
Tank::createUserTank(void)
{
	Ogre::Entity *tankEntity = SceneManager()->createEntity("Utank","Cube.mesh");
	mTankNode = mMainNode;
	//mTankNode = mMainNode->createChildSceneNode("U");
	//mTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("U");
	mTankNode->attachObject(tankEntity);
	mTankNode->scale(2,2,2);
	mTankNode->setPosition(0,0,0);
	 //mWorld->mHumanPlayer=mTankNode;
	/* DEBUGGING PURPOSES */
	mTankNode->showBoundingBox(false);

	mAABB = &tankEntity->getWorldBoundingBox();

	//mWorld->SceneManager()->getSceneNode("U");
	
	
	
	
	
	//->getRootSceneNode()->getChild("U");

}


/* Creates enemy tank entity and node */
void
Tank::createEnemyTank(int i)
{
	int Number = i;       // number to be converted to a string
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream

	ID.append(Result);
	//Node *node = new Node();
	Node *node = new Node();
	Ogre::SceneNode *eTankNode;
	Ogre::Entity *tank = SceneManager()->createEntity(ID,"Tank.mesh");
	
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode(ID);
	eTankNode->setPosition(mWorld->spawnPoints[i]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;

	/* DEBUGGING PURPOSES */
	node->eTankNode->showBoundingBox(false);
	Ogre::Real time=mWorld->t;
	//Ogre::SceneNode* sceneNode = getSceneNode();
	//eTankNode->translate((1,0,0) * getSpeed() * time *0.001);
	//eTankNode->roll(Ogre::Degree(mSpin*time));
	//eTankNode->translate(Ogre::Vector3( -1, 0, -1 )* time*0.1);


	/* Push new tank node onto AI tank list */
	mWorld->Push(node);
}
/* Creates enemy tank entity and node */
void
Tank::createEnemyshell(int i)
{

	//Node *node = new Node();
	Node *node = new Node();
	Ogre::SceneNode *eTankNode;
	Ogre::Entity *tank = SceneManager()->createEntity("XYZ_Function.mesh");
	
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
	eTankNode->setPosition(mWorld->spawnPoints[i]);
	eTankNode->attachObject(tank);
	eTankNode->scale(100, 100, 100);
	
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;

	/* DEBUGGING PURPOSES */
	node->eTankNode->showBoundingBox(false);
	Ogre::Real time=mWorld->t;
	//Ogre::SceneNode* sceneNode = getSceneNode();
	//eTankNode->translate((1,0,0) * getSpeed() * time *0.001);
	//eTankNode->roll(Ogre::Degree(mSpin*time));
	//eTankNode->translate(Ogre::Vector3( -1, 0, -1 )* time*0.1);


	/* Push new tank node onto AI tank list */
	mWorld->Push(node);
}
/* Creates enemy tank entity and node */
void
Tank::createsatellite(int i)
{

	//Node *node = new Node();
	Node *node = new Node();
	MovingObject *ob = new MovingObject(mSceneManager, "ogrehead.mesh", NULL);
	MovingObject *ob1 = new MovingObject(mSceneManager, "ogrehead.mesh", ob);
	MovingObject *ob2 = new MovingObject(mSceneManager, "ogrehead.mesh", ob1);
	MovingObject *ob3 = new MovingObject(mSceneManager, "ogrehead.mesh", ob2);
	MovingObject *mCHair = new MovingObject(mSceneManager, "Crosshair.mesh", NULL);

    mCHair->setScale(Ogre::Vector3(0.5F,1,1));
	mCHair->setPosition(100*(mWorld->spawnPoints[i]));
    mCHair->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	node->eTankNode = mCHair->mObjectSceneNode;
	node->eAABB = &mCHair->ent1->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);

	ob->setPosition(mWorld->spawnPoints[i]);
	node->eTankNode = ob->mObjectSceneNode;
	node->eAABB = &ob->ent1->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);

	ob1->setPosition(mWorld->spawnPoints[i]);
	node->eTankNode = ob1->mObjectSceneNode;
	node->eAABB = &ob1->ent1->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);

	ob2->setPosition(mWorld->spawnPoints[i]);
	node->eTankNode = ob2->mObjectSceneNode;
	node->eAABB = &ob2->ent1->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);

	ob3->setPosition(mWorld->spawnPoints[i]);
	node->eTankNode = ob3->mObjectSceneNode;
	node->eAABB = &ob3->ent1->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);

}

void
Tank::destroyTank(Node *node)
{
	node->eTankNode->detachAllObjects();
	int temp = mWorld->getUserScore();
	temp++;
	mWorld->setUserScore(++temp);

	node->destroyed = true;
}
void
Tank::destroyshell(Node *node)
{
	node->eTankNode->detachAllObjects();
	int temp = mWorld->getUserScore();
	mWorld->setUserScore(++temp);
	node->destroyed = true;
}

void
Tank::respawnEnemyTank(Node *node)
{
	Ogre::Entity *tankEntity = SceneManager()->createEntity("coin.mesh");
	node->eTankNode->attachObject(tankEntity);
	node->eAABB = &tankEntity->getWorldBoundingBox();
	node->destroyed = false;
}

void Tank::move(const Ogre::Real time) {
	Ogre::SceneNode* sceneNode = getSceneNode();
	sceneNode->translate(getvelocity() * getSpeed() * time);
	sceneNode->roll(Ogre::Degree(mSpin*time));
}

void Tank::load() {
	Ogre::SceneManager* sceneManager = getSceneManager();
	Ogre::Entity* entity = sceneManager->createEntity("Sphere.mesh");
	setEntity(entity);
}

void Tank::reverseHorizontalvelocity() {
	setvelocity(getvelocity() * HORIZONTAL_REVERSE_FACTOR);
}

void Tank::reverseVerticalvelocity() {
	setvelocity(getvelocity() * VERTICAL_REVERSE_FACTOR);
}

void Tank::reset() {
	setPosition(pong_0_POSITION);
	setSpeed(pong_0_SPEED);
}