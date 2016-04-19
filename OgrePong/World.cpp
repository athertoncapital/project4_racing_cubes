// My header file.  This should go first!
#include "World.h"
#include "Properties.h"
// Ogre header files
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreVector3.h"
#include "PongObject.h"
#include "MovingObject.h"

// IOS (Input system) header files

#include <ois/ois.h>

// Other input files for my project
#include "Camera.h"
#include "InputHandler.h"
#include "border.h"

#include "OgreColourValue.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "RedBrick.h"
#include "slideredbrick.h"
#include "AIManager.h"
#include "PongManager.h"
#include "WorldManager.h"
#include <vector>


World::World(Ogre::SceneManager *sceneManager, InputHandler *input, Tank *tank)   : mSceneManager(sceneManager), mInputHandler(input), mTank(tank)
{
	Switch = 0;
	PROJECTILE_SPEED_V=100;
	PROJECTILE_SPEED_H=100;
	mScore = 0;
	mWorldManager = new WorldManager(this);
	//mAIScore = 0;
	//mUserScore = 0;
	initialStates();
	




	mUser = mUserRedBrick;
	mAIPlayer = mAIRedBrick;
	
	//mOverlay = Ogre::OverlayManager::getSingleton().getByName("Score");
	//mOverlay->show();
	mBorder_4 = new Border_(mSceneManager, Borde_dim_0);
	mBorder_4->load();
	/*mBorder_4->setScene();
	mBorder_4->setScale(HORIZONTAL_Border__0_SCALE);
	mBorder_4->setPosition(BOTTOM_Border__0_POSITION);*/

	mBorder_1 = new Border_(mSceneManager, Borde_dim_0);
	mBorder_1->load();
	/*mBorder_1->setScene();
	mBorder_1->setScale(HORIZONTAL_Border__0_SCALE);
	mBorder_1->setPosition(Border__0_POSITION1);*/

	mBorder_3 = new Border_(mSceneManager, Borde_dim_0);
	mBorder_3->load();
	/*mBorder_3->setScene();
	mBorder_3->setScale(scaleOfyBorder);
	mBorder_3->setPosition(Border__0_POSITION3);*/

	mBorder_2 = new Border_(mSceneManager, Borde_dim_0);
	mBorder_2->load();
	/*mBorder_2->setScene();
	mBorder_2->setScale(scaleOfyBorder);
	mBorder_2->setPosition(Border__0_POSITION2);*/
	//Ogre::FontManager::getSingleton().getByName("BlueHighwayBig")->load();
	mSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));
	
	//mUserRedBrick->load();
	mUserRedBrick = new RedBrick(mSceneManager, RB_DIM_0);
	mUserRedBrick->load();
	/*mUserRedBrick->setScene();
	mUserRedBrick->setScale(RedBrick_0_SCALE);
	mUserRedBrick->setPosition(User_RedBrick_0_POSITION);
	mUser = mUserRedBrick;*/

	mAIRedBrick = new RedBrick(mSceneManager, RB_DIM_0);
	mAIRedBrick->load();
	/*mAIRedBrick->setScene();
	mAIRedBrick->setScale(RedBrick_0_SCALE);
	mAIRedBrick->setPosition(AI_RedBrick_0_POSITION);
	mAIPlayer = mAIRedBrick;*/

	//mpong = new Tank(mSceneManager, this, pong_0_DIMENSION);
	//mpong->load();
	//mpong->setScene();
	//mpong->setScale(pong_0_SCALE);
	//mpong->setPosition(pong_0_POSITION);
	createOverlay();

	tanks = new LinkedList();
	tanks->head = NULL;

	/* Initialize positions for an AI tank */
	spawnPoints = new Ogre::Vector3[50];
	spawnPoints[0] = Ogre::Vector3(900, 0, 10);
	spawnPoints[1] = Ogre::Vector3(700, 0, 200);
	spawnPoints[2] = Ogre::Vector3(510, 0, 400);
	spawnPoints[3] = Ogre::Vector3(3343, 0, 6540);
	spawnPoints[4] = Ogre::Vector3(42450, 0, 5550);
	spawnPoints[5] = Ogre::Vector3(5234, 0, 4560);
	spawnPoints[6] = Ogre::Vector3(6345, 0, 3570);
	spawnPoints[7] = Ogre::Vector3(7765, 0, 2580);
	spawnPoints[8] = Ogre::Vector3(8450, 0, 1590);
	spawnPoints[9] = Ogre::Vector3(93870, 0, 90);

	spawnPoints[10] = Ogre::Vector3(-120, 1230, 9500);
	spawnPoints[11] = Ogre::Vector3(-1243, 3210, 8500);
	spawnPoints[12] = Ogre::Vector3(-234, 2340, 7500);
	spawnPoints[13] = Ogre::Vector3(-30, 5340, 6500);
	spawnPoints[14] = Ogre::Vector3(-500, 6450, 5520);
	spawnPoints[15] = Ogre::Vector3(-300, 0, 4530);
	spawnPoints[16] = Ogre::Vector3(-300, 2430, 3540);
	spawnPoints[17] = Ogre::Vector3(-2300, 8670, 2500);
	spawnPoints[18] = Ogre::Vector3(-1300, 340, 1560);
	spawnPoints[19] = Ogre::Vector3(-800, 4320, 570);

	spawnPoints[20] = Ogre::Vector3(-1300, 10, 9100);
	spawnPoints[21] = Ogre::Vector3(-2300, 20, 8200);
	spawnPoints[22] = Ogre::Vector3(-3300, 30, 7300);
	spawnPoints[23] = Ogre::Vector3(-4300, 40, 6400);
	spawnPoints[24] = Ogre::Vector3(-5300, 50, 5500);
	spawnPoints[25] = Ogre::Vector3(-6300, 60, 4600);
	spawnPoints[26] = Ogre::Vector3(-7300, 70, 3700);
	spawnPoints[27] = Ogre::Vector3(-8300, 80, 2800);
	spawnPoints[28] = Ogre::Vector3(-9300, 90, 900);
	spawnPoints[29] = Ogre::Vector3(-10300, 100, 1000);

	spawnPoints[30] = Ogre::Vector3(1300, 80, -500);
	spawnPoints[31] = Ogre::Vector3(2300, 70, -1500);
	spawnPoints[32] = Ogre::Vector3(3300, 4, -1000);
	spawnPoints[33] = Ogre::Vector3(4300, 30, -5000);
	spawnPoints[34] = Ogre::Vector3(5300, 50, -520);
	spawnPoints[35] = Ogre::Vector3(6300, 2, -530);
	spawnPoints[36] = Ogre::Vector3(7300, 20, -540);
	spawnPoints[37] = Ogre::Vector3(8300, 40, -550);
	spawnPoints[38] = Ogre::Vector3(9300, 0, -560);
	spawnPoints[39] = Ogre::Vector3(10300, 0, -570);

	spawnPoints[40] = Ogre::Vector3(300, -10, 9500);
	spawnPoints[41] = Ogre::Vector3(4300, -205, 8500);
	spawnPoints[42] = Ogre::Vector3(350, -303, 7500);
	spawnPoints[43] = Ogre::Vector3(7340, -440, 6100);
	spawnPoints[44] = Ogre::Vector3(5330, -530, 2500);
	spawnPoints[45] = Ogre::Vector3(3320, -650, 4300);
	spawnPoints[46] = Ogre::Vector3(4310, -720, 3400);
	spawnPoints[47] = Ogre::Vector3(6390, -860, 2500);
	spawnPoints[48] = Ogre::Vector3(1200, -940, 1600);
	spawnPoints[49] = Ogre::Vector3(1900, -100, 700);
	start = time(NULL);


	 
	
}
//flying_or_diving
void
World::fly_or_dive_Tank(InputHandler *mInputHandler, const Ogre::Real& mTime)
{
	const float RADIANS_PER_SECOND = 1;
	if (mInputHandler->IsKeyDown(OIS::KC_W)) 
		mTank->mMainNode->translate(Ogre::Vector3(0,10,0)*mTime*10);
	else mTank->mMainNode->translate(Ogre::Vector3(0,-10,0)*mTime*10);
}
//Rotating
void
World::yawTank(InputHandler *mInputHandler, const Ogre::Real& mTime)
{
	const float RADIANS_PER_SECOND = 1;
	if (mInputHandler->IsKeyDown(OIS::KC_LEFT)) 
		mTank->mMainNode->yaw(Ogre::Radian(mTime * RADIANS_PER_SECOND));
	else mTank->mMainNode->yaw(-Ogre::Radian(mTime * RADIANS_PER_SECOND));
}
void
World::setIterator() 
{
	iterator = tanks->head;
}
void
World::Push(Tank::Node *node)
{
	node->next = tanks->head;
	tanks->head = node;
}
//void World::Think(float mTime)

void World::Think(const Ogre::Real& mTime)
{
	/*mObj1->yaw(Ogre::Radian(0.5f * mTime));
    mObj2->pitch(Ogre::Radian(0.6f * mTime));
    mObj3->roll(Ogre::Radian(0.5f * mTime));
	mObj4->translate(mTime * Ogre::Vector3(-1, 0,0));
	*/

	mWorldManager->doWork();
	t=mTime;


	int k =Ogre::ControllerManager::getSingleton().getElapsedTime();
	int cd = 5-k;
	if (cd<5){
		Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	     mGameOverOverlay = om.getByName("GameOver");
		 mGameOverOverlay->show();
	}


	//mpong->move(mTime);
	const float TANK_SPEED = 50;
	end = time(NULL);
	diff = end - start;
	/* Checkthe condition in each second */
	if (diff > 1) {
		setIterator();
		while (iterator != NULL)
		{
			if (iterator->destroyed)
				start = time(NULL);
			iterator = iterator->next;
		}
		setIterator();
	}
	if (mInputHandler->IsKeyDown(OIS::KC_LEFT) || mInputHandler->IsKeyDown(OIS::KC_RIGHT))
		yawTank(mInputHandler, mTime);
	else if (mInputHandler->IsKeyDown(OIS::KC_W))
	{
		fly_or_dive_Tank(mInputHandler, mTime);
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_S))
	{
		fly_or_dive_Tank(mInputHandler, mTime);
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_UP))
	{
		if (iterator != NULL && iterator->eAABB != NULL)
		{
			if (!mTank->mAABB->intersects(*iterator->eAABB)&&!mTank->mAABB->intersects(*mTank->mo2ABB))
			{
				mTank->mMainNode->translate(0, 0, mTime * TANK_SPEED *20, Ogre::Node::TS_LOCAL);
				iterator = iterator->next;
			}
			
			else mTank->mMainNode->translate(0, 0, -mTime * 500 * TANK_SPEED, Ogre::Node::TS_LOCAL);
		}
		
		else setIterator();
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
	{
		if (iterator != NULL && iterator->eAABB != NULL)
		{
			if (!mTank->mAABB->intersects(*iterator->eAABB))
			{
				mTank->mMainNode->translate(0, 0, -mTime*20 * TANK_SPEED, Ogre::Node::TS_LOCAL);
				iterator = iterator->next;
			}
			else mTank->mMainNode->translate(0, 0, mTime * 100 * TANK_SPEED, Ogre::Node::TS_LOCAL);
		}
		else setIterator();
	}





}

World::~World() {
	delete mBorder_2;
	delete mBorder_3;
	delete mBorder_1;
	delete mBorder_4;

	delete mAIRedBrick;
	delete mUserRedBrick;
	delete mWorldManager;



}


void World::updateLevel() {
	if(!flag()){/*
	if (mAIScore == 3)
	{
		mLevel--;
		    mAIScore = 0;
		    mUserScore = 0;
			Ogre::Vector3 newScale = mUserRedBrick->getScale() - RedBrick_SCALE_DEC_STEP;
			if (newScale.y > RedBrick_MIN_SCALE.y) {
			    mUserRedBrick->setScale(mUserRedBrick->getScale() - RedBrick_SCALE_DEC_STEP);
			}
	}
	else if ( mUserScore == 3) {
			mLevel++;
		    mAIScore = 0;
		    mUserScore = 0;
			Ogre::Vector3 newScale = mUserRedBrick->getScale() - RedBrick_SCALE_DEC_STEP;
			if (newScale.y > RedBrick_MIN_SCALE.y) {
			    mUserRedBrick->setScale(mUserRedBrick->getScale() - RedBrick_SCALE_DEC_STEP);
				if(mLevel==1)
				{

					mpong1 = new Tank(mSceneManager, this, pong_0_DIMENSION);
					mpong1->load();
					mpong1->setScene();
					mpong1->setScale(pong_0_SCALE);
					mpong1->setPosition(pong_0_POSITION);
				}
				else if(mLevel==2)
				{
					mpong2 = new Tank(mSceneManager, this, pong_0_DIMENSION);
					mpong2->load();
					mpong2->setScene();
					mpong2->setScale(pong_0_SCALE);
					mpong2->setPosition(pong_0_POSITION);
				}
				else if(mLevel==3)
				{
					mpong3 = new Tank(mSceneManager, this, pong_0_DIMENSION);
					mpong3->load();
					mpong3->setScene();
					mpong3->setScale(pong_0_SCALE);
					mpong3->setPosition(pong_0_POSITION);
				}
				else if(mLevel==4)
				{
					mpong4 = new Tank(mSceneManager, this, pong_0_DIMENSION);
					mpong4->load();
					mpong4->setScene();
					mpong4->setScale(pong_0_SCALE);
					mpong4->setPosition(pong_0_POSITION);
				}
				else if(mLevel==5)
				{
					mpong5 = new Tank(mSceneManager, this, pong_0_DIMENSION);
					mpong5->load();
					mpong5->setScene();
					mpong5->setScale(pong_0_SCALE);
					mpong5->setPosition(pong_0_POSITION);
				}
				else if(mLevel==6)
				{
					mpong6 = new Tank(mSceneManager, this, pong_0_DIMENSION);
					mpong6->load();
					mpong6->setScene();
					mpong6->setScale(pong_0_SCALE);
					mpong6->setPosition(pong_0_POSITION);
				}
				} 
			}*/
	}


}
bool World::flag() {
    return mLevel <-7;
}


void World::createOverlay() {
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	mOverlay = om.getByName("Score");
	//mOverlay = om.getByName("Horizontal_Initial_Value");
	mOverlay->show();
}

void World::getEventFrom(PongManager *pongManager) {
	mWorldManager->getEvent(pongManager);
}

void World::initialStates() {
	mAIScore = 0;

	mLevel = 0;
	mUserScore = 0;
	mUser = mUserRedBrick;
	mAIPlayer = mAIRedBrick;
}