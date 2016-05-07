#include "LuaWrapper.h"
#include "World.h"
#include "OgreException.h"
#include "OgreResourceGroupManager.h"
#include "DebugInterface.h"
//#include "TriggerArea.h"
#include "MovingObject.h"

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"

}

//////////////////////////////////////
// Code for making the singleton work
//////////////////////////////////////

LuaWrapper *LuaWrapper::_instance = 0;

LuaWrapper* 
LuaWrapper::getSingleton()
{
    if (!_instance)
    {
        _instance = new LuaWrapper();
		_instance->setup();\
    }
    return _instance;
}


//////////////////////////////////////////////
/// C/C++ functions we are exposing to lua
///////////////////////////////////////////////




void addDebugText(std::string text)
{
	DebugInterface *dbi = LuaWrapper::getSingleton()->getDebugInterface();

	if (dbi != NULL)
	{
		dbi->addDebugText(text);
	}

}


int removeObject(lua_State *L)
{
    int numArgs = lua_gettop(L);

    if (numArgs != 1)
    {
        return 0;
    }
	bool success = false;
    const char* nodeName = lua_tostring(L,1);
    try
    {
		success = LuaWrapper::getSingleton()->getWorld()->removeMovingObject(nodeName);
		if (!success)
		{
			 addDebugText("Object " + std::string(nodeName) + " Could not be removed.   Perhaps doesn't exist");
		}
    }
    catch (Ogre::Exception e)
    {
        Ogre::String x = e.getFullDescription();
			addDebugText(x);

    } catch(...)
    {

    }
	lua_pushboolean(L, success);
    return 1;
}


int createObject(lua_State *L)
{
    int numArgs = lua_gettop(L);

    if (numArgs != 2)
    {
        return 0;
    }
    const char* meshName = lua_tostring(L,1);
    const char* nodeName = lua_tostring(L,2);
    try
    {
		MovingObject *m = LuaWrapper::getSingleton()->getWorld()->createMovingObject(meshName, nodeName);
		if (m == NULL)
		{
			addDebugText("Object " + std::string(nodeName) + " Could not be created.   Perhaps already exists?");
		}
    }
    catch (Ogre::Exception e)
    {
        Ogre::String x = e.getFullDescription();
			addDebugText(x);

    } catch(...)
    {

    }
    return 0;
}


int setPosition(lua_State *L)
{
    int numArgs = lua_gettop(L);

    if (numArgs < 4)
    {
		return 0;
	}
	const char* nodeName = lua_tostring(L,1);
	float x = (float) lua_tonumber(L,2);
	float y = (float) lua_tonumber(L,3);
	float z = (float) lua_tonumber(L,4);
	try
	{
		LuaWrapper::getSingleton()->getWorld()->setPosition(nodeName, Ogre::Vector3(x,y,z));
	} catch (std::exception e)
	{

	} catch(...)
	{

	}
	return 0;
}


int getPosition(lua_State *L)
{
	int numArgs = lua_gettop(L);

	if (numArgs != 1)
    {
        return 0;
    }
    const char* nodeName = lua_tostring(L,1);

	Ogre::Vector3 pos = Ogre::Vector3::ZERO;
		try
	{
		//pos = LuaWrapper::getSingleton()->getWorld()->getPosition(nodeName);
	} catch (std::exception e)
	{
		return 0;
	} catch(...)
	{
		return 0;
	}

	 lua_pushnumber(L, pos.x);
	 lua_pushnumber(L, pos.y);
	 lua_pushnumber(L, pos.z);

	return 3;

}

//int objectInsideTriggerArea(lua_State *L)
//{
//	int numArgs = lua_gettop(L);
//
//	if (numArgs != 1)
//    {
//        return 0;
//    }
//    const char* triggerName = lua_tostring(L,1);
//	boolean inside = false;
//	Ogre::Vector3 pos = Ogre::Vector3::ZERO;
//	try
//	{
//		TriggerArea *t =  LuaWrapper::getSingleton()->getWorld()->getTriggerArea(triggerName);
//		if (t != NULL)
//		{
//			inside = t->obejctsInside();
//		}
//
//
//	} catch (std::exception e)
//	{
//		return 0;
//	} catch(...)
//	{
//		return 0;
//	}
//
//	 lua_pushboolean(L, inside);
//
//	return 1;
//
//}



int setOnEnter(lua_State *L)
{
	int numArgs = lua_gettop(L);

    if (numArgs < 2)
    {
        return 0;
    }
    const char* nodeName = lua_tostring(L,1);
	const char* script =  lua_tostring(L,2);
    try
    {
    LuaWrapper::getSingleton()->getWorld()->setTriggerAreaOnEnter(nodeName, script);
    } catch (std::exception e)
    {

    } catch(...)
    {

    }
    return 0;

}

int setOnExit(lua_State *L)
{

		int numArgs = lua_gettop(L);

    if (numArgs < 2)
    {
        return 0;
    }
    const char* nodeName = lua_tostring(L,1);
	const char* script =  lua_tostring(L,2);
    try
    {
    LuaWrapper::getSingleton()->getWorld()->setTriggerAreaOnExit(nodeName, script);
    } catch (std::exception e)
    {

    } catch(...)
    {

    }
    return 0;
}

int createTriggerArea(lua_State *L)
{
	int numArgs = lua_gettop(L);

    if (numArgs == 1)
    {
		const char* nodeName = lua_tostring(L,1);
		    LuaWrapper::getSingleton()->getWorld()->addTriggerArea(nodeName);

        return 0;
    }
	else if (numArgs == 4)
	{
		const char* nodeName = lua_tostring(L,1);
		float x = (float) lua_tonumber(L,2);
		float y = (float) lua_tonumber(L,3);
		float z = (float) lua_tonumber(L,4);

		    LuaWrapper::getSingleton()->getWorld()->addTriggerArea(nodeName, Ogre::Vector3(x,y,z), Ogre::Vector3::UNIT_SCALE);

        return 0;

	}
	else if (numArgs == 7)
	{
		const char* nodeName = lua_tostring(L,1);
		float x = (float) lua_tonumber(L,2);
		float y = (float) lua_tonumber(L,3);
		float z = (float) lua_tonumber(L,4);

		float sx = (float) lua_tonumber(L,5);
		float sy = (float) lua_tonumber(L,6);
		float sz = (float) lua_tonumber(L,7);

		LuaWrapper::getSingleton()->getWorld()->addTriggerArea(nodeName, Ogre::Vector3(x,y,z), Ogre::Vector3(sx, sy,sz));

		return 0;


	}
	return 0;

}


int setTriggerPosition(lua_State *L)
{
	    int numArgs = lua_gettop(L);

    if (numArgs < 4)
    {
        return 0;
    }
    const char* nodeName = lua_tostring(L,1);
    float x = (float) lua_tonumber(L,2);
    float y = (float) lua_tonumber(L,3);
    float z = (float) lua_tonumber(L,4);
    try
    {
    LuaWrapper::getSingleton()->getWorld()->setTriggerAreaLocation(nodeName, Ogre::Vector3(x,y,z));
    } catch (std::exception e)
    {

    } catch(...)
    {

    }
    return 0;

}

int setTriggerSize(lua_State *L)
{
		    int numArgs = lua_gettop(L);

    if (numArgs < 4)
    {
        return 0;
    }
    const char* nodeName = lua_tostring(L,1);
    float x = (float) lua_tonumber(L,2);
    float y = (float) lua_tonumber(L,3);
    float z = (float) lua_tonumber(L,4);
    try
    {
    LuaWrapper::getSingleton()->getWorld()->setTriggerAreaSize(nodeName, Ogre::Vector3(x,y,z));
    } catch (std::exception e)
    {

    } catch(...)
    {

    }
    return 0;

}
int setVelocity(lua_State *L)
{
    int numArgs = lua_gettop(L);

    if (numArgs < 4)
    {
        return 0;
    }
    const char* nodeName = lua_tostring(L,1);
    float x = (float) lua_tonumber(L,2);
    float y = (float) lua_tonumber(L,3);
    float z = (float) lua_tonumber(L,4);
    try
    {
    LuaWrapper::getSingleton()->getWorld()->setVelocity(nodeName, Ogre::Vector3(x,y,z));
    } catch (std::exception e)
    {

    } catch(...)
    {

    }
    return 0;
}


int setObjectSize(lua_State *L)
 {
    int numArgs = lua_gettop(L);
    float scaleX;
    float scaleY ;
    float scaleZ;

	if (numArgs < 1)
	{
		return 0;
	}
	
	const char* nodeName = lua_tostring(L,1);

	if (numArgs == 2)
	{
     scaleX = (float) lua_tonumber(L,2);
     scaleY = (float) lua_tonumber(L,2);
     scaleZ = (float) lua_tonumber(L,2);
	}
	else if (numArgs == 4)
	{
		scaleX = (float) lua_tonumber(L,2);
     scaleY = (float) lua_tonumber(L,3);
     scaleZ = (float) lua_tonumber(L,4);
	}
	else 
	{
		return 0;
	}
     try
    {
		MovingObject *m = 
    LuaWrapper::getSingleton()->getWorld()->getMovingObject(nodeName);
		if (m != NULL)
		{
			m->setScale(Ogre::Vector3(scaleX, scaleY,scaleZ));
		}
    } catch (std::exception e)
    {

    } catch(...)
    {

    }
    return 0;
}

int setDebugTime(lua_State *L)
{
	    int numArgs = lua_gettop(L);
		float time = (float) lua_tonumber(L,1);

	DebugInterface *dbi = LuaWrapper::getSingleton()->getDebugInterface();

	if (dbi != NULL)
	{
		dbi->setDebugMessageTime(time);
	}
	return 0;
}




int debugOutput(lua_State *L)
{
    int numArgs = lua_gettop(L);

    const char *c =  lua_tostring(L,1);
	addDebugText(c);

    return 0;
}

int clearDebugOutput(lua_State *L)
{
    int numArgs = lua_gettop(L);

	DebugInterface *dbi = LuaWrapper::getSingleton()->getDebugInterface();

	if (dbi != NULL)
	{
		dbi->clearDebugOutput();
	}

    return 0;
}

int showFunctions(lua_State *L)
{
    int numArgs = lua_gettop(L);

	DebugInterface *dbi = LuaWrapper::getSingleton()->getDebugInterface();

	dbi->addDebugText("showFunctions()");
	dbi->addDebugText("setDebugTime(time) (sets how long debug messages remain)");
	dbi->addDebugText("objectInsideTriggerArea(name) (returns true if there is at least one objects inside trigger area)");
	dbi->addDebugText("debugOutput(stringToOutput)");
	dbi->addDebugText("clearDebugOutput()");
	dbi->addDebugText("setTriggerPosition(triggerAreaName,x, y, z)");
	dbi->addDebugText("setTriggerSize(triggerAreaName, scaleX, scaleY, scaleZ");
	dbi->addDebugText("setPosition(name, x, y, z)");
	dbi->addDebugText("getPosition(name) > x, y , z");
	dbi->addDebugText("setVelocity(name, x, y, z)");
	dbi->addDebugText("createObject(name, [x, y, z])");
	dbi->addDebugText("removeObject(name)");

	dbi->addDebugText("setObjectSize(name, scaleX, scaleY, scaleZ)");
	dbi->addDebugText("setOnExit(triggerAreaName, script (string))");
	dbi->addDebugText("setOnEnter(triggerAreaName, script (string))");
	dbi->addDebugText("createTriggerArea(name, [x, y, z], [scaleX, sccaleY, scaleZ])");

	return 0;
}
////////////////////////////////////////////////
/// Utility function for grabbbing file path of scripts
//////////////////////////////////////////////////



std::string getFullPath(std::string resourceName)
{
	std::string foundPath = resourceName;
	Ogre::ResourceGroupManager* groupManager = Ogre::ResourceGroupManager::getSingletonPtr() ;
	Ogre::String group = groupManager->findGroupContainingResource(resourceName) ;
	Ogre::FileInfoListPtr fileInfos = groupManager->findResourceFileInfo(group,resourceName);
	Ogre::FileInfoList::iterator it = fileInfos->begin();
	if(it != fileInfos->end())
	{
		foundPath = it->archive->getName() +  resourceName;
	}

	return foundPath;
}




////////////////////////////////////////////////
///  Registering functions with lua
//////////////////////////////////////////////////

void LuaWrapper::initializeLuaFunctions()
{
    lua_register(mLuaState, "createObject", createObject);
    lua_register(mLuaState, "removeObject", removeObject);
    lua_register(mLuaState, "setPosition", setPosition);
    lua_register(mLuaState, "setVelocity", setVelocity);
	lua_register(mLuaState,"debugOutput", debugOutput);
	lua_register(mLuaState, "getPosition", getPosition);
	lua_register(mLuaState,"setDebugTime", setDebugTime);
	lua_register(mLuaState, "clearDebugOutput", clearDebugOutput);
	lua_register(mLuaState, "createTriggerArea", createTriggerArea);
	lua_register(mLuaState, "setOnEnter", setOnEnter);
	lua_register(mLuaState, "setOnExit", setOnExit);
	lua_register(mLuaState, "setTriggerPosition", setTriggerPosition);
	lua_register(mLuaState, "setTriggerSize", setTriggerSize);
	lua_register(mLuaState, "showFunctions", showFunctions);
	lua_register(mLuaState, "help", showFunctions);
	lua_register(mLuaState, "objectInsideTriggerArea", objectInsideTriggerArea);
	lua_register(mLuaState, "setObjectSize", setObjectSize);

}





void 
LuaWrapper::setWorld(World *world)
{
    mWorld = world;
}


void  LuaWrapper::doString(const char *s)
{ 

	try
	{
		luaL_dostring(mLuaState, s); 
	} catch (std::exception e)
	{
		DebugInterface *dbi = LuaWrapper::getSingleton()->getDebugInterface();

		if (dbi != NULL)
		{
			dbi->addDebugText(e.what());
		}

	} catch(...)
	{
		DebugInterface *dbi = LuaWrapper::getSingleton()->getDebugInterface();

		if (dbi != NULL)
		{
			dbi->addDebugText("Exception caught in lua");
		};

	}

}
 void LuaWrapper::Think(float time)
 {	 
    lua_getglobal(mLuaState, "ScriptManagerThink");
    lua_pushnumber(mLuaState, time);
    lua_call(mLuaState, 1, 0);
 }

void LuaWrapper::setup()
{
    mLuaState = luaL_newstate();
    luaL_openlibs(mLuaState);
    initializeLuaFunctions();
	std::string path = getFullPath("ScriptManager.lua");
	luaL_dofile(mLuaState, path.c_str());
	mDebugInterface = NULL;
	mWorld = NULL;
}

LuaWrapper::~LuaWrapper()
{
	lua_close(mLuaState);
}

void LuaWrapper::loadLuaFile(std::string luaFile)
{
	std::string path = getFullPath(luaFile);
	luaL_dofile(mLuaState, path.c_str());


}
