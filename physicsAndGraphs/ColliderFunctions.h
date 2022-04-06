#pragma once
#include "Collider.h"
#include "GameEngine.h"
#include <algorithm>

//THIS SCRIPT HAS ALL OF THE COLLISION CHECKING FOR EVERY COLLIDER, THIS IS CALLED BY THE CHILDREN COLLIDER ITSEL FROM THE FUNCTION CHECKCOLLISION

//if a sphere and a cube collided
CollisionInformation CheckBoxWithSphere(Collider& boxCollider1, Collider& sphereCollider);
//if a box collided with a box
CollisionInformation CheckBoxWithBox(Collider& boxCollider1, Collider& boxCollider2);
//if a box collided with a box
CollisionInformation CheckBoxWithOobb(Collider& boxCollider1, Collider& oobbCollider2);
//if its a sphere with sphere collision
CollisionInformation CheckSphereWithSphere(Collider& sphereCollider1, Collider& sphereCollider2);
//if its a sphere with sphere collision
CollisionInformation CheckSphereWithOobb(Collider& sphereCollider1, Collider& oobbCollider2);
//if its a sphere with sphere collision
CollisionInformation CheckOobbWithOobb(Collider& oobbCollider1, Collider& oobbCollider2);
//if its a sphere with sphere collision
CollisionInformation CheckPlaneWithSphere(Collider& planeCollider1, Collider& sphereCollider1);
//if its a sphere with sphere collision
CollisionInformation CheckPlaneWithOobb(Collider& planeCollider1, Collider& oobbCollider1);
//if its a sphere with sphere collision
CollisionInformation CheckPlaneWithBox(Collider& planeCollider1, Collider& boxCollider1);
//if its a sphere with sphere collision
CollisionInformation CheckPlaneWithPlane(Collider& planeCollider1, Collider& planeCollider2);
