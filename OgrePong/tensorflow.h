#include "Ogre.h"
#include "Tank.h"
#ifndef __tensorflow_h_
#define __tensorflow_h_
/*Implement some functions that could be uesd in Tensorflow*/ 
class Tank;
class World;
//Ogre::Vector3 HP;
class tensorflow 
{
public:
	tensorflow(World *world);
	~tensorflow();
    void Think(const Ogre::Real& mTime);
	class Variable;
	float tensorflow::relu(float x);
	int tensorflow::relu(int x);

protected:
	Tank *mTank;
	Ogre::SceneNode *mNode;
	Ogre::SceneNode *maiNode;
	Ogre::Matrix3 mOrientation;
    Ogre::Vector3 mPosition;
private:

	World *mWorld;
	
	

};
class tensorflow::Variable { 
	public:
		Variable(float initial);
		float initial;
};

#endif