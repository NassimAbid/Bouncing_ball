#include "Collision.h"
#include <cmath>
#include <iostream>


// detects collosion if there is any between the current object and all other objects in the scene
void checkCollision(Physics &currobj, Physics &SecondObj) {
		

		//multiplied by 0.5 as only half of the size from the center to get to the edge.
		bool collosionx = currobj.position.x + (currobj.size.x * 0.5) + (SecondObj.size.x * 0.5) >= SecondObj.position.x &&
			SecondObj.position.x + (SecondObj.size.x * 0.5) + (currobj.size.x * 0.5) >= currobj.position.x;

		bool collosiony = currobj.position.y + (currobj.size.y * 0.5) + (SecondObj.size.y * 0.5) >= SecondObj.position.y &&
			SecondObj.position.y + (SecondObj.size.y * 0.5) + (currobj.size.y * 0.5) >= currobj.position.y;

		bool collosionz = currobj.position.z + (currobj.size.z * 0.5) + (SecondObj.size.z * 0.5) >= SecondObj.position.z &&
			SecondObj.position.z + (SecondObj.size.z * 0.5) + (currobj.size.z * 0.5) >= currobj.position.z;

		if (collosionx && collosiony && collosionz) {
			handleCollision(currobj, SecondObj);
		}

	
}


void handleCollision(Physics &one, Physics &two) {
	glm::vec3 interDepth = GetInterDepth(one, two);
	one.position += interDepth;

	// Reduce velocity because of absorption
	one.velocity *= glm::vec3(0.8f, 0.8f, 0.8f);


	if (interDepth.x != 0.0f)
		one.velocity.x *= -1.0f;

	if (interDepth.y != 0.0f)
		one.velocity.y *= -1.0f;

	if (interDepth.z != 0.0f)
		one.velocity.z *= -1.0f;
}


glm::vec3 GetInterDepth(Physics one, Physics two) {


	// this function calculates intersection on both direcctions. currobj time from the first object 
	//and another time from the second object. This is used later on to determine how the objects
	//interact with eachother to give an organic bounce
	float xInter = (one.size.x * 0.5) - (one.position.x - (two.position.x + (two.size.x * 0.5)));
	float yInter = (one.size.y * 0.5) - (one.position.y - (two.position.y + (two.size.y * 0.5)));
	float zInter = (one.size.z * 0.5) - (one.position.z - (two.position.z + (two.size.z * 0.5)));


	//simply the inverse of the above.
	float InverxInter = (two.size.x * 0.5) - (two.position.x - (one.position.x + (one.size.x * 0.5)));
	float InveryInter = (two.size.y * 0.5) - (two.position.y - (one.position.y + (one.size.y * 0.5)));
	float InverzInter = (two.size.z * 0.5) - (two.position.z - (one.position.z + (one.size.z * 0.5)));


	
	//gets the min value
	glm::vec3 MinInter = glm::vec3(0.0f, 0.0f, 0.0f);
	
	float lowest = FLT_MAX;


	

	//checks intersection on the X axis is lowest
	if (xInter < yInter && xInter < zInter) {
		if (xInter < lowest)
			lowest = xInter;
			MinInter = glm::vec3(xInter, 0.0f, 0.0f);
	}
	
	//checks intersection on the Y axis is lowest
	if (yInter < xInter && yInter < zInter) {
		if (yInter < lowest)
			lowest = yInter;
			MinInter = glm::vec3(0.0f, yInter, 0.0f);
	}

	//checks intersection on the Z axis is lowest
	if (zInter < yInter && zInter < xInter) {
		if (zInter < lowest)
			lowest = zInter;
			MinInter = glm::vec3(0.0f, 0.0f, zInter);
	}

	//checks when the second object intersects the first and checks if the lowest value is lower

	if (InverxInter < InveryInter && InverxInter < InverzInter 
			&& InverxInter < lowest) {
		MinInter = glm::vec3(-InverxInter, 0.0f, 0.0f);
	}

	if (InveryInter < InverxInter && InveryInter < InverzInter
		&& InveryInter < lowest) {
		MinInter = glm::vec3(0.0f, -InveryInter, 0.0f);
	}

	if (InverzInter < InverxInter && InverzInter < InveryInter
		&& InverzInter < lowest) {
		MinInter = glm::vec3(0.0f, 0.0f, -InverzInter);
	}



	return MinInter;
}

