#ifndef __World_h_
#define __World_h_

#include "Tank.h"
#include <time.h>

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Vector3;
	class Overlay;
	class AxisAlignedBox;
}

// Forward delcarations of our own classes
class PongManager;
class InputHandler;
class RedBrick;
enum slideredbrick;
class WorldManager;
class MovingObject;
class PongCamera;
class InputHandler;
class Tank;
class ProjectileManager;
class Border_;

class AIManager;

class World
{
public:
	
	int frame0[161];
	int frame1[81][81];
	int frame2[81][81];
	int frame3[81][81];

	float U_u;
	float U_v;
	float AI_0_u;
	float AI_0_v;
	float AI_1_u;
	float AI_1_v;
	float AI_2_u;
	float AI_2_v;

    float SPEED_COEFFICIENT;

    float SPEED_COEFFICIENT_AI_0;
    float SPEED_COEFFICIENT_AI_1;
    float SPEED_COEFFICIENT_AI_2;

	Ogre::Camera* mCamera;
	Ogre::Camera* mRCamera;
	Ogre::Vector3 World::Normal(float u, float v);
	Ogre::Vector3 World::Tangent(float u, float v);
	Ogre::Vector3 World::Binormal(float u, float v);
	Ogre::Matrix3 World::Orientation(Ogre::Vector3 xBasis, Ogre::Vector3 yBasis, Ogre::Vector3 zBasis);
	int Switch;
	World(Ogre::SceneManager *sceneManager, InputHandler *input, Tank *tank);
	~World();
	MovingObject *mObj1;
    MovingObject *mObj2;
    MovingObject *mObj3;
	MovingObject *mObj4;

    MovingObject *mCrossHair;

    //InputHandler *mInputHandler;
	Ogre::Real t;
	Border_* getBorder_2() const { return mBorder_2; }
	Border_* getBorder_3() const { return mBorder_3; }
	Border_* getBorder_1() const { return mBorder_1; }
	Border_* getBorder_4() const { return mBorder_4; }
	//    void think(const Ogre::Real& time);

	Tank* getpong() const { return mpong; }
	Tank* getpong1() const { return mpong1; }
	Tank* getpong2() const { return mpong2; }
	Tank* getpong3() const { return mpong3; }
	Tank* getpong4() const { return mpong4; }
	Tank* getpong5() const { return mpong5; }
	Tank* getpong6() const { return mpong6; }
	void getEventFrom(PongManager *pongManager);
	RedBrick* getAIRedBrick() const { return mAIRedBrick; }
	RedBrick* getUserRedBrick() const { return mUserRedBrick; }
	RedBrick* getAIPlayer() const { return mAIPlayer; }
	int getUserScore() const { return mUserScore; }
	void setUserScore(int score) { mUserScore = score; }
	RedBrick* getUser() const { return mUser; }
	void reset();

	int getAIPlayerScore() const { return mAIScore; }
	void setAIPlayerScore(int score) { mAIScore = score; }
	void updateLevel();
	bool flag();
	int getLevel() { return mLevel; }
	
	int mLevel;
	void World::Think(const Ogre::Real& mTime);
    //void Think(float mTime);
	void yawTank(InputHandler *mInputHandler, const Ogre::Real& mTime);
	void fly_or_dive_Tank(InputHandler *mInputHandler, const Ogre::Real& mTime);
	
	void addTank(Tank *t) {mTank = t; }
	void addProjectile(ProjectileManager *pm) { mProjectileManager = pm; }
	void setIterator();
    void recordMove();

	
	//Tank *getHumanTank() { return mHumanPlayer; }
	
	void Push(Tank::Node *node);

	/* Linked list structure that will contain AI tank nodes */
	struct LinkedList {
		Tank::Node *head;
	} mList;

	/* List of AI tanks */
	LinkedList *tanks;

	Ogre::SceneManager *SceneManager() { return mSceneManager; }
	Tank* getHumanPlayer() const { return mHuman; }
    Ogre::Vector3 *spawnPoints;
	Tank *mHuman;
	float Hpoint_x;
	/*Ogre::Real Hpoint_y;
	Ogre::Real Hpoint_z;
	Ogre::Real AIpoint_x;
	Ogre::Real AIpoint_y;

	Ogre::Real AIpoint_z;*/
	time_t start, end, diff;
	ProjectileManager *mProjectileManager;
	float PROJECTILE_SPEED_H;
	float PROJECTILE_SPEED_V;
private:

	Ogre::Overlay *mGameOverOverlay;
	void createGameOverOverlay();

	Border_* mBorder_2;
	Border_* mBorder_3;
	Border_* mBorder_4;
	Border_* mBorder_1;
	AIManager *mAIManager;
	void createModifiers();
	int mScore;
	Ogre::Overlay* mOverlay;
	Tank* mpong;
	Tank* mpong1;
	Tank* mpong2;
	Tank* mpong3;
	Tank* mpong4;
	Tank* mpong5;
	Tank* mpong6;
	RedBrick* mUserRedBrick;
	RedBrick* mAIRedBrick;
	RedBrick* mAIPlayer;
	RedBrick* mUser;
	WorldManager *mWorldManager;
	int mUserScore;
	int mAIScore;
	void createOverlay();
	void initialStates();
protected:
	Ogre::SceneManager* getSceneManager() { return mSceneManager; }
	
	Ogre::SceneManager *mSceneManager;
	InputHandler *mInputHandler;
	
	Tank *mTank;
	
	
	//Ogre::SceneNode *mFloorNode;

	/* Used to iterate through AI tank list to see if any user tank collides with another tank */
	Tank::Node *iterator;

	
};

#endif