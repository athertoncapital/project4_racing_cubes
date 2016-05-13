#ifndef __WorldManager_h_
#define __WorldManager_h_
#include "slideredbrick.h"
#include "Ogre.h"

class World;
class PongManager;
enum slideredbrick;

class WorldManager {
public:
	WorldManager(World *world);
	void doWork();
	void getEvent(const PongManager *pongManager);
	World *mWorld;
private:
	void updateObjects();
	void updateAIPlayer(slideredbrick velocity); 
	void updateUser(slideredbrick velocity);
	bool TestpongCollideWithBorder_2();
	bool TestpongCollideWithBorder_2_1();
	bool TestpongCollideWithBorder_2_2();
	bool TestpongCollideWithBorder_2_3();
	bool TestpongCollideWithBorder_2_4();
	bool TestpongCollideWithBorder_2_5();
	bool TestpongCollideWithBorder_2_6();

	bool TestpongCollideWithBorder_3();
	bool TestpongCollideWithBorder_3_1();
	bool TestpongCollideWithBorder_3_2();
	bool TestpongCollideWithBorder_3_3();
	bool TestpongCollideWithBorder_3_4();
	bool TestpongCollideWithBorder_3_5();
	bool TestpongCollideWithBorder_3_6();

	bool TestpongCollideWithBorder_1();
	bool TestpongCollideWithBorder_1_1();
	bool TestpongCollideWithBorder_1_2();
	bool TestpongCollideWithBorder_1_3();
	bool TestpongCollideWithBorder_1_4();
	bool TestpongCollideWithBorder_1_5();
	bool TestpongCollideWithBorder_1_6();



	bool TestpongCollideWithBorder_4();
	bool TestpongCollideWithBorder_4_1();
	bool TestpongCollideWithBorder_4_2();
	bool TestpongCollideWithBorder_4_3();
	bool TestpongCollideWithBorder_4_4();
	bool TestpongCollideWithBorder_4_5();
	bool TestpongCollideWithBorder_4_6();

	//bool TestAIPlayerHitBorder_1();
	//bool TestAIPlayerHitBorder_4();
	bool TestUserHitBorder_1();
	bool TestUserHitBorder_4();
	bool TestpongHitByUserRedBrick();
	
	bool TestpongHitByUserRedBrick_1();
	bool TestpongHitByUserRedBrick_2();
	bool TestpongHitByUserRedBrick_3();
	bool TestpongHitByUserRedBrick_4();
	bool TestpongHitByUserRedBrick_5();
	bool TestpongHitByUserRedBrick_6();
	bool TestpongHitByAIRedBrick();
	bool TestpongHitByAIRedBrick_1();
	bool TestpongHitByAIRedBrick_2();
	bool TestpongHitByAIRedBrick_3();
	bool TestpongHitByAIRedBrick_4();
	bool TestpongHitByAIRedBrick_5();
	bool TestpongHitByAIRedBrick_6();
	void putpongAtBorder_Edge();
	void putpongAtRedBrickEdge();
	void putpongAtBorder_1Edge();
	void putpongAtBorder_4Edge();
	void putpongAtAIRedBrickEdge();
	void putpongAtUserRedBrickEdge();
	void updateScore();
    void updateLevel();
	

};

#endif