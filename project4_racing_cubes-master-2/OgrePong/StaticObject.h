#pragma once
#include "OgreMatrix3.h"
#include "OgreVector3.h"

class Ogre::SceneManager;
class Ogre::SceneNode;
class OBB;

class StaticObject
{

public:
    StaticObject(Ogre::SceneManager *sceneManager, const char *objectName, const char *meshName, StaticObject *parent);

    Ogre::Matrix3 getOrientation() {return mOrientation;}
    Ogre::Vector3 getPosition() {return mPosition;}

    void setOrientation(Ogre::Matrix3 orientation); 
    void setPosition(Ogre::Vector3 position); 

    void yaw(Ogre::Radian theta);
    void pitch(Ogre::Radian theta);
    void roll(Ogre::Radian theta);

    void translate(Ogre::Vector3 deltaPosition);
	
    void setPositionFromWorldPosition(Ogre::Vector3 worldPosition);
    void setOrentationFromWorldOrientation(Ogre::Matrix3 worldOrientation);

    void setScale(Ogre::Vector3 newScale);
    void setOBB();
    Ogre::SceneNode *getSceneNode() { return mObjectSceneNode;}
    Ogre::Vector3 getFacing();

    OBB* getOBB() { return mOBB;}
	 Ogre::Entity *ent1;
	 Ogre::SceneNode *mObjectSceneNode;


protected:

    void GetWorldPositionAndOrientation(Ogre::Vector3 &position, Ogre::Matrix3 &orientation);
    void SetGraphicPosition();

    Ogre::Matrix3 mOrientation;
    Ogre::Vector3 mPosition;
    StaticObject *mParent;
    OBB *mOBB;
    
};