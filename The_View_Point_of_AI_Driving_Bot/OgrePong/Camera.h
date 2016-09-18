#ifndef __Camera_h_
#define __Camera_h_
#include "Ogre.h"
namespace Ogre
{
    class Camera;
	class SceneNode;
}

class World;
class InputHandler;
class PongCamera
{

public:
	
    PongCamera(Ogre::Camera *renderCamera, World *world, InputHandler *input); 
	Ogre::Camera *getCamera(void);
	void PongCamera::capture();
    void Think(const Ogre::Real& mTime);
    // If you have a different cameras, you'll want some acessor methods here.
    //  If your camera always stays still, you could remove this class entirely

protected:

    Ogre::Camera *mRenderCamera; 
	Ogre::Camera *mRenderCameraR;
    World *mWorld;
	InputHandler *mInputHandler;
};

#endif