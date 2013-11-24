/*
* This is the main file that will be commited
*/


//variables
float myZRState[12], myPos[3], otherPos[3], nullList[3],positionOther[12], positionOurs[12], myVel[3], otherVel[3], loc[3]; //locAO and AT store previous locs
int timeElapsed, whichMap /*tells which map you are [1~4] and technically sometimes 0*/;
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
        if(number < 0)        {
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
//         //If x is > 0 then you are blue, set iAmRed to false
//         if(myZRState[0]/*x coord*/ > 0 ){iAmRed = false;}//ur blue
//         else{iAmRed = true;}
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
        if(zeroForYourselfoneForOther == 0)        {
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
* @author davidlLi
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
* @author davidLi
*/
void QG(float xC, float yC, float zC, float speed){

        float distance, vel[3];
        /*loc[0] = xC;
        loc[1] = yC;
        loc[2] = zC;*/ 
        setValues(loc, xC, yC, zC);
        setValues(vel, speed*(xC-myPos[0]),speed*(yC-myPos[1]), speed*(zC-myPos[2])); 
        distance = sqrtf((loc[0] - myPos[0])*(loc[0] - myPos[0])+(loc[1] - myPos[1])*(loc[1] - myPos[1])+(loc[2] - myPos[2])*(loc[2] - myPos[2]));

        if(distance > 0.05){
        api.setPositionTarget(loc);
        if(speed != 0)
        {
            api.setVelocityTarget(vel);
        }
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
        if(aV(xDist*xDist        + yDist*yDist + zDist*zDist) <= (distance*distance)){
                
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

void init(){

        timeElapsed = 0;
        setValues(nullList, 0,0,0);
				//Author == David Li
				float dFoZ[3], dFoT[3]; //Debris field of Zero and Two, respectively.
				game.getDebrisLocation(0, dFoZ);
				game.getDebrisLocation(2, dFoT);
				whichMap = -1; //Default value if not found in database.
				float dbZ[3][5] = {{0.3,0.35,0.1,0.45,0.25},{-0.3,-0.35,-0.4,-0.35,-0.4},{0.1,0.05,0.4,0.1,0.1}};
				float dbT[3][5] = {{0.1,0.1,0.25,0.25,0.35},{-0.3,-0.35,-0.25,-0.3,-0.35},{-0.4,-0.4,0.15,-0.4,-0.3}};
				for(int i = 0; i<=4; ++i)
				{
					if((dbZ[0][i] == dFoZ[0] && dbZ[1][i] == dFoZ[1] && dbZ[2][i] == dFoZ[2]) && (dbT[0][i] == dFoT[0] && dbT[1][i] == dFoT[1] && dbT[2][i] == dFoT[2]))
					{
						whichMap = i;
					}
				}

}

/**
* This function is called once per second
* Most implementation of functions will go here
*/
void loop(){
DEBUG(("%i", whichMap)); //!<warning!> This code will be pulled soon. -David
        getInfo();
        setSphere(myZRState);
        /*Code vvvv  */
        
        
    QG(0,0,0,1);
    
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
