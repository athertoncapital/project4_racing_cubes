#include "Tank.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "World.h"
#include "PongObject.h"
#include "MotionObject.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "Properties.h"
#include "OgreVector3.h"
#include "Ogre.h"
#include "OgreAxisAlignedBox.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "SdkSample.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h> 
#include "wingdi.h"
#include <Windows.h>
#include <sstream>
#include <fstream>      // std::ifstream, std::ofstream
#include "tensorflow.h"
#include <vector>

 #define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}


int id=0;
string ID = "AItank";


Tank::Tank(Ogre::SceneManager *sceneManager, World *world, Ogre::Vector3 dimension) :  MotionObject(sceneManager, dimension, 
																				   pong_0_SPEED, pong_MOVE_User_BOTTOM), mSceneManager(sceneManager), mWorld(world)
{

    //Initializing MovingObject Array
    setMovObjs();
    setStatObjs();

    //Sets space background on all the 3d space
    createBackground();
    
    
    //-----------------------------------------------
	//mMainNode = SceneManager()->getRootSceneNode()->createChildSceneNode("U");
	//mSpin = 1000;
	//mWorld->SceneManager()->getSceneNode("U")->setPosition(100,100,100);
	//Ogre::Vector3 vUser=mWorld->SceneManager()->getSceneNode("U")->getPosition();


    Node *node = new Node();
	Ogre::SceneNode *eTankNode = NULL;
	Ogre::Entity *tank = NULL;

    /* Create user tank */
	createUserTank();

    //////////////////////////////////////////////////////////////////////////
    //////////////  START OF NODE OBJECTS ////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

    createAICubes();


	//////////////////////////////////////////////////////////////////////////
    //////////////  START OF STATIC OBJECTS //////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	createStaticObjects2(node,tank,eTankNode); //Testing staticobject2 func

    //////////////////////////////////////////////////////////////////////////
    //////////////  START OF MOVING OBJECTS //////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

    node = new Node();
	mObj1 = new MovingObject(mSceneManager,"movObject1", "coin.mesh", NULL);
	mObj1->setPosition(mWorld->spawnPoints[1]);

	node->eTankNode = mObj1->mObjectSceneNode;
    node->obb = mObj1->getOBB();
	mWorld->Push(node);

    //movObjs.assign(movObjs.begin(), mObj1);
    movObjs[1] = mObj1;

    mMovingObjects[std::string("movObject1")] = mObj1;
    //node->obb = createOBB(node,entity,scene);

	mObj2 = new MovingObject(mSceneManager,"movObject2", "MyCube.mesh", mObj1);
    mObj3 = new MovingObject(mSceneManager,"movObject3", "MyCube.mesh", mObj2);
	mObj4 = new MovingObject(mSceneManager,"movObject4", "MyCube.mesh", NULL);
	mObj5 = new MovingObject(mSceneManager,"movObject5", "XYZ_Function.mesh", NULL);

    mSunObj = new MovingObject(mSceneManager,"movSun","Icosphere.mesh",NULL);
    mSunObj->setPosition(Ogre::Vector3(1500, 2500, -700));
    mSunObj->setScale(Ogre::Vector3(1000, 1000, 1000));

    mCrossHair = new MovingObject(mSceneManager,"movCrossHair", "Crosshair.mesh", NULL);
    mCrossHair->setScale(Ogre::Vector3(0.5F,1,1));
	mObj1->setScale(Ogre::Vector3(1.1F,1.1F,1.1F));
	//mObj5->setScale(Ogre::Vector3(30000,1.1F,30000));
	mObj5->setScale(Ogre::Vector3(1000,1000,1000));
    mObj1->setPosition(Ogre::Vector3(500, 20, 300));
    mObj2->setPosition(Ogre::Vector3(20, 0, 0));
    mObj3->setPosition(Ogre::Vector3(0, 20, 0));
	mObj4->setPosition(Ogre::Vector3(0, 0, 200));
	mObj5->setPosition(Ogre::Vector3(0, 0, 0));
	Ogre::Vector3 xBasis = Ogre::Vector3(1,0, 0);
    Ogre::Vector3 yBasis = Ogre::Vector3(0,0 ,1);
    Ogre::Vector3 zBasis = Ogre::Vector3(0,-1,0);
    Ogre::Matrix3 rotate;
    rotate.FromAxes(xBasis, yBasis, zBasis);
	mObj5->setOrientation(rotate);
    mCrossHair->setPosition(Ogre::Vector3(0,-20,0));

    movObjs[2] = mObj2;
    movObjs[3] = mObj3;
    movObjs[4] = mObj4;
    //movObjs[4] = mObj5; Taken off since it is the mobius strip and objects are inside it.
    movObjs[5] = mSunObj;
    movObjs[6] = mCrossHair;

    mMovingObjects[std::string("movObject2")] = mObj1;
    mMovingObjects[std::string("movObject3")] = mObj2;
    mMovingObjects[std::string("movObject4")] = mObj3;
    mMovingObjects[std::string("movObject5")] = mObj4;
    mMovingObjects[std::string("movObject6")] = mSunObj;
    mMovingObjects[std::string("movObject7")] = mCrossHair;
}


Tank::~Tank(void)
{
}

/* Attach camera to the main user node */
void
Tank::attachCamera(void)
{
	mCameraNode = SceneManager()->getSceneNode("U")->createChildSceneNode();
	mCameraNode_AI1 = SceneManager()->getSceneNode("AItank1")->createChildSceneNode();//mAI1->createChildSceneNode();
	mCameraNode_AI2 = SceneManager()->getSceneNode("AItank2")->createChildSceneNode();//mAI2->createChildSceneNode();
	mCameraNode_AI3 = SceneManager()->getSceneNode("AItank3")->createChildSceneNode();//mAI3->createChildSceneNode();
	mCameraNode->attachObject(mCamera->getCamera());
	mCameraNode->attachObject(mCameraR->getCamera());
	mCameraNode_AI1->attachObject(mCamera_ai1->getCamera());
	mCameraNode_AI2->attachObject(mCamera_ai2->getCamera());
	mCameraNode_AI3->attachObject(mCamera_ai3->getCamera());

	//mTempNode=SceneManager()->getSceneNode("AItank0");
}
void Tank::Think(const Ogre::Real& mTime)
{
    mWorld->setIterator();
    Node *iterator = mWorld->getIterator();
    Ogre::Vector3 MTD;
	if(mWorld->cllision==0){
    for (std::map<std::string, MovingObject *>::iterator it = mMovingObjects.begin(); it != mMovingObjects.end(); it++) {
        std::string name = it->first;
		MovingObject *obj = it->second;

        for (std::map<std::string, MovingObject *>::iterator it2 = mMovingObjects.begin(); it2 != mMovingObjects.end(); it2++)
			{
				if (it2->second != obj)
				{
					Ogre::Vector3 MTD;
					if (obj->getOBB()->collides(it2->second->getOBB(), MTD))
					{
						obj->translate(MTD);
						if(obj->getSceneNode()->getName()=="U")
						{
							mWorld->uScore--;
							//PlaySound(TEXT("gone.wav"), NULL, SND_FILENAME);
						}
						if(obj->getSceneNode()->getName()=="AItank1"){mWorld->ais;}

					}

				}
			}
			for (std::map<std::string, StaticObject *>::iterator it2 = mStaticObjects.begin(); it2 != mStaticObjects.end(); it2++)
			{
					float u;
					float v;
					Ogre::Vector3 MTD = Ogre::Vector3::ZERO;
					StaticObject *colliderObj = it2->second;
					std::string colliderName = it2->first;
					OBB *collider = it2->second->getOBB();
					OBB *mover = obj->getOBB();
					if  (mover->collides(collider, MTD))
					{
						obj->translate(MTD);
						if(obj->getSceneNode()->getName()=="AItank1")
						{
							mWorld->ais++;
							//PlaySound(TEXT("coin.wav"), NULL, SND_FILENAME);
							//PlaySound(TEXT("translate.wav"), NULL, SND_FILENAME);
						}
						if(obj->getSceneNode()->getName()=="U")
						{
							mWorld->uScore++;
							//PlaySound(TEXT("coin.wav"), NULL, SND_FILENAME);
							//PlaySound(TEXT("translate.wav"), NULL, SND_FILENAME);
						}
						
						u=rand()%27;
						if(rand()%2==0)
							v =(rand()%10)/100.0f-0.1;
						else
							v =-(rand()%10)/100.0f-0.1;

						mStaticObjects[colliderName]->setPosition(Ogre::Vector3(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v)));
						//mStaticObjects[colliderName]->translate(Normal(u, v)*5);
						mStaticObjects[colliderName]->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));
						mStaticObjects[colliderName]->setOrientation(Orientation(Binormal(u, v),-Tangent(u,v),Normal(u, v)));
					}

			}
		}
	}


	mObj1->yaw(Ogre::Radian(0.5f * mTime));
    mObj2->pitch(Ogre::Radian(0.6f * mTime));
    mObj3->roll(Ogre::Radian(0.5f * mTime));
	mObj4->translate(mTime * Ogre::Vector3(-1, 0,0));
	int k = mWorld->GlblTime; //Ogre::ControllerManager::getSingleton().getElapsedTime();
	int c = k%4;//for selecting frame storages
	if(k%8==1){
	//if(k%5==0){
		/*
		* ai1
		*/
	Ogre::TexturePtr ai1_tex = Ogre::TextureManager::getSingleton().createManual(
         "MainRenderTarget", 
         Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
         Ogre::TextureType::TEX_TYPE_2D, 
         3,
         3,
		 20,
		 0,
		 Ogre::PixelFormat::PF_R8G8B8,
	     Ogre::TextureUsage::TU_RENDERTARGET);
	Ogre::RenderTexture *renderTexture_ai1 = ai1_tex->getBuffer()->getRenderTarget();
	//renderTexture_ai1->add
	(mCamera_ai1->getCamera(),0);//for predition
	renderTexture_ai1->addViewport(mCamera->getCamera(),0);//for training
	renderTexture_ai1->getViewport(0)->setClearEveryFrame(true);
	renderTexture_ai1->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
	renderTexture_ai1->getViewport(0)->setOverlaysEnabled(true);
	renderTexture_ai1->update();
	string ID_ai1 = "ai1_Render";
	string exd_ai1 = ".bmp";
	string Result_ai1;          // string which will contain the result  
	ostringstream convert_ai1;
	convert_ai1 << k;      // insert the textual representation of 'Number' in the characters in the stream
	Result_ai1 = convert_ai1.str(); // set 'Result' to the contents of the stream
	ID_ai1.append(Result_ai1);
	ID_ai1.append(exd_ai1);
	// Now save the contents
	renderTexture_ai1->writeContentsToFile(ID_ai1);
	string id_ai1=ID_ai1;
	char *infile_ai1 = new char[id_ai1.length() + 1]; //argv[2];
	strcpy(infile_ai1, id_ai1.c_str());
	string bintxtID_ai1 = "ai1_binary_in_txt";
	exd_ai1 = ".txt";
	string bintxtResult_ai1;          // string which will contain the result  
	ostringstream bintxtconvert_ai1;
	bintxtconvert_ai1 << k;      // insert the textual representation of 'Number' in the characters in the stream
	bintxtResult_ai1 = bintxtconvert_ai1.str(); // set 'Result' to the contents of the stream
	bintxtID_ai1.append(bintxtResult_ai1);
	bintxtID_ai1.append(exd_ai1);
	char *outfile_ai1 = new char[bintxtID_ai1.length() + 1]; //argv[3];
	strcpy(outfile_ai1, bintxtID_ai1.c_str());
	ofstream fout_ai1;
    ifstream fin_ai1;
	string binID_ai1 = "ai1_bindata";
	exd_ai1 = ".dat";
	string binResult_ai1;          // string which will contain the result  
	ostringstream binconvert_ai1;
	binconvert_ai1 << k;      // insert the textual representation of 'Number' in the characters in the stream
	binResult_ai1 = binconvert_ai1.str(); // set 'Result' to the contents of the stream
	binID_ai1.append(binResult_ai1);
	binID_ai1.append(exd_ai1);
	fout_ai1.open(binID_ai1,ios::binary);
	string readID_ai1 = "ai1_readable";
	exd_ai1 = ".txt";
	string readResult_ai1;          // string which will contain the result  
	ostringstream readconvert_ai1;
	readconvert_ai1 << k;      // insert the textual representation of 'Number' in the characters in the stream
	readResult_ai1 = readconvert_ai1.str(); // set 'Result' to the contents of the stream
	readID_ai1.append(readResult_ai1);
	readID_ai1.append(exd_ai1);
	ofstream outtxt_ai1( readID_ai1 );
	 // open input file 
    FILE* inptr_ai1 = fopen(infile_ai1, "r");
    if (inptr_ai1 == NULL)
    {
        printf("Could not open %s.\n", infile_ai1);
		DBOUT("Could not open%s.\n ");
    }
	//create the foo array for storing the bmp image
	//int foo_ai1 [81][81];

    // open output file
    FILE* outptr_ai1 = fopen(outfile_ai1, "w");
    /*if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);

    }*/
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_ai1;
    fread(&bf_ai1, sizeof(BITMAPFILEHEADER), 1, inptr_ai1);
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_ai1;
    fread(&bi_ai1, sizeof(BITMAPINFOHEADER), 1, inptr_ai1);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_ai1, sizeof(BITMAPFILEHEADER), 1, outptr_ai1);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_ai1, sizeof(BITMAPINFOHEADER), 1, outptr_ai1);
    // determine padding for scanlines
    int padding_ai1 =  (4 - (bi_ai1.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	//DBOUT("padding: " << padding);
    // iterate over infile's scanlines
	int counter=0;
	 for (int i = 0, biHeight = abs(bi_ai1.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi_ai1.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple_ai1;
            // read RGB triple from infile
            fread(&triple_ai1, sizeof(RGBTRIPLE), 1, inptr_ai1);
			mean_ai1 =(int)(triple_ai1.rgbtBlue+triple_ai1.rgbtRed+triple_ai1.rgbtGreen)/3;
			//store into foo[81][81] array
			//foo_ai1[i][j]=mean_ai1;
			//we have five batches per second, i.e., 5 fps
			if(k%5==0){
				mWorld->ai1[0][counter]=mean_ai1;
				counter++;
			}
			else if(k%5==1)
			{
				mWorld->ai1[1][counter]=mean_ai1;
				counter++;
			}
			else if(k%5==2)
			{
				mWorld->ai1[2][counter]=mean_ai1;
				counter++;
			}
			else if(k%5==3)
			{
				mWorld->ai1[3][counter]=mean_ai1;
				counter++;
			}
			else if(k%5==4)
			{
				mWorld->ai1[4][counter]=mean_ai1;
				counter++;
			}
			//store(c, mean_ai1, i, j);
			//write in text file 
			outtxt_ai1 << mean_ai1 << flush;
			outtxt_ai1 << " "<< flush;
			//DBOUT("mean: " << mean);
            // write RGB triple to outfile
            fwrite(&mean_ai1, sizeof(int), sizeof(mean_ai1), outptr_ai1);
			fout_ai1.write((char*)&mean_ai1,sizeof(int));
		}
        // skip over padding, if any
        fseek(inptr_ai1, padding_ai1, SEEK_CUR);
        // then add it back (to demonstrate how)
        for (int k = 0; k < padding_ai1; k++){
			store(c,0x00 , i, k);
			//foo_ai1[i][k];
			//we have five batches per second, fill in the paddings
			if(k%5==0){
				mWorld->ai1[0][counter]=0;
				counter++;
			}
			else if(k%5==1)
			{
				mWorld->ai1[1][counter]=0;
				counter++;
			}
			else if(k%5==2)
			{
				mWorld->ai1[2][counter]=0;
				counter++;
			}
			else if(k%5==3)
			{
				mWorld->ai1[3][counter]=0;
				counter++;
			}
			else if(k%5==4)
			{
				mWorld->ai1[4][counter]=0;
				counter++;
			}
            fputc(0x00, outptr_ai1);
			outtxt_ai1 << 0x00 << flush;
			outtxt_ai1 << " "<< flush;
		}
		outtxt_ai1 << endl;

    }
    // close infile
    fclose(inptr_ai1);
    // close outfile
	fout_ai1.close();
	fin_ai1.open(binID_ai1,ios::binary);
	for (int i = 0, biHeight = abs(bi_ai1.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi_ai1.biWidth; j++)
        {
			int my_int2;
			fin_ai1.read((char*)&my_int2,sizeof(int));
			//DBOUT("my_int2: " << my_int2);
		}
	}
	fin_ai1.close();
    fclose(outptr_ai1);
	outtxt_ai1.close();
	delete [] infile_ai1;
	}
	
	

	/*
	* ai2
	*/
	//	Ogre::TexturePtr ai2_tex = Ogre::TextureManager::getSingleton().createManual(
 //        "MainRenderTarget", 
 //        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
 //        Ogre::TextureType::TEX_TYPE_2D, 
 //        3,
 //        3,
	//	 20,
	//	 0,
	//	 Ogre::PixelFormat::PF_R8G8B8,
	//     Ogre::TextureUsage::TU_RENDERTARGET);
	//	Ogre::RenderTexture *renderTexture_ai2 = ai2_tex->getBuffer()->getRenderTarget();
	//	renderTexture_ai2->addViewport(mCamera_ai2->getCamera(),0);
	//	renderTexture_ai2->getViewport(0)->setClearEveryFrame(true);
	//	renderTexture_ai2->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
	//	renderTexture_ai2->getViewport(0)->setOverlaysEnabled(true);
	//	renderTexture_ai2->update();

	//	string ID_ai2 = "ai2_Render";
	//	string exd_ai2 = ".bmp";
	//	string Result_ai2;          // string which will contain the result  
	//	ostringstream convert_ai2;
	//	convert_ai2 << k;      // insert the textual representation of 'Number' in the characters in the stream
	//	Result_ai2 = convert_ai2.str(); // set 'Result' to the contents of the stream
	//	ID_ai2.append(Result_ai2);
	//	ID_ai2.append(exd_ai2);
	//	// Now save the contents
	//	renderTexture_ai2->writeContentsToFile(ID_ai2);

	//	string id_ai2=ID_ai2;
	//	char *infile_ai2 = new char[id_ai2.length() + 1]; //argv[2];
	//	strcpy(infile_ai2, id_ai2.c_str());

	//	string bintxtID_ai2 = "ai2_binary_in_txt";
	//	exd_ai2 = ".txt";
	//	string bintxtResult_ai2;          // string which will contain the result  
	//	ostringstream bintxtconvert_ai2;
	//	bintxtconvert_ai2 << k;      // insert the textual representation of 'Number' in the characters in the stream
	//	bintxtResult_ai2 = bintxtconvert_ai2.str(); // set 'Result' to the contents of the stream
	//	bintxtID_ai2.append(bintxtResult_ai2);
	//	bintxtID_ai2.append(exd_ai2);
	//	char *outfile_ai2 = new char[bintxtID_ai2.length() + 1]; //argv[3];
	//	strcpy(outfile_ai2, bintxtID_ai2.c_str());

	//ofstream fout_ai2;
	//string binID_ai2 = "ai2_bindata";
	//exd_ai2 = ".dat";
	//string binResult_ai2;          // string which will contain the result  
	//ostringstream binconvert_ai2;
	//binconvert_ai2 << k;      // insert the textual representation of 'Number' in the characters in the stream
	//binResult_ai2 = binconvert_ai2.str(); // set 'Result' to the contents of the stream
	//binID_ai2.append(binResult_ai2);
	//binID_ai2.append(exd_ai2);
	//fout_ai2.open(binID_ai2,ios::binary);

	//string readID_ai2 = "ai2_readable";
	//exd_ai2 = ".txt";
	//string readResult_ai2;          // string which will contain the result  
	//ostringstream readconvert_ai2;
	//readconvert_ai2 << k;      // insert the textual representation of 'Number' in the characters in the stream
	//readResult_ai2 = readconvert_ai2.str(); // set 'Result' to the contents of the stream
	//readID_ai2.append(readResult_ai2);
	//readID_ai2.append(exd_ai2);
	//ofstream outtxt_ai2( readID_ai2 );
	// // open input file 

 //   FILE* inptr_ai2 = fopen(infile_ai2, "r");
 //   if (inptr_ai2 == NULL)
 //   {
 //       printf("Could not open %s.\n", infile_ai2);
	//	DBOUT("Could not open%s.\n ");
 //   }
	////create the foo array for storing the bmp image
	//int foo_ai2 [81][81];

 //   // open output file
 //   FILE* outptr_ai2 = fopen(outfile_ai2, "w");
 //   /*if (outptr == NULL)
 //   {
 //       fclose(inptr);
 //       fprintf(stderr, "Could not create %s.\n", outfile);

 //   }*/
 //   // read infile's BITMAPFILEHEADER
 //   BITMAPFILEHEADER bf_ai2;
 //   fread(&bf_ai2, sizeof(BITMAPFILEHEADER), 1, inptr_ai2);
 //   // read infile's BITMAPINFOHEADER
 //   BITMAPINFOHEADER bi_ai2;
 //   fread(&bi_ai2, sizeof(BITMAPINFOHEADER), 1, inptr_ai2);
 //   // write outfile's BITMAPFILEHEADER
 //   fwrite(&bf_ai2, sizeof(BITMAPFILEHEADER), 1, outptr_ai2);
 //   // write outfile's BITMAPINFOHEADER
 //   fwrite(&bi_ai2, sizeof(BITMAPINFOHEADER), 1, outptr_ai2);
 //   // determine padding for scanlines
 //   int padding_ai2 =  (4 - (bi_ai2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	////DBOUT("padding: " << padding);
 //   // iterate over infile's scanlines
	//for (int i = 0, biHeight = abs(bi_ai2.biHeight); i < biHeight; i++)
 //   {
 //       // iterate over pixels in scanline
 //       for (int j = 0; j < bi_ai2.biWidth; j++)
 //       {
	//		//DBOUT("bi.biHeight: " << bi.biHeight);
	//		//DBOUT("bi.biWidth: " << bi.biWidth);
 //           // temporary storage
 //           RGBTRIPLE triple_ai2;
 //           // read RGB triple from infile
 //           fread(&triple_ai2, sizeof(RGBTRIPLE), 1, inptr_ai2);
	//		//DBOUT("triple.rgbtBlue: " << triple.rgbtBlue);
	//		//DBOUT("triple.rgbtRed: " << triple.rgbtRed);
	//		//DBOUT("triple.rgbtGreen: " << triple.rgbtGreen);
	//		mean_ai2 =(int)(triple_ai2.rgbtBlue+triple_ai2.rgbtRed+triple_ai2.rgbtGreen)/3;
	//		//char b[] = {mean};
	//		//write in ascii
	//		//std::string buf = "";
	//		//char str[20];
	//		//buf += itoa(mean, str, 10);
	//		//write in char
	//		//ostringstream a;
	//		//a << mean;
	//		//store into foo[81][81] array
	//		//foo_ai2 [i][j]=mean_ai2;
	//		//store(c, mean_ai2, i, j);
	//		//we have five batches per second, i.e., 5 fps
	//		if(k%5==0){
	//			mWorld->ai2[0][counter]=mean_ai2;
	//			counter++;
	//		}
	//		else if(k%5==1)
	//		{
	//			mWorld->ai2[1][counter]=mean_ai2;
	//			counter++;
	//		}
	//		else if(k%5==2)
	//		{
	//			mWorld->ai2[2][counter]=mean_ai2;
	//			counter++;
	//		}
	//		else if(k%5==3)
	//		{
	//			mWorld->ai2[3][counter]=mean_ai2;
	//			counter++;
	//		}
	//		else if(k%5==4)
	//		{
	//			mWorld->ai2[4][counter]=mean_ai2;
	//			counter++;
	//		}
	//		//write in text file 
	//		outtxt_ai2 << mean_ai2 << flush;
	//		outtxt_ai2 << " "<< flush;
	//		//DBOUT("mean: " << mean);
 //           // write RGB triple to outfile
 //           fwrite(&mean_ai2, sizeof(int), sizeof(mean_ai2), outptr_ai2);
	//		fout_ai2.write((char*)&mean_ai2,sizeof(int));
 //       }
 //       // skip over padding, if any
 //       fseek(inptr_ai2, padding_ai2, SEEK_CUR);
 //       // then add it back (to demonstrate how)
 //       for (int k = 0; k < padding_ai2; k++){
	//		store(c,0x00 , i, k);
	//		//foo_ai2[i][k];
	//					//we have five batches per second, fill in the paddings
	//		if(k%5==0){
	//			mWorld->ai2[0][counter]=0;
	//			counter++;
	//		}
	//		else if(k%5==1)
	//		{
	//			mWorld->ai2[1][counter]=0;
	//			counter++;
	//		}
	//		else if(k%5==2)
	//		{
	//			mWorld->ai2[2][counter]=0;
	//			counter++;
	//		}
	//		else if(k%5==3)
	//		{
	//			mWorld->ai2[3][counter]=0;
	//			counter++;
	//		}
	//		else if(k%5==4)
	//		{
	//			mWorld->ai2[4][counter]=0;
	//			counter++;
	//		}
 //           fputc(0x00, outptr_ai2);
	//		outtxt_ai2 << 0x00 << flush;
	//		outtxt_ai2 << " "<< flush;
	//	}
	//	outtxt_ai2 << endl;
 //   }
 //   // close infile
 //   fclose(inptr_ai2);
 //   // close outfile
	//fout_ai2.close();

	//ifstream fin_ai2;//for double check the output file (whether there are readable by the machine)
	//fin_ai2.open(binID_ai2,ios::binary);
	//for (int i = 0, biHeight = abs(bi_ai2.biHeight); i < biHeight; i++)
 //   {
 //       // iterate over pixels in scanline
 //       for (int j = 0; j < bi_ai2.biWidth; j++)
 //       {
	//		int my_int2_ai2;
	//		fin_ai1.read((char*)&my_int2_ai2,sizeof(int));
	//		//DBOUT("my_int2: " << my_int2);
	//	}
	//}
	//fin_ai2.close();

 //   fclose(outptr_ai2);
	//outtxt_ai2.close();
	//delete [] infile_ai2;


	///*
	//* ai3
	//*/
	//	Ogre::TexturePtr ai3_tex = Ogre::TextureManager::getSingleton().createManual(
 //        "MainRenderTarget", 
 //        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
 //        Ogre::TextureType::TEX_TYPE_2D, 
 //        3,
 //        3,
	//	 20,
	//	 0,
	//	 Ogre::PixelFormat::PF_R8G8B8,
	//     Ogre::TextureUsage::TU_RENDERTARGET);
	//	Ogre::RenderTexture *renderTexture_ai3 = ai3_tex->getBuffer()->getRenderTarget();
	//	renderTexture_ai3->addViewport(mCamera_ai2->getCamera(),0);
	//	renderTexture_ai3->getViewport(0)->setClearEveryFrame(true);
	//	renderTexture_ai3->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
	//	renderTexture_ai3->getViewport(0)->setOverlaysEnabled(true);
	//	renderTexture_ai3->update();
	//	string ID_ai3 = "ai3_Render";
	//	string exd_ai3 = ".bmp";
	//	string Result_ai3;          // string which will contain the result  
	//	ostringstream convert_ai3;
	//	convert_ai3 << k;      // insert the textual representation of 'Number' in the characters in the stream
	//	Result_ai3 = convert_ai3.str(); // set 'Result' to the contents of the stream
	//	ID_ai3.append(Result_ai3);
	//	ID_ai3.append(exd_ai3);
	//	// Now save the contents
	//	renderTexture_ai3->writeContentsToFile(ID_ai3);
	//	string id_ai3=ID_ai3;
	//	char *infile_ai3 = new char[id_ai3.length() + 1]; //argv[2];
	//	strcpy(infile_ai3, id_ai3.c_str());
	//	string bintxtID_ai3 = "ai3_binary_in_txt";
	//	exd_ai3 = ".txt";
	//	string bintxtResult_ai3;          // string which will contain the result  
	//	ostringstream bintxtconvert_ai3;
	//	bintxtconvert_ai3 << k;      // insert the textual representation of 'Number' in the characters in the stream
	//	bintxtResult_ai3 = bintxtconvert_ai3.str(); // set 'Result' to the contents of the stream
	//	bintxtID_ai3.append(bintxtResult_ai3);
	//	bintxtID_ai3.append(exd_ai3);
	//	char *outfile_ai3 = new char[bintxtID_ai3.length() + 1]; //argv[3];
	//	strcpy(outfile_ai3, bintxtID_ai3.c_str());
	//	ofstream fout_ai3;
 //   ifstream fin_ai3;
	//string binID_ai3 = "ai3_bindata";
	//exd_ai3 = ".dat";
	//string binResult_ai3;          // string which will contain the result  
	//ostringstream binconvert_ai3;
	//binconvert_ai3 << k;      // insert the textual representation of 'Number' in the characters in the stream
	//binResult_ai3 = binconvert_ai3.str(); // set 'Result' to the contents of the stream
	//binID_ai3.append(binResult_ai3);
	//binID_ai3.append(exd_ai3);
	//fout_ai3.open(binID_ai3,ios::binary);
	//string readID_ai3 = "ai3_readable";
	//exd_ai3 = ".txt";
	//string readResult_ai3;          // string which will contain the result  
	//ostringstream readconvert_ai3;
	//readconvert_ai3 << k;      // insert the textual representation of 'Number' in the characters in the stream
	//readResult_ai3 = readconvert_ai3.str(); // set 'Result' to the contents of the stream
	//readID_ai3.append(readResult_ai3);
	//readID_ai3.append(exd_ai3);
	//ofstream outtxt_ai3( readID_ai3 );
	// // open input file 
 //   FILE* inptr_ai3 = fopen(infile_ai3, "r");
 //   if (inptr_ai3 == NULL)
 //   {
 //       printf("Could not open %s.\n", infile_ai3);
	//	DBOUT("Could not open%s.\n ");
 //   }
	////create the foo array for storing the bmp image
	//int foo_ai3 [81][81];

 //   // open output file
 //   FILE* outptr_ai3 = fopen(outfile_ai3, "w");
 //   /*if (outptr == NULL)
 //   {
 //       fclose(inptr);
 //       fprintf(stderr, "Could not create %s.\n", outfile);

 //   }*/
 //   // read infile's BITMAPFILEHEADER
 //   BITMAPFILEHEADER bf_ai3;
 //   fread(&bf_ai3, sizeof(BITMAPFILEHEADER), 1, inptr_ai3);
 //   // read infile's BITMAPINFOHEADER
 //   BITMAPINFOHEADER bi_ai3;
 //   fread(&bi_ai3, sizeof(BITMAPINFOHEADER), 1, inptr_ai3);
 //   // write outfile's BITMAPFILEHEADER
 //   fwrite(&bf_ai3, sizeof(BITMAPFILEHEADER), 1, outptr_ai3);
 //   // write outfile's BITMAPINFOHEADER
 //   fwrite(&bi_ai3, sizeof(BITMAPINFOHEADER), 1, outptr_ai3);
 //   // determine padding for scanlines
 //   int padding_ai3 =  (4 - (bi_ai3.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	////DBOUT("padding: " << padding);
 //   // iterate over infile's scanlines


	//	 for (int i = 0, biHeight = abs(bi_ai3.biHeight); i < biHeight; i++)
 //   {
 //       // iterate over pixels in scanline
 //       for (int j = 0; j < bi_ai3.biWidth; j++)
 //       {
	//		//DBOUT("bi.biHeight: " << bi.biHeight);
	//		//DBOUT("bi.biWidth: " << bi.biWidth);
 //           // temporary storage
 //           RGBTRIPLE triple_ai3;
 //           // read RGB triple from infile
 //           fread(&triple_ai3, sizeof(RGBTRIPLE), 1, inptr_ai3);
	//		//DBOUT("triple.rgbtBlue: " << triple.rgbtBlue);
	//		//DBOUT("triple.rgbtRed: " << triple.rgbtRed);
	//		//DBOUT("triple.rgbtGreen: " << triple.rgbtGreen);
	//		mean_ai3 =(int)(triple_ai3.rgbtBlue+triple_ai3.rgbtRed+triple_ai3.rgbtGreen)/3;
	//		//char b[] = {mean};
	//		//write in ascii
	//		//std::string buf = "";
	//		//char str[20];
	//		//buf += itoa(mean, str, 10);
	//		//write in char
	//		//ostringstream a;
	//		//a << mean;
	//		//store into foo[81][81] array
	//		//foo_ai3 [i][j]=mean_ai3;
	//		//we have five batches per second, i.e., 5 fps
	//		if(k%5==0){
	//			mWorld->ai3[0][counter]=mean_ai3;
	//			counter++;
	//		}
	//		else if(k%5==1)
	//		{
	//			mWorld->ai3[1][counter]=mean_ai3;
	//			counter++;
	//		}
	//		else if(k%5==2)
	//		{
	//			mWorld->ai3[2][counter]=mean_ai3;
	//			counter++;
	//		}
	//		else if(k%5==3)
	//		{
	//			mWorld->ai3[3][counter]=mean_ai3;
	//			counter++;
	//		}
	//		else if(k%5==4)
	//		{
	//			mWorld->ai3[4][counter]=mean_ai3;
	//			counter++;
	//		}
	//		//store(c, mean_ai3, i, j);
	//		//write in text file 
	//		outtxt_ai3 << mean_ai3 << flush;
	//		outtxt_ai3 << " "<< flush;
	//		//DBOUT("mean: " << mean);
 //           // write RGB triple to outfile
 //           fwrite(&mean_ai3, sizeof(int), sizeof(mean_ai3), outptr_ai3);
	//		fout_ai3.write((char*)&mean_ai3,sizeof(int));
 //       }
 //       // skip over padding, if any
 //       fseek(inptr_ai3, padding_ai3, SEEK_CUR);
 //       // then add it back (to demonstrate how)
 //       for (int k = 0; k < padding_ai3; k++){
	//		//store(c,0x00 , i, k);
	//		//foo_ai3[i][k];
	//					//we have five batches per second, fill in the paddings
	//		if(k%5==0){
	//			mWorld->ai3[0][counter]=0;
	//			counter++;
	//		}
	//		else if(k%5==1)
	//		{
	//			mWorld->ai3[1][counter]=0;
	//			counter++;
	//		}
	//		else if(k%5==2)
	//		{
	//			mWorld->ai3[2][counter]=0;
	//			counter++;
	//		}
	//		else if(k%5==3)
	//		{
	//			mWorld->ai3[3][counter]=0;
	//			counter++;
	//		}
	//		else if(k%5==4)
	//		{
	//			mWorld->ai3[4][counter]=0;
	//			counter++;
	//		}
 //           fputc(0x00, outptr_ai3);
	//		outtxt_ai3 << 0x00 << flush;
	//		outtxt_ai3 << " "<< flush;
	//	}
	//	outtxt_ai3 << endl;
 //   }
 //   // close infile
 //   fclose(inptr_ai3);
 //   // close outfile
	//fout_ai3.close();
	//fin_ai3.open(binID_ai3,ios::binary);
	//for (int i = 0, biHeight = abs(bi_ai3.biHeight); i < biHeight; i++)
 //   {
 //       // iterate over pixels in scanline
 //       for (int j = 0; j < bi_ai3.biWidth; j++)
 //       {
	//		int my_int2_ai3;
	//		fin_ai3.read((char*)&my_int2_ai3,sizeof(int));
	//		//DBOUT("my_int2: " << my_int2);
	//	}
	//}
	//fin_ai3.close();
 //   fclose(outptr_ai3);
	//outtxt_ai3.close();
	//delete [] infile_ai3;
	//int SwitchMode =1;

	//}

		/*control*/
		if(mWorld->Mode==0){
		int control;

		/*if(k%5==0){
			//calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
			control = prediction(mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
			if(control==0){
				mWorld->U_u+=1.0f;
				mWorld->AI_0_u+=1.0f;
				mWorld->AI_1_u+=1.0f;
			}
			else if(control==1){
				mWorld->U_v+=1.0f;
				mWorld->AI_0_v+=1.0f;	
				mWorld->AI_1_v+=1.0f;
			}
			else if(control==2){
				mWorld->U_v-=1.0f;
				mWorld->AI_0_v-=1.0f;
				mWorld->AI_1_v-=1.0f;
		}
			else if(control==3){
				mWorld->U_u-=1.0f;
				mWorld->AI_0_u-=1.0f;
				mWorld->AI_1_u-=1.0f;	
			}
		}*/
		if(k%8==1)
		{
			//calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
			control = prediction(mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);

			if(control==0){
				mWorld->U_u+=1.0f;
				mWorld->AI_0_u+=1.0f;
				mWorld->AI_1_u+=1.0f;
			}
			else if(control==1){
				mWorld->U_v+=1.0f;
				mWorld->AI_0_v+=1.0f;
				mWorld->AI_1_v+=1.0f;
			}
			else if(control==2){
				mWorld->U_v-=1.0f;
				mWorld->AI_0_v-=1.0f;
				mWorld->AI_1_v-=1.0f;
			}
			else if(control==3){
				mWorld->U_u-=1.0f;
				mWorld->AI_0_u-=1.0f;
				mWorld->AI_1_u-=1.0f;
			}
		}
		else if(k%5==2)
		{
			//calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
		/*	control = prediction(mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
			if(control==0){
				mWorld->U_u+=1.0f;
				mWorld->AI_0_u+=1.0f;
				mWorld->AI_1_u+=1.0f;
			}
			else if(control==1){
				mWorld->U_v+=1.0f;
				mWorld->AI_0_v+=1.0f;
				mWorld->AI_1_v+=1.0f;
			}
			else if(control==2){
				mWorld->U_v-=1.0f;
				mWorld->AI_0_v-=1.0f;
				mWorld->AI_1_v-=1.0f;
			}
			else if(control==3){
				mWorld->U_u-=1.0f;
				mWorld->AI_0_u-=1.0f;
				mWorld->AI_1_u-=1.0f;
			}
			*/
		}
		else if(k%5==3)
		{
			//calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
			control = prediction(mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
			/*
			if(control==0){
				mWorld->U_u+=1.0f;
				mWorld->AI_0_u+=1.0f;
				mWorld->AI_1_u+=1.0f;
			}
			else if(control==1){
				mWorld->U_v+=1.0f;
				mWorld->AI_0_v+=1.0f;
				mWorld->AI_1_v+=1.0f;
			}
			else if(control==2){
				mWorld->U_v-=1.0f;
				mWorld->AI_0_v-=1.0f;
				mWorld->AI_1_v-=1.0f;
			}
			else if(control==3){
				mWorld->U_u-=1.0f;
				mWorld->AI_0_u-=1.0f;
				mWorld->AI_1_u-=1.0f;
			}
			*/
		}
		else if(k%5==4)
		{
			//calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
			/*control = prediction(mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
			
			if(control==0){
				mWorld->U_u+=1.0f;
				mWorld->AI_0_u+=1.0f;
				mWorld->AI_1_u+=1.0f;
			}
			else if(control==1){
				mWorld->U_v+=1.0f;
				mWorld->AI_0_v+=1.0f;
				mWorld->AI_1_v+=1.0f;
			}
			else if(control==2){
				mWorld->U_v-=1.0f;
				mWorld->AI_0_v-=1.0f;
				mWorld->AI_1_v-=1.0f;
			}
			else if(control==3){
				mWorld->U_u-=1.0f;
				mWorld->AI_0_u-=1.0f;
				mWorld->AI_1_u-=1.0f;
			}
			*/
		}
	}
	else if(mWorld->Mode==1){
		//read input parameters

		if(k%5==0){
			calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
		}
		else if(k%5==1){
		    calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
		}
		else if(k%5==2){
			calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
		}
		else if(k%5==3){
		    calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
		}
		else if(k%5==4){
			calculate_loss(mWorld->lab, mWorld->ai1, mWorld->w1, mWorld->w2, mWorld->b1, mWorld->b2);
		}
	}
		if((int)k==99&&mWorld->Mode==1){
		//wrtie parameters as outputs
		string w1ID = "Trained_w1_readable.txt";
		ofstream outtxt_ai2( w1ID );
		string bintxtID_w1 = "Trained_w1_binary";
		ofstream fout_w1( bintxtID_w1 );
		//for fopen, fwrite
		//char *outfile_w1 = new char[bintxtID_w1.length() + 1]; 
		//strcpy(outfile_w1, bintxtID_w1.c_str());
		//FILE* outptr_w1 = fopen(outfile_w1, "w");
		
		for(int j=0; j< 9; j++)
		{
			for(int k=0; k< 6; k++)
			{
				//write in text file 
				//fwrite(&mWorld->w1[k][j], sizeof(float), sizeof(mWorld->w1[k][j]), outptr_w1);
				fout_w1.write((char*)&mWorld->w1[j][k],sizeof(float));
			    outtxt_ai2 << mWorld->w1[j][k] << flush;
			    outtxt_ai2 << ", "<< flush;
				
			}
			outtxt_ai2 << endl;
			fout_w1 << endl;
			//fputc('\n',outptr_w1);
		}
		outtxt_ai2.close();
		fout_w1.close();
		//fclose(outptr_w1);

		string w2ID = "Trained_w2_readable.txt";
		ofstream outtxt_w2( w2ID );
		string bintxtID_w2 = "Trained_w2_binary";
		ofstream fout_w2( bintxtID_w2 );
		for(int j=0; j< 6; j++)
		{
			for(int k=0; k< 4; k++)
			{
				fout_w2.write((char*)&mWorld->w2[j][k],sizeof(float));
				outtxt_w2 << mWorld->w2[j][k] << flush;
			    outtxt_w2 << ", "<< flush;
			}
			outtxt_w2 << endl;
			fout_w2 << endl;
		}
		outtxt_w2.close();
		fout_w2.close();

		string b1ID = "Trained_b1_readable.txt";
		ofstream outtxt_b1( b1ID );
		string bintxtID_b1 = "Trained_b1_binary";
		ofstream fout_b1( bintxtID_b1 );
		for(int k=0; k< 6; k++)
		{
			fout_b1.write((char*)&mWorld->b1[k],sizeof(float));
			outtxt_b1 << mWorld->b1[k] << flush;
			outtxt_b1 << ", "<< flush;
			
		}
		outtxt_b1.close();
		fout_b1.close();

		string b2ID = "Trained_b2_readable.txt";
		ofstream outtxt_b2( b2ID );
		string bintxtID_b2 = "Trained_b2_binary";
		ofstream fout_b2( bintxtID_b2 );
		for(int k=0; k< 4; k++)
		{
			fout_b2.write((char*)&mWorld->b2[k],sizeof(float));
			outtxt_b2 << mWorld->b2[k] << flush;
			outtxt_b2 << ", "<< flush;
			outtxt_b2 << endl;
		}		
		outtxt_b2.close();
		fout_b2.close();

		string loss = "loss_readable.txt";
		ofstream outtxt_loss( loss );
		string lossbi = "loss_binary";
		ofstream fout_loss( lossbi );

			fout_loss.write((char*)&mWorld->batch_loss,sizeof(float));
			outtxt_loss << mWorld->batch_loss << flush;
			outtxt_loss << endl;
		
		outtxt_loss.close();
		fout_loss.close();
	}
}

void
Tank::calculate_loss(int lab[6][5], int x[6][10], float (&w1)[10][7], float (&w2)[7][5], float *b1, float *b2)
{
	
	/*int k = mWorld->GlblTime;
	string L ="lab_readable";
	string lab_readable;
	ostringstream readconvert_L;
	readconvert_L << k;
	lab_readable = readconvert_L.str();
	string exd_L = ".txt";
	L.append(lab_readable );
	L.append(exd_L);
	ofstream outtxt_loss( L );
	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			outtxt_loss << lab[i][j] << flush;
		}
		outtxt_loss << endl;
	}
		outtxt_loss.close();
		*/
		



				//# FEEDFORWARD
				//# reshape array in order to easily calculate dot product
				//w1*x + b1
				
				for(int i=0;i<5;i++)//for the output
				{
					for(int j=0; j< 6; j++)
					{
						mWorld->z_1[i][j]=0.0f;
						for(int k=0; k< 9; k++)
						{
							mWorld->z_1[i][j] += x[i][k]*(w1[k][j]);
						}
						mWorld->z_1[i][j]+= b1[j];
					}
				}
				//y_ij = sigmoid(z_1_ij)
				
				tf = new tensorflow(mWorld);
				
				for(int i=0; i<5;i++){
					for(int j=0; j<6; j++)
					{
						mWorld->y[i][j]=tf->sigmoid(mWorld->z_1[i][j]);
					}
				}
				
				//z = w2*y + b2
				for(int i=0;i<5;i++)//for the output
				{
					for(int j=0; j< 4; j++)
					{
						mWorld->z[i][j]=0.0f;
						for(int k=0; k< 6; k++)
						{
							mWorld->z[i][j] += w2[k][j]*mWorld->y[i][k];
						}
						mWorld->z[i][j]+= b2[j];
					}
				}
				
				for(int i=0;i<5;i++)//for the output
				{
					mWorld->M[i]=INT_FAST16_MIN;
					for(int j=0; j< 4; j++){
						if(mWorld->z[i][j]>mWorld->M[i])
							mWorld->M[i]=mWorld->z[i][j];
					}
					
				}
				
				for(int i=0;i<5;i++)//for the output
				{
					for(int j=0; j< 4; j++)
					{
						mWorld->softsum[i]+= (mWorld->z[i][j]-mWorld->M[i]);
					}
					
				}
				//p = apply_along_axis(softmax, 0, z)
				for(int i=0;i<5;i++)//for the output
				{
					for(int j=0; j< 4; j++)
					{
						mWorld->p[i][j]= tf->softmax(mWorld->z[i][j]-mWorld->M[i],mWorld->softsum[i]);
					}
				}
				//normalized
				for(int i=0;i<5;i++)//for the output
				{
					float norm=0.0f;
					for(int j=0; j< 4; j++)
					{
						norm+=mWorld->p[i][j];
					}
					for(int j=0; j< 4; j++)
					{
						mWorld->p[i][j]/=norm;
					}
				}

			/*	string P ="Prob_readable";
				string Prob_readable;
				ostringstream readconvert_P;
				readconvert_P << k;
				Prob_readable = readconvert_P.str();
				string exd_P = ".txt";
				P.append(Prob_readable );
				P.append(exd_P);
				ofstream outtxt_Prob( P );
				for(int i=0;i<5;i++){
					for(int j=0;j<4;j++){
						outtxt_Prob << mWorld->p[i][j] << flush;
						
					}
					outtxt_Prob << endl;
				}
				
				outtxt_Prob.close();
				*/

				
				//# calculate loss
				//loss = np.zeros(batch_size)
				
				for(int i=0;i<5;i++)//initialize the loss
				{
					mWorld->loss[i]=0.0f;
				}
				//for j, (a, b) in enumerate(zip(p.T, label_mini_batches[i])):
					//loss[j] = cross_entropy_loss(a, b)
				//return -np.sum((target_vector * np.log(probability_distribution)))
				
				for(int i=0;i<5;i++)
				{
					for(int j=0; j< 4; j++)
					{
						if(mWorld->p[i][j]<=0){
							mWorld->loss[i] +=0.0f;
						}
						else
						mWorld->loss[i] += ((-1)*log(mWorld->p[i][j])*lab[i][j]);
					}
				}
				
				//batch_loss = sum(loss) / batch_size
				float batch_loss = 0.0f;
				for(int i=0;i<5;i++)
				{
					batch_loss+=mWorld->loss[i];	
				}
				batch_loss/=5;
				mWorld->batch_loss=batch_loss;

				//BACKPROPAGATION
				//output layer (z) gradient
				//dloss_dz = p - label_mini_batches[i].T
				
				for(int i=0;i<5;i++)
				{
					for(int j=0; j< 4; j++)
					{
						mWorld->dloss_dz[i][j] = mWorld->p[i][j]-lab[i][j];
					}
				}
				//dloss_dw2 = dloss_dz*y.T
				
				for(int i=0;i<6;i++)//for the output
				{
					for(int j=0; j< 5; j++)
					{
						mWorld->y_t[i][j]=mWorld->y[j][i];
					}
				}
				
				
				for(int i=0;i<6;i++)
				{
					for(int j=0; j< 4; j++)
					{
						mWorld->dloss_dw2[i][j]=0.0f;
						for(int k=0; k< 5; k++)
						{
							mWorld->dloss_dw2[i][j] += mWorld->dloss_dz[k][j]*mWorld->y[k][i];
						}
					}
				}
				// hidden layer (y) gradient
				//dloss_dy = w2.T*dloss_dz
				
				for(int i=0;i<5;i++)
				{
					for(int j=0; j< 6; j++)
					{
						mWorld->dloss_dy[i][j]=0.0f;
						for(int k=0; k< 5; k++)
						{
							mWorld->dloss_dy[i][j] +=mWorld->dloss_dz[k][i]*w2[j][k];
						}
					}
				}
				//dy_da = sigmoid_derivative(y)
				
				for(int i=0;i<5;i++)
				{
					for(int j=0; j< 6; j++)
					{
						mWorld->dy_da[i][j]=tf->sigmoid_derivative(mWorld->y[i][j]);
					}
				}
				//dloss_da = dloss_dy * dy_da
				
				for(int i=0;i<6;i++)
				{
					for(int j=0; j< 5; j++)
					{
						mWorld->dloss_da[j][i] = mWorld->dloss_dy[j][i]*mWorld->dy_da[j][i];
					}
				}
				
				//dloss_dw1 = np.dot(dloss_da, x.T)
				
				for(int i=0;i<9;i++)
				{
					for(int j=0; j< 6; j++)
					{
						mWorld->dloss_dw1[i][j]=0.0f;
						for(int k=0; k< 5; k++)
						{
							mWorld->dloss_dw1[i][j] += mWorld->dloss_da[j][k]*x[k][i];
						}
					}
				}
				//perform weight update
				//w1 -= dloss_dw1 * learning_rate
				for(int i=0;i<9;i++)
				{
					for(int j=0; j< 6; j++)
					{
						w1[i][j]-=(mWorld->dloss_dw1[i][j]*0.001f);
					}
				}
				//w2 -= dloss_dw2 * learning_rate
				for(int i=0;i<6;i++)
				{
					for(int j=0; j< 5; j++)
					{
						w2[i][j]-=(mWorld->dloss_dw2[i][j]*0.001f);
					}
				}

				/*
				string W2 ="w2_readable";
				string w2_readable;
				ostringstream readconvert_w2;
				readconvert_w2 << k;
				w2_readable = readconvert_w2.str();
				string exd_w2 = ".txt";
				W2.append(w2_readable );
				W2.append(exd_w2);
				ofstream outtxt_w2( W2 );
				for(int i=0;i<6;i++){
					for(int j=0;j<5;j++){
						outtxt_w2 << w2[i][j] << flush;
						
					}
					outtxt_w2 << endl;
				}
				
				outtxt_w2.close();
				*/
				// perform bias update
				//b1 -= sum(dloss_da, axis=1).reshape(sizeof[hidden layer], 1) * learning_rate
				
				for(int i=0;i<6;i++)
				{
					for(int j=0; j< 5; j++)
					{
						mWorld->sum_dloss_da[i]+=(mWorld->dloss_da[i][j]);
					}
				}
				
				for(int i=0;i<6;i++)
				{
				    b1[i]-=(mWorld->sum_dloss_da[i]*0.001);
				}
				//b2 -= sum(dloss_dz, axis=1).reshape(sizeof[output layer], 1) * learning_rate
				
				for(int i=0;i<5;i++)
				{
					for(int j=0; j<4; j++)
					{
						mWorld->sum_dloss_dz[i]+=(mWorld->dloss_dz[i][j]);
					}
				}
				for(int i=0;i<4;i++)
				{
				    b2[i]-=(mWorld->sum_dloss_dz[i]*0.001);
				}

	


}
int Tank::prediction(int x[6][10], float w1[10][7], float w2[7][5], float b1[7], float b2[5])
{
				//# FEEDFORWARD
				//# reshape array in order to easily calculate dot product
				//w1*x + b1
				float z_1[6][7];
				for(int i=0;i<5;i++)//for the output
				{
					for(int j=0; j< 6; j++)
					{
						z_1[i][j]=0.0f;
						for(int k=0; k< 9; k++)
						{
							z_1[i][j] += x[i][k]*w1[k][j];
						}
						z_1[i][j]+= b1[j];
					}
				}
				//y_ij = sigmoid(z_1_ij)
				tf = new tensorflow(mWorld);
				float y[6][7];
				for(int i=0; i<6;i++){
					for(int j=0; j<6; j++)
					{
						y[i][j]=tf->sigmoid(z_1[i][j]);
					}
				}
				float z[6][5];
				//z = w2*y + b2
				for(int i=0;i<5;i++)//for the output
				{
					for(int j=0; j< 4; j++)
					{
						z[i][j]=0.0f;
						for(int k=0; k< 6; k++)
						{
							z[i][j] += w2[k][j]*y[i][k];
						}
						z[i][j]+= b2[j];
					}
				}
				float p[6][5];
				float M[6];
				for(int i=0;i<5;i++)//for the output
				{
					M[i]=INT_FAST16_MIN;
					for(int j=0; j< 4; j++){
						if(z[i][j]>M[i])
							M[i]=z[i][j];
					}
					
				}
				float softsum[6];
				for(int i=0;i<5;i++)//for the output
				{
					for(int j=0; j< 4; j++)
					{
						softsum[i]+= (z[i][j]-M[i]);
					}
					
				}
				//p = apply_along_axis(softmax, 0, z)
				for(int i=0;i<5;i++)//for the output
				{
					for(int j=0; j< 4; j++)
					{
						p[i][j]= tf->softmax(z[i][j]-M[i],softsum[i]);
					}
				}
				float Max = INT_FAST16_MIN;
				int tmp =0;
				for(int j=0; j< 4; j++)
					{
						if(p[4][j]>Max)
							tmp=j;
					}
	return tmp;
}

/*Store inputs*/
void
Tank::store(int c, int m, int i, int j)
{

}

/* Creates user tank entity and node */
void
Tank::createUserTank(void)
{

    //movObjs[0] = new MovingObject(SceneManager(),"U","Cube.mesh", NULL);
    //movObjs[0]->setScale(Ogre::Vector3(10,10,10));
    //movObjs[0]->setPosition(Ogre::Vector3(100,100,100));

    mMovingObjects[std::string("U")] =  new MovingObject(SceneManager(),"U","Cube.mesh", NULL);
    mMovingObjects[std::string("U")]->setScale(Ogre::Vector3(10,10,10));
    mMovingObjects[std::string("U")]->setPosition(Ogre::Vector3(100,100,-100));
   
    mMainNode =  mMovingObjects[std::string("U")];
 //   mMainNode = SceneManager()->getRootSceneNode()->createChildSceneNode("U");
	//Ogre::Entity *tankEntity = SceneManager()->createEntity("Utank","Cube.mesh");
	//mTankNode = mMainNode;
	////mTankNode = mMainNode->createChildSceneNode("U");
	////mTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("U");
	//mTankNode->attachObject(tankEntity);
	//mTankNode->scale(10,10,10);
	//mTankNode->setPosition(100,100,100);
	// //mWorld->mHumanPlayer=mTankNode;
	///* DEBUGGING PURPOSES */
	//mTankNode->showBoundingBox(false);
	//mAABB = &tankEntity->getWorldBoundingBox();

 //   mOBB = new OBB(tankEntity->getBoundingBox());
 //   mOBB->setScale(mTankNode->getScale());
 //   mOBB->setOrientation(mTankNode->getOrientation());
 //   mOBB->setPosition(mTankNode->getPosition());

	////mWorld->SceneManager()->getSceneNode("U");
	////->getRootSceneNode()->getChild("U");
}


/* Creates enemy tank entity and node */
void
Tank::createEnemyTank(int i)
{
	int Number = i;       // number to be converted to a string
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream

	ID.append(Result);
	//Node *node = new Node();
	Node *node = new Node();
	Ogre::SceneNode *eTankNode;
	Ogre::Entity *tank = SceneManager()->createEntity(ID,"Tank.mesh");
	
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode(ID);
	eTankNode->setPosition(mWorld->spawnPoints[i]);
	eTankNode->attachObject(tank);
	eTankNode->scale(20, 20, 20);
	
	node->eTankNode = eTankNode;


	/* Push new tank node onto AI tank list */
	mWorld->Push(node);
}
/* Creates enemy tank entity and node */
void
Tank::createEnemyshell(int i)
{

	//Node *node = new Node();
	Node *node = new Node();
	Ogre::SceneNode *eTankNode;
	Ogre::Entity *tank = SceneManager()->createEntity("Penguin.mesh");
	
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode();
	//eTankNode->setPosition(mWorld->spawnPoints[i]);

	int u=i%80;
	float V=0.5f;
	eTankNode->setPosition(1000*cos(u)+1000*cos(u/2)*cos(u)*(V),1000*sin(u)+1000*cos(u/2)*sin(u)*(V),1000*sin(u/2)*(V));
	eTankNode->setOrientation(Orientation(Binormal(u, V),Normal(u, V),Tangent(u,V)));
	eTankNode->translate(Normal(u, V)*30);
	eTankNode->attachObject(tank);
	eTankNode->scale(1, 1, 1);
	
}
/* Creates enemy tank entity and node */

Ogre::Vector3 Tank::Normal(float u, float v){
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
Ogre::Vector3 Tank::Tangent(float u, float v){
	float kappa = 1;
	
	float A=kappa*(-sin(u)+ v*((-1/2)*sin(u/2)*cos(u)-cos(u/2)*sin(u)));
	float B=kappa*(cos(u)+ v*((-1/2)*sin(u/2)*sin(u)+cos(u/2)*cos(u)));
	float C=kappa*((v/2)*cos(u/2));
	Ogre::Vector3 T = Ogre::Vector3(A,B,C);
	return T;
}
Ogre::Vector3 Tank::Binormal(float u, float v){
	float kappa = 1;
	
	float D=kappa*(cos(u/2)*cos(u));
	float E=kappa*(cos(u/2)*sin(u));
	float F=kappa*(sin(u/2));
	Ogre::Vector3 B = Ogre::Vector3(D,E,F);
	return B;
}
Ogre::Matrix3 Tank::Orientation(Ogre::Vector3 xBasis, Ogre::Vector3 yBasis, Ogre::Vector3 zBasis){
    Ogre::Matrix3 rotate;
    rotate.FromAxes(xBasis, yBasis, zBasis);
	return rotate;
}
void
Tank::destroyTank(Node *node)
{
	node->eTankNode->detachAllObjects();
	int temp = mWorld->getUserScore();
	temp++;
	mWorld->setUserScore(++temp);

}
void
Tank::destroyshell(Node *node)
{
	node->eTankNode->detachAllObjects();
	int temp = mWorld->getUserScore();
	mWorld->setUserScore(++temp);
}

void
Tank::respawnEnemyTank(Node *node)
{
	Ogre::Entity *tankEntity = SceneManager()->createEntity("coin.mesh");
	node->eTankNode->attachObject(tankEntity);
}

void Tank::move(const Ogre::Real time) {
	Ogre::SceneNode* sceneNode = getSceneNode();
	sceneNode->translate(getvelocity() * getSpeed() * time);
	sceneNode->roll(Ogre::Degree(mSpin*time));
}

void Tank::load() {
	Ogre::SceneManager* sceneManager = getSceneManager();
	Ogre::Entity* entity = sceneManager->createEntity("Icosphere.mesh");
	setEntity(entity);
}

void Tank::reverseHorizontalvelocity() {
	setvelocity(getvelocity() * HORIZONTAL_REVERSE_FACTOR);
}

void Tank::reverseVerticalvelocity() {
	setvelocity(getvelocity() * VERTICAL_REVERSE_FACTOR);
}

void Tank::reset() {
	setPosition(pong_0_POSITION);
	setSpeed(pong_0_SPEED);
}

void Tank::createBackground() {
       
    // Create background material
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("space.jpg");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
 
    // Create background rectangle covering the whole screen
    Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
    rect->setCorners(-1.0, 1.0, 1.0, -1.0);
    rect->setMaterial("Background");
 
    // Render the background before everything else
    rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
 
    // Use infinite AAB to always stay visible
    Ogre::AxisAlignedBox aabInf;
    aabInf.setInfinite();
    rect->setBoundingBox(aabInf);
 
    // Attach background to the scene
    Ogre::SceneNode* New_node = SceneManager()->getRootSceneNode()->createChildSceneNode("Background");
    New_node->attachObject(rect);
}

OBB* Tank::createOBB(Node *node, Ogre::Entity *entity, Ogre::SceneNode *scene) {
    OBB *tmpOBB = new OBB(entity->getBoundingBox());
    tmpOBB->setScale(scene->getScale());
    tmpOBB->setOrientation(scene->getOrientation());
    tmpOBB->setPosition(scene->getPosition());

    return tmpOBB;

}

void Tank::createStaticObjects(Node *node, Ogre::Entity *entity, Ogre::SceneNode *scene) {
    
	node = new Node();
	entity = SceneManager()->createEntity("StaticCube1","Penguin.mesh");
	scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube1");
	scene->attachObject(entity);
	scene->scale(1, 1, 1);
	node->eTankNode = scene;
	mWorld->Push(node);
	scene->setPosition(1000*cos(1)+1000*cos(1/2)*cos(1)*(1/3),1000*sin(1)+1000*cos(1/2)*sin(1)*(1/3),1000*sin(1/2)*(1/3));
	scene->translate(Normal(1, 1/3)*30);
	scene->setOrientation(Orientation(Binormal(1, 1/3),Normal(1, 1/3),Tangent(1,1/3)));

    node->obb = createOBB(node,entity,scene);
	//////////////////////////////////////////////////////////////////////////

	node = new Node();
	entity = SceneManager()->createEntity("StaticCube2","Penguin.mesh");
	scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube2");
	scene->attachObject(entity);
	scene->scale(1, 1, 1);
	node->eTankNode = scene;
	mWorld->Push(node);
	scene->setPosition(1000*cos(80)+1000*cos(1/2)*cos(80)*(1/3),1000*sin(80)+1000*cos(1/2)*sin(80)*(1/3),1000*sin(1/2)*(1/3));
	scene->translate(Normal(80, 1/3)*30);
	scene->setOrientation(Orientation(Binormal(80, 1/3),Normal(80, 1/3),Tangent(80,1/3)));

    node->obb = createOBB(node,entity,scene);
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	entity = SceneManager()->createEntity("StaticCube3","Cube.mesh");
	scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube3");
	scene->attachObject(entity);
	scene->scale(1, 1, 1);
	node->eTankNode = scene;
	mWorld->Push(node);
	float u =40;
	float v =0.3;
	scene->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	scene->translate(Normal(u, v)*30);
	scene->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));

    node->obb = createOBB(node,entity,scene);
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	entity = SceneManager()->createEntity("StaticCube4","Sphere.mesh");

	scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube4");
	scene->attachObject(entity);
	scene->scale(100, 100, 100);
	node->eTankNode = scene;
	mWorld->Push(node);
	u =30;
	v =0.2;
	scene->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	scene->translate(Normal(u, v)*30);
	scene->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));

    node->obb = createOBB(node,entity,scene);
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	entity = SceneManager()->createEntity("StaticCube5","coin.mesh");
	scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube5");
	//eTankNode->setPosition(mWorld->spawnPoints[20]);
	scene->attachObject(entity);
	scene->scale(1, 1, 1);
	node->eTankNode = scene;
	mWorld->Push(node);
	u =20;
	v =0.1;
	scene->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	scene->translate(Normal(u, v)*30);
	scene->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));

    node->obb = createOBB(node,entity,scene);
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	entity = SceneManager()->createEntity("StaticCube6","Penguin.mesh");
	scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube6");
	//scene->setPosition(mWorld->spawnPoints[20]);
	scene->attachObject(entity);
	scene->scale(1, 1, 1);
	node->eTankNode = scene;
	mWorld->Push(node);
	scene->setPosition(1000*cos(10)+1000*cos(1/2)*cos(10)*(1/3),1000*sin(10)+1000*cos(1/2)*sin(10)*(1/3),1000*sin(1/2)*(1/3));
	scene->translate(Normal(10, 1/3));
	scene->setOrientation(Orientation(Binormal(10, 1/3),Normal(10, 1/3),Tangent(10,1/3)));

    node->obb = createOBB(node,entity,scene);

    ///////////////////////////////////////////
    /// Start for loop for generic static cubes
    ///////////////////////////////////////////
	for(int s=7;s<100;s++)
	{
	    string ID = "StaticCube";
	    string Result;          // string which will contain the result  
	    ostringstream convert;
	    convert << s;      // insert the textual representation of 'Number' in the characters in the stream
	    Result = convert.str(); // set 'Result' to the contents of the stream
	    ID.append(Result);
	    node = new Node();
	    entity = SceneManager()->createEntity(ID,"coin.mesh");
	    scene = SceneManager()->getRootSceneNode()->createChildSceneNode(ID);
	    scene->attachObject(entity);
	    scene->scale(1, 1, 1);
	    node->eTankNode = scene;
	    mWorld->Push(node);
	    //u =s%120;
	    u=s;
	    if(rand()%2==0)
	    v =(rand()%10)/100.0f-0.1;
	    else
		    v =-(rand()%10)/100.0f-0.1;
	    scene->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	    scene->translate(Normal(u, v)*1);
	    scene->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));
        node->obb = createOBB(node,entity,scene);
	}
}

void Tank::createStaticObjects2(Node *node, Ogre::Entity *entity, Ogre::SceneNode *scene) {
    /*

    mStaticObjects[std::string("StaticCube1")] = new StaticObject(mSceneManager,"StaticCube1","Penguin.mesh",NULL);
    mStaticObjects[std::string("StaticCube1")]->setScale(Ogre::Vector3(3,3,3));
    mStaticObjects[std::string("StaticCube1")]->setPosition(Ogre::Vector3(1000*cos(1)+1000*cos(1/2)*cos(1)*(1/3),1000*sin(1)+1000*cos(1/2)*sin(1)*(1/3),1000*sin(1/2)*(1/3)));
    mStaticObjects[std::string("StaticCube1")]->translate(Normal(1, 1/3));
    mStaticObjects[std::string("StaticCube1")]->setOrientation(Orientation(Binormal(1, 1/3),Normal(1, 1/3),Tangent(1,1/3)));

    //node->obb = createOBB(node,entity,scene);
	//////////////////////////////////////////////////////////////////////////

	//node = new Node();
	//entity = SceneManager()->createEntity("StaticCube2","Penguin.mesh");
	//scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube2");
	//scene->attachObject(entity);
	//scene->scale(1, 1, 1);
	//node->eTankNode = scene;
	//mWorld->Push(node);
	//scene->setPosition(1000*cos(80)+1000*cos(1/2)*cos(80)*(1/3),1000*sin(80)+1000*cos(1/2)*sin(80)*(1/3),1000*sin(1/2)*(1/3));
	//scene->translate(Normal(80, 1/3)*30);
	//scene->setOrientation(Orientation(Binormal(80, 1/3),Normal(80, 1/3),Tangent(80,1/3)));

 //   node->obb = createOBB(node,entity,scene);

    mStaticObjects[std::string("StaticCube2")] = new StaticObject(mSceneManager,"StaticCube2","Penguin.mesh",NULL);
    mStaticObjects[std::string("StaticCube2")]->setScale(Ogre::Vector3(3,3,3));
    mStaticObjects[std::string("StaticCube2")]->setPosition(Ogre::Vector3(1000*cos(80)+1000*cos(1/2)*cos(80)*(1/3),1000*sin(80)+1000*cos(1/2)*sin(80)*(1/3),1000*sin(1/2)*(1/3)));
    //mStaticObjects[std::string("StaticCube2")]->translate(Normal(80, 1/3));
    mStaticObjects[std::string("StaticCube2")]->setOrientation(Orientation(Binormal(80, 1/3),Normal(80, 1/3),Tangent(80,1/3)));

		//////////////////////////////////////////////////////////////////////////
	//node = new Node();
	//entity = SceneManager()->createEntity("StaticCube3","Cube.mesh");
	//scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube3");
	//scene->attachObject(entity);
	//scene->scale(1, 1, 1);
	//node->eTankNode = scene;
	//mWorld->Push(node);
	float u =40;
	float v =0.3;
	//scene->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	//scene->translate(Normal(u, v)*30);
	//scene->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));

 //   node->obb = createOBB(node,entity,scene);

    mStaticObjects[std::string("StaticCube3")] = new StaticObject(mSceneManager,"StaticCube3","Penguin.mesh",NULL);
    mStaticObjects[std::string("StaticCube3")]->setScale(Ogre::Vector3(3,3,3));
    mStaticObjects[std::string("StaticCube3")]->setPosition(Ogre::Vector3(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v)));
   // mStaticObjects[std::string("StaticCube3")]->translate(Normal(u, v));
    mStaticObjects[std::string("StaticCube3")]->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));

		//////////////////////////////////////////////////////////////////////////
	//node = new Node();
	//entity = SceneManager()->createEntity("StaticCube4","Sphere.mesh");

	//scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube4");
	//scene->attachObject(entity);
	//scene->scale(100, 100, 100);
	//node->eTankNode = scene;
	//mWorld->Push(node);
	u =30;
	v =0.2;
	//scene->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	//scene->translate(Normal(u, v)*30);
	//scene->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));

 //   node->obb = createOBB(node,entity,scene);

    mStaticObjects[std::string("StaticCube4")] = new StaticObject(mSceneManager,"StaticCube4","Sphere.mesh",NULL);
    mStaticObjects[std::string("StaticCube4")]->setScale(Ogre::Vector3(3,3,3));
    mStaticObjects[std::string("StaticCube4")]->setPosition(Ogre::Vector3(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v)));
   // mStaticObjects[std::string("StaticCube4")]->translate(Normal(u, v));
    mStaticObjects[std::string("StaticCube4")]->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));

		//////////////////////////////////////////////////////////////////////////
	//node = new Node();
	//entity = SceneManager()->createEntity("StaticCube5","coin.mesh");
	//scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube5");
	////eTankNode->setPosition(mWorld->spawnPoints[20]);
	//scene->attachObject(entity);
	//scene->scale(1, 1, 1);
	//node->eTankNode = scene;
	//mWorld->Push(node);
	u =20;
	v =0.1;
	//scene->setPosition(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v));
	//scene->translate(Normal(u, v)*30);
	//scene->setOrientation(Orientation(BiCnormal(u, v),Normal(u, v),Tangent(u,v)));

 //   node->obb = createOBB(node,entity,scene);

    mStaticObjects[std::string("StaticCube5")] = new StaticObject(mSceneManager,"StaticCube5","coin.mesh",NULL);
    mStaticObjects[std::string("StaticCube5")]->setScale(Ogre::Vector3(3,3,3));
    mStaticObjects[std::string("StaticCube5")]->setPosition(Ogre::Vector3(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v)));
    //mStaticObjects[std::string("StaticCube5")]->translate(Normal(u, v));
    mStaticObjects[std::string("StaticCube5")]->setOrientation(Orientation(Binormal(u, v),Normal(u, v),Tangent(u,v)));

		//////////////////////////////////////////////////////////////////////////
	//node = new Node();
	//entity = SceneManager()->createEntity("StaticCube6","Penguin.mesh");
	//scene = SceneManager()->getRootSceneNode()->createChildSceneNode("StaticCube6");
	////scene->setPosition(mWorld->spawnPoints[20]);
	//scene->attachObject(entity);
	//scene->scale(1, 1, 1);
	//node->eTankNode = scene;
	//mWorld->Push(node);
	//scene->setPosition(1000*cos(10)+1000*cos(1/2)*cos(10)*(1/3),1000*sin(10)+1000*cos(1/2)*sin(10)*(1/3),1000*sin(1/2)*(1/3));
	//scene->translate(Normal(10, 1/3)*30);
	//scene->setOrientation(Orientation(Binormal(10, 1/3),Normal(10, 1/3),Tangent(10,1/3)));

 //   node->obb = createOBB(node,entity,scene);

    mStaticObjects[std::string("StaticCube6")] = new StaticObject(mSceneManager,"StaticCube6","Penguin.mesh",NULL);
    mStaticObjects[std::string("StaticCube6")]->setScale(Ogre::Vector3(3,3,3));
    mStaticObjects[std::string("StaticCube6")]->setPosition(Ogre::Vector3(1000*cos(10)+1000*cos(1/2)*cos(10)*(1/3),1000*sin(10)+1000*cos(1/2)*sin(10)*(1/3),1000*sin(1/2)*(1/3)));
   // mStaticObjects[std::string("StaticCube6")]->translate(Normal(10, 1/3));
    mStaticObjects[std::string("StaticCube6")]->setOrientation(Orientation(Binormal(10, 1/3),Normal(10, 1/3),Tangent(10,1/3)));
	*/
    ///////////////////////////////////////////
    /// Start for loop for generic static cubes
    ///////////////////////////////////////////
	for(int s=7;s<81;s++)
	{
	    string ID = "StaticCube";
	    string Result;          // string which will contain the result  
	    ostringstream convert;
	    convert << s;      // insert the textual representation of 'Number' in the characters in the stream
	    Result = convert.str(); // set 'Result' to the contents of the stream
	    ID.append(Result);
	    //node = new Node();
	    //entity = SceneManager()->createEntity(ID,"coin.mesh");
	    //scene = SceneManager()->getRootSceneNode()->createChildSceneNode(ID);
	    //scene->attachObject(entity);
	    //scene->scale(0.3f, 0.3f, 0.3f);
        mStaticObjects[std::string(ID.c_str())] = new StaticObject(mSceneManager,ID.c_str(),"coin.mesh",NULL);
        mStaticObjects[std::string(ID.c_str())]->setScale(Ogre::Vector3(100,100,100));
	    //node->eTankNode = scene;
	    //mWorld->Push(node);
	    //u =s%120;


		int v;
	    int u=s;
	    if(rand()%2==0)
	      v =(rand()%10)/100.0f-0.1;
	    else
		    v =-(rand()%10)/100.0f-0.1;
        mStaticObjects[std::string(ID.c_str())]->setPosition(Ogre::Vector3(1000*cos(u)+1000*cos(1/2)*cos(u)*(v),1000*sin(u)+1000*cos(1/2)*sin(u)*(v),1000*sin(1/2)*(v)));
        //mStaticObjects[std::string(ID.c_str())]->translate(Normal(u, v));
		Ogre::Matrix3 k =mStaticObjects[std::string(ID.c_str())]->getOrientation();
        mStaticObjects[std::string(ID.c_str())]->setOrientation(Orientation(Binormal(u, v),-Tangent(u,v),Normal(u, v)));
        //node->obb = createOBB(node,entity,scene);
		//mStaticObjects[std::string(ID.c_str())]->translate(Normal(u, v)*6);
	}
}

void
Tank::setMovObjs() {

    for (int i = 0; i < 30; i++) {
        movObjs[i] = NULL;
    }
}

void
Tank::setStatObjs() {

    for (int i = 0; i < 30; i++) {
        statObjs[i] = NULL;
    }
}
void
Tank::createAICubesOld() {
	int Number = 0;       // number to be converted to a string
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);

	Node *node = new Node();
	Ogre::SceneNode *eTankNode;
	Ogre::Entity *tank = SceneManager()->createEntity("AItank1","Cube.mesh");
	mAI1 = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank1");
	mAI1->setPosition(mWorld->spawnPoints[1]);
	mAI1->attachObject(tank);
	mAI1->scale(10, 10, 10);

	Ogre::Vector3 XBasis = Ogre::Vector3(-1,0, 0);
    Ogre::Vector3 YBasis = Ogre::Vector3(0,-1 ,0);
    Ogre::Vector3 ZBasis = Ogre::Vector3(0,0,1);
    Ogre::Matrix3 R;
    R.FromAxes(XBasis, YBasis, ZBasis);
	mAI1->setOrientation(R);

	node->eTankNode = mAI1;
    mWorld->Push(node);

	Ogre::Real time=mWorld->t;


	//////////////////////////////////////////////////////////////////////////
    Number = 1;       // number to be converted to a string
	Result;          // string which will contain the result  
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	node = new Node();
	
	tank = SceneManager()->createEntity("AItank0","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank0");
	eTankNode->setPosition(mWorld->spawnPoints[0]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);

	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);

	//////////////////////////////////////////////////////////////////////////
	Number = 2;       // number to be converted to a string
	Result;          // string which will contain the result
	convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	node = new Node();
	tank = SceneManager()->createEntity("AItank2","Cube.mesh");
	mAI2 = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank2");
	mAI2->setPosition(mWorld->spawnPoints[2]);
	mAI2->attachObject(tank);
	mAI2->scale(10, 10, 10);
	node->eTankNode = mAI2;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	Number = 3;       // number to be converted to a string
	Result;          // string which will contain the result
	convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	ID.append(Result);
	node = new Node();
	tank = SceneManager()->createEntity("AItank3","Cube.mesh");
	mAI3 = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank3");
	mAI3->setPosition(mWorld->spawnPoints[3]);
	mAI3->attachObject(tank);
	mAI3->scale(10, 10, 10);
	node->eTankNode = mAI3;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);

	/////////////////////////////////////////////////////////////////////////
	/*
	node = new Node();
	tank = SceneManager()->createEntity("AItank4","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank4");
	eTankNode->setPosition(mWorld->spawnPoints[4]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank5","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank5");
	eTankNode->setPosition(mWorld->spawnPoints[5]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank6","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank6");
	eTankNode->setPosition(mWorld->spawnPoints[6]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank7","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank7");
	eTankNode->setPosition(mWorld->spawnPoints[7]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank8","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank8");
	eTankNode->setPosition(mWorld->spawnPoints[8]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank9","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank9");
	eTankNode->setPosition(mWorld->spawnPoints[9]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank10","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank10");
	eTankNode->setPosition(mWorld->spawnPoints[10]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank11","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank11");
	eTankNode->setPosition(mWorld->spawnPoints[11]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);

	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank12","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank12");
	eTankNode->setPosition(mWorld->spawnPoints[12]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank13","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank13");
	eTankNode->setPosition(mWorld->spawnPoints[13]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank14","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank14");
	eTankNode->setPosition(mWorld->spawnPoints[14]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank15","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank15");
	eTankNode->setPosition(mWorld->spawnPoints[15]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank16","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank16");
	eTankNode->setPosition(mWorld->spawnPoints[16]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank17","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank17");
	eTankNode->setPosition(mWorld->spawnPoints[17]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank18","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank18");
	eTankNode->setPosition(mWorld->spawnPoints[18]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
		//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank19","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank19");
	eTankNode->setPosition(mWorld->spawnPoints[19]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	time=mWorld->t;
	mWorld->Push(node);
	//////////////////////////////////////////////////////////////////////////
	node = new Node();
	tank = SceneManager()->createEntity("AItank20","Cube.mesh");
	eTankNode = SceneManager()->getRootSceneNode()->createChildSceneNode("AItank20");
	eTankNode->setPosition(mWorld->spawnPoints[20]);
	eTankNode->attachObject(tank);
	eTankNode->scale(10, 10, 10);
	node->eTankNode = eTankNode;
    node->obb = createOBB(node,tank,eTankNode);
	mWorld->Push(node);*/
}

void
Tank::createAICubes() {

    int numCont = 7;
    const char * base = "AItank";
    Ogre::Real time;
    for (int i = 0; i <= 20; i++) {
        std::string tmp = base + std::to_string(i);
        //movObjs[i + numCont] = 
        //movObjs[i + numCont]->setPosition(mWorld->spawnPoints[i]);
        //movObjs[i + numCont]->setScale(Ogre::Vector3(10,10,10));

        mMovingObjects[std::string(tmp.c_str())] = new MovingObject(SceneManager(),tmp.c_str(),"Cube.mesh", NULL);
        mMovingObjects[std::string(tmp.c_str())]->setPosition(mWorld->spawnPoints[i]);
        mMovingObjects[std::string(tmp.c_str())]->setScale(Ogre::Vector3(10,10,10));
    
	    time=mWorld->t;
    }
}

MovingObject*
    Tank::getMovingObject(std::string name) {

        return mMovingObjects[name];

}

StaticObject*
    Tank::getStaticObject(std::string name) {

        return mStaticObjects[name];

}
