#ifndef __PongManager_h_
#define __PongManager_h_

#include "Ogre.h"
#include "OgreFrameListener.h"

namespace Ogre
{
	class RenderWindow;
	class Camera;
	class SceneManager;
	class Overlay;
}

class InputHandler;
class AIManager;
class World;
class PongCamera;

class PongManager : public Ogre::FrameListener
{
public:
	PongManager(Ogre::SceneManager* sceneManager, Ogre::RenderWindow *mainWindow);
	~PongManager();
	bool frameStarted(const Ogre::FrameEvent &evt);
	const InputHandler* getInputHandler() const { return mInputHandler; }
	const AIManager* getAIManager() const { return mAIManager; }
	void setUp();

private:
	void createCamera();
	void createViewports();
	Ogre::Overlay *mGameOverOverlay;
	void createGameOverOverlay();
	void think(const Ogre::Real& time);
	void startOver();

	Ogre::SceneManager* mSceneManager;
	InputHandler *mInputHandler;
	AIManager *mAIManager;
	World *mWorld;


	Ogre::Camera *mCamera;
	Ogre::RenderWindow *mRenderWindow;
	bool mKeepGoing;
	
	bool mTestPaused;
	bool mTestOver;
	bool flag;
};

#endif