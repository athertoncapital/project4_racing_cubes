#include <OIS\OIS.h>
// Including header files within header files is frowned upon,
// but this one is requried for Ogre Strings.
#include "OgrePrerequisites.h"

namespace Ogre
{
    class Overlay;
    class TextAreaOverlayElement;
}

class MenuInterface
{
public:
    MenuInterface(void);
    ~MenuInterface(void);

    void SetMenuConsoleActive(bool activate);
    bool MenuConsoleActive() { return mIsActive; }
    void HandleKeystroke(OIS::KeyEvent key);
	void addMenuText(std::string message);
	void Think(float time);
	void setDebugMessageTime(float time) {mMessageTime = time; }
	void clearDebugOutput();

private:
    bool mIsActive;
    Ogre::Overlay *mDebugConsoleOverlay;
    Ogre::Overlay *mDebugOutputOverlay;
    Ogre::TextAreaOverlayElement *mOverlayText;
    Ogre::String mLuaCommand;
    int mHistoryIndex;
    std::vector<Ogre::String> mHistory;

	std::vector<Ogre::String> mDebugOutput;
	std::vector<float> mDebugTimeRemaining;
	Ogre::TextAreaOverlayElement *mOverlayDebugOutputText;

	float mMessageTime;
	void resetOverlayText();

};