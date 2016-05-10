/*Implement some functions that could be uesd in Tensorflow*/ 

#include "World.h"
#include "Tank.h"
#include "OgreVector3.h"
#include "tensorflow.h"
#include <math.h>
#include <algorithm> 
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

tensorflow::tensorflow(World *world) {
	mWorld = world;
	//orientation = mWorld->SceneManager()->getSceneNode("AItank0")->getOrientation();

}

tensorflow::~tensorflow()
{
    
}

void 
tensorflow::Think(const Ogre::Real& mTime)
{

}
float tensorflow::softmax(float a, float b){
	/*
		Takes a vector of arbitrary real-valued scores and squashes it to a vector of values 
		between zero and one that sum to one. This vector represents a probability distribution
		over mutually exclusive alternatives.
		Parameters
		----------
		z : numpy.ndarray
			a vector with real values that represent the scores of each class. 
		Returns
		-------
		numpy.ndarray
			 a vector of values between zero and one that sum to one.
		*/
		
		return exp(a)/b;

}
float tensorflow:: cross_entropy_loss(float a, float b)
{
	return 0.0f;
}

float tensorflow::sigmoid(float x)
{
	/*
		A function that takes a real-valued number and "squashes" it into range between 0 and 1, so
		that large negative numbers become 0 and large positive numbers become 1.  
		Parameters
		----------
		x : numpy.ndarray
			an array of real values, each of them is given as an argument to the sigmoid function.
		Returns
		-------
		numpy.ndarray
			an array of real values that are "squashed" into range between 0 and 1 by the function.
	*/
		if (x >= 0){
			float z;
			z = exp(-x);
			return 1 / (1 + z);
		}
		else{
			// if x is less than zero then z will be small, denominator can't be zero because it's 1+z
			float z;	
			z = exp(x);
			return z / (1 + z);
		}
}
float tensorflow::sigmoid_derivative(float x)
{
	return sigmoid(x)*(1-sigmoid(x));
}


float tensorflow::relu(float x)
{
	return max(0.0f,x);
}

tensorflow::Variable::Variable(float initial){
	this->initial = initial;

}