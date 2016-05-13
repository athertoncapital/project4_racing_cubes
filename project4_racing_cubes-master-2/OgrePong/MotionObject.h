#ifndef __MotionObject_h_
#define __MotionObject_h_

#include "PongObject.h"
#include "Ogre.h"

namespace Ogre {
	class SceneManager;
	class Vector3;
}

class PongObject;

class MotionObject : public PongObject {

public:
	MotionObject(Ogre::SceneManager *sceneManager, Ogre::Vector3 dimension, Ogre::Vector3 speed, Ogre::Vector3 velocity);
	bool hitHorizontallyWith(const PongObject* pongObject);
	bool hitVerticallyWith(const PongObject* pongObject);
	bool atAIArea() const;
	bool atUserArea() const;
	bool atTopArea() const;
	bool atBottomArea() const;
	void virtual move(const Ogre::Real time);
	Ogre::Vector3 getSpeed() { return mSpeed; }
	void setSpeed(Ogre::Vector3 speed);
	void setvelocity(const Ogre::Vector3& velocity) { mvelocity = velocity; }
	Ogre::Vector3 getvelocity() const { return mvelocity; }
	void virtual reset() = 0;
	void virtual load() = 0;
	void stop();

private:
	Ogre::Vector3 mvelocity;
	Ogre::Vector3 mSpeed;
};

#endif