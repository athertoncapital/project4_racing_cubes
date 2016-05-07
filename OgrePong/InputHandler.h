#ifndef __InputHandler_h_
#define __InputHandler_h_

#include <ois/ois.h>
#include <Ogre.h>
#include "OgreRenderWindow.h"

class World;
class PongCamera;
class InputHandler;
class DebugInterface;


class InputHandler : OIS::KeyListener // : public OIS::MouseListener, public OIS::KeyListener
{
public:

	InputHandler(Ogre::RenderWindow* win, DebugInterface *dbInterface);
	~InputHandler();
	void Think(const Ogre::Real& mTime);

	bool IsKeyDown(OIS::KeyCode key);
	bool WasKeyDown(OIS::KeyCode key);

    bool keyPressed(const OIS::KeyEvent &e);
    bool keyReleased(const OIS::KeyEvent &e);


protected:
	OIS::InputManager* mInputManager;
	Ogre::RenderWindow *mRenderWindow;
	OIS::Keyboard *mPreviousKeyboard;
	OIS::Keyboard *mCurrentKeyboard;
	char mOldKeys[256];
    bool mSpaceDown;
    DebugInterface *mDebugInterface;



};

#endif