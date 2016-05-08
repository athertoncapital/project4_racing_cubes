#include "OgrePong.h"
#include"Properties.h"
#include "Tank.h"
#include "ProjectileManager.h"
#include "World.h"
#include "InputHandler.h"
#include "AIManager.h"
#include "MainListener.h"
#include "Camera.h"
#include "PongObject.h"
#include "Ogre.h"
#include "OgreConfigFile.h"
#include "OgreFontManager.h"
#include "OgreOverlaySystem.h"
#include "PongManager.h"
#include <OgreRenderTexture.h>
#include "DebugInterface.h"
#include "LuaWrapper.h"




OgrePong::OgrePong()
{
    mPongFrameListener = 0;
    mRoot = 0;
    // Provide a nice cross platform solution for locating the configuration files
    // On windows files are searched for in the current working directory, on OS X however
    // you must provide the full path, the helper function macBundlePath does this for us.
	//  (Note:  This is not fully tested under IOS)
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    mResourcePath = macBundlePath() + "/Contents/Resources/";
#else
    mResourcePath = "";
#endif
}

/// Standard destructor
OgrePong::~OgrePong()
{
    if (mPongFrameListener)
        delete mPongFrameListener;
    if (mRoot)
        delete mRoot;
}

void
OgrePong::createRearCamera()
{
	mRCamera = mSceneMgr->createCamera("RearCam");
	mRCamera->setPosition(Ogre::Vector3(0, 25,100)); //0,25,100 200, 400
	mRCamera->lookAt(Ogre::Vector3(0,0,0));
}

void
OgrePong::createCamera()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0, 25, -100));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
}

// We will create a single frame listener, to handle our main event loop.  While we could
// add as many frame listeners as we want (and let the main rendering loop call them),
// we would not have as much control over the order that the listeners are called --
//  so we will just have one listener and handle everything ourselves.
void 
OgrePong::createFrameListener(void)
{
	mPongFrameListener = new MainListener(mWindow, mInputHandler, mAIManager, mWorld, mPongCamera, mProjectileManager, mTank,mDebugInterface);
	mRoot->addFrameListener(mPongFrameListener);
}

// We will have a single viewport.  If you wanted splitscreen, or a rear-view mirror, then
// you may want multiple viewports.
void 
OgrePong::createViewports(void)
{
	
	    // Create one viewport, entire window
        Ogre::Viewport* vp = mWindow->addViewport(mCamera,0);
		Ogre::Viewport* rearvp = mWindow->addViewport(mRCamera, 1, 0.375f, 0.75f, 0.5, 0.15);
		rearvp->setBackgroundColour(Ogre::ColourValue(244, 164, 96));
        vp->setBackgroundColour(Ogre::ColourValue(244, 164, 96));
        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight())); 
		mRCamera->setAspectRatio(Ogre::Real(rearvp->getActualWidth()) / Ogre::Real(rearvp->getActualHeight())); 
		Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
        mWindow->getViewport(0)->setBackgroundColour(fadeColour);
		mWindow->getViewport(1)->setBackgroundColour(fadeColour);











}

// Here is where we set up all of the non-rendering stuff (our world, various managers, etc)
void 
OgrePong::createScene() 
{
	// Ogre::FontManager::getSingleton().getByName("Big")->load();
    mDebugInterface = new DebugInterface();

    mInputHandler = new InputHandler(mWindow,mDebugInterface);
	
    LuaWrapper::getSingleton()->setWorld(mWorld);
	LuaWrapper::getSingleton()->setDebugInterface(mDebugInterface);
	//LuaWrapper::getSingleton()->loadLuaFile("Level1.lua");

    
	mPongMag = new PongManager(mSceneMgr,mWindow);
	mWorld = new World(mSceneMgr, mInputHandler, mTank);
	mWorld->Switch=0;
	mPongCamera = new PongCamera(mCamera, mWorld, mInputHandler);///
	mPongCameraRear = new PongCamera(mRCamera, mWorld, mInputHandler);
    mPongCameraRear->getCamera()->getViewport()->setOverlaysEnabled(false);
	mTank = new Tank(mSceneMgr, mWorld, pong_0_DIMENSION);
	mTank->addCamera(mPongCamera,mPongCameraRear);
	mTank->attachCamera();
	
    LuaWrapper::getSingleton()->setWorld(mWorld);
	LuaWrapper::getSingleton()->setDebugInterface(mDebugInterface);


	mProjectileManager = new ProjectileManager(mSceneMgr, mInputHandler, mWorld);
	mProjectileManager->addTank(mTank);
	mProjectileManager->setIterator();

	//mWorld->addCamera(mPongCamera);
	mWorld->addTank(mTank);
	mWorld->addProjectile(mProjectileManager);
	mWorld->setIterator();
	mAIManager = new AIManager(mWorld);
	

	// If a class needs access to another class, you can pass in a pointer in the constructor
	//   or, if you need circular accesses (player needs access to the world, and the world needs
	//   access to the player), you can add the pointers later.  Here's an example of both ways
	//   of doing it, giving the world access to the camera and the input handler.

	 Ogre::Vector3 lightdir(0.55F, -0.3F, 0.75F);
     lightdir.normalise();
	 Ogre::Light* light = mSceneMgr->createLight("tstLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(lightdir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4F, 0.4F, 0.4F));
 
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2F, 0.2F, 0.2F));
 
    Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    //mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1200);
    mWindow->getViewport(0)->setBackgroundColour(fadeColour);

	
}

bool 
OgrePong::setup(void)
{

    Ogre::String pluginsPath;
	Ogre::String configPath;
    // only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB

#if OGRE_DEBUG_MODE == 1 && (OGRE_PLATFORM != OGRE_PLATFORM_APPLE && OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS)
	// add _d suffix to config files
	pluginsPath = mResourcePath + "plugins_d.cfg";
	configPath = mResourcePath + "ogre_d.cfg";
#else
	pluginsPath = mResourcePath + "plugins.cfg";
	configPath = mResourcePath + "ogre.cfg";

#endif


#endif
	
    mRoot = new Ogre::Root(pluginsPath, 
        configPath, mResourcePath + "Ogre.log");

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    // Create the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "PongSMInstance");
    createCamera();
	createRearCamera();
	//mWorld->mCamera = mCamera;
	//mWorld->mRCamera = mRCamera;
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    createScene();


    // When we start the renderer, it will run forever, making callbacks every
    // frame to the frame listeners.  These listeners are where all of the non-
    // rendering work is done.  
    createFrameListener();

    return true;

}
/** Configures the application - returns false if the user chooses to abandon configuration. */
bool 
OgrePong::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true);
        return true;
    }
    else
    {
        return false;
    }
}

void
OgrePong::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;

	#if OGRE_DEBUG_MODE == 1 && (OGRE_PLATFORM != OGRE_PLATFORM_APPLE && OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS)
			// add _d suffix to config files
    cf.load(mResourcePath + "resources_d.cfg");
#else
	cf.load(mResourcePath + "resources.cfg");
#endif
		

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                String(macBundlePath() + "/" + archName), typeName, secName);
#else
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
#endif
        }
    }
}

void
OgrePong::destroyScene()
{
    delete mWorld;
    delete mAIManager;
    delete mPongCamera;
    delete mInputHandler;
}

void 
OgrePong::go(void)
{
    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    destroyScene();
}


