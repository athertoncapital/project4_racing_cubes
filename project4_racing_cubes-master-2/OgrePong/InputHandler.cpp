#include "InputHandler.h"
#include "Ogre.h"
#include "OgreStringConverter.h"
#include <OIS/OIS.h>
#include "PongObject.h"
#include <stdio.h>
#include "DebugInterface.h"
#include "MenuInterface.h"
#include "VirtualClock.h"

InputHandler::InputHandler(Ogre::RenderWindow* renderWindow, Ogre::RenderWindow* renderWindow_ai1, DebugInterface* dbi, MenuInterface* mi,
        Ogre::Camera* cam, Ogre::Camera* camR, Ogre::Camera* camMenu, Ogre::Camera* camai1, Ogre::Camera* camai2, Ogre::Camera* camai3, VirtualClock* vc) : 
	 mRenderWindow(renderWindow), mRenderWindow_ai1(renderWindow_ai1), mDebugInterface(dbi), mMenuInterface(mi),
         mCamera(cam), mCameraR(camR), mCameraMenu(camMenu), mCamera_ai1(camai1), mCamera_ai2(camai2), mCamera_ai3(camai3), mMenu(true), mClock(vc)
{
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mCurrentKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mCurrentKeyboard->setEventCallback(this);
//////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	OIS::ParamList pl_ai1;
	size_t windowHnd_ai1 = 1;
	std::ostringstream windowHndStr_ai1;
	
	renderWindow_ai1->getCustomAttribute("WINDOW", &windowHnd);

	windowHndStr_ai1 << windowHnd_ai1;
	pl_ai1.insert(std::make_pair(std::string("WINDOW_ai1"), windowHndStr_ai1.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl_ai1 );

	mCurrentKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));*/
	
}


bool
InputHandler::IsKeyDown(OIS::KeyCode key)
{
	 // Ignore keys when debug console is active
	 if (mDebugInterface->DebugConsoleActive())
	 {
		 return false;
	 }
	 // Ignore keys when menu console is active
     else if (mMenuInterface->MenuConsoleActive())
     {
         return false;
     }
	 else
	 {
		 return mCurrentKeyboard->isKeyDown(key);
	 }
}

 bool 
 InputHandler::keyPressed(const OIS::KeyEvent &e)
 {
    if (e.key == OIS::KC_GRAVE)
    {
        mDebugInterface->SetDebugConsoleActive(!mDebugInterface->DebugConsoleActive());
    }

    else if (e.key == OIS::KC_P)
    {
        //mMenu = !mMenu;
        
        mMenuInterface->SetMenuConsoleActive(!mMenuInterface->MenuConsoleActive());
        std::string s = "Value of bool is: ";
        s += mMenu ? "true" : "false";
        s += " and menu interface is: ";
        s += mMenuInterface->MenuConsoleActive() ? "true" : "false";
        mDebugInterface->addDebugText(s);
        if (mMenuInterface->MenuConsoleActive())
        {
            createMenuViewport();
            mClock->pause();
        
            
        }
        else
        {

            createGameViewports();
            mClock->start();
        }
        
    }
    else if (mMenuInterface->MenuConsoleActive()) {
        mMenuInterface->HandleKeystroke(e);
    }
    else  if (mDebugInterface->DebugConsoleActive())
    {
        mDebugInterface->HandleKeystroke(e);
    } 
    return true;
 }
   
 bool 
 InputHandler::keyReleased(const OIS::KeyEvent &e)
 {
     return true;
 }

bool
InputHandler::WasKeyDown(OIS::KeyCode key)
{
	return mOldKeys[key] != '\0';
}

void 
InputHandler::Think(const Ogre::Real& mTime)
{

	mCurrentKeyboard->copyKeyStates(mOldKeys);
	mCurrentKeyboard->capture();
	if (!mDebugInterface->DebugConsoleActive() && !mMenuInterface->MenuConsoleActive())
	{
		if (mCurrentKeyboard->isKeyDown(OIS::KC_UP))
		{

		}
	}

}

void InputHandler::createGameViewports()
{
    mRenderWindow->removeAllViewports();
    Ogre::Viewport* vp_ai1= mRenderWindow->addViewport(mCamera_ai1,3, 0.1f, 0.5f, 0.5, 0.15);
    Ogre::Viewport* rearvp = mRenderWindow->addViewport(mCameraR, 2, 0.375f, 0.75f, 0.5, 0.15);
    Ogre::Viewport* vp = mRenderWindow->addViewport(mCamera,1);

    rearvp->setBackgroundColour(Ogre::ColourValue(244, 164, 96));
    vp->setBackgroundColour(Ogre::ColourValue(244, 164, 96));
    vp_ai1->setBackgroundColour(Ogre::ColourValue(244, 164, 96));
    
    vp->setOverlaysEnabled(false);
    rearvp->setOverlaysEnabled(false);
    vp_ai1->setOverlaysEnabled(false);


    mCameraR->setAspectRatio(Ogre::Real(rearvp->getActualWidth()) / Ogre::Real(rearvp->getActualHeight())); 
	mCamera_ai1->setAspectRatio(Ogre::Real(vp_ai1->getActualWidth()) / Ogre::Real(vp_ai1->getActualHeight()));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight())); 

    Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    mRenderWindow->getViewport(0)->setBackgroundColour(fadeColour);
    mRenderWindow->getViewport(1)->setBackgroundColour(fadeColour);
}

void InputHandler::createMenuViewport()
{
   mRenderWindow->removeAllViewports();
   Ogre::Viewport* menuvp = mRenderWindow->addViewport(mCameraMenu,4);
   menuvp->setBackgroundColour(Ogre::ColourValue(244, 164, 96));
   mCameraMenu->setAspectRatio(Ogre::Real(menuvp->getActualWidth()) / Ogre::Real(menuvp->getActualHeight()));
   menuvp->setOverlaysEnabled(true);
   menuvp->setClearEveryFrame(true);
}

InputHandler::~InputHandler()
{
	mInputManager->destroyInputObject(mCurrentKeyboard);
}

