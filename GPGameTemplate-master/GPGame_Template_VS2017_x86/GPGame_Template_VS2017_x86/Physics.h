#pragma once

#include <iostream>
#include <vector>
using namespace std;

// Helper graphic libraries
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"



class Physics {
public:
	
	Physics();
	// Init size
	Physics(glm::vec3 size);
	
	
	bool touchGround;

	// Define attributes
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 velocity;
	float mass;
};

//update velocity
void updateVelocity(Physics &obj, float deltaTime);

//updates position
void updatePosition(Physics &obj, float deltaTime);