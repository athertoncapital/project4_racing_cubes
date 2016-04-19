#include "MainListener.h"
#include "AIManager.h"
#include "InputHandler.h"
#include "World.h"
#include "Camera.h"
#include "ProjectileManager.h"
#include <ois.h>
#include "PongObject.h"
#include "Tank.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreSceneManager.h"

MainListener::MainListener(Ogre::RenderWindow *mainWindow, InputHandler *inputManager, AIManager *aiManager, World *world, PongCamera *cam, ProjectileManager *pm, Tank *mT) :
mRenderWindow(mainWindow), mInputHandler(inputManager), mAIManager(aiManager), mWorld(world), mPongCamera(cam), mProjectileManager(pm), mTank(mT)
{
	x = 0;
}

bool 
	MainListener::frameStarted(const Ogre::FrameEvent &evt)
{
	float mTime = evt.timeSinceLastFrame;
	if (mTime > 0.5)
	{
		mTime = 0.5;
	}
	bool keepGoing = true;
	
	mInputHandler->Think(mTime);
	mWorld->Think(mTime);
    mPongCamera->Think(mTime);
	mTank->Think(mTime);
	mProjectileManager->Think(mTime);
	mAIManager->Think(mTime);
	int k =Ogre::ControllerManager::getSingleton().getElapsedTime();
	int cd = 185-k;
	if (mInputHandler->IsKeyDown(OIS::KC_X)){
		mProjectileManager->SceneManager()->setFog(Ogre::FOG_NONE);
	}
	if (mInputHandler->IsKeyDown(OIS::KC_ESCAPE) || mRenderWindow->isClosed()||cd<0)keepGoing = false;
	
	return keepGoing;
}