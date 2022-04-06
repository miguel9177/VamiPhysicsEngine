#include "ColliderFunctions.h"

//if a sphere and a cube collided
CollisionInformation CheckBoxWithSphere(Collider& boxCollider1, Collider& sphereCollider)
{
	//FOR THE CHECKING COLLISION BETWEEN SPHERE AND AAAB BOX I USED THIS LINK https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#point_vs._aabb
	// get box closest point to sphere center by clamping
	float x = std::max(boxCollider1.positionOfCollider.x - boxCollider1.ReturnSize().x, std::min(sphereCollider.positionOfCollider.x, boxCollider1.positionOfCollider.x + boxCollider1.ReturnSize().x));
	float y = std::max(boxCollider1.positionOfCollider.y - boxCollider1.ReturnSize().y, std::min(sphereCollider.positionOfCollider.y, boxCollider1.positionOfCollider.y + boxCollider1.ReturnSize().y));
	float z = std::max(boxCollider1.positionOfCollider.z - boxCollider1.ReturnSize().z, std::min(sphereCollider.positionOfCollider.z, boxCollider1.positionOfCollider.z + boxCollider1.ReturnSize().z));

	// this will know the distance beetween the sphere and the box collider
	float distance = std::sqrt((x - sphereCollider.positionOfCollider.x) * (x - sphereCollider.positionOfCollider.x) +
		(y - sphereCollider.positionOfCollider.y) * (y - sphereCollider.positionOfCollider.y) +
		(z - sphereCollider.positionOfCollider.z) * (z - sphereCollider.positionOfCollider.z));

	//float distance2 = glm::distance(glm::vec3(x, y, z), sphereCollider.positionOfCollider);

	//if the distance is less then radius then we have a collision, if we have draw the information if we are in debug mode and return the information about the collision
	if (distance < (sphereCollider.ReturnRadius()))
	{
		//this will create the collision information, to return
		CollisionInformation tempRealCollisionInfo;
		//say that it collided
		tempRealCollisionInfo.collided = true;
		//store the colliders
		tempRealCollisionInfo.colliders[0] = &sphereCollider;
		tempRealCollisionInfo.colliders[1] = &boxCollider1;
		//get the normal of the collision and then store it
		glm::vec3 normal = glm::normalize(glm::vec3(x,y,z)- sphereCollider.positionOfCollider);
		
		//MIGUEL FIX FOR TABLE BUT IT BREAKS EVERY CUBE WITH SPHERE IS HERE, THE PROBLEM IS THE NORMAL SHOULD ONLY BE AFFECTING THE Y ON THE TABLE
		//normal.x = 0; normal.z = 0;

		tempRealCollisionInfo.collisionNormal = normal;
		
		//get the collision point. formula pos+normal*radius, IN THE FUTURE WE PROBABLY WILL NEED TO DO THE SAME FOR THE OTHER COLLIDER, WE MAY WANT TO KNOW MULTIPLE COLLISION POINTS
		tempRealCollisionInfo.collisionPoint = sphereCollider.positionOfCollider + normal;
		//get the penetration depth
		tempRealCollisionInfo.penetrationDepth = std::fabs(sphereCollider.ReturnRadius() - distance);

		

		//return the collision info
		return tempRealCollisionInfo;
		
	}

	CollisionInformation tempFalseCollisionInfo;
	tempFalseCollisionInfo.collided = false;
	return tempFalseCollisionInfo;
}

//if a box collided with a box
CollisionInformation CheckBoxWithBox(Collider& boxCollider1, Collider& boxCollider2)
{
	

	//Get the minimum positions from both boxes
	float xMin = boxCollider1.positionOfCollider.x - boxCollider1.ReturnSize().x; float xMin2 = boxCollider2.positionOfCollider.x - boxCollider2.ReturnSize().x;
	float yMin = boxCollider1.positionOfCollider.y - boxCollider1.ReturnSize().y; float yMin2 = boxCollider2.positionOfCollider.y - boxCollider2.ReturnSize().y;
	float zMin = boxCollider1.positionOfCollider.z - boxCollider1.ReturnSize().z; float zMin2 = boxCollider2.positionOfCollider.z - boxCollider2.ReturnSize().z;

	//Get the max positions from both boxes
	float xMax = boxCollider1.positionOfCollider.x + boxCollider1.ReturnSize().x; float xMax2 = boxCollider2.positionOfCollider.x + boxCollider2.ReturnSize().x;
	float yMax = boxCollider1.positionOfCollider.y + boxCollider1.ReturnSize().y; float yMax2 = boxCollider2.positionOfCollider.y + boxCollider2.ReturnSize().y;
	float zMax = boxCollider1.positionOfCollider.z + boxCollider1.ReturnSize().z; float zMax2 = boxCollider2.positionOfCollider.z + boxCollider2.ReturnSize().z;



	//FOR this if i used this LINK https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#point_vs._aabb
	//if a collision happened return the information about the collision and draw debug collision info if debug is on
	if ((xMin <= xMax2 && xMax >= xMin2) &&
		(yMin <= yMax2 && yMax >= yMin2) &&
		(zMin <= zMax2 && zMax >= zMin2))
	{
		//this will create the collision information, to return
		CollisionInformation tempRealCollisionInfo;
		//say that it collided
		tempRealCollisionInfo.collided = true;
		//store the colliders
		tempRealCollisionInfo.colliders[0] = &boxCollider1;
		tempRealCollisionInfo.colliders[1] = &boxCollider2;

		//THIS PART WAS TAKEN FROM https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/physicstutorials/4collisiondetection/Physics%20-%20Collision%20Detection.pdf page 15
		
		//this will get the normal for each face (left, right, bottom, top, far, near)
		static const glm::vec3 normalfaces[6] =
		{
			glm::vec3(-1, 0, 0), 
			glm::vec3(1, 0, 0),

			glm::vec3(0, -1, 0),
			glm::vec3(0, 1, 0),

			glm::vec3(0, 0, -1),
			glm::vec3(0, 0, 1),
		};

		//this will get all of the distances from box 1 to box 2 (left, right, bottom, top, far, near) this needs to be with the same order has the normal faces
		float penetrations[6] =
		{
			(xMax2 - xMin),// distance of box ’b’ to ’left ’ of ’a ’.
			(xMax - xMin2),// distance of box ’b’ to ’right ’ of ’a ’.

			(yMax2 - yMin),// distance of box ’b’ to ’bottom ’ of ’a ’.
			(yMax - yMin2),// distance of box ’b’ to ’top ’ of ’a ’.

			(zMax2 - zMin),// distance of box ’b’ to ’far ’ of ’a ’.
			(zMax - zMin2) // distance of box ’b’ to ’near ’ of ’a ’.
		};

		/*i use float max, for it to always enter the if of the first loop below, since it checks if the current penetration is smaller then penetration depth, since this will be the maximum value possible for a float
		(3.40282347e+38) and it will always enter the first if*/
		tempRealCollisionInfo.penetrationDepth = FLT_MAX;

		//do a loop trough every penetration and  normal faces, and store the normals and penetration depth of the smallest penetration
		for (int i = 0; i < 6; i++)
		{
			//if the penetration is smaller then the current penetration depth store the penetration depth and collision normal, with this will always use the smallest penetration, and that is what we want
			if (penetrations[i] < tempRealCollisionInfo.penetrationDepth) {
				tempRealCollisionInfo.penetrationDepth = penetrations[i];
				tempRealCollisionInfo.collisionNormal = normalfaces[i];
			}
		}

		//get the collision point. formula pos+normal
		tempRealCollisionInfo.collisionPoint = boxCollider2.positionOfCollider + tempRealCollisionInfo.collisionNormal;

		//return the collision info
		return tempRealCollisionInfo;

	}

	CollisionInformation tempFalseCollisionInfo;
	tempFalseCollisionInfo.collided = false;
	return tempFalseCollisionInfo;
}


//if its a sphere with sphere collision
CollisionInformation CheckSphereWithSphere(Collider& sphereCollider1, Collider& sphereCollider2)
{

	//create the variables that are going to store the distance and the radius sum
	float distance = 0.f;
	float radiusSum = 0.f;
	//do the calculation for the radius Sum (add both radius)
	radiusSum = sphereCollider1.ReturnRadius() + sphereCollider2.ReturnRadius();
	
	//get the distance between both vectors
	distance = glm::distance(sphereCollider2.positionOfCollider, sphereCollider1.positionOfCollider);

	//if the distance is less then the radius sum is because we are colliding with the other collider in this case a sphere
	if (distance < radiusSum)
	{
		//this will create the collision information, to return
		CollisionInformation tempRealCollisionInfo;
		//say that it collided
		tempRealCollisionInfo.collided = true;
		//store the colliders
		tempRealCollisionInfo.colliders[0] = &sphereCollider1;
		tempRealCollisionInfo.colliders[1] = &sphereCollider2;
		//get the normal of the collision and then store it
		glm::vec3 normal = glm::normalize(sphereCollider2.positionOfCollider - sphereCollider1.positionOfCollider);
		tempRealCollisionInfo.collisionNormal = normal;

		//get the collision point. formula pos+normal*radius, IN THE FUTURE WE PROBABLY WILL NEED TO DO THE SAME FOR THE OTHER COLLIDER, WE MAY WANT TO KNOW MULTIPLE COLLISION POINTS
		tempRealCollisionInfo.collisionPoint = sphereCollider1.positionOfCollider + normal * sphereCollider1.ReturnRadius();
		//get the penetration depth
		tempRealCollisionInfo.penetrationDepth = radiusSum - distance;

		//return the collision info
		return tempRealCollisionInfo;
	}

	
	//this will create a fake info, and return false, since it didnt collide
	CollisionInformation tempFalseCollisionInfo;
	tempFalseCollisionInfo.collided = false;
	return tempFalseCollisionInfo;

}

//if a box collided with a oobb
CollisionInformation CheckBoxWithOobb(Collider& boxCollider1, Collider& oobbCollider2)
{
	std::cout << "COLLISION WITH OOBB BUT OOBB ISNT DONE YET" << std::endl;
	return CollisionInformation();
}

//if a sphere collided with a oobb
CollisionInformation CheckSphereWithOobb(Collider& sphereCollider1, Collider& oobbCollider2)
{
	std::cout << "COLLISION WITH OOBB BUT OOBB ISNT DONE YET" << std::endl;
	return CollisionInformation();
}

//if a oobb collided with a oobb
CollisionInformation CheckOobbWithOobb(Collider& oobbCollider1, Collider& oobbCollider2)
{
	std::cout << "COLLISION WITH OOBB BUT OOBB ISNT DONE YET" << std::endl;
	return CollisionInformation();
}

CollisionInformation CheckPlaneWithSphere(Collider& planeCollider1, Collider& sphereCollider1)
{	
	//FOR THE CHECKING COLLISION BETWEEN SPHERE AND Plane BOX I USED THIS LINK https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#point_vs._aabb
	// get box closest point to sphere center by clamping
	float x = std::max(planeCollider1.positionOfCollider.x - planeCollider1.ReturnSize().x, std::min(sphereCollider1.positionOfCollider.x, planeCollider1.positionOfCollider.x + planeCollider1.ReturnSize().x));
	//since this ais a plane the y is always 0 so i dont need to check y
	float y = std::max(planeCollider1.positionOfCollider.y, std::min(sphereCollider1.positionOfCollider.y, planeCollider1.positionOfCollider.y));
	float z = std::max(planeCollider1.positionOfCollider.z - planeCollider1.ReturnSize().z, std::min(sphereCollider1.positionOfCollider.z, planeCollider1.positionOfCollider.z + planeCollider1.ReturnSize().z));

	// this will know the distance beetween the sphere and the box collider
	float distance = std::sqrt((x - sphereCollider1.positionOfCollider.x) * (x - sphereCollider1.positionOfCollider.x) +
		(y - sphereCollider1.positionOfCollider.y) * (y - sphereCollider1.positionOfCollider.y) +
		(z - sphereCollider1.positionOfCollider.z) * (z - sphereCollider1.positionOfCollider.z));

	float distance2 = glm::distance(glm::vec3(x, y, z), sphereCollider1.positionOfCollider);

	//if the distance is less then radius then we have a collision, if we have draw the information if we are in debug mode and return the information about the collision
	if (distance < (sphereCollider1.ReturnRadius()))
	{
		//this will create the collision information, to return
		CollisionInformation tempRealCollisionInfo;
		//say that it collided
		tempRealCollisionInfo.collided = true;
		//store the colliders
		tempRealCollisionInfo.colliders[0] = &planeCollider1;
		tempRealCollisionInfo.colliders[1] = &sphereCollider1;
		//get the normal of the collision and then store it
		glm::vec3 normal = glm::normalize(sphereCollider1.positionOfCollider - glm::vec3(x, y, z));

		//MIGUEL FIX FOR TABLE BUT IT BREAKS EVERY CUBE WITH SPHERE IS HERE, THE PROBLEM IS THE NORMAL SHOULD ONLY BE AFFECTING THE Y ON THE TABLE
		//normal.x = 0; normal.z = 0;

		tempRealCollisionInfo.collisionNormal = normal;

		//get the collision point. formula pos+normal*radius, IN THE FUTURE WE PROBABLY WILL NEED TO DO THE SAME FOR THE OTHER COLLIDER, WE MAY WANT TO KNOW MULTIPLE COLLISION POINTS
		tempRealCollisionInfo.collisionPoint = sphereCollider1.positionOfCollider + normal;
		//get the penetration depth
		tempRealCollisionInfo.penetrationDepth = sphereCollider1.ReturnRadius() - distance;



		//return the collision info
		return tempRealCollisionInfo;

	}

	CollisionInformation tempFalseCollisionInfo;
	tempFalseCollisionInfo.collided = false;
	return tempFalseCollisionInfo;
}

CollisionInformation CheckPlaneWithOobb(Collider& planeCollider1, Collider& oobbCollider1)
{
	std::cout << "COLLISION PLANE WITH OOBB ISNT DONE YET" << std::endl;
	return CollisionInformation();
}

CollisionInformation CheckPlaneWithBox(Collider& planeCollider1, Collider& boxCollider1)
{
	//std::cout << "COLLISION PLANE WITH BOX ISNT DONE YET" << std::endl;

	//Get the minimum positions from both boxes
	float xMin = planeCollider1.positionOfCollider.x - planeCollider1.ReturnSize().x; float xMin2 = boxCollider1.positionOfCollider.x - boxCollider1.ReturnSize().x;
	float yMin = planeCollider1.positionOfCollider.y; float yMin2 = boxCollider1.positionOfCollider.y - boxCollider1.ReturnSize().y;
	float zMin = planeCollider1.positionOfCollider.z - planeCollider1.ReturnSize().z; float zMin2 = boxCollider1.positionOfCollider.z - boxCollider1.ReturnSize().z;

	//Get the max positions from both boxes
	float xMax = planeCollider1.positionOfCollider.x + planeCollider1.ReturnSize().x; float xMax2 = boxCollider1.positionOfCollider.x + boxCollider1.ReturnSize().x;
	float yMax = planeCollider1.positionOfCollider.y; float yMax2 = boxCollider1.positionOfCollider.y + boxCollider1.ReturnSize().y;
	float zMax = planeCollider1.positionOfCollider.z + planeCollider1.ReturnSize().z; float zMax2 = boxCollider1.positionOfCollider.z + boxCollider1.ReturnSize().z;



	//FOR this if i used this LINK https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#point_vs._aabb
	//if a collision happened return the information about the collision and draw debug collision info if debug is on
	if ((xMin <= xMax2 && xMax >= xMin2) &&
		(yMin <= yMax2 && yMax >= yMin2) &&
		(zMin <= zMax2 && zMax >= zMin2))
	{
		//this will create the collision information, to return
		CollisionInformation tempRealCollisionInfo;
		//say that it collided
		tempRealCollisionInfo.collided = true;
		//store the colliders
		tempRealCollisionInfo.colliders[0] = &planeCollider1;
		tempRealCollisionInfo.colliders[1] = &boxCollider1;

		//THIS PART WAS TAKEN FROM https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/physicstutorials/4collisiondetection/Physics%20-%20Collision%20Detection.pdf page 15

		//this will get the normal for each face (left, right, bottom, top, far, near)
		static const glm::vec3 normalfaces[6] =
		{
			glm::vec3(-1, 0, 0),
			glm::vec3(1, 0, 0),

			glm::vec3(0, -1, 0),
			glm::vec3(0, 1, 0),

			glm::vec3(0, 0, -1),
			glm::vec3(0, 0, 1),
		};

		//this will get all of the distances from box 1 to box 2 (left, right, bottom, top, far, near) this needs to be with the same order has the normal faces
		float penetrations[6] =
		{
			(xMax2 - xMin),// distance of box ’b’ to ’left ’ of ’a ’.
			(xMax - xMin2),// distance of box ’b’ to ’right ’ of ’a ’.

			(yMax2 - yMin),// distance of box ’b’ to ’bottom ’ of ’a ’.
			(yMax - yMin2),// distance of box ’b’ to ’top ’ of ’a ’.

			(zMax2 - zMin),// distance of box ’b’ to ’far ’ of ’a ’.
			(zMax - zMin2) // distance of box ’b’ to ’near ’ of ’a ’.
		};

		/*i use float max, for it to always enter the if of the first loop below, since it checks if the current penetration is smaller then penetration depth, since this will be the maximum value possible for a float
		(3.40282347e+38) and it will always enter the first if*/
		tempRealCollisionInfo.penetrationDepth = FLT_MAX;

		//do a loop trough every penetration and  normal faces, and store the normals and penetration depth of the smallest penetration
		for (int i = 0; i < 6; i++)
		{
			//if the penetration is smaller then the current penetration depth store the penetration depth and collision normal, with this will always use the smallest penetration, and that is what we want
			if (penetrations[i] < tempRealCollisionInfo.penetrationDepth) {
				tempRealCollisionInfo.penetrationDepth = penetrations[i];
				tempRealCollisionInfo.collisionNormal = normalfaces[i];
			}
		}

		//get the collision point. formula pos+normal
		tempRealCollisionInfo.collisionPoint = planeCollider1.positionOfCollider + tempRealCollisionInfo.collisionNormal;

		//return the collision info
		return tempRealCollisionInfo;

	}

	CollisionInformation tempFalseCollisionInfo;
	tempFalseCollisionInfo.collided = false;
	return tempFalseCollisionInfo;
	return CollisionInformation();
	
}

CollisionInformation CheckPlaneWithPlane(Collider& planeCollider1, Collider& planeCollider2)
{
	//std::cout << "COLLISION PLANE WITH PLANE ISNT DONE YET" << std::endl;
	//Get the minimum positions from both planes
	float xMin = planeCollider1.positionOfCollider.x - planeCollider1.ReturnSize().x; float xMin2 = planeCollider2.positionOfCollider.x - planeCollider2.ReturnSize().x;
	float yMin = planeCollider1.positionOfCollider.y - 0.1f; float yMin2 = planeCollider2.positionOfCollider.y - 0.1f;
	float zMin = planeCollider1.positionOfCollider.z - planeCollider1.ReturnSize().z; float zMin2 = planeCollider2.positionOfCollider.z - planeCollider2.ReturnSize().z;

	//Get the max positions from both planes
	float xMax = planeCollider1.positionOfCollider.x + planeCollider1.ReturnSize().x; float xMax2 = planeCollider2.positionOfCollider.x + planeCollider2.ReturnSize().x;
	float yMax = planeCollider1.positionOfCollider.y + 0.1f; float yMax2 = planeCollider2.positionOfCollider.y + 0.1f;
	float zMax = planeCollider1.positionOfCollider.z + planeCollider1.ReturnSize().z; float zMax2 = planeCollider2.positionOfCollider.z + planeCollider2.ReturnSize().z;



	//FOR this if i used this LINK https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#point_vs._aabb
	//if a collision happened return the information about the collision and draw debug collision info if debug is on
	if ((xMin <= xMax2 && xMax >= xMin2) &&
		(yMin <= yMax2 && yMax >= yMin2) &&
		(zMin <= zMax2 && zMax >= zMin2))
	{
		//this will create the collision information, to return
		CollisionInformation tempRealCollisionInfo;
		//say that it collided
		tempRealCollisionInfo.collided = true;
		//store the colliders
		tempRealCollisionInfo.colliders[0] = &planeCollider1;
		tempRealCollisionInfo.colliders[1] = &planeCollider2;

		//THIS PART WAS TAKEN FROM https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/physicstutorials/4collisiondetection/Physics%20-%20Collision%20Detection.pdf page 15

		//this will get the normal for each face (left, right, bottom, top, far, near)
		static const glm::vec3 normalfaces[6] =
		{
			glm::vec3(-1, 0, 0),
			glm::vec3(1, 0, 0),

			glm::vec3(0, -1, 0),
			glm::vec3(0, 1, 0),

			glm::vec3(0, 0, -1),
			glm::vec3(0, 0, 1),
		};

		//this will get all of the distances from box 1 to box 2 (left, right, bottom, top, far, near) this needs to be with the same order has the normal faces
		float penetrations[6] =
		{
			(xMax2 - xMin),// distance of planes ’b’ to ’left ’ of ’a ’.
			(xMax - xMin2),// distance of planes ’b’ to ’right ’ of ’a ’.

			(yMax2 - yMin),// distance of planes ’b’ to ’bottom ’ of ’a ’.
			(yMax - yMin2),// distance of planes ’b’ to ’top ’ of ’a ’.

			(zMax2 - zMin),// distance of planes ’b’ to ’far ’ of ’a ’.
			(zMax - zMin2) // distance of planes ’b’ to ’near ’ of ’a ’.
		};

		/*i use float max, for it to always enter the if of the first loop below, since it checks if the current penetration is smaller then penetration depth, since this will be the maximum value possible for a float
		(3.40282347e+38) and it will always enter the first if*/
		tempRealCollisionInfo.penetrationDepth = FLT_MAX;

		//do a loop trough every penetration and  normal faces, and store the normals and penetration depth of the smallest penetration
		for (int i = 0; i < 6; i++)
		{
			//if the penetration is smaller then the current penetration depth store the penetration depth and collision normal, with this will always use the smallest penetration, and that is what we want
			if (penetrations[i] < tempRealCollisionInfo.penetrationDepth) {
				tempRealCollisionInfo.penetrationDepth = penetrations[i];
				tempRealCollisionInfo.collisionNormal = normalfaces[i];
			}
		}

		//get the collision point. formula pos+normal
		tempRealCollisionInfo.collisionPoint = planeCollider1.positionOfCollider + tempRealCollisionInfo.collisionNormal;

		//return the collision info
		return tempRealCollisionInfo;

	}

	CollisionInformation tempFalseCollisionInfo;
	tempFalseCollisionInfo.collided = false;
	return tempFalseCollisionInfo;
}
