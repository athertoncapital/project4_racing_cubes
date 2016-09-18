#include "StaticObject.h"
#include "OgreSceneManager.h"
#include "OgreStringConverter.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "OgreQuaternion.h"
#include "OgreMath.h"
#include "CollisionManager.h"


StaticObject::StaticObject(Ogre::SceneManager *sceneManager, const char *objectName, const char *meshName,StaticObject *parent) :mParent(parent)
{
    ent1 = sceneManager->createEntity(objectName,meshName);
    mObjectSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(objectName);
    mObjectSceneNode->attachObject(ent1);
    mPosition = Ogre::Vector3::ZERO;
    mOrientation = Ogre::Matrix3::IDENTITY;
    setOBB();
}


void StaticObject::setScale(Ogre::Vector3 newScale)
{
    mObjectSceneNode->setScale(newScale);
    mOBB->setScale(mObjectSceneNode->getScale());
}

void 
    StaticObject::yaw(Ogre::Radian theta)
{
    Ogre::Vector3 xBasis = Ogre::Vector3(Ogre::Math::Cos(theta),0, - Ogre::Math::Sin(theta));
    Ogre::Vector3 yBasis = Ogre::Vector3(0,1,0);
    Ogre::Vector3 zBasis = Ogre::Vector3(Ogre::Math::Sin(theta),0,Ogre::Math::Cos(theta));
    Ogre::Matrix3 rotate;
    rotate.FromAxes(xBasis, yBasis, zBasis);
    mOrientation = rotate *  mOrientation ;

    // Once we change our internal data structures, we will modify the OGRE 
    // internals to actually move the models around
    SetGraphicPosition();
}

void 
    StaticObject::pitch(Ogre::Radian theta)
{

    Ogre::Vector3 xBasis = Ogre::Vector3(1,0,0);
    Ogre::Vector3 yBasis = Ogre::Vector3(0, Ogre::Math::Cos(theta), Ogre::Math::Sin(theta));
    Ogre::Vector3 zBasis = Ogre::Vector3(0, -Ogre::Math::Sin(theta), Ogre::Math::Cos(theta));
    Ogre::Matrix3 rotate;
    rotate.FromAxes(xBasis, yBasis, zBasis);
    mOrientation = rotate *mOrientation;


    // Once we change our internal data structures, we will modify the OGRE 
    // internals to actually move the models around
    SetGraphicPosition();
}
void
    StaticObject::roll(Ogre::Radian theta)
{
    Ogre::Vector3 xBasis = Ogre::Vector3(Ogre::Math::Cos(theta), Ogre::Math::Sin(theta), 0);
    Ogre::Vector3 yBasis = Ogre::Vector3(-Ogre::Math::Sin(theta), Ogre::Math::Cos(theta), 0);
    Ogre::Vector3 zBasis = Ogre::Vector3(0,0,1);
    Ogre::Matrix3 rotate;
    rotate.FromAxes(xBasis, yBasis, zBasis);
    mOrientation = rotate *  mOrientation;

    // Once we change our internal data structures, we will modify the OGRE 
    // internals to actually move the models around
    SetGraphicPosition();
}

void
    StaticObject::translate(Ogre::Vector3 deltaPosition)
{
    mPosition = mPosition + deltaPosition;
    SetGraphicPosition();
}

void 
    StaticObject::setOrientation(Ogre::Matrix3 orientation)
{
    mOrientation = orientation; 
    SetGraphicPosition();
}
void 
    StaticObject::setPosition(Ogre::Vector3 position)
{
    mPosition = position;
    SetGraphicPosition();
}


void StaticObject::GetWorldPositionAndOrientation(Ogre::Vector3 &position, Ogre::Matrix3 &orientation)
{
    position = mPosition;
    orientation = mOrientation;

    StaticObject *parent = mParent;
    while (parent != NULL)
    {
        position =  parent->getOrientation() * position + parent->getPosition();
        orientation = parent->getOrientation() * orientation;
        parent = parent->mParent;
    }
}

void
    StaticObject::SetGraphicPosition()
{    
    Ogre::Vector3 pos;
    Ogre::Matrix3 orientation;

    GetWorldPositionAndOrientation(pos, orientation);
    mObjectSceneNode->setOrientation(Ogre::Quaternion(orientation));
    mObjectSceneNode->setPosition(pos);
    
    mOBB->setOrientation(mObjectSceneNode->getOrientation());
    mOBB->setPosition(mObjectSceneNode->getPosition());
}

void StaticObject::setOBB() {
    mOBB = new OBB(ent1->getBoundingBox());
    mOBB->setScale(mObjectSceneNode->getScale());
    mOBB->setOrientation(mObjectSceneNode->getOrientation());
    mOBB->setPosition(mObjectSceneNode->getPosition());
}

Ogre::Vector3 StaticObject::getFacing() 
{
	return  mObjectSceneNode->getOrientation() * Ogre::Vector3::UNIT_Z;
}