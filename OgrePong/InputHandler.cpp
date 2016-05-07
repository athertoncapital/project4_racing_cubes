#include "InputHandler.h"
#include "Ogre.h"
#include "OgreStringConverter.h"
#include <OIS/OIS.h>
#include "PongObject.h"
#include <stdio.h>

InputHandler::InputHandler(Ogre::RenderWindow *renderWindow, Ogre::RenderWindow *renderWindow_ai1) : 
	 mRenderWindow(renderWindow), mRenderWindow_ai1(renderWindow_ai1)
{
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mCurrentKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false /* not buffered */ ));
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
	return mCurrentKeyboard->isKeyDown(key);
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
}


InputHandler::~InputHandler()
{
	mInputManager->destroyInputObject(mCurrentKeyboard);
}

