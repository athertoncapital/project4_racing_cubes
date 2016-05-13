#include "Ogre.h"
#include "Tank.h"
#include "World.h"
#ifndef __VirtualClock_h_
#define __VirtualClock_h_
/*Implement a virtual VirtualClock to synchronize all moving objecs, and the start, pause and restart features*/ 
class Tank;
class World;
//Ogre::Vector3 HP;
class VirtualClock
{
public:
	float y;
	float i;
	float f;
	float k;
	float t;
	int s;
	VirtualClock();
	~VirtualClock(void);
    void Think(const Ogre::Real& mTime);
	float VirtualClock::report();
	void VirtualClock::start();
	void VirtualClock::pause();
	void VirtualClock::reset();

protected:
	Tank *mTank;
	Ogre::SceneNode *mNode;
	Ogre::SceneNode *maiNode;
	Ogre::Matrix3 mOrientation;
    Ogre::Vector3 mPosition;
private:

	World *mWorld;
	
	

};


#endif