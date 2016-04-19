#ifndef __RedBrick_h_
#define __RedBrick_h_
#include "MotionObject.h"

namespace Ogre {
	class SceneManager;
	class Vector3;
}
class MotionObject;
class RedBrick : public MotionObject {
public:
	RedBrick(Ogre::SceneManager* sceneManager, Ogre::Vector3 dimension);
	void load();
	void reset();
};

#endif