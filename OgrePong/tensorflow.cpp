/*Implement some functions that could be uesd in Tensorflow*/ 

#include "World.h"
#include "Tank.h"
#include "OgreVector3.h"
#include "tensorflow.h"
#include <math.h>
#include <algorithm> 

tensorflow::tensorflow(World *world) {
	mWorld = world;
	
	
	//orientation = mWorld->SceneManager()->getSceneNode("AItank0")->getOrientation();

	 
	
}

tensorflow::~tensorflow()
{
    
}

void 
tensorflow::Think(const Ogre::Real& mTime)
{

}



float tensorflow::relu(float x)
{
	return max(0.0f,x);
}

tensorflow::Variable::Variable(float initial){
	this->initial = initial;

}