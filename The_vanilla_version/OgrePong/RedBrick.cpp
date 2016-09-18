#include "RedBrick.h"
#include "MotionObject.h"
#include "Properties.h"

#include "OgreSceneManager.h"

RedBrick::RedBrick(Ogre::SceneManager* sceneManager, Ogre::Vector3 dimension) : MotionObject(sceneManager, 
																							 dimension, 
																							RedBrick_0_SPEED, 
																							RedBrick_velocity_UP) {
}

void RedBrick::load() {
	Ogre::SceneManager* sceneManager = getSceneManager();
	Ogre::Entity* entity = sceneManager->createEntity("Cube.mesh");
	setEntity(entity);
}

void RedBrick::reset() {
	Ogre::Vector3 position = getPosition();
	position.y = 0;
	setPosition(position);
	setSpeed(RedBrick_0_SPEED);
}
