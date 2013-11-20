/*
* This is the main file that will be commited
*/


//variables
float myPos[3], // {x, y, z} coordinates of our robot
	otherPos[3], // {x, y, z} coordinates of their robot
	nullList[3], //{0, 0, 0}
	otherZRState[12], //ZRState of opponent
	ourZRState[12],  //ZRState of us
	myVel[3], //Vector for velocity
	otherVel[3],//Opponent's velocity vector
	distFromTarget, //used for setPositionSpeed
	initialDistance; //used for setPositionSpeed

//depricated game.getTime();
//int timeElapsed;
int sphereColor; //1 for blue -1 for red

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*Basic utility functions
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


/**
*This function calculates the absolute value of a given number
*@param number This is the number to be absolute-valued
*@return The distance from zero that the parameter is
*@author davidLi
*/
float aV(float number){
	if(number < 0)	{
		number = -number;
	}
	return number;
} 

/**
*This function determines what color you are by setting the iAmRed variable
*@author chrisHuaman
*/

/**
* @deprecated setSphere is replacement
*/

// void whatColor(){	
// 
// api.getMyZRState( myZRState );
// if(timeElapsed == 0){
// 	//If x is > 0 then you are blue, set iAmRed to false
// 	if(myZRState[0]/*x coord*/ > 0 ){iAmRed = false;}//ur blue
// 	else{iAmRed = true;}
// }	
// 



/**
* This function sets the sphereColor variable
* @param myState current position of robot
* @author jim
*/

int setSphere(ZRState myState){
	//if is red
	if (myState[0] < 0) {
		return -1; //red
	} else {
		return 1; //blue
	}
}

/**
* This function determines whether or not you are in peril of being kicked out of bounds
* @param zeroForYourselfoneForOther Who you are testing for in peril
* @return True if you are in peril, false if you are not
* @author davidLi
*/

bool inPeril(int zeroForYourselfoneForOther){
	float test[3];
	if(zeroForYourselfoneForOther == 0)	{
		test[0] = myPos[0];
		test[1] = myPos[1];
		test[2] = myPos[2];
	}
else{
		test[0] = otherPos[0];
		test[1] = otherPos[1];
		test[2] = otherPos[2];
	}
	
return (aV(test[0]) > .48) || (aV(test[1]) > .64) || (aV(test[2]) > .48);
}


/**
* This function takes you out of bounds when pushed
* @author davidLi
*/

void gOOOOB(){ //get out of out of bounds

	float targetvelocity[3];
	
	if(inPeril(0)){

		for(int i=0; i < 3; ++i){
			targetvelocity[i] = -2*myPos[i];
		}
		api.setPositionTarget(nullList);
		api.setVelocityTarget(targetvelocity);
	}
}

/**
* Collects essential information 
* @author davidlLi
*/

void getInfo(){

	 api.getOtherZRState(otherZRState);
	 api.getMyZRState(ourZRState);

	 myPos[0] = ourZRState[0];
	 myPos[1] = ourZRState[1]; 
	 myPos[2] = ourZRState[2];
	 myVel[0] = ourZRState[3]; 
	 myVel[1] = ourZRState[4]; 
	 myVel[2] = ourZRState[5];
	 
	 otherPos[0] = otherZRState[0]; otherPos[1] = otherZRState[1]; otherPos[2] = otherZRState[2];
	 otherVel[0] = otherZRState[3]; otherVel[1] = otherZRState[4]; otherVel[2] = otherZRState[5];


}

/**
* shorthand way to setPositionTarget()
* @param xC x coordinate to travel to 
* @param yC y coordinate to travel to 
* @param zC z coordinate to travel to 
* @author davidLi
*/
void QG(float xC, float yC, float zC){

	float loc[3], distance;
	loc[0] = xC;
	loc[1] = yC;
	loc[2] = zC;
	distance = sqrtf((loc[0] - myPos[0])*(loc[0] - myPos[0])+(loc[1] - myPos[1])*(loc[1] - myPos[1])+(loc[2] - myPos[2])*(loc[2] - myPos[2]));

	if(distance > 0.02){
		api.setPositionTarget(loc);
	}else{
		DEBUG(("You are hitting f*ing wood! \n"));
	}
}
		

/**
*This function is called once at the beginning of the simulation
* @author
*/

/**
* Sets the values of a given array 
* @param Float to shove values into
* @param Value to shove into index[0]
* @param Value to shove into index[1]
* @param Value to shove into index[2]
* @author jim
*/
void setValues (float array[3], float a, float b, float c){
	array[0] = a;
	array[1] = b;
	array[2] = c;

}

/**

This function returns the distance between two points in space
@param object1[3] First object for comparison
@param object2[3] Second object for comparison
@return Distance between the two objects

*/

float getDistBetween(float object1[3], float object2[3]){
	
	float xDist = fabsf(object1[0] - object2[0]), //just x distance
		yDist = fabsf(object1[1] - object2[1]), //just y distance
		zDist = fabsf(object1[2] - object2[2]); //just z distance

		float distance = (mathSquare(xDist)+mathSquare(yDist)+mathSquare(zDist)); //needs to be square-rooted

		
		return sqrtf(distance);
}


/**
* Determines if a point is close to another point
*
* @param target[3] first point for comparison
* @param object[3] second point for comparison
* @param distance between the objects to be considered "close"
* @return true if the two objects are within a certain distance false otherwise
* @author jim
*/

bool isClose(float target[3], float object[3], float distance) {
	
	float xDist = object[0] - target[0],
		yDist = object[1] - target[1],
		zDist = object[2] - target[2];
	if(aV(xDist*xDist	+ yDist*yDist + zDist*zDist) <= (distance*distance)){
		
		return true;
	}
	
	return false;
}

/**
* Determines if a value on an axis is close to another
*
* @param target first point for comparison
* @param object second point for comparison
* @param distance between the objects to be considered "close"
* @return true if the two values are within a certain distance false otherwise
* @author jim
*/


bool isClose(float target, float object, float distance) {
	
	if (aV(target - object) < distance){
		return true;
	} else {
		return false;
	}
	
}


/**
*This function acts as an api.setPositionTarget() but has a speed parameter
*@param targetPos[3] Position desired to go to
*@param speed length of the vector that you wish to go to
*
*/
void setPositionSpeed(float targetPos[3], float speed){
	
	

	float speedXDist = targetPos[0] - myPos[0],
		speedYDist = targetPos[1] - myPos[1],
		speedZDist = targetPos[2] - myPos[2]; //gathers components of distance

	if(initialDistance == -69.0f){
		initialDistance = getDistBetween(myPos, targetPos);

		
	}

	float directionVector[] = {speedXDist, speedYDist, speedZDist};
	float negativeDirectionVector[] = {-speedXDist, -speedYDist, -speedZDist};

	mathVecNormalize(directionVector, speed);

	
	
	if(isClose(targetPos, myPos, .1f)){
		
		api.setPositionTarget(targetPos);

	} else if(getDistBetween(myPos, targetPos) < initialDistance/2){

		api.setVelocityTarget(negativeDirectionVector);
		
	}

	 else{
		api.setVelocityTarget(directionVector);
		
	}
	


}



void init(){

	nullList[0] = 0;
	nullList[1] = 0;
	nullList[2] = 0;

	initialDistance = -69.0f;
}

/**
* This function is called once per second
* Most implementation of functions will go here
*/
void loop(){

	getInfo();
	setSphere(ourZRState);
	/*Code vvvv  */


	setPositionSpeed(nullList, .02f);
}