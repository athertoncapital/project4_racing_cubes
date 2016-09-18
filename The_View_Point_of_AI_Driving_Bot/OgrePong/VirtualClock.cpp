#include "World.h"
#include "Tank.h"
#include "OgreVector3.h"
#include "VirtualClock.h"
#include <math.h>
#include <algorithm> 
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

VirtualClock::VirtualClock() {
	s=1;
	f=0;
	i=0;
	y=0;
	k = Ogre::ControllerManager::getSingleton().getElapsedTime();
	//orientation = mWorld->SceneManager()->getSceneNode("AItank0")->getOrientation();

}

VirtualClock::~VirtualClock()
{

}

void 
VirtualClock::Think(const Ogre::Real& mTime)
{
	k = Ogre::ControllerManager::getSingleton().getElapsedTime();
}
float VirtualClock::report(){
	float el =  Ogre::ControllerManager::getSingleton().getElapsedTime();
	if(s==1){
		if(f!=0){
			t = el-(y-f);// - (y-i);
		}
		else 
			t = el-(y-i);
		return t*1;}
	else if(s==2)
	{
		return f*1;
	}
	else//s==0, reset
	{
		
	return 0;
	}
}
void VirtualClock::start(){
	y=Ogre::ControllerManager::getSingleton().getElapsedTime();
	s=1;
	//f = Ogre::ControllerManager::getSingleton().getElapsedTime() -i;
}
void VirtualClock::pause()
{
	f=Ogre::ControllerManager::getSingleton().getElapsedTime();
	s=2;

}
void VirtualClock::reset(){
	i=Ogre::ControllerManager::getSingleton().getElapsedTime();
	s=0;

}
