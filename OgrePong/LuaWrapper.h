extern "C"
{
#include "lua.h"
}
#include <string>

class World;
class DebugInterface;
class MenuInterface;
class InputHandler;


class LuaWrapper
{
public:
    static LuaWrapper *getSingleton();
    void doString(const char *s); 
    void setWorld(World *world);
	void setDebugInterface(DebugInterface *dbi) { mDebugInterface = dbi; }
    void setMenuInterface(MenuInterface *mi) { mMenuInterface = mi;}
    void setInputHandler(InputHandler *ih) {mInputHandler = ih;}

    World *getWorld() { return mWorld; }
	DebugInterface *getDebugInterface() { return mDebugInterface; }
	MenuInterface *getMenuInterface() { return mMenuInterface; }
    InputHandler *getInputHandler() { return mInputHandler;}
    bool isDone() { return done; }
    void setDone(bool statement) { done = statement;}

    ~LuaWrapper();
	void Think(float time);
	void loadLuaFile(std::string luaFile);
    void LuaWrapper::showMenuOverlay(bool activate);
private:

	void setup();
    static LuaWrapper *_instance;
	LuaWrapper() {} 
    void initializeLuaFunctions();
    World *mWorld;
	DebugInterface *mDebugInterface;
    MenuInterface *mMenuInterface;
    InputHandler *mInputHandler;
    lua_State* mLuaState;
    bool done;
};