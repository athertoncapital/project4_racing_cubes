#ifndef __border_h_
#define __border_h_
#include "PongObject.h"

namespace Ogre {
	class SceneManager;
}
class PongObject;
class Border_ : public PongObject {
public:
	Border_(Ogre::SceneManager* sceneManager, Ogre::Vector3 dimension);
	void load();
};

#endif