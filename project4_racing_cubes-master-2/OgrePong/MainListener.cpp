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
#include "DebugInterface.h"
#include "MenuInterface.h"
#include "LuaWrapper.h"

 #define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

MainListener::MainListener(Ogre::RenderWindow *mainWindow, InputHandler *inputManager, AIManager *aiManager, World *world, PongCamera *cam, ProjectileManager *pm, Tank *mT, DebugInterface *dbi, MenuInterface *mi) :
mRenderWindow(mainWindow), mInputHandler(inputManager), mAIManager(aiManager), mWorld(world), mPongCamera(cam), mProjectileManager(pm), mTank(mT),mDebugInterface(dbi),mMenuInterface(mi)
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
    mDebugInterface->Think(mTime);
    mMenuInterface->Think(mTime);

    LuaWrapper::getSingleton()->Think(mTime);

	int k = mWorld->GlblTime; //Ogre::ControllerManager::getSingleton().getElapsedTime();
	int cd = 185-k;
	if (mInputHandler->IsKeyDown(OIS::KC_X)){
		mProjectileManager->SceneManager()->setFog(Ogre::FOG_NONE);
	}
    bool quitButton = LuaWrapper::getSingleton()->isDone();
	if (mInputHandler->IsKeyDown(OIS::KC_ESCAPE) || mRenderWindow->isClosed()||cd<0 || quitButton)
    {
        keepGoing = false;
        //std::string answer = LuaWrapper::getSingleton()->isDone() ? "true" : "false";
        //DBOUT(answer.c_str());
        //if (LuaWrapper::getSingleton()->isDone()) {
        //    DBOUT("SHOULD ESCAPE");
        //    keepGoing = false;
        //}
    }
	
	return keepGoing;
}