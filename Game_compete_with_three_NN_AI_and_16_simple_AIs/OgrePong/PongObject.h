#ifndef __PongObject_h_
#define __PongObject_h_
#include "Ogre.h"
namespace Ogre {
	class SceneManager;
	class Entity;
	class Vector3;
	class SceneNode;
}
class PongObject {
public:
	PongObject(Ogre::SceneManager* sceneManager, Ogre::Vector3 dimension);
	void setPosition(Ogre::Vector3 position);
	void setScale(Ogre::Vector3 scale);
	Ogre::Vector3 getDimension() const;
	Ogre::Vector3 getScale() const;
	virtual void setScene();
	virtual void load() = 0;
	Ogre::Vector3 getPosition() const;
	bool hitHorizontallyWith(const PongObject* pongObject);
	bool hitVerticallyWith(const PongObject* pongObject);
	bool atAIArea() const;
	bool atUserArea() const;
	bool atTopArea() const;
	bool atBottomArea() const;

protected:
	Ogre::SceneManager* getSceneManager() { return mSceneManager; }
	void setEntity(Ogre::Entity* entity) { mEntity = entity; }
	Ogre::SceneNode* getSceneNode() { return mSceneNode; }

private:
	Ogre::SceneManager* mSceneManager;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mSceneNode;
	Ogre::Vector3 mDimension;
};

#endif