#pragma once
#include "Physics.h"

glm::vec3 GetInterDepth(Physics one, Physics two);

void checkCollision(Physics &one, Physics &two);

void handleCollision(Physics &one, Physics &two);