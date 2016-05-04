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
	Ogre::Entity *tank = SceneManager()->createEntity("AItank0","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank0");
	eTankNode->setPosition(mWorld->spawnPoints[0]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);

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
	eTankNode;
	tank = SceneManager()->createEntity("AItank2","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank2");
	eTankNode->setPosition(mWorld->spawnPoints[2]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
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
	eTankNode->scale(10, 10, 10);
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
	mCameraNode->attachObject(mCamera->getCamera());
	mCameraNode->attachObject(mCameraR->getCamera());
}
void Tank::Think(const Ogre::Real& mTime)
{
	mObj1->yaw(Ogre::Radian(0.5f * mTime));
    mObj2->pitch(Ogre::Radian(0.6f * mTime));
    mObj3->roll(Ogre::Radian(0.5f * mTime));
	mObj4->translate(mTime * Ogre::Vector3(-1, 0,0));


	int k =Ogre::ControllerManager::getSingleton().getElapsedTime();
	if(k%10==0){
	Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual(
         "MainRenderTarget", 
         Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
         Ogre::TextureType::TEX_TYPE_2D, 
         80,
         80,
		 20,
		 0,
		 Ogre::PixelFormat::PF_B8G8R8,
	     Ogre::TextureUsage::TU_RENDERTARGET);

   Ogre::RenderTexture *renderTexture = tex->getBuffer()->getRenderTarget();

   renderTexture->addViewport(mCamera->getCamera(),0);
   //renderTexture->addViewport(mCameraR->getCamera(),1,0.4f, 0.75f, 0.5, 0.15);
   int count = renderTexture->getNumViewports();
   
   renderTexture->getViewport(0)->setClearEveryFrame(true);
   renderTexture->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
   renderTexture->getViewport(0)->setOverlaysEnabled(false);

   //renderTexture->getViewport(1)->setClearEveryFrame(true);
   //renderTexture->getViewport(1)->setBackgroundColour(Ogre::ColourValue::Black);
   //renderTexture->getViewport(1)->setOverlaysEnabled(true);

   renderTexture->update();
	string ID = "RoomRender";
	string exd = ".bmp";
	string Result;          // string which will contain the result  
	ostringstream convert;
	convert << k;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	ID.append(exd);
   // Now save the contents
   renderTexture->writeContentsToFile(ID);
	}
	char* infile = "testing.bmp";//argv[2];
    char* outfile = "try2.bmp";//argv[3];
	 // open input file 
    FILE* inptr = fopen(infile, "r");
    /*if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);

    }*/

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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    /*if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");

    }*/

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
            fputc(0x00, outptr);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
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

