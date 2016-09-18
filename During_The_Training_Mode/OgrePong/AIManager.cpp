#include "AIManager.h"
#include "World.h"
#include "Tank.h"
#include "OgreVector3.h"
#include "PongObject.h"

#include <set>
AIManager::AIManager(World *world) {
	mWorld = world;
	
	
	//orientation = mWorld->SceneManager()->getSceneNode("AItank0")->getOrientation();

	 
	
}

AIManager::~AIManager()
{
    
}

void 
AIManager::Think(const Ogre::Real& mTime)
{
	Ogre::Quaternion Q=Ogre::Quaternion(Ogre::Degree(1), Ogre::Vector3(0,1000,0));
	Ogre::Vector3 xBasis = Ogre::Vector3(Ogre::Math::Cos(Ogre::Math::PI / 2),0, - Ogre::Math::Sin(Ogre::Math::PI / 2));
    Ogre::Vector3 yBasis = Ogre::Vector3(0,1,0);
    Ogre::Vector3 zBasis = Ogre::Vector3(Ogre::Math::Sin(Ogre::Math::PI / 2),0,Ogre::Math::Cos(Ogre::Math::PI / 2));
    Ogre::Matrix3 rotate;
	
    rotate.FromAxes(xBasis, yBasis, zBasis);
	//Ogre::Vector3 vUser=mWorld->SceneManager()->getSceneNode("U")->getPosition();
	/*Ogre::Vector3 pos;
	
    Ogre::Matrix3 orientation;
	pos = mWorld->SceneManager()->getSceneNode("AItank0")->getPosition();

	
	pos = rotate*pos ;*/
	//Ogre::Quaternion Q1=Ogre::Quaternion(rotate);
	//Ogre::Quaternion q = mWorld->SceneManager()->getSceneNode("AItank0")->getOrientation();
    //q =  Q1 * q  ;
	//Ogre::Quaternion q((Ogre::Math::PI / 2), (0,0,1));

	//mWorld->SceneManager()->getSceneNode("AItank0")-rotate();

	//mWorld->SceneManager()->getSceneNode("AItank0")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	/*mWorld->SceneManager()->getSceneNode("AItank1")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	mWorld->SceneManager()->getSceneNode("AItank2")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	 mWorld->SceneManager()->getSceneNode("AItank3")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	 mWorld->SceneManager()->getSceneNode("AItank4")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	 mWorld->SceneManager()->getSceneNode("AItank5")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	 mWorld->SceneManager()->getSceneNode("AItank6")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	 mWorld->SceneManager()->getSceneNode("AItank7")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	 mWorld->SceneManager()->getSceneNode("AItank8")->yaw(Ogre::Radian(Ogre::Math::PI / 2));
	 mWorld->SceneManager()->getSceneNode("AItank9")->yaw(Ogre::Radian(Ogre::Math::PI / 2));*/
	/*
	for(int i=0; i<21; i++){
	//if(mWorld->SceneManager()->getSceneNode("U")!=NULL){}
	
	string ID = "AItank";
	int Number = i;       // number to be converted to a string
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	Ogre::Vector3 vAI=mWorld->SceneManager()->getSceneNode(ID)->getPosition();
	Ogre::Vector3 speed = vAI-vUser;
	int r = 650;
	if(((vAI.x-vUser.x)*(vAI.x-vUser.x)+(vAI.y-vUser.y)*(vAI.y-vUser.y)+(vAI.z-vUser.z)*(vAI.z-vUser.z))>=r*r*600){
		int i = rand();
		if (i % 3 == 0) {
		
		} 
		else if(i % 3 == 1)
	{
		mWorld->SceneManager()->getSceneNode(ID)->translate(-1*speed*mTime*5);
		
	}
	else if(i % 3 == 2)
	{
		mWorld->SceneManager()->getSceneNode(ID)->translate(-1*speed*mTime*0.3);
		
	}
	}//end open ball check
	


	
	if(((vAI.x-vUser.x)*(vAI.x-vUser.x)+(vAI.y-vUser.y)*(vAI.y-vUser.y)+(vAI.z-vUser.z)*(vAI.z-vUser.z))<r*r){
		//mWorld->SceneManager()->getSceneNode(ID)->setPosition(vAI+(vAI-vUser)*3);

	int i = rand();
	if (i % 3 == 0) {
		Ogre::Vector3 temp;
		temp = rotate*(vAI-vUser);

	    mWorld->SceneManager()->getSceneNode(ID)->setPosition(vAI+(temp)*3);
		vAI.z-=100;
		Ogre::ColourValue fadeColour(0.8, 0.8, 0.8);
	
		mWorld->SceneManager()->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1200);
	} 
	else if(i % 3 == 1)
	{
		Ogre::Vector3 temp;
		temp = rotate*(vAI-vUser);

		mWorld->SceneManager()->getSceneNode(ID)->translate(vAI+(temp)*mTime*0.5);
		vAI.x-=100;
		Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
	
		mWorld->SceneManager()->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1200);
	}
	else if(i % 3 == 2)
	{
		Ogre::Vector3 temp;
		temp = rotate*(vAI-vUser);
		mWorld->SceneManager()->getSceneNode(ID)->translate(vAI+(temp)*mTime*0.3);
		vAI.z+=100;
		Ogre::ColourValue fadeColour(0.7, 0.7, 0.7);
		mWorld->SceneManager()->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1200);
	}
	}//end open ball check*/

	/*mWorld->Hpoint_x)<0.1) break;
	}//end for loop

	*/
		//->head->eTankNode->
 	//if(mWorld->Hpoint_x-;
}
void AIManager::move(Tank *tank, const Ogre::Real& mTime) {
	/*mNode = mTank->mMainNode;
	HP = mNode->getPosition();
	mWorld->tanks->head->getPosition();
	*/

}