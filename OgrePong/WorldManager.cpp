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
	
	if(mLevel>=1)
	{
		pong = mWorld->getpong1();
	RedBrick *AIPlayer = mWorld->getAIPlayer();
	RedBrick *User = mWorld->getUser();
	if (TestpongHitByAIRedBrick_1() || TestpongHitByUserRedBrick_1()) { 
		pong->reverseHorizontalvelocity();
		putpongAtRedBrickEdge();
		pong->setSpeed(pong->getSpeed() + SPEED_INC_STEP);
	    AIPlayer->setSpeed(AIPlayer->getSpeed() + SPEED_INC_STEP);
	    User->setSpeed(User->getSpeed() + SPEED_INC_STEP);
	} 
	if (TestpongCollideWithBorder_1_1() || TestpongCollideWithBorder_4_1()) {
		pong->reverseVerticalvelocity();
		putpongAtBorder_Edge();
	}
	if (TestpongCollideWithBorder_2_1() || TestpongCollideWithBorder_3_1()) {
		pong->reset();
		AIPlayer->reset();
		User->reset();
	}
	}
	if(mLevel>=2)
	{
	pong = mWorld->getpong2();
	RedBrick *AIPlayer = mWorld->getAIPlayer();
	RedBrick *User = mWorld->getUser();
	if (TestpongHitByAIRedBrick_2() || TestpongHitByUserRedBrick_2()) { 
		pong->reverseHorizontalvelocity();
		putpongAtRedBrickEdge();
		pong->setSpeed(pong->getSpeed() + SPEED_INC_STEP);
	    AIPlayer->setSpeed(AIPlayer->getSpeed() + SPEED_INC_STEP);
	    User->setSpeed(User->getSpeed() + SPEED_INC_STEP);
	} 
	if (TestpongCollideWithBorder_1_2() || TestpongCollideWithBorder_4_2()) {
		pong->reverseVerticalvelocity();
		putpongAtBorder_Edge();
	}
	if (TestpongCollideWithBorder_2_2() || TestpongCollideWithBorder_3_2()) {
		pong->reset();
		AIPlayer->reset();
		User->reset();
	}
	}
	if(mLevel>=3)
	{
	pong = mWorld->getpong3();
	RedBrick *AIPlayer = mWorld->getAIPlayer();
	RedBrick *User = mWorld->getUser();
	if (TestpongHitByAIRedBrick_3() || TestpongHitByUserRedBrick_3()) { 
		pong->reverseHorizontalvelocity();
		putpongAtRedBrickEdge();
		pong->setSpeed(pong->getSpeed() + SPEED_INC_STEP);
	    AIPlayer->setSpeed(AIPlayer->getSpeed() + SPEED_INC_STEP);
	    User->setSpeed(User->getSpeed() + SPEED_INC_STEP);
	} 
	if (TestpongCollideWithBorder_1_3() || TestpongCollideWithBorder_4_3()) {
		pong->reverseVerticalvelocity();
		putpongAtBorder_Edge();
	}
	if (TestpongCollideWithBorder_2_3() || TestpongCollideWithBorder_3_3()) {
		pong->reset();
		AIPlayer->reset();
		User->reset();
	}
	}
	if(mLevel>=4)
	{
	pong = mWorld->getpong4();
	RedBrick *AIPlayer = mWorld->getAIPlayer();
	RedBrick *User = mWorld->getUser();
	if (TestpongHitByAIRedBrick_4() || TestpongHitByUserRedBrick_4()) { 
		pong->reverseHorizontalvelocity();
		putpongAtRedBrickEdge();
		pong->setSpeed(pong->getSpeed() + SPEED_INC_STEP);
	    AIPlayer->setSpeed(AIPlayer->getSpeed() + SPEED_INC_STEP);
	    User->setSpeed(User->getSpeed() + SPEED_INC_STEP);
	} 
	if (TestpongCollideWithBorder_1_4() || TestpongCollideWithBorder_4_4()) {
		pong->reverseVerticalvelocity();
		putpongAtBorder_Edge();
	}
	if (TestpongCollideWithBorder_2_4() || TestpongCollideWithBorder_3_4()) {
		pong->reset();
		AIPlayer->reset();
		User->reset();
	}
	}
	if(mLevel>=5)
	{
	pong = mWorld->getpong5();
	RedBrick *AIPlayer = mWorld->getAIPlayer();
	RedBrick *User = mWorld->getUser();
	if (TestpongHitByAIRedBrick_5() || TestpongHitByUserRedBrick_5()) { 
		pong->reverseHorizontalvelocity();
		putpongAtRedBrickEdge();
		pong->setSpeed(pong->getSpeed() + SPEED_INC_STEP);
	    AIPlayer->setSpeed(AIPlayer->getSpeed() + SPEED_INC_STEP);
	    User->setSpeed(User->getSpeed() + SPEED_INC_STEP);
	} 
	if (TestpongCollideWithBorder_1_5() || TestpongCollideWithBorder_4_5()) {
		pong->reverseVerticalvelocity();
		putpongAtBorder_Edge();
	}
	if (TestpongCollideWithBorder_2_5() || TestpongCollideWithBorder_3_5()) {
		pong->reset();
		AIPlayer->reset();
		User->reset();}
	}
	if(mLevel>=6)
	{
	pong = mWorld->getpong6();
	RedBrick *AIPlayer = mWorld->getAIPlayer();
	RedBrick *User = mWorld->getUser();
	if (TestpongHitByAIRedBrick_6() || TestpongHitByUserRedBrick_6()) { 
		pong->reverseHorizontalvelocity();
		putpongAtRedBrickEdge();
		pong->setSpeed(pong->getSpeed() + SPEED_INC_STEP);
	    AIPlayer->setSpeed(AIPlayer->getSpeed() + SPEED_INC_STEP);
	    User->setSpeed(User->getSpeed() + SPEED_INC_STEP);
	} 
	if (TestpongCollideWithBorder_1_6() || TestpongCollideWithBorder_4_6()) {
		pong->reverseVerticalvelocity();
		putpongAtBorder_Edge();
	}
	if (TestpongCollideWithBorder_2_6() || TestpongCollideWithBorder_3_6()) {
		pong->reset();
		AIPlayer->reset();
		User->reset();
	}
	}
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


void WorldManager::putpongAtBorder_Edge() {
	Tank *pong = mWorld->getpong();
	if (pong->atTopArea()) {
		putpongAtBorder_1Edge();
	} else {
		putpongAtBorder_4Edge();
	}
	
	int mLevel = mWorld->getLevel();
	if (pong->atTopArea()) {
		putpongAtBorder_1Edge();
	} else {
		putpongAtBorder_4Edge();
	}
	if(mLevel>=2)
	{
		pong = mWorld->getpong2();
		if (pong->atTopArea()) {
		putpongAtBorder_1Edge();
	} else {
		putpongAtBorder_4Edge();
	}
	}




	if(mLevel>=3)
	{
		pong = mWorld->getpong3();
		if (pong->atTopArea()) {
		putpongAtBorder_1Edge();
	} else {
		putpongAtBorder_4Edge();
	}
	}
	if(mLevel>=4)
	{
		pong = mWorld->getpong4();
		if (pong->atTopArea()) {
		putpongAtBorder_1Edge();
	} else {
		putpongAtBorder_4Edge();
	}
	}
	if(mLevel>=5)
	{
		pong = mWorld->getpong5();
		if (pong->atTopArea()) {
		putpongAtBorder_1Edge();
	} else {
		putpongAtBorder_4Edge();
	}
	}
	if(mLevel>=6)
	{
		pong = mWorld->getpong6();
		if (pong->atTopArea()) {
		putpongAtBorder_1Edge();
	} else {
		putpongAtBorder_4Edge();
	}
	}

	
}

void WorldManager::putpongAtRedBrickEdge() {
	Tank *pong = mWorld->getpong();
	if (pong->atAIArea()) {
		putpongAtAIRedBrickEdge();
	} else {
		putpongAtUserRedBrickEdge();
	}
	
	int mLevel = mWorld->getLevel();
	if(mLevel>=1)
	{
		pong = mWorld->getpong1();
		if (pong->atAIArea()) {
		putpongAtAIRedBrickEdge();
	} else {
		putpongAtUserRedBrickEdge();
	}
	}
	if(mLevel>=2)
	{
		pong = mWorld->getpong2();
		if (pong->atAIArea()) {
		putpongAtAIRedBrickEdge();
	} else {
		putpongAtUserRedBrickEdge();
	}
	}
	if(mLevel>=3)
	{
		pong = mWorld->getpong3();
		if (pong->atAIArea()) {
		putpongAtAIRedBrickEdge();
	} else {
		putpongAtUserRedBrickEdge();
	}
	}
	if(mLevel>=4)
	{
		pong = mWorld->getpong4();
		if (pong->atAIArea()) {
		putpongAtAIRedBrickEdge();
	} else {
		putpongAtUserRedBrickEdge();
	}
	}
	if(mLevel>=5)
	{
		pong = mWorld->getpong5();
		if (pong->atAIArea()) {
		putpongAtAIRedBrickEdge();
	} else {
		putpongAtUserRedBrickEdge();
	}
	}
	if(mLevel>=6)
	{
		pong = mWorld->getpong6();
		if (pong->atAIArea()) {
		putpongAtAIRedBrickEdge();
	} else {
		putpongAtUserRedBrickEdge();
	}
	}

	

}

void WorldManager::updateAIPlayer(slideredbrick velocity) {
	RedBrick *AIPlayer = mWorld->getAIPlayer();
	/*if (velocity == gony && !TestAIPlayerHitBorder_4()) {
		AIPlayer->setvelocity(RedBrick_velocity_neg_y);
	} else if (velocity == gotopy && !TestAIPlayerHitBorder_1()) {
		AIPlayer->setvelocity(RedBrick_velocity_UP);
	} else {
		AIPlayer->stop();
	}*/
}

void WorldManager::updateUser(slideredbrick velocity) {
	RedBrick *User = mWorld->getUser();
	if (velocity == gony && !TestUserHitBorder_4()) {
		User->setvelocity(Ogre::Vector3(0, -1, 0));
	} else if (velocity == gotopy && !TestUserHitBorder_1()) {
		User->setvelocity(Ogre::Vector3(0, 1, 0));
	} else {
		User->stop();
	}
}

void WorldManager::putpongAtBorder_4Edge() {
	Border_ *Border_4 = mWorld->getBorder_4();
	Tank *pong = mWorld->getpong();
	Ogre::Vector3 Border_4Position = Border_4->getPosition();
	Ogre::Vector3 Border_4Dimension = Border_4->getDimension();
	Ogre::Vector3 pongPosition = pong->getPosition();
	Ogre::Vector3 pongDimension = pong->getDimension();
	pongPosition.y = Border_4Position.y + (Border_4Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	
	int mLevel = mWorld->getLevel();
	if(mLevel>=1)
	{
	pong = mWorld->getpong1();	
	pongPosition.y = Border_4Position.y + (Border_4Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
	if(mLevel>=2)
	{
	pong = mWorld->getpong2();	
	pongPosition.y = Border_4Position.y + (Border_4Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=3)
	{
	pong = mWorld->getpong3();	
	pongPosition.y = Border_4Position.y + (Border_4Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=4)
	{
	pong = mWorld->getpong4();	
	pongPosition.y = Border_4Position.y + (Border_4Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=5)
	{
	pong = mWorld->getpong5();	
	pongPosition.y = Border_4Position.y + (Border_4Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=6)
	{
	pong = mWorld->getpong6();	
	pongPosition.y = Border_4Position.y + (Border_4Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}

		
}

void WorldManager::putpongAtBorder_1Edge() {
	Border_ *Border_1 = mWorld->getBorder_1();
	Tank *pong = mWorld->getpong();
	Ogre::Vector3 Border_1Position = Border_1->getPosition();
	Ogre::Vector3 Border_1Dimension = Border_1->getDimension();
	Ogre::Vector3 pongPosition = pong->getPosition();
	Ogre::Vector3 pongDimension = pong->getDimension();
	pongPosition.y = Border_1Position.y - (Border_1Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	
		int mLevel = mWorld->getLevel();
	if(mLevel>=1)
	{
	pong = mWorld->getpong1();	
	pongPosition.y = Border_1Position.y - (Border_1Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
	if(mLevel>=2)
	{
	pong = mWorld->getpong2();	
	pongPosition.y = Border_1Position.y - (Border_1Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=3)
	{
	pong = mWorld->getpong3();	
	pongPosition.y = Border_1Position.y - (Border_1Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=4)
	{
	pong = mWorld->getpong4();	
	pongPosition.y = Border_1Position.y - (Border_1Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=5)
	{
	pong = mWorld->getpong5();	
	pongPosition.y = Border_1Position.y - (Border_1Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=6)
	{
	pong = mWorld->getpong6();	
	pongPosition.y = Border_1Position.y - (Border_1Dimension.y + pongDimension.y)/2;
	pong->setPosition(pongPosition);
	
	}
}

void WorldManager::putpongAtAIRedBrickEdge() {
	RedBrick *AIRedBrick = mWorld->getAIRedBrick();
	Tank *pong = mWorld->getpong();
	Ogre::Vector3 AIRedBrickPosition = AIRedBrick->getPosition();
	Ogre::Vector3 AIRedBrickDimension = AIRedBrick->getDimension();
	Ogre::Vector3 pongPosition = pong->getPosition();
	Ogre::Vector3 pongDimension = pong->getDimension();
	pongPosition.x = AIRedBrickPosition.x + (AIRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	
			int mLevel = mWorld->getLevel();
	if(mLevel>=1)
	{
	pong = mWorld->getpong1();	
	pongPosition.x = AIRedBrickPosition.x + (AIRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
	if(mLevel>=2)
	{
	pong = mWorld->getpong2();	
	pongPosition.x = AIRedBrickPosition.x + (AIRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=3)
	{
	pong = mWorld->getpong3();	
	pongPosition.x = AIRedBrickPosition.x + (AIRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=4)
	{
	pong = mWorld->getpong4();	
	pongPosition.x = AIRedBrickPosition.x + (AIRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=5)
	{
	pong = mWorld->getpong5();	
	pongPosition.x = AIRedBrickPosition.x + (AIRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=6)
	{
	pong = mWorld->getpong6();	
	pongPosition.x = AIRedBrickPosition.x + (AIRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		

}

void WorldManager::putpongAtUserRedBrickEdge() {
	RedBrick *UserRedBrick = mWorld->getUserRedBrick();
	Tank *pong = mWorld->getpong();
	Ogre::Vector3 UserRedBrickPosition = UserRedBrick->getPosition();
	Ogre::Vector3 UserRedBrickDimension = UserRedBrick->getDimension();
	Ogre::Vector3 pongPosition = pong->getPosition();
	Ogre::Vector3 pongDimension = pong->getDimension();
	pongPosition.x = UserRedBrickPosition.x - (UserRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);

	
				int mLevel = mWorld->getLevel();
	if(mLevel>=1)
	{
	pong = mWorld->getpong1();	
	pongPosition.x = UserRedBrickPosition.x - (UserRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
	if(mLevel>=2)
	{
	pong = mWorld->getpong2();	
	pongPosition.x = UserRedBrickPosition.x - (UserRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=3)
	{
	pong = mWorld->getpong3();	
	pongPosition.x = UserRedBrickPosition.x - (UserRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=4)
	{
	pong = mWorld->getpong4();	
	pongPosition.x = UserRedBrickPosition.x - (UserRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=5)
	{
	pong = mWorld->getpong5();	
	pongPosition.x = UserRedBrickPosition.x - (UserRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
		if(mLevel>=6)
	{
	pong = mWorld->getpong6();	
	pongPosition.x = UserRedBrickPosition.x - (UserRedBrickDimension.x + pongDimension.x)/2;
	pong->setPosition(pongPosition);
	}
	

}



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
	mWorld->updateLevel();
	int level = mWorld->getLevel();
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("level");
	char levelCaption[25];
	sprintf(levelCaption, "Level : %i", level);
	//te->setCaption(levelCaption);
}

void WorldManager::updateScore() {
	int mUserScore = mWorld->getUserScore();
	int mAIScore = mWorld->getAIPlayerScore();
	int mLevel=mWorld->getLevel();
	/*
	if (TestpongCollideWithBorder_2()) {
		mWorld->setUserScore(++mUserScore);
	}
	if (TestpongCollideWithBorder_3()) {
		mWorld->setAIPlayerScore(++mAIScore);
	}*/
	/*
	if(mLevel>=1)
	{
		if (TestpongCollideWithBorder_2_1()) {
		mWorld->setUserScore(++mUserScore);
	}
	if (TestpongCollideWithBorder_3_1()) {
		mWorld->setAIPlayerScore(++mAIScore);
	}
	}
	if(mLevel>=2)
		{
		if (TestpongCollideWithBorder_2_2()) {
		mWorld->setUserScore(++mUserScore);
	}
	if (TestpongCollideWithBorder_3_2()) {
		mWorld->setAIPlayerScore(++mAIScore);
	}
	}
	if(mLevel>=3)
		{
		if (TestpongCollideWithBorder_2_3()) {
		mWorld->setUserScore(++mUserScore);
	}
	if (TestpongCollideWithBorder_3_3()) {
		mWorld->setAIPlayerScore(++mAIScore);
	}
	}
	if(mLevel>=4)
		{
		if (TestpongCollideWithBorder_2_4()) {
		mWorld->setUserScore(++mUserScore);
	}
	if (TestpongCollideWithBorder_3_4()) {
		mWorld->setAIPlayerScore(++mAIScore);
	}
	}
	if(mLevel>=5)
		{
		if (TestpongCollideWithBorder_2_5()) {
		mWorld->setUserScore(++mUserScore);
	}
	if (TestpongCollideWithBorder_3_5()) {
		mWorld->setAIPlayerScore(++mAIScore);
	}
	}
	if(mLevel>=6)
	{
	if (TestpongCollideWithBorder_2_6()) {
		mWorld->setUserScore(++mUserScore);
	}
	if (TestpongCollideWithBorder_3_6()) {
		mWorld->setAIPlayerScore(++mAIScore);
	}
	}
	*/

	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("left");
	char score[500];
	//char time[25];
	//sprintf(score, "AI\nPlayer's\nScore:\n%i", mAIScore);
	//te->setCaption(score);
	int k =Ogre::ControllerManager::getSingleton().getElapsedTime();
	int cd = 180 -k;
	sprintf(score, "Human\nUser's\nScore:\n%i", mUserScore);
	//sprintf(time, "ElapsedTime:\n%i", k);
	te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("right");
	te->setCaption(score);
	te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("left");
	int v = mWorld->PROJECTILE_SPEED_V;
	int H = mWorld->PROJECTILE_SPEED_H;
    float cubeSpeed = mWorld->SPEED_COEFFICIENT;
	if(v!=NULL&&H!=NULL){
		//sprintf(score, "%i\n", v);
		//sprintf(score, "Conutdown:\n%i\nHorizontal Velocity: %i \nVertical Velocity: %i\n", cd,H,v);
		sprintf(score,"Countdown: %i\n Cube Speed: %f",cd,cubeSpeed);
        te->setCaption(score);
	}
	else
	{
		sprintf(score, "Conutdown:\n%i\n", cd);
	te->setCaption(score);
	}
	int CD = 185-k;
	if (cd<0){
		if(mUserScore>=59){
			te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("center");
			sprintf(score, "Congrats!!\nAll enemies were destroyed!:\n%i", CD);
			te->setCaption(score);
		}
		else if(mUserScore<20&&mUserScore>10){
			te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("center");
			sprintf(score, "Congrats!\n10 enemy tanks\n were destroyed!:\n%i", CD);
			te->setCaption(score);
		}
		else{
			te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("center");
			sprintf(score, "Game Over:\n%i", CD);
			te->setCaption(score);
		}
	}
	
}