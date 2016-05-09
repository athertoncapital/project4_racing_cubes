extern "C"
{
#include "lua.h"
}
#include <string>

class World;
class DebugInterface;


class LuaWrapper
{
public:
    static LuaWrapper *getSingleton();
    void doString(const char *s); 
    void setWorld(World *world);
	void setDebugInterface(DebugInterface *dbi) { mDebugInterface = dbi; }
    World *getWorld() { return mWorld; }
	DebugInterface *getDebugInterface() { return mDebugInterface; }
    ~LuaWrapper();
	void Think(float time);
	void loadLuaFile(std::string luaFile);
private:

	void setup();
    static LuaWrapper *_instance;
	LuaWrapper() {} 
    void initializeLuaFunctions();
    World *mWorld;
	DebugInterface *mDebugInterface;
    lua_State* mLuaState;
};