#ifndef __InputHandler_h_
#define __InputHandler_h_

#include <ois/ois.h>
#include <Ogre.h>
#include "OgreRenderWindow.h"

class World;
class PongCamera;
class InputHandler;
class DebugInterface;
class MenuInterface;
class VirtualClock;


class InputHandler : OIS::KeyListener // : public OIS::MouseListener, public OIS::KeyListener
{
public:

	//InputHandler(Ogre::RenderWindow* win, Ogre::RenderWindow* win2, DebugInterface* dbi);
    InputHandler(Ogre::RenderWindow* win, Ogre::RenderWindow* win2, DebugInterface* dbi, MenuInterface* mi,
        Ogre::Camera* cam, Ogre::Camera* camR, Ogre::Camera* camMenu, Ogre::Camera* camai1, Ogre::Camera* camai2, Ogre::Camera* camai3, VirtualClock *vc);
	~InputHandler();
	void Think(const Ogre::Real& mTime);

	bool IsKeyDown(OIS::KeyCode key);
	bool WasKeyDown(OIS::KeyCode key);

    bool keyPressed(const OIS::KeyEvent &e);
    bool keyReleased(const OIS::KeyEvent &e);

    void createGameViewports();
    void createMenuViewport();

protected:
	OIS::InputManager* mInputManager;
	Ogre::RenderWindow *mRenderWindow;
	Ogre::RenderWindow *mRenderWindow_ai1;
	OIS::Keyboard *mPreviousKeyboard;
	OIS::Keyboard *mCurrentKeyboard;
	char mOldKeys[256];
    bool mSpaceDown;
    DebugInterface *mDebugInterface;
    MenuInterface *mMenuInterface;
    bool mMenu;

    Ogre::Camera *mCamera;
    Ogre::Camera *mCameraR;
    Ogre::Camera *mCameraMenu;
    Ogre::Camera *mCamera_ai1;
    Ogre::Camera *mCamera_ai2;
    Ogre::Camera *mCamera_ai3;

    VirtualClock *mClock;

};

#endif