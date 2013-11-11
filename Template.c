/*
* This is the main file that will be commited
*/


//variables
float myZRState[12], myPos[3], otherPos[3], nullList[3],positionOther[12], positionOurs[12], myVel[3], otherVel[3];
int timeElapsed;
bool iAmRed;

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*Basic utility functions
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


/**
*This function calculates the absolute value of a given number
*@param number This is the number to be absolute-valued
*@return The distance from zero that the parameter is
*@author 
*/
float aV(float number){
	if(number < 0)	{
		number = -number;
	}
	return number;
} 

/**
*This function determines what color you are by setting the iAmRed variable
*@author
*/
void whatColor(){	
	
	api.getMyZRState( myZRState );
	if(timeElapsed == 0){
		//If x is > 0 then you are blue, set iAmRed to false
		if(myZRState[0]/*x coord*/ > 0 ){iAmRed = false;}//ur blue
		else{iAmRed = true;}
	}	
}

/**
* This function determines whether or not you are in peril of being kicked out of bounds
* @param zeroForYourselfoneForOther Who you are testing for in peril
* @return True if you are in peril, false if you are not
* @author
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
* @author
*/

void gOOOOB() //get out of out of bounds
{
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
* @author
*/

void getInfo(){

 api.getOtherZRState(positionOther);
 api.getMyZRState(positionOurs);
 myPos[0] = positionOurs[0]; myPos[1] = positionOurs[1]; myPos[2] = positionOurs[2];
 myVel[0] = positionOurs[3]; myVel[1] = positionOurs[4]; myVel[2] = positionOurs[5];
 otherPos[0] = positionOther[0]; otherPos[1] = positionOther[1]; otherPos[2] = positionOther[2];
 otherVel[0] = positionOther[3]; otherVel[1] = positionOther[4]; otherVel[2] = positionOther[5];

}

/**
* shorthand way to setPositionTarget()
* @param xC x coordinate to travel to 
* @param yC y coordinate to travel to 
* @param zC z coordinate to travel to 
* @author
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

void init(){

timeElapsed = 0;
nullList[0] = 0;
nullList[1] = 0;
nullList[2] = 0;

}

/**
* This function is called once per second
* Most implementation of functions will go here
*/
void loop(){

	getInfo();
	whatColor();
	/*Code vvvv  */
	
	
    QG(0,0,0);
    
    /*Syntacies ~ and ~ functions:
    DON'T TOUCH ANYTHING IN VOID LOOP THAT IS OUTSIDE CODE!
    Your position is myPos[3] Other position is otherPos[3]. 
	Your velocity is myVel[3] Other velocity is otherVel[3]
	iAmRed tells you if you are red.True if red, else false
	QG(float x, float y, float z) is a convenient function
    that goes to a location without needing to store a list
    aV() is absolute value function; timeElapsed is time elapsed
    No need to avoid out of bounds; already have gOOOOB()
	*/
	
	
	
	
	/*Code ^^^^  */
	gOOOOB();
	timeElapsed++;
}