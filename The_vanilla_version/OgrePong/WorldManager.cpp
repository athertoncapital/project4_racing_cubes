#include "WorldManager.h"
#include "World.h"
#include "PongManager.h"
#include "RedBrick.h"
#include "border.h"
#include "Tank.h"
#include "InputHandler.h"
#include "AIManager.h"
#include "slideredbrick.h"
#include "Properties.h"

#include "OgreOverlayManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "Ogre.h"
WorldManager::WorldManager(World *world) {
	mWorld = world;
}

void WorldManager::doWork() {
	updateScore();
	updateLevel();
	updateObjects();
	
	
}
void WorldManager::getEvent(const PongManager *pongManager) {
	const InputHandler *inputHandler = pongManager->getInputHandler();
	const AIManager* aiManager = pongManager->getAIManager();
	/*if (inputHandler->isKeyDown(OIS::KC_LEFT)) {
		updateUser(gony);
	} else if (inputHandler->isKeyDown(OIS::KC_RIGHT)) {
		updateUser(gotopy);
	} else {
		updateUser(statover);
	}*/


	//updateAIPlayer(aiManager->onemorestep());
}


/*
bool WorldManager::TestAIPlayerHitBorder_4() {//s
	//RedBrick *AIPlayer = mWorld->getAIPlayer();
	Border_ *Border_4 = mWorld->getBorder_4();
	return AIPlayer->hitVerticallyWith(Border_4);
}

*/

bool WorldManager::TestUserHitBorder_1() {//n
	RedBrick *User = mWorld->getUser();
	Border_ *Border_1 = mWorld->getBorder_1();
	return User->hitVerticallyWith(Border_1);
}

bool WorldManager::TestUserHitBorder_4() {//s
	RedBrick *User = mWorld->getUser();
	Border_ *Border_4 = mWorld->getBorder_4();
	return User->hitVerticallyWith(Border_4);
}

/*
bool WorldManager::TestAIPlayerHitBorder_1() {//n
	//RedBrick *AIPlayer = mWorld->getAIPlayer();
	Border_ *Border_1 = mWorld->getBorder_1();
	return AIPlayer->hitVerticallyWith(Border_1);
}
*/
bool WorldManager::TestpongHitByAIRedBrick() {
	Tank *pong = mWorld->getpong();
	RedBrick *AIRedBrick = mWorld->getAIRedBrick();
	return pong->hitHorizontallyWith(AIRedBrick);
}

bool WorldManager::TestpongHitByAIRedBrick_1() {
	Tank *pong = mWorld->getpong1();
	RedBrick *AIRedBrick = mWorld->getAIRedBrick();
	return pong->hitHorizontallyWith(AIRedBrick);
}
bool WorldManager::TestpongHitByAIRedBrick_2() {
	Tank *pong = mWorld->getpong2();
	RedBrick *AIRedBrick = mWorld->getAIRedBrick();
	return pong->hitHorizontallyWith(AIRedBrick);
}
bool WorldManager::TestpongHitByAIRedBrick_3() {
	Tank *pong = mWorld->getpong3();
	RedBrick *AIRedBrick = mWorld->getAIRedBrick();
	return pong->hitHorizontallyWith(AIRedBrick);
}
bool WorldManager::TestpongHitByAIRedBrick_4() {
	Tank *pong = mWorld->getpong4();
	RedBrick *AIRedBrick = mWorld->getAIRedBrick();
	return pong->hitHorizontallyWith(AIRedBrick);
}
bool WorldManager::TestpongHitByAIRedBrick_5() {
	Tank *pong = mWorld->getpong5();
	RedBrick *AIRedBrick = mWorld->getAIRedBrick();
	return pong->hitHorizontallyWith(AIRedBrick);
}
bool WorldManager::TestpongHitByAIRedBrick_6() {
	Tank *pong = mWorld->getpong6();
	RedBrick *AIRedBrick = mWorld->getAIRedBrick();
	return pong->hitHorizontallyWith(AIRedBrick);
}
bool WorldManager::TestpongCollideWithBorder_2() {//w
	Tank *pong = mWorld->getpong();
	Border_ *Border_2 = mWorld->getBorder_2();
	return pong->hitHorizontallyWith(Border_2);
}

bool WorldManager::TestpongCollideWithBorder_2_1() {//w
	Tank *pong = mWorld->getpong1();
	Border_ *Border_2 = mWorld->getBorder_2();
	return pong->hitHorizontallyWith(Border_2);
}
bool WorldManager::TestpongCollideWithBorder_2_2() {//w
	Tank *pong = mWorld->getpong2();
	Border_ *Border_2 = mWorld->getBorder_2();
	return pong->hitHorizontallyWith(Border_2);
}
bool WorldManager::TestpongCollideWithBorder_2_3() {//w
	Tank *pong = mWorld->getpong3();
	Border_ *Border_2 = mWorld->getBorder_2();
	return pong->hitHorizontallyWith(Border_2);
}
bool WorldManager::TestpongCollideWithBorder_2_4() {//w
	Tank *pong = mWorld->getpong4();
	Border_ *Border_2 = mWorld->getBorder_2();
	return pong->hitHorizontallyWith(Border_2);
}
bool WorldManager::TestpongCollideWithBorder_2_5() {//w
	Tank *pong = mWorld->getpong5();
	Border_ *Border_2 = mWorld->getBorder_2();
	return pong->hitHorizontallyWith(Border_2);
}
bool WorldManager::TestpongCollideWithBorder_2_6() {//w
	Tank *pong = mWorld->getpong6();
	Border_ *Border_2 = mWorld->getBorder_2();
	return pong->hitHorizontallyWith(Border_2);
}


bool WorldManager::TestpongCollideWithBorder_3() {//e
	Tank *pong = mWorld->getpong();
	Border_ *Border_3 = mWorld->getBorder_3();
	return pong->hitHorizontallyWith(Border_3);
}

bool WorldManager::TestpongCollideWithBorder_3_1() {//e
	Tank *pong = mWorld->getpong1();
	Border_ *Border_3 = mWorld->getBorder_3();
	return pong->hitHorizontallyWith(Border_3);
}
bool WorldManager::TestpongCollideWithBorder_3_2() {//e
	Tank *pong = mWorld->getpong2();
	Border_ *Border_3 = mWorld->getBorder_3();
	return pong->hitHorizontallyWith(Border_3);
}
bool WorldManager::TestpongCollideWithBorder_3_3() {//e
	Tank *pong = mWorld->getpong3();
	Border_ *Border_3 = mWorld->getBorder_3();
	return pong->hitHorizontallyWith(Border_3);
}
bool WorldManager::TestpongCollideWithBorder_3_4() {//e
	Tank *pong = mWorld->getpong4();
	Border_ *Border_3 = mWorld->getBorder_3();
	return pong->hitHorizontallyWith(Border_3);
}
bool WorldManager::TestpongCollideWithBorder_3_5() {//e
	Tank *pong = mWorld->getpong5();
	Border_ *Border_3 = mWorld->getBorder_3();
	return pong->hitHorizontallyWith(Border_3);
}
bool WorldManager::TestpongCollideWithBorder_3_6() {//e
	Tank *pong = mWorld->getpong6();
	Border_ *Border_3 = mWorld->getBorder_3();
	return pong->hitHorizontallyWith(Border_3);
}

void WorldManager::updateObjects() {

	Tank *pong = mWorld->getpong();
	RedBrick *AIPlayer = mWorld->getAIPlayer();
	RedBrick *User = mWorld->getUser();
	/*if (TestpongHitByAIRedBrick() || TestpongHitByUserRedBrick()) { 
		pong->reverseHorizontalvelocity();
		putpongAtRedBrickEdge();
		pong->setSpeed(pong->getSpeed() + SPEED_INC_STEP);
	    AIPlayer->setSpeed(AIPlayer->getSpeed() + SPEED_INC_STEP);
	    User->setSpeed(User->getSpeed() + SPEED_INC_STEP);
	} 
	if (TestpongCollideWithBorder_1() || TestpongCollideWithBorder_4()) {
		pong->reverseVerticalvelocity();
		putpongAtBorder_Edge();
	}
	if (TestpongCollideWithBorder_2() || TestpongCollideWithBorder_3()) {
		pong->reset();
		AIPlayer->reset();
		User->reset();
	}*/
	int mLevel = mWorld->getLevel();


	
	
	
}

bool WorldManager::TestpongHitByUserRedBrick() {
	Tank *pong = mWorld->getpong();
	RedBrick *UserRedBrick = mWorld->getUserRedBrick();
	return pong->hitHorizontallyWith(UserRedBrick);
}

bool WorldManager::TestpongHitByUserRedBrick_1() {
	Tank *pong = mWorld->getpong1();
	RedBrick *UserRedBrick = mWorld->getUserRedBrick();
	return pong->hitHorizontallyWith(UserRedBrick);
}
bool WorldManager::TestpongHitByUserRedBrick_2() {
	Tank *pong = mWorld->getpong2();
	RedBrick *UserRedBrick = mWorld->getUserRedBrick();
	return pong->hitHorizontallyWith(UserRedBrick);
}
bool WorldManager::TestpongHitByUserRedBrick_3() {
	Tank *pong = mWorld->getpong3();
	RedBrick *UserRedBrick = mWorld->getUserRedBrick();
	return pong->hitHorizontallyWith(UserRedBrick);
}
bool WorldManager::TestpongHitByUserRedBrick_4() {
	Tank *pong = mWorld->getpong4();
	RedBrick *UserRedBrick = mWorld->getUserRedBrick();
	return pong->hitHorizontallyWith(UserRedBrick);
}
bool WorldManager::TestpongHitByUserRedBrick_5() {
	Tank *pong = mWorld->getpong5();
	RedBrick *UserRedBrick = mWorld->getUserRedBrick();
	return pong->hitHorizontallyWith(UserRedBrick);
}
bool WorldManager::TestpongHitByUserRedBrick_6() {
	Tank *pong = mWorld->getpong6();
	RedBrick *UserRedBrick = mWorld->getUserRedBrick();
	return pong->hitHorizontallyWith(UserRedBrick);
}

bool WorldManager::TestpongCollideWithBorder_1() {//n
	Tank *pong = mWorld->getpong();
	Border_ *Border_1 = mWorld->getBorder_1();
	return pong->hitVerticallyWith(Border_1);
}

bool WorldManager::TestpongCollideWithBorder_1_1() {//n
	Tank *pong = mWorld->getpong1();
	Border_ *Border_1 = mWorld->getBorder_1();
	return pong->hitVerticallyWith(Border_1);
}
bool WorldManager::TestpongCollideWithBorder_1_2() {//n
	Tank *pong = mWorld->getpong2();
	Border_ *Border_1 = mWorld->getBorder_1();
	return pong->hitVerticallyWith(Border_1);
}
bool WorldManager::TestpongCollideWithBorder_1_3() {//n
	Tank *pong = mWorld->getpong3();
	Border_ *Border_1 = mWorld->getBorder_1();
	return pong->hitVerticallyWith(Border_1);
}
bool WorldManager::TestpongCollideWithBorder_1_4() {//n
	Tank *pong = mWorld->getpong4();
	Border_ *Border_1 = mWorld->getBorder_1();
	return pong->hitVerticallyWith(Border_1);
}
bool WorldManager::TestpongCollideWithBorder_1_5() {//n
	Tank *pong = mWorld->getpong5();
	Border_ *Border_1 = mWorld->getBorder_1();
	return pong->hitVerticallyWith(Border_1);
}
bool WorldManager::TestpongCollideWithBorder_1_6() {//n
	Tank *pong = mWorld->getpong6();
	Border_ *Border_1 = mWorld->getBorder_1();
	return pong->hitVerticallyWith(Border_1);
}


bool WorldManager::TestpongCollideWithBorder_4() {//s
	Tank *pong = mWorld->getpong();
	Border_ *Border_4 = mWorld->getBorder_4();
	return pong->hitVerticallyWith(Border_4);
}

bool WorldManager::TestpongCollideWithBorder_4_1() {//s
	Tank *pong = mWorld->getpong1();
	Border_ *Border_4 = mWorld->getBorder_4();
	return pong->hitVerticallyWith(Border_4);
}
bool WorldManager::TestpongCollideWithBorder_4_2() {//s
	Tank *pong = mWorld->getpong2();
	Border_ *Border_4 = mWorld->getBorder_4();
	return pong->hitVerticallyWith(Border_4);
}
bool WorldManager::TestpongCollideWithBorder_4_3() {//s
	Tank *pong = mWorld->getpong3();
	Border_ *Border_4 = mWorld->getBorder_4();
	return pong->hitVerticallyWith(Border_4);
}
bool WorldManager::TestpongCollideWithBorder_4_4() {//s
	Tank *pong = mWorld->getpong4();
	Border_ *Border_4 = mWorld->getBorder_4();
	return pong->hitVerticallyWith(Border_4);
}
bool WorldManager::TestpongCollideWithBorder_4_5() {//s
	Tank *pong = mWorld->getpong5();
	Border_ *Border_4 = mWorld->getBorder_4();
	return pong->hitVerticallyWith(Border_4);
}
bool WorldManager::TestpongCollideWithBorder_4_6() {//s
	Tank *pong = mWorld->getpong6();
	Border_ *Border_4 = mWorld->getBorder_4();
	return pong->hitVerticallyWith(Border_4);
}


void WorldManager::putpongAtBorder_Edge() {}

void WorldManager::putpongAtRedBrickEdge() {}

void WorldManager::updateAIPlayer(slideredbrick velocity) {}

void WorldManager::updateUser(slideredbrick velocity) {}

void WorldManager::putpongAtBorder_4Edge() {}

void WorldManager::putpongAtBorder_1Edge() {}

void WorldManager::putpongAtAIRedBrickEdge() {}

void WorldManager::putpongAtUserRedBrickEdge() {}



void World::reset() {
	initialStates();
	mpong->reset();
	if(mLevel>=1)
	mpong1->reset();
	if(mLevel>=2)
	mpong2->reset();
	if(mLevel>=3)
	mpong3->reset();
	if(mLevel>=4)
	mpong4->reset();
	if(mLevel>=5)
	mpong5->reset();
	if(mLevel>=6)
	mpong6->reset();
	mAIRedBrick->reset();
	mUserRedBrick->reset();

}
void WorldManager::updateLevel() {
	//mWorld->updateLevel();
	int level = 0;
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("level");
	char levelCaption[25];
	if(mWorld->uScore>2) level=1;
	if(mWorld->uScore>4) level=2;
	if(mWorld->uScore>8) level=4;
	if(mWorld->uScore>16)level=5;
	if(mWorld->uScore>32)level=6;
	if(mWorld->uScore>64)level=7;
	if(mWorld->uScore>128)level=8;

	sprintf(levelCaption, "Level : %i", level);
	te->setCaption(levelCaption);
}

void WorldManager::updateScore() {
	int mUserScore = mWorld->getUserScore();
	int mAIScore = mWorld->getAIPlayerScore();
	int mLevel=mWorld->getLevel();
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("left");
	char score[500];
	char time[25];
	int k = mWorld->GlblTime;//Ogre::ControllerManager::getSingleton().getElapsedTime();
	int cd = 90 -k;
	sprintf(score, "Human\nUser's\nScore:\n%i", mUserScore);
	sprintf(time, "ElapsedTime:\n%i", k);
	te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("right");
	te->setCaption(score);
	te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("left");
	int v = mWorld->PROJECTILE_SPEED_V;
	int H = mWorld->PROJECTILE_SPEED_H;
    float cubeSpeed = mWorld->SPEED_COEFFICIENT_AI_0;
	if(v!=NULL&&H!=NULL){
		sprintf(score, "%i\n", v);
		//sprintf(score, "Conutdown:\n%i\nHorizontal Velocity: %i \nVertical Velocity: %i\n", cd,H,v);
		sprintf(score,"Countdown: %i\n User score: %i",cd,mWorld->uScore);
        te->setCaption(score);
	}
	else
	{
		sprintf(score, "Conutdown:\n%i\n", cd);
	te->setCaption(score);
	}
	int CD = 95-k;
	if (cd<0){
		if(mWorld->uScore>=4){

			te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("center");
			sprintf(score, "Congrats!!:\n%i", CD);
			te->setCaption(score);

		
		}
		else{
			te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("center");
			sprintf(score, "Game Over:\n%i", CD);
			te->setCaption(score);
			mWorld->go==0;
		}
	}
	
}