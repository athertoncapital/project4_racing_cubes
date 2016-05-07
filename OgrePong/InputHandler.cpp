#include "InputHandler.h"
#include "Ogre.h"
#include "OgreStringConverter.h"
#include <OIS/OIS.h>
#include "PongObject.h"
#include <stdio.h>
#include "DebugInterface.h"


InputHandler::InputHandler(Ogre::RenderWindow *renderWindow, DebugInterface *dbInterface) : 
	 mRenderWindow(renderWindow), mDebugInterface(dbInterface)
{
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mCurrentKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false /* not buffered */ ));
    mCurrentKeyboard->setEventCallback(this);
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

