#include "InputHandler.h"
#include "Ogre.h"
#include "OgreStringConverter.h"
#include <OIS/OIS.h>
#include "PongObject.h"
#include <stdio.h>
#include "DebugInterface.h"

InputHandler::InputHandler(Ogre::RenderWindow *renderWindow, Ogre::RenderWindow *renderWindow_ai1, DebugInterface *dbi) : 
	 mRenderWindow(renderWindow), mRenderWindow_ai1(renderWindow_ai1), mDebugInterface(dbi)
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
	if (!mDebugInterface->DebugConsoleActive())
	{
		if (mCurrentKeyboard->isKeyDown(OIS::KC_UP))
		{

		}
	}

}


InputHandler::~InputHandler()
{
	mInputManager->destroyInputObject(mCurrentKeyboard);
}

