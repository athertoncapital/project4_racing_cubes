#include "PongObject.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "Properties.h"
#include "OgreVector3.h"

PongObject::PongObject(Ogre::SceneManager* sceneManager, Ogre::Vector3 dimension) {
	mSceneManager = sceneManager;
	mDimension = dimension;
}

void PongObject::setScene() {
	mSceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	mSceneNode->attachObject(mEntity);
}

Ogre::Vector3 PongObject::getPosition() const {
	return mSceneNode->getPosition();
}

void PongObject::setPosition(Ogre::Vector3 position) {
	mSceneNode->setPosition(position);
}

void PongObject::setScale(Ogre::Vector3 scale) {
	mSceneNode->setScale(scale);
}

Ogre::Vector3 PongObject::getScale() const {
	return mSceneNode->getScale();
}

Ogre::Vector3 PongObject::getDimension() const {
	return mDimension * mSceneNode->getScale();
}

bool PongObject::hitHorizontallyWith(const PongObject* pongObject) {
	return true;
}

bool PongObject::hitVerticallyWith(const PongObject* pongObject) {
	return true;
}

bool PongObject::atAIArea() const {
	return true;
}

bool PongObject::atUserArea() const {
return true;
}

bool PongObject::atTopArea() const {
	return true;
}

bool PongObject::atBottomArea() const {
	return true;
}
