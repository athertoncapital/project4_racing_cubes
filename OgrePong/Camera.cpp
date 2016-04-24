#include "Camera.h"
#include "OgreCamera.h"
#include "Tank.h"
#include "World.h"
#include <OgreRenderTexture.h>
#include "InputHandler.h"


PongCamera::PongCamera(Ogre::Camera *renderCamera, World *world, InputHandler *input) :
mRenderCamera(renderCamera), mWorld(world), mInputHandler(input)
{
	mRenderCamera->setNearClipDistance(5);
	mWorld->Switch = 0;

}

Ogre::Camera *
PongCamera::getCamera()
{
	return mRenderCamera;
}

void
PongCamera::Think(const Ogre::Real& mTime)
{
	
		if (mInputHandler->IsKeyDown(OIS::KC_O)){ mWorld->Switch = 1; }
		if (mInputHandler->IsKeyDown(OIS::KC_P)){ mWorld->Switch = 0; }
		if(mWorld->Switch==1){
			capture();
		}
	


}
void
PongCamera::capture(){
	//for recording 
	int k =Ogre::ControllerManager::getSingleton().getElapsedTime();
	if(k%10==0){
	Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual(
         "MainRenderTarget", 
         Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
         Ogre::TextureType::TEX_TYPE_2D, 
         680,
         480,
		 20,
		 0,
		 Ogre::PixelFormat::PF_R8G8B8,
	     Ogre::TextureUsage::TU_RENDERTARGET);

   Ogre::RenderTexture *renderTexture = tex->getBuffer()->getRenderTarget();

   renderTexture->addViewport(mRenderCamera);
   int count = renderTexture->getNumViewports();
   
   renderTexture->getViewport(0)->setClearEveryFrame(true);
   renderTexture->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
   renderTexture->getViewport(0)->setOverlaysEnabled(true);

   renderTexture->update();
	string ID = "RoomRender";
	string exd = ".png";
	string Result;          // string which will contain the result  
	ostringstream convert;
	convert << k;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	ID.append(exd);
   // Now save the contents
   renderTexture->writeContentsToFile(ID);
	}
}