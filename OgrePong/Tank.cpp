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
#include "wingdi.h"
#include <Windows.h>
#include <sstream>
#include <fstream>      // std::ifstream, std::ofstream

#include "tensorflow.h"

 #define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}


int id=0;
string ID = "AItank";


Tank::Tank(Ogre::SceneManager *sceneManager, World *world, Ogre::Vector3 dimension) :  MotionObject(sceneManager, dimension, 
																				   pong_0_SPEED, pong_MOVE_User_BOTTOM), mSceneManager(sceneManager), mWorld(world)
{

   
    // Create background material
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("space.jpg");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
 
    // Create background rectangle covering the whole screen
    Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
    rect->setCorners(-1.0, 1.0, 1.0, -1.0);
    rect->setMaterial("Background");
 
    // Render the background before everything else
    rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
 
    // Use infinite AAB to always stay visible
    Ogre::AxisAlignedBox aabInf;
    aabInf.setInfinite();
    rect->setBoundingBox(aabInf);
 
    // Attach background to the scene
    Ogre::SceneNode* New_node = SceneManager()->getRootSceneNode()->createChildSceneNode("Background");
    New_node->attachObject(rect);
    
    
    //-----------------------------------------------
	mMainNode = SceneManager()->getRootSceneNode()->createChildSceneNode("U");
	mSpin = 1000;
	/* Create 1 user tank */
	createUserTank();
	mWorld->SceneManager()->getSceneNode("U")->setPosition(100,100,100);
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
	Ogre::Entity *tank = SceneManager()->createEntity("AItank1","Cube.mesh");
	mAI1 = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank1");
	mAI1->setPosition(mWorld->spawnPoints[1]);
	mAI1->attachObject(tank);
	mAI1->scale(10, 10, 10);

	Ogre::Vector3 XBasis = Ogre::Vector3(-1,0, 0);
    Ogre::Vector3 YBasis = Ogre::Vector3(0,-1 ,0);
    Ogre::Vector3 ZBasis = Ogre::Vector3(0,0,1);
    Ogre::Matrix3 R;
    R.FromAxes(XBasis, YBasis, ZBasis);
	mAI1->setOrientation(R);

	node->eTankNode = mAI1;
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
	
	tank = SceneManager()->createEntity("AItank0","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank0");
	eTankNode->setPosition(mWorld->spawnPoints[0]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
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
	tank = SceneManager()->createEntity("AItank2","Cube.mesh");
	mAI2 = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank2");
	mAI2->setPosition(mWorld->spawnPoints[2]);
	mAI2->attachObject(tank);
	mAI2->scale(10, 10, 10);
	node->eTankNode = mAI2;
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
	tank = SceneManager()->createEntity("AItank3","Cube.mesh");
	mAI3 = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank3");
	mAI3->setPosition(mWorld->spawnPoints[3]);
	mAI3->attachObject(tank);
	mAI3->scale(10, 10, 10);
	node->eTankNode = mAI3;
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);

	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("StaticCube1","Penguin.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube1");
	//eTankNode->setPosition(mWorld->spawnPoints[20]);
	eTankNode->attachObject(tank);
	eTankNode->scale(1, 1, 1);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);
	eTankNode->setPosition(1000*cos(1)+1000*cos(1/2)*cos(1)*(1/3),1000*sin(1)+1000*cos(1/2)*sin(1)*(1/3),1000*sin(1/2)*(1/3));
	eTankNode->translate(Normal(1, 1/3)*30);
	eTankNode->setOrientation(Orientation(Binormal(1, 1/3),Normal(1, 1/3),Tangent(1,1/3)));
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("StaticCube2","Penguin.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube2");
	//eTankNode->setPosition(mWorld->spawnPoints[20]);
	eTankNode->attachObject(tank);
	eTankNode->scale(1, 1, 1);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);
	eTankNode->setPosition(1000*cos(80)+1000*cos(1/2)*cos(80)*(1/3),1000*sin(80)+1000*cos(1/2)*sin(80)*(1/3),1000*sin(1/2)*(1/3));
	eTankNode->translate(Normal(80, 1/3)*30);
	eTankNode->setOrientation(Orientation(Binormal(80, 1/3),Normal(80, 1/3),Tangent(80,1/3)));
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("StaticCube3","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube3");
	//eTankNode->setPosition(mWorld->spawnPoints[20]);
	eTankNode->attachObject(tank);
	eTankNode->scale(1, 1, 1);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);
	float u =40;
	float v =0.3;
	eTankNode->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	eTankNode->translate(Normal(u, v)*30);
	eTankNode->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("StaticCube4","Sphere.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube4");
	//eTankNode->setPosition(mWorld->spawnPoints[20]);
	eTankNode->attachObject(tank);
	eTankNode->scale(1, 1, 1);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);
	u =30;
	v =0.2;
	eTankNode->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	eTankNode->translate(Normal(u, v)*30);
	eTankNode->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("StaticCube5","ogrehead.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube5");
	//eTankNode->setPosition(mWorld->spawnPoints[20]);
	eTankNode->attachObject(tank);
	eTankNode->scale(1, 1, 1);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);
	u =20;
	v =0.1;
	eTankNode->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	eTankNode->translate(Normal(u, v)*30);
	eTankNode->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("StaticCube6","Penguin.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube6");
	//eTankNode->setPosition(mWorld->spawnPoints[20]);
	eTankNode->attachObject(tank);
	eTankNode->scale(1, 1, 1);
	node->eTankNode = eTankNode;
	node->eAABB = &tank->getWorldBoundingBox();
	node->destroyed = false;
	mWorld->Push(node);
	eTankNode->setPosition(1000*cos(10)+1000*cos(1/2)*cos(10)*(1/3),1000*sin(10)+1000*cos(1/2)*sin(10)*(1/3),1000*sin(1/2)*(1/3));
	eTankNode->translate(Normal(10, 1/3)*30);
	eTankNode->setOrientation(Orientation(Binormal(10, 1/3),Normal(10, 1/3),Tangent(10,1/3)));

	for(int s=7;s<17;s++)
	{
	string ID = "StaticCube";
	string Result;          // string which will contain the result  
	ostringstream convert;
	convert << s;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);

	node = new Node();
	if(rand()%3==0)
	tank = SceneManager()->createEntity(ID,"ogrehead.mesh");
	else if(s%3==1)
	tank = SceneManager()->createEntity(ID,"tudorhouse.mesh");
	else
	tank = SceneManager()->createEntity(ID,"XYZ_Function.001.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode(ID);
	eTankNode->attachObject(tank);
	eTankNode->scale(0.3f, 0.3f, 0.3f);
	//node->eTankNode = eTankNode;
	//node->eAABB = &tank->getWorldBoundingBox();
	//node->destroyed = false;
	//mWorld->Push(node);
	//u =s%180;
	u=s;
	if(rand()%2==0)
	v =(rand()%10)/100.0f-0.1;
	else
		v =-(rand()%10)/100.0f-0.1;
	eTankNode->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	eTankNode->translate(Normal(u, v)*5);
	eTankNode->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));
	}


	//for (int i = 0; i < 500; i++) {
		//createEnemyshell(i);
	//}
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
	mObj5 = new MovingObject(mSceneManager, "XYZ_Function.mesh", NULL);
    

    mSunObj = new MovingObject(mSceneManager,"Icosphere.mesh",NULL);
    mSunObj->setPosition(Ogre::Vector3(1500, 2000, -700));
    mSunObj->setScale(Ogre::Vector3(1000, 1000, 1000));

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
	mCameraNode_AI1 = mAI1->createChildSceneNode();
	mCameraNode_AI2 = mAI2->createChildSceneNode();
	mCameraNode_AI3 = mAI3->createChildSceneNode();
	mCameraNode->attachObject(mCamera->getCamera());
	mCameraNode->attachObject(mCameraR->getCamera());
	mCameraNode_AI1->attachObject(mCamera_ai1->getCamera());
	mCameraNode_AI2->attachObject(mCamera_ai2->getCamera());
	mCameraNode_AI3->attachObject(mCamera_ai3->getCamera());

	//mTempNode=SceneManager()->getSceneNode("AItank0");
}
void Tank::Think(const Ogre::Real& mTime)
{
	mObj1->yaw(Ogre::Radian(0.5f * mTime));
    mObj2->pitch(Ogre::Radian(0.6f * mTime));
    mObj3->roll(Ogre::Radian(0.5f * mTime));
	mObj4->translate(mTime * Ogre::Vector3(-1, 0,0));
	int k =Ogre::ControllerManager::getSingleton().getElapsedTime();
	int c = k%4;//for selecting frame storages
	if(k%10==0){
	Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual(
         "MainRenderTarget", 
         Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
         Ogre::TextureType::TEX_TYPE_2D, 
         80,
         80,
		 20,
		 0,
		 Ogre::PixelFormat::PF_R8G8B8,
	     Ogre::TextureUsage::TU_RENDERTARGET);

   Ogre::RenderTexture *renderTexture = tex->getBuffer()->getRenderTarget();

   renderTexture->addViewport(mCamera_ai1->getCamera(),0);
   //renderTexture->addViewport(mCamera_ai1->getCamera(),1,0.4f, 0.75f, 0.5, 0.15);
   int count = renderTexture->getNumViewports();
   
   renderTexture->getViewport(0)->setClearEveryFrame(true);
   renderTexture->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
   renderTexture->getViewport(0)->setOverlaysEnabled(true);

   //renderTexture->getViewport(1)->setClearEveryFrame(true);
   //renderTexture->getViewport(1)->setBackgroundColour(Ogre::ColourValue::Black);
   //renderTexture->getViewport(1)->setOverlaysEnabled(true);
   renderTexture->update();
	string ID = "ai1_Render";
	string exd = ".bmp";
	string Result;          // string which will contain the result  
	ostringstream convert;
	convert << k;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	ID.append(exd);
   // Now save the contents
   renderTexture->writeContentsToFile(ID);
   string id=ID;
	char *infile = new char[id.length() + 1]; //argv[2];
	strcpy(infile, id.c_str());
	string bintxtID = "binary_in_txt";
	exd = ".txt";
	string bintxtResult;          // string which will contain the result  
	ostringstream bintxtconvert;
	bintxtconvert << k;      // insert the textual representation of 'Number' in the characters in the stream
	bintxtResult = bintxtconvert.str(); // set 'Result' to the contents of the stream
	bintxtID.append(bintxtResult);
	bintxtID.append(exd);
	char *outfile = new char[bintxtID.length() + 1]; //argv[3];
	strcpy(outfile, bintxtID.c_str());
    //char* outfile = "try2.txt";
	ofstream fout;
    ifstream fin;
	string binID = "bindata";
	exd = ".dat";
	string binResult;          // string which will contain the result  
	ostringstream binconvert;
	binconvert << k;      // insert the textual representation of 'Number' in the characters in the stream
	binResult = binconvert.str(); // set 'Result' to the contents of the stream
	binID.append(binResult);
	binID.append(exd);
	fout.open(binID,ios::binary);

	string readID = "readable";
	exd = ".txt";
	string readResult;          // string which will contain the result  
	ostringstream readconvert;
	readconvert << k;      // insert the textual representation of 'Number' in the characters in the stream
	readResult = readconvert.str(); // set 'Result' to the contents of the stream
	readID.append(readResult);
	readID.append(exd);
	ofstream outtxt( readID );
	 // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
		DBOUT("Could not open%s.\n ");
    }
	//create the foo array for storing the bmp image
	int foo [81][81];

    // open output file
    FILE* outptr = fopen(outfile, "w");
    /*if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);

    }*/
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	//DBOUT("padding: " << padding);
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
    //DBOUT("bi.biHeight: " << bi.biHeight);
	//DBOUT("bi.biWidth: " << bi.biWidth);
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
	//DBOUT("triple.rgbtBlue: " << triple.rgbtBlue);
	//DBOUT("triple.rgbtRed: " << triple.rgbtRed);
	//DBOUT("triple.rgbtGreen: " << triple.rgbtGreen);
	mean =(int)(triple.rgbtBlue+triple.rgbtRed+triple.rgbtGreen)/3;
	//char b[] = {mean};
	//write in ascii
	//std::string buf = "";
	//char str[20];
	//buf += itoa(mean, str, 10);
	//write in char
	//ostringstream a;
	//a << mean;

	//store into foo[81][81] array
	foo [i][j]=mean;
	
	store(c, mean, i, j);
	//write in text file 
	outtxt << mean << flush;
	outtxt << " "<< flush;
	//DBOUT("mean: " << mean);
            // write RGB triple to outfile
            fwrite(&mean, sizeof(int), sizeof(mean), outptr);
			fout.write((char*)&mean,sizeof(int));
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++){
			store(c,0x00 , i, k);
			foo[i][k];
            fputc(0x00, outptr);
			outtxt << 0x00 << flush;
			outtxt << " "<< flush;
		}
		outtxt << endl;
    }
    // close infile
    fclose(inptr);
    // close outfile
	fout.close();
	fin.open(binID,ios::binary);
	for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
			int my_int2;
			fin.read((char*)&my_int2,sizeof(int));
			//DBOUT("my_int2: " << my_int2);
		}
	}
	fin.close();
    fclose(outptr);
	outtxt.close();
	delete [] infile;

	
    tf = new tensorflow(mWorld);
	int num_examples = 80*80; // training set size
    int nn_input_dim = 2; // input layer dimensionality
    int nn_output_dim = 1; // output layer dimensionality
	// Gradient descent parameters (I picked these by hand)
    float epsilon = 0.01f;// learning rate for gradient descent
    float reg_lambda = 0.01f;// regularization strength
	float bar[161];
	for(int i=0;i<80;i++)
	{
		for(int j=0; j<80;j++)
		{
			bar[i+j]=foo[i][j];
		}
	}



	int SwitchMode =1;
	/*training
	* input: bar[161]
	* ouput: corrected parameters
	*/
	if(SwitchMode==1){
		int conv[79][79];

		for (int i = 0; i<80; i++ )
		{
			for (int j = 0; j<80; j++ )
			{
					int tmp= tanh(mean);
			        foo[i][j]=tmp;
			}
		}
	}
	/*prediction
	* input: corrected parameters, and foo[81][81]
	* output: control command
	*/
	else if(SwitchMode==2)
	{
		//TODO
	}



	}
}

float
Tank::calculate_loss(float w1[][66], float w2[], float b1[], float b2[], float z_2[], float reg_lambda)
{
	for(int i=0;i<65;i++)
	{
		for(int j=0; j< 161; j++)
		{
			for(int k=0; k< 65; k++)
			{
				z_2[i] += w1[j][k]* (mWorld->frame0[j]);
			}
		}
		z_2[i]+= b1[i];
	}
	float a_2[66];
	for(int i=0; i<65; i++)
	{
		a_2[i] = tanh(z_2[i]);
	}
	float z_3[4];
	for(int i=0; i<4; i++)
	{
		z_3[i] += w2[i] * a_2[i] +b2[i];
	}
	//get unnormalized probabilities
	float exp_scores[66];
	for(int i=0; i<65; i++)
	{
		exp_scores[i] = exp(z_2[i]);
	}
	//normalize them for each example
	float norm=0.0f;
	for(int i=0; i<65; i++)
	{
		norm += exp_scores[i];
	}
	float probs[66];
	for(int i=0; i<65; i++)
	{
		probs[i] = exp_scores[i]/norm;
	}
	//Calculating the loss
	float corect_logprobs[66];
	for(int i=0; i<65; i++)
	{
		corect_logprobs[i] = -log(probs[i]);
	}
	//compute the loss: average cross-entropy loss and regularization
	float data_loss =0.0f;
	for(int i=0; i<65; i++)
	{
		data_loss += corect_logprobs[i];
	}
	// Add regulatization term to loss (optional)
	float sum_w1=0.0f;
	for(int j=0; j< 80; j++)
		{
			for(int k=0; k< 80; k++)
			{
				sum_w1 += w1[j][k]* w1[j][k];
			}
		}
	float sum_w2=0.0f;
	for(int i=0; i<4; i++)
	{
		sum_w2 += w2[i];
	}
    data_loss += reg_lambda*0.5f * (sum_w1) + sum_w2;
	return 1.0f/65 * data_loss;
}
/*
*This function learns parameters for the neural network and returns the model.
* - nn_hdim: Number of nodes in the hidden layer, default = 65
* - num_passes: Number of passes through the training data for gradient descent
* - print_loss: If True, print the loss every 1000 iterations
*/
void
	Tank::build_model(float w1[][66], float w2[], float b1[], float b2[], float z_2[], float reg_lambda, int nn_hdim, int num_passes, boolean print_loss){
		//Initialize the parameters to random values. We need to learn these.
		int HI = 1;
		int LO = 0;
		//float r = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
		for(int j=0; j< 80; j++)
		{
			for(int k=0; k< 80; k++)
			{
				w1[j][k]= LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
			}
		}
		for(int i=0; i<4; i++)
		{
			w2[i] = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
		}
		for(int j=0; j< 65; j++)
		{
			b1[j] = 1;
		}
		for(int j=0; j< 4; j++)
		{
			b2[j] = 1;
		}
		//Gradient descent. For each batch...
		for(int i=0; i< num_passes; i++){
			//Forward propagation
			for(int i=0;i<66;i++)
			{
				for(int j=0; j< 80; j++)
				{
					for(int k=0; k< 80; k++)
					{
						z_2[i] += w1[j][k]* (mWorld->frame0[j]);
					}
				}
				z_2[i]+= b1[i];
			}
			float a_2[66];
			for(int i=0; i<65; i++)
			{
				a_2[i] = tanh(z_2[i]);
			}
			float z_3[4];
			for(int i=0; i<4; i++)
			{
				z_3[i] += w2[i] * a_2[i] +b2[i];
			}
			//get unnormalized probabilities
			float exp_scores[5];
			for(int i=0; i<4; i++)
			{
				exp_scores[i] = exp(z_3[i]);
			}
			//normalize them for each example
			float norm=0.0f;
			for(int i=0; i<4; i++)
			{
				norm += exp_scores[i];
			}
			float probs[5];
			for(int i=0; i<4; i++)
			{
				probs[i] = exp_scores[i]/norm;
			}

		
			//Backpropagation: backpropate the gradient to the parameters (W,b)
			float delta3[5];
			for(int i=0; i<4; i++)
			{
				delta3[i]=probs[i]-1;
			}
			float dW2[5];
			for(int i=0; i<4; i++)
			{
				dW2[i]=a_2[i] * delta3[i];
			}
			float db2 =0.0f;
			for(int i=0; i<4; i++)
			{
				db2+=delta3[i];
			}
			// delta3.dot(W2.T)
			float delta2[5];

			for(int i=0; i<4; i++)
			{
				delta2[i]=delta3[i]*w2[i];
			}

			//Add regularization terms (b1 and b2 don't have regularization terms)
			//Gradient descent parameter update (Assign new parameters to the model)
			
		}

}


/*Store inputs*/
void
Tank::store(int c, int m, int i, int j)
{
	if(c==0)
	{
		mWorld->frame0[i]=m;
	}
	else if(c==1)
	{
		mWorld->frame1[i][j]=m;
	}
	else if(c==2)
	{
		mWorld->frame2[i][j]=m;
	}
	else if(c==3)
	{
		mWorld->frame3[i][j]=m;
	}
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
	mTankNode->scale(10,10,10);
	mTankNode->setPosition(100,100,100);
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
	//node->eAABB = &tank->getWorldBoundingBox();
	//node->destroyed = false;

	/* DEBUGGING PURPOSES */
	//node->eTankNode->showBoundingBox(false);
	//Ogre::Real time=mWorld->t;


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
	Ogre::Entity *tank = SceneManager()->createEntity("Penguin.mesh");
	
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
	//eTankNode->setPosition(mWorld->spawnPoints[i]);

	int u=i%80;
	float V=0.5f;
	eTankNode->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(V),1000*sin(u)+1000*cos(u/2)*sin(u)*(V),1000*sin(u/2)*(V));
	eTankNode->setOrientation(Orientation(Binormal(u, V),Normal(u, V),Tangent(u,V)));
	eTankNode->translate(Normal(u, V)*30);
	eTankNode->attachObject(tank);
	eTankNode->scale(1, 1, 1);
	
	//node->eTankNode = eTankNode;
	//node->eAABB = &tank->getWorldBoundingBox();
	//node->destroyed = false;

	/* DEBUGGING PURPOSES */
	//node->eTankNode->showBoundingBox(false);
	//Ogre::Real time=mWorld->t;
	//Ogre::SceneNode* sceneNode = getSceneNode();
	//eTankNode->translate((1,0,0) * getSpeed() * time *0.001);
	//eTankNode->roll(Ogre::Degree(mSpin*time));
	//eTankNode->translate(Ogre::Vector3( -1, 0, -1 )* time*0.1);


	/* Push new tank node onto AI tank list */
	//mWorld->Push(node);
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
Ogre::Vector3 Tank::Normal(float u, float v){
	float kappa = 1;
	
	float A=kappa*(-sin(u)+ v*((-1/2)*sin(u/2)*cos(u)-cos(u/2)*sin(u)));
	float B=kappa*(cos(u)+ v*((-1/2)*sin(u/2)*sin(u)+cos(u/2)*cos(u)));
	float C=kappa*((v/2)*cos(u/2));
	float D=kappa*(cos(u/2)*cos(u));
	float E=kappa*(cos(u/2)*sin(u));
	float F=kappa*(sin(u/2));

	float N_x = B*F-C*E;
	float N_y = C*D-A*F;
	float N_z = A*E-B*D;
	Ogre::Vector3 N = Ogre::Vector3(N_x,N_y,N_z);
	return N;
}
Ogre::Vector3 Tank::Tangent(float u, float v){
	float kappa = 1;
	
	float A=kappa*(-sin(u)+ v*((-1/2)*sin(u/2)*cos(u)-cos(u/2)*sin(u)));
	float B=kappa*(cos(u)+ v*((-1/2)*sin(u/2)*sin(u)+cos(u/2)*cos(u)));
	float C=kappa*((v/2)*cos(u/2));
	Ogre::Vector3 T = Ogre::Vector3(A,B,C);
	return T;
}
Ogre::Vector3 Tank::Binormal(float u, float v){
	float kappa = 1;
	
	float D=kappa*(cos(u/2)*cos(u));
	float E=kappa*(cos(u/2)*sin(u));
	float F=kappa*(sin(u/2));
	Ogre::Vector3 B = Ogre::Vector3(D,E,F);
	return B;
}
Ogre::Matrix3 Tank::Orientation(Ogre::Vector3 xBasis, Ogre::Vector3 yBasis, Ogre::Vector3 zBasis){
    Ogre::Matrix3 rotate;
    rotate.FromAxes(xBasis, yBasis, zBasis);
	return rotate;
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

