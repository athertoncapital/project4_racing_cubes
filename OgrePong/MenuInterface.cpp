#include "MenuInterface.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayElement.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreResourceManager.h"
#include "OgreFontManager.h"
#include "LuaWrapper.h"

MenuInterface::MenuInterface(void)
{
	// There is a bug in current version of Ogre, doesn't seem to load fonts like it should.  This will
	// kick the resouce manager so that the fonts load properly (really shouldn't need it, but ...)
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) { iter.getNext()->load(); }

	Ogre::OverlayManager *olm;
	Ogre::OverlayContainer *panel ;
	Ogre::String szElement;

	olm=Ogre::OverlayManager::getSingletonPtr();


	mMenuOverlay=olm->create("MenuConsole");  
	// Next, we create a panel within this overlay:
	panel=static_cast<Ogre::OverlayContainer*>(olm->createOverlayElement("Panel","MenuTextPanel"));
	panel->setMetricsMode(Ogre::GMM_RELATIVE); 
	panel->setPosition(.0f,.0f);
	panel->setDimensions(1.0f,1.0f);
	panel->setMaterialName("Menu");
	mMenuOverlay->add2D(panel);     


	mOverlayText=static_cast<Ogre::TextAreaOverlayElement*>(olm->createOverlayElement("TextArea","MenuConsoleText"));

	mOverlayText->setFontName("BlueHighwayBig"); 
	mOverlayText->setMetricsMode(Ogre::GMM_PIXELS);   
	mOverlayText->setCaption("Start");	              // Set what we want the text area to show    
	mOverlayText->setCharHeight(100);	              // Set the height of the text (in pixels)
    
    mOverlayText->setPosition(200,200);


	// Add the text area to the panel
	panel->addChild(mOverlayText);

	// Start out active
	mMenuOverlay->show();
	mIsActive = true;

    mHistory.push_back("Start");
    mHistory.push_back("Continue");
    mHistory.push_back("Quit");
    //mHistory.push_back("Start");
    //mHistory[1] = "Continue";
    //mHistory[2] = "Quit";
    //mHistory[0] = "Start";
    


	//mDebugOutputOverlay=olm->create("DebuggingOutput");  

	//panel=static_cast<Ogre::OverlayContainer*>(olm->createOverlayElement("Panel","DebugOutputTextPanel"));
	//panel->setMetricsMode(Ogre::GMM_RELATIVE); 
	//panel->setPosition(.05f,.5f);
	//panel->setDimensions(0.9f,0.49f);
	//panel->setMaterialName("BlueSemiTran");
	//mDebugOutputOverlay->add2D(panel);    

	//mOverlayDebugOutputText=static_cast<Ogre::TextAreaOverlayElement*>(olm->createOverlayElement("TextArea","DebugOutputText"));
	//mOverlayDebugOutputText->setFontName("BlueHighwayBig"); 
	//mOverlayDebugOutputText->setMetricsMode(Ogre::GMM_PIXELS);
	//mOverlayDebugOutputText->setCharHeight(23);	              // Set the height of the text (in pixels)
	//mOverlayDebugOutputText->setCaption("");	

	//panel->addChild(mOverlayDebugOutputText);

	//// Start out inactive
	//mDebugOutputOverlay->hide();

	//mMessageTime = 30;
}



void 
	MenuInterface::HandleKeystroke(OIS::KeyEvent e)
{
	if (e.key == OIS::KC_RETURN)
	{
		LuaWrapper::getSingleton()->doString(mMenuCommand.c_str());
        //mMenuOverlay->hide();
		mHistory.push_back(mMenuCommand);
		mHistoryIndex = (int) mHistory.size();
		mMenuCommand = "";
		mOverlayText->setCaption(mMenuCommand);
	}
	else if (e.key == OIS::KC_UP)
	{
		mHistoryIndex--;
		mHistoryIndex = std::max<int>(mHistoryIndex,0);
		if (mHistoryIndex < mHistory.size())
		{
			mMenuCommand = mHistory[mHistoryIndex];
			mOverlayText->setCaption(mMenuCommand);
		}
	}
	else if (e.key == OIS::KC_DOWN)
	{
		mHistoryIndex++;
		mHistoryIndex = (int) std::min<size_t>(mHistoryIndex,mHistory.size()-1);
		if (mHistoryIndex < mHistory.size())
		{
			mMenuCommand = mHistory[mHistoryIndex];
			mOverlayText->setCaption(mMenuCommand);
		}
	}

	/*else if (e.key != OIS::KC_LSHIFT && e.key != OIS::KC_RSHIFT && e.key != OIS::KC_LCONTROL && e.key != OIS::KC_RCONTROL)
	{
		mMenuCommand.push_back((char) e.text);
		mOverlayText->setCaption("Lua >" + mMenuCommand);
	}*/
}


void 
	MenuInterface::SetMenuConsoleActive(bool activate)
{
	if (activate != mIsActive)
	{
		mIsActive = activate;
		if (mIsActive)
		{
			mMenuCommand = "";
			mOverlayText->setCaption("");
			mMenuOverlay->show();
		}
		else
		{
			mMenuOverlay->hide();
		}
	}
}

//void MenuInterface::addMenuText(std::string message)
//{
//	
//    mDebugOutput.push_back(message);
//	//mDebugTimeRemaining.push_back(mMessageTime);
//	resetOverlayText();
//}
void MenuInterface::Think(float time)
{
	//bool changed = false;

	//for (int i = 0; i < mDebugTimeRemaining.size(); i++)
	//{
	//	mDebugTimeRemaining[i] = mDebugTimeRemaining[i] - time;
	//}
	//while (!mDebugTimeRemaining.empty() && mDebugTimeRemaining.front() <= 0)
	//{
	//	changed = true;
	//	mDebugTimeRemaining.erase(mDebugTimeRemaining.begin());
	//	mDebugOutput.erase(mDebugOutput.begin());
	//}

	//if (changed)
	//{
	//	resetOverlayText();
	//}

}


//void 
//	MenuInterface::clearDebugOutput()
//{
//	mDebugTimeRemaining.clear();
//	mDebugOutput.clear();
//	resetOverlayText();
//}


//void MenuInterface::resetOverlayText()
//{
//	if (mDebugOutput.size() > 0)
//	{
//		mDebugOutputOverlay->show();
//	}
//	else 
//	{
//		mDebugOutputOverlay->hide();
//	}
//	std::string display = std::string();
//	for (std::vector<std::string>::reverse_iterator it  = mDebugOutput.rbegin(); it != mDebugOutput.rend(); it++)
//	{
//		display.append(*it + "\n");
//	}
//	mOverlayDebugOutputText->setCaption(display);
//
//
//}

void MenuInterface::showOverlay()
{
    mMenuOverlay->show();
}

void MenuInterface::hideOverlay()
{
    mMenuOverlay->hide();

}
MenuInterface::~MenuInterface(void)
{
}
