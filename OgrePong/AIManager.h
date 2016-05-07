#include "Ogre.h"
#include "Tank.h"
#ifndef __AIManager_h_
#define __AIManager_h_

enum slideredbrick;
class Tank;
class World;
//Ogre::Vector3 HP;
class AIManager 
{
public:
	AIManager(World *world);
	~AIManager();
    void Think(const Ogre::Real& mTime);
	bool atAIArea() const;
protected:
	Tank *mTank;
	Ogre::SceneNode *mNode;
	Ogre::SceneNode *maiNode;
	Ogre::Matrix3 mOrientation;
    Ogre::Vector3 mPosition;
private:
void move(Tank *tank, const Ogre::Real& mTime);
	World *mWorld;
	
	

};

#endif