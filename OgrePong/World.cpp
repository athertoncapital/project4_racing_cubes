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
#include <math.h> 


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

	U_u = 0.0f;
	U_v = 0.0f;
	AI_0_u = 0.0f;
	AI_0_v = 0.333f; //setting number that was on AITank
	AI_1_u = 0.0f;
	AI_1_v = 0.010f;
	AI_2_u = 0.0f;
	AI_2_v = 0.0f;
    SPEED_COEFFICIENT = 10.0;
    SPEED_COEFFICIENT_AI_0 = 10.0;
    SPEED_COEFFICIENT_AI_1 = 10.0;
    SPEED_COEFFICIENT_AI_2 = 10.0;

	 
	
	
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
Ogre::Vector3 World::Normal(float u, float v){
	float kappa = 1;
	
	float A=kappa*(-sin(u)+ v*((-1/2)*sin(u/2)*cos(u)-cos(u/2)*sin(u)));
	float B=kappa*(cos(u)+ v*((-1/2)*sin(u/2)*sin(u)+cos(u/2)*cos(u)));
	float C=kappa*((v/2)*cos(u/2));
	float D=kappa*(cos(u/2)*cos(u));
	float E=kappa*(cos(u/2)*sin(u));
	float F=kappa*(sin(u/2));

	float N_x = B*F-C*E;
	float N_y = C*D-A*F;
	float N_z = A*E-B*D;
	Ogre::Vector3 N = Ogre::Vector3(N_x,N_y,N_z);
	return N;
}
Ogre::Vector3 World::Tangent(float u, float v){
	float kappa = 1;
	
	float A=kappa*(-sin(u)+ v*((-1/2)*sin(u/2)*cos(u)-cos(u/2)*sin(u)));
	float B=kappa*(cos(u)+ v*((-1/2)*sin(u/2)*sin(u)+cos(u/2)*cos(u)));
	float C=kappa*((v/2)*cos(u/2));
	Ogre::Vector3 T = Ogre::Vector3(A,B,C);
	return T;
}
Ogre::Vector3 World::Binormal(float u, float v){
	float kappa = 1;
	
	float D=kappa*(cos(u/2)*cos(u));
	float E=kappa*(cos(u/2)*sin(u));
	float F=kappa*(sin(u/2));
	Ogre::Vector3 B = Ogre::Vector3(D,E,F);
	return B;
}
Ogre::Matrix3 World::Orientation(Ogre::Vector3 xBasis, Ogre::Vector3 yBasis, Ogre::Vector3 zBasis){
    Ogre::Matrix3 rotate;
    rotate.FromAxes(xBasis, yBasis, zBasis);
	return rotate;
}

void World::Think(const Ogre::Real& mTime)
{
	Ogre::Vector3 position = mTank->mMainNode->getPosition();
	float u = 2*asin(position.z/1000);
	Ogre::Vector3 N;
    float ftime =Ogre::ControllerManager::getSingleton().getElapsedTime();
    u=ftime;
	U_u=-ftime/SPEED_COEFFICIENT;// ORIGINALLY -ftime/10
    AI_0_u=-ftime/SPEED_COEFFICIENT_AI_0;// ORIGINALLY -ftime/10
    AI_1_u=-ftime/SPEED_COEFFICIENT_AI_1;// ORIGINALLY -ftime/10

	float u1 = u+U_u;
    float u2 = u+AI_0_u;
    float u3 = u+AI_1_u;
    //For Debug use:
    //"AItank0" will make User cube Designer

	mTank->SceneManager()->getSceneNode("AItank0")->setPosition(1000*cos(u1)+1000*cos(u1/2)*cos(u1)*(U_v),1000*sin(u1)+1000*cos(u1/2)*sin(u1)*(U_v),1000*sin(u1/2)*(U_v));
	mTank->SceneManager()->getSceneNode("AItank0")->translate(Normal(u1, U_v)*10);
	//mTank->SceneManager()->getSceneNode("U")->translate(Binormal(u1, U_v)*U_v);
	mTank->SceneManager()->getSceneNode("AItank0")->setOrientation(Orientation(Binormal(u1, U_v),Normal(u1, U_v),Tangent(u1,U_v)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank0")->setPosition(1000*cos(u2)+1000*cos(u2/2)*cos(u2)*(AI_0_v),1000*sin(u2)+1000*cos(u2/2)*sin(u2)*(AI_0_v),1000*sin(u2/2)*(AI_0_v));
	mTank->SceneManager()->getSceneNode("AItank0")->translate(Normal(u2, AI_0_v)*11);
	mTank->SceneManager()->getSceneNode("AItank0")->setOrientation(Orientation(Binormal(u2, AI_0_v),Normal(u2, AI_0_v),Tangent(u2,AI_0_v)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank2")->setPosition(1000*cos(u3)+1000*cos(u3/2)*cos(u3)*(AI_1_v),1000*sin(u3)+1000*cos(u3/2)*sin(u3)*(AI_1_v),1000*sin(u3/2)*(AI_1_v));
	mTank->SceneManager()->getSceneNode("AItank2")->translate(Normal(u3, AI_1_v)*11);
	mTank->SceneManager()->getSceneNode("AItank2")->setOrientation(Orientation(Binormal(u3, AI_1_v),Normal(u3, AI_1_v),Tangent(u3,AI_1_v)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank3")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/-100),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/-100),1000*sin(u/2)*(1/-100));
	mTank->SceneManager()->getSceneNode("AItank3")->translate(Normal(u, 1/-100)*11);
	mTank->SceneManager()->getSceneNode("AItank3")->setOrientation(Orientation(Binormal(u, 1/-100),Normal(u, 1/-100),Tangent(u,1/-100)));
	u+=5;


	mTank->SceneManager()->getSceneNode("AItank4")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(-0.6),1000*sin(u)+1000*cos(u/2)*sin(u)*(-0.6),1000*sin(u/2)*(-0.6));
	mTank->SceneManager()->getSceneNode("AItank4")->translate(Normal(u, -0.6)*11);
	mTank->SceneManager()->getSceneNode("AItank4")->setOrientation(Orientation(Binormal(u, -0.6),Normal(u, -0.6),Tangent(u,-0.6)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank5")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(-0.8),1000*sin(u)+1000*cos(u/2)*sin(u)*(-0.8),1000*sin(u/2)*(-0.8));
	mTank->SceneManager()->getSceneNode("AItank5")->translate(Normal(u, -0.8)*11);
	mTank->SceneManager()->getSceneNode("AItank5")->setOrientation(Orientation(Binormal(u, 1/7),Normal(u, -0.8),Tangent(u,-0.8)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank6")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(0.8),1000*sin(u)+1000*cos(u/2)*sin(u)*(0.8),1000*sin(u/2)*(0.8));
	mTank->SceneManager()->getSceneNode("AItank6")->translate(Normal(u, 0.8)*11);
	mTank->SceneManager()->getSceneNode("AItank6")->setOrientation(Orientation(Binormal(u, 0.8),Normal(u, 0.8),Tangent(u,0.8)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank7")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1),1000*sin(u)+1000*cos(u/2)*sin(u)*(1),1000*sin(u/2)*(1));
	mTank->SceneManager()->getSceneNode("AItank7")->translate(Normal(u, 1)*11);
	mTank->SceneManager()->getSceneNode("AItank7")->setOrientation(Orientation(Binormal(u, 1),Normal(u, 1),Tangent(u,1)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank8")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(0),1000*sin(u)+1000*cos(u/2)*sin(u)*(0),1000*sin(u/2)*(0));
	mTank->SceneManager()->getSceneNode("AItank8")->translate(Normal(u, 0)*11);
	mTank->SceneManager()->getSceneNode("AItank8")->setOrientation(Orientation(Binormal(u, 0),Normal(u, 0),Tangent(u,0)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank9")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(-1),1000*sin(u)+1000*cos(u/2)*sin(u)*(-1),1000*sin(u/2)*(-1));
	mTank->SceneManager()->getSceneNode("AItank9")->translate(Normal(u, -1)*11);
	mTank->SceneManager()->getSceneNode("AItank9")->setOrientation(Orientation(Binormal(u, -1),Normal(u, -1),Tangent(u,-1)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank10")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1),1000*sin(u)+1000*cos(u/2)*sin(u)*(1),1000*sin(u/2)*(1));
	mTank->SceneManager()->getSceneNode("AItank10")->translate(Normal(u, 1)*11);
	mTank->SceneManager()->getSceneNode("AItank10")->setOrientation(Orientation(Binormal(u, 1),Normal(u, 1),Tangent(u,1)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank11")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1),1000*sin(u)+1000*cos(u/2)*sin(u)*(1),1000*sin(u/2)*(1));
	mTank->SceneManager()->getSceneNode("AItank11")->translate(Normal(u, 1)*11);
	mTank->SceneManager()->getSceneNode("AItank11")->setOrientation(Orientation(Binormal(u, 1),Normal(u, 1),Tangent(u,1)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank12")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/14),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/14),1000*sin(u/2)*(1/14));
	mTank->SceneManager()->getSceneNode("AItank12")->translate(Normal(u, 1/14)*11);
	mTank->SceneManager()->getSceneNode("AItank12")->setOrientation(Orientation(Binormal(u, 1/14),Normal(u, 1/14),Tangent(u,1/14)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank13")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/15),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/15),1000*sin(u/2)*(1/15));
	mTank->SceneManager()->getSceneNode("AItank13")->translate(Normal(u, 1/15)*11);
	mTank->SceneManager()->getSceneNode("AItank13")->setOrientation(Orientation(Binormal(u, 1/15),Normal(u, 1/15),Tangent(u,1/15)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank14")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/16),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/16),1000*sin(u/2)*(1/16));
	mTank->SceneManager()->getSceneNode("AItank14")->translate(Normal(u, 1/16)*11);
	mTank->SceneManager()->getSceneNode("AItank14")->setOrientation(Orientation(Binormal(u, 1/16),Normal(u, 1/16),Tangent(u,1/16)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank15")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/17),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/17),1000*sin(u/2)*(1/17));
	mTank->SceneManager()->getSceneNode("AItank15")->translate(Normal(u, 1/17)*11);
	mTank->SceneManager()->getSceneNode("AItank15")->setOrientation(Orientation(Binormal(u, 1/17),Normal(u, 1/17),Tangent(u,1/17)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank16")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/18),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/18),1000*sin(u/2)*(1/18));
	mTank->SceneManager()->getSceneNode("AItank16")->translate(Normal(u, 1/18)*11);
	mTank->SceneManager()->getSceneNode("AItank16")->setOrientation(Orientation(Binormal(u, 1/18),Normal(u, 1/18),Tangent(u,1/18)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank17")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/19),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/19),1000*sin(u/2)*(1/19));
	mTank->SceneManager()->getSceneNode("AItank17")->translate(Normal(u, 1/19)*11);
	mTank->SceneManager()->getSceneNode("AItank17")->setOrientation(Orientation(Binormal(u, 1/19),Normal(u, 1/19),Tangent(u,1/19)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank18")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/20),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/20),1000*sin(u/2)*(1/20));
	mTank->SceneManager()->getSceneNode("AItank18")->translate(Normal(u, 1/20)*11);
	mTank->SceneManager()->getSceneNode("AItank18")->setOrientation(Orientation(Binormal(u, 1/20),Normal(u, 1/20),Tangent(u,1/20)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank19")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(-1/2),1000*sin(u)+1000*cos(u/2)*sin(u)*(-1/2),1000*sin(u/2)*(-1/2));
	mTank->SceneManager()->getSceneNode("AItank19")->translate(Normal(u, -1/2)*11);
	mTank->SceneManager()->getSceneNode("AItank19")->setOrientation(Orientation(Binormal(u, -1/2),Normal(u, -1/2),Tangent(u,-1/2)));
	u+=5;
	mTank->SceneManager()->getSceneNode("AItank20")->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(-1/3),1000*sin(u)+1000*cos(u/2)*sin(u)*(-1/3),1000*sin(u/2)*(-1/3));
	mTank->SceneManager()->getSceneNode("AItank20")->translate(Normal(u, -1/3)*11);
	mTank->SceneManager()->getSceneNode("AItank20")->setOrientation(Orientation(Binormal(u, -1/3),Normal(u, -1/3),Tangent(u,-1/3)));


	/*mObj1->yaw(Ogre::Radian(0.5f * mTime));
    mObj2->pitch(Ogre::Radian(0.6f * mTime));
    mObj3->roll(Ogre::Radian(0.5f * mTime));
	mObj4->translate(mTime * Ogre::Vector3(-1, 0,0));
	*/

	mWorldManager->doWork();
	t=mTime;


	int k =Ogre::ControllerManager::getSingleton().getElapsedTime();
	int cd = 185-k;
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
    //LEFT,RIGHT,UP,DOWN MOVE DESIGNER MODE CUBE
	if (mInputHandler->IsKeyDown(OIS::KC_LEFT) || mInputHandler->IsKeyDown(OIS::KC_RIGHT))
    {
		yawTank(mInputHandler, mTime);
    }
    else if (mInputHandler->IsKeyDown(OIS::KC_UP))
	{
		if (iterator != NULL && iterator->eAABB != NULL)
		{
			if (!mTank->mAABB->intersects(*iterator->eAABB)&&!mTank->mAABB->intersects(*mTank->mo2ABB))
			{
				mTank->mMainNode->translate(0, 0, mTime * TANK_SPEED *20, Ogre::Node::TS_LOCAL);
				iterator = iterator->next;
				
				/*float u = 2*asin(position.z/1000);
				int inttime =Ogre::ControllerManager::getSingleton().getElapsedTime();
				u=inttime;
				mTank->mMainNode->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(1/2),1000*sin(u)+1000*cos(u/2)*sin(u)*(1/2),1000*sin(u/2)*(1/2));
				*/
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
	else if (mInputHandler->IsKeyDown(OIS::KC_Z))
	{
		fly_or_dive_Tank(mInputHandler, mTime);
                recordMove();

	}
	else if (mInputHandler->IsKeyDown(OIS::KC_X))
	{
		fly_or_dive_Tank(mInputHandler, -mTime);
	}


    //J,L,I,K Move cube 1
	else if (mInputHandler->IsKeyDown(OIS::KC_J))
	{
		if(U_v<0.5){
			U_v+=0.01f;
		}
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_L))
	{
		if(U_v>-0.5){
			U_v-=0.01f;
		}
	}
		else if (mInputHandler->IsKeyDown(OIS::KC_I))
	{
			//U_u+=0.01f;
        if (SPEED_COEFFICIENT < 20) {
            SPEED_COEFFICIENT += 0.5f;

        }
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_K))
	{

			//U_u-=0.01f;
        //if (SPEED_COEFFICIENT <= 1.0 && SPEED_COEFFICIENT > 0) {
        //    SPEED_COEFFICIENT -= 0.1f;
        //}
        if (SPEED_COEFFICIENT > 1.0) {
            SPEED_COEFFICIENT -= 0.5f;
        }

	}


        //T,G,F,H Move cube 2
	else if (mInputHandler->IsKeyDown(OIS::KC_F))
	{
		if(AI_0_v<0.5){
			AI_0_v+=0.01f;
		}
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_H))
	{
		if(AI_0_v>-0.5){
			AI_0_v-=0.01f;
		}
	}
		else if (mInputHandler->IsKeyDown(OIS::KC_T))
	{
			//U_u+=0.01f;
        if (SPEED_COEFFICIENT_AI_0 < 20) {
            SPEED_COEFFICIENT_AI_0 += 0.5f;

        }
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_G))
	{

			//U_u-=0.01f;
        if (SPEED_COEFFICIENT_AI_0 > 1.0) {
            SPEED_COEFFICIENT_AI_0 -= 0.5f;
        }

	}

            //W,A,S,D Move cube 3
	else if (mInputHandler->IsKeyDown(OIS::KC_A))
	{
		if(AI_1_v<0.5){
			AI_1_v+=0.01f;
		}
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_D))
	{
		if(AI_1_v>-0.5){
			AI_1_v-=0.01f;
		}
	}
		else if (mInputHandler->IsKeyDown(OIS::KC_W))
	{
			//U_u+=0.01f;
        if (SPEED_COEFFICIENT_AI_1 < 20) {
            SPEED_COEFFICIENT_AI_1 += 0.5f;

        }
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_S))
	{

			//U_u-=0.01f;
        if (SPEED_COEFFICIENT_AI_1 > 1.0) {
            SPEED_COEFFICIENT_AI_1 -= 0.5f;
        }

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
	if(!flag()){
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

void World::recordMove() {
    string readID = "moves";
	string exd = ".txt";
	string readResult;          // string which will contain the result  
	ostringstream readconvert;
	//readconvert << k;      // insert the textual representation of 'Number' in the characters in the stream
	//readResult = readconvert.str(); // set 'Result' to the contents of the stream
	//readID.append(readResult);
	readID.append(exd);

    ofstream outtxt( readID, std::ios_base::app | std::ios_base::out );

    outtxt << "Hello World!ed";
    outtxt << endl; //End of Line

    outtxt.close();
}