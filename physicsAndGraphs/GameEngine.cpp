#include "GameEngine.h"

//THIS IS NEEDED BECAUSE WE DECLARED THIS VARIABLES AS STATIC, AND THEY NEED TO BE DEFIEND ON THE CPP
std::vector<GameObject*> GameEngine::objects;
std::vector<Collider*> GameEngine::colliders;
std::vector<CollisionInformation> GameEngine::collisionInformations;
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;
bool GameEngine::debugMode;
ForceGenerator* GameEngine::forceGenerator;
std::vector<std::vector<CollisionGrid>> GameEngine::broadPhaseGrid;
float GameEngine::sizeOfEachGridSquare;
float GameEngine::currentDeltaTime;

GameEngine::GameEngine()
{
    
}

//this will activate or deactivate debug mode
void GameEngine::ActivateOrDeactivateDebugMode(bool debugMode_)
{
    debugMode = debugMode_;
}

//update the objects and work out deltaTime between frames, it also adds force generator forces (gravity, etc) (called every frame)
void GameEngine::UpdateGame()
{
    //this will get the old elapsed time
    oldTimeSinceStart = newTimeSinceStart;
    //this will get the new elapsed time since the last time we got the old one
    newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    //delta time is equal to the difference of the new time minus the old time (time passed)
    float deltaTime_ = (newTimeSinceStart - oldTimeSinceStart);
    //we divide it by 1000 so that we have milleseconds
    deltaTime_ /= 1000.f;

    //put a limit on the delta time, to prevent bugs.
    if (deltaTime_ > 0.1f) {
        deltaTime_ = 0.1f;
    }
        
    currentDeltaTime = deltaTime_;
    
    //this will call the function that will check if a collision happened and if it did it will store the information
    CheckCollision();

    //do a loop to call every update method of every gameobject  
    for (int i = 0; i < objects.size(); ++i)
    {
        objects[i]->Update(deltaTime_);
    }



    //this will apply every gravity forces etc
    forceGenerator->UpdateObjectsForces();

    //this gonna call all of the updates of all of the gameplay scripts
    scriptManager::Update();
    
    glutPostRedisplay();
}

//this will be true after i run the broad phase one time, i use this so that the counter doesnt spam the console
bool d_runedOnce = false;
//this will count how many times the broad phase loop is runed
int d_counterOfBigOBroadPhase = 0;

//this will do the collision checking and it will be called o the update game function
void GameEngine::CheckCollision()
{
    //Values alreadyChecked is for me to not repeat the same checks
    int valuesAlreadyChecked = 0;

    //this will do the broad phase by checking where a object is on the grid, and add him to that grid square
    BroadPhase();
    
    //this is for debug purposes only, and its for me to be able to know the big O
    int counterCollideCheck = 0;
   
 

    //this double loop will go trough every grid cube, if the cub doesnt have 2 objects we will have a early out, if the grid cube has 2 or more colliders, we will check for a collision
    for (int x = 0; x < broadPhaseGrid.size(); x++)
    {
        for (int y = 0; y < broadPhaseGrid[0].size(); y++)
        {
            //early out, if theres no even 2 colliders in this grid cube, we dont need to check collision since theres only one or zero objects here
            if(broadPhaseGrid[x][y].collidersOnThisGridSpace.size() < 2)
            {continue;}
            //since theres 2 or more colliders in this grid cube, we cehck for collision
            else {

                //double loop to go troigh every object on the grid cube
                for (int i = 0; i < broadPhaseGrid[x][y].collidersOnThisGridSpace.size(); i++)
                {
                    //if theres no colliders in this object do early out
                    if (broadPhaseGrid[x][y].collidersOnThisGridSpace[i]==nullptr)
                        continue;

                    for (int j = 0; j < broadPhaseGrid[x][y].collidersOnThisGridSpace.size(); j++)
                    {

                        //if tthe collider is a null ptr, or they are th same, just continue, since we dont want to check the same colliders
                        if (broadPhaseGrid[x][y].collidersOnThisGridSpace[j] == nullptr || broadPhaseGrid[x][y].collidersOnThisGridSpace[i] == broadPhaseGrid[x][y].collidersOnThisGridSpace[j])
                            continue;

                        //remove collision from the same object 
                        if (broadPhaseGrid[x][y].collidersOnThisGridSpace[j]->gameObjectOfCollider == broadPhaseGrid[x][y].collidersOnThisGridSpace[i]->gameObjectOfCollider)
                            continue;

                        counterCollideCheck = counterCollideCheck + 1;

                        //store the information about the collision
                        CollisionInformation tempCollisionInfo = broadPhaseGrid[x][y].collidersOnThisGridSpace[i]->CollideCheck(*broadPhaseGrid[x][y].collidersOnThisGridSpace[j]);
                        //if a collision happened
                        if (tempCollisionInfo.collided)
                        {
                            //this will store the collision information
                            collisionInformations.push_back(tempCollisionInfo);
                        }
                     
                    }
                    
                }

            }
        }
    }

    if(d_runedOnce == false)
        std::cout << "Big O of collisions is: " << counterCollideCheck << std::endl;

    d_runedOnce = true;
    CollisionResolution();
}

//this will resolve the collision by doing the calculations necessary this is called after the Check collision
void GameEngine::CollisionResolution()
{

    //do a loop trough every collision, and do the collision resolution
    for (int i = 0; i < collisionInformations.size(); i++)
    {
        //if debug mode change color since they are colliding
        if (IsDebugModeOn())
        {
            collisionInformations[i].colliders[0]->currentTextureId = 0;
            collisionInformations[i].colliders[1]->currentTextureId = 0;
        }

        //this will get what type of phisics body the game object are
        int physicsType1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnType();
        int physicsType2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnType();

        //if the collider is a trigger
        if (collisionInformations[i].colliders[0]->isTrigger == true)
        {
            scriptManager::OnTriggerEnter(collisionInformations[i].colliders[0], collisionInformations[i].colliders[1]);
            continue;
        }
        //if the collider is a trigger
        if (collisionInformations[i].colliders[1]->isTrigger == true)
        {
            scriptManager::OnTriggerEnter(collisionInformations[i].colliders[1], collisionInformations[i].colliders[0]);
            continue;
        }

        //if both colliders are particles
        if (physicsType1 == RigidBodyType::PARTICLE && physicsType2 == RigidBodyType::PARTICLE)
        {
            //get both velocitys from the objects
            glm::vec3 velocity1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnVelocity();
            glm::vec3 velocity2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnVelocity();

            //get both coeficient of restitution, value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided, this is the coefficient of restitution
            float E1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnCoefficientOfRestitution();
            float E2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnCoefficientOfRestitution();
            
            //get both masses
            float mass1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnMass();
            float mass2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnMass();
            
            //get the collision normal
            glm::vec3 normal = collisionInformations[i].collisionNormal;

            //get the average of the coefficient of restitution
            E1 = (E1 + E2) / 2;

            //do the first formula from last page of https://files.coventry.aula.education/f23319df03d347a8a0dc856d34bbe0a3particle_impulse___how_the_formula_is_derived.pdf
            float impulse1 = -(glm::dot((velocity1 - velocity2), normal) * (1+E1));
            impulse1 = impulse1 / (glm::dot(normal, normal) * ((1 / mass1) + (1 / mass2)));

            //do the first formula from last page but for the 2nd impulse of https://files.coventry.aula.education/f23319df03d347a8a0dc856d34bbe0a3particle_impulse___how_the_formula_is_derived.pdf
           /* float impulse2 = -(glm::dot((velocity1 - velocity2), normal) * (1 + E2));
            impulse2 = impulse2 / (glm::dot(normal, (normal * ((1 / mass1) + (1 / mass2)))));*/

            //this is going to get the velocity after collision 
            glm::vec3 velocityAfterCol1 = velocity1 + ((impulse1 / mass1) * normal);
            //this is going to get the velocity after collision 
            glm::vec3 velocityAfterCol2 = velocity2 - ((impulse1 / mass2) * normal);

            //IMPLEMENTING FRCITION, it will get the friction of the body that is colliding with and decrease velocity overtime.
            velocityAfterCol1 *= pow(collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnFriction(), currentDeltaTime);
            //IMPLEMENTING FRCITION, it will get the friction of the body that is colliding with and decrease velocity overtime.
            velocityAfterCol2 *= pow(collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnFriction(), currentDeltaTime);

            //VARIABLES TO FIX INTERPENETRATION
            //this will get how much the two objects has penetrated
            float penetrationDepth = collisionInformations[i].penetrationDepth;
           
            /*glm::vec3 position1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnPosition();

            //fix interpenetration, by moving the object the amount of penetration both objects have, it will use the normal to know where it needs to move
            collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->SetPosition(position1 - (normal * penetrationDepth));
            */

            //get both objects positions
            glm::vec3 position1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnPosition();
            glm::vec3 position2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnPosition();

            //if the current object is static, dont move him and move the other one
            if (collisionInformations[i].colliders[0]->gameObjectOfCollider->movable == true)
                //fix interpenetration, by moving the object the amount of penetration both objects have, it will use the normal to know where it needs to move
                collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->SetPosition(position1 - (normal * (penetrationDepth)));
            else
                collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->SetPosition(position2 + (normal * (penetrationDepth)));



            //std::cout << collisionInformations[i].penetrationDepth << std::endl;

            //if the current object is static, dont move him and move the other one
            if (collisionInformations[i].colliders[0]->gameObjectOfCollider->movable == true)
                //change the velocity directly for instant speed
                collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->SetVelocity(velocityAfterCol1);
            
            //if the current object is static, dont move him and move the other one
            if (collisionInformations[i].colliders[1]->gameObjectOfCollider->movable == true)
                collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->SetVelocity(velocityAfterCol2);
        }
        //if both colliders arent particles
        else
        {
            //for this i used this pdf given by the physics teacher https://files.coventry.aula.education/75013d79734251f4ed7195deba90205arigid_body_impulse___how_the_formula_is_derived.pdf
            
            //get both velocitys from the objects
            glm::vec3 velocity1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnVelocity();
            glm::vec3 velocity2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnVelocity();
            glm::vec3 velocityRelative = velocity1 - velocity2;

            //get both angular velocities
            glm::vec3 angularVelocity1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnAngularVelocity();
            glm::vec3 angularVelocity2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnAngularVelocity();

            //get both coeficient of restitution, value from 0 to 1, 0 means no bounce, 1 means bounce with the same speed it collided, this is the coefficient of restitution
            float E1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnCoefficientOfRestitution();
            float E2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnCoefficientOfRestitution();

            //get both masses
            float mass1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnMass();
            float mass2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnMass();

            float inertia1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnInertia();
            float inertia2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnInertia();

            //transform the inertia to a matrix
            glm::mat3 inertia1_;
            inertia1_[0][0] = inertia1;
            inertia1_[1][1] = inertia1;
            inertia1_[2][2] = inertia1;

            //transform the inertia to a matrix
            glm::mat3 inertia2_;
            inertia2_[0][0] = inertia2;
            inertia2_[1][1] = inertia2;
            inertia2_[2][2] = inertia2;

            //distance  from collision point to the centre of mass of object 1
            //float r1 = glm::distance(collisionInformations[i].colliders[0]->gameObjectOfCollider->g_position, collisionInformations[i].collisionPoint);
            glm::vec3 r1_ = collisionInformations[i].colliders[0]->gameObjectOfCollider->g_position - collisionInformations[i].collisionPoint;
            
            //float r2 = glm::distance(collisionInformations[i].colliders[1]->gameObjectOfCollider->g_position, collisionInformations[i].collisionPoint);
            glm::vec3 r2_ = collisionInformations[i].colliders[1]->gameObjectOfCollider->g_position - collisionInformations[i].collisionPoint;

            //get the collision normal
            glm::vec3 normal = collisionInformations[i].collisionNormal;


            //get the average of the coefficient of restitution
            E1 = (E1 + E2) / 2;

            //do the first formula from last page of https://files.coventry.aula.education/f23319df03d347a8a0dc856d34bbe0a3particle_impulse___how_the_formula_is_derived.pdf
            float impulse1 = -(glm::dot(velocityRelative, normal) * (1 + E1));
            impulse1 = impulse1 / ((1 / mass1) + (1 / mass2) + glm::dot(normal, glm::cross(glm::inverse(inertia1_) * glm::cross(r1_, normal), r1_)) + glm::dot(normal, glm::cross(glm::inverse(inertia2_) * glm::cross(r2_, normal),  r2_)));

           
                        
            //this is going to get the linear velocity after collision 
            glm::vec3 velocityAfterCol1 = velocity1 + ((impulse1 / mass1) * normal);
            //this is going to get the linear velocity after collision 
            glm::vec3 velocityAfterCol2 = velocity2 - ((impulse1 / mass2) * normal);

            //IMPLEMENTING FRCITION, it will get the friction of the body that is colliding with and decrease velocity overtime.
            velocityAfterCol1 *= pow(collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnFriction(), currentDeltaTime);
            //IMPLEMENTING FRCITION, it will get the friction of the body that is colliding with and decrease velocity overtime.
            velocityAfterCol2 *= pow(collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnFriction(), currentDeltaTime);

            //this is going to get the angular velocity after collision 
            glm::vec3 angularVelocityAfterCol1 = angularVelocity1 + (glm::inverse(inertia1_) * (glm::cross(r1_, impulse1 * normal)));
            glm::vec3 angularVelocityAfterCol2 = angularVelocity2 - (glm::inverse(inertia2_) * (glm::cross(r2_, impulse1 * normal)));

            //VARIABLES TO FIX INTERPENETRATION
            //this will get how much the two objects has penetrated
            float penetrationDepth = collisionInformations[i].penetrationDepth;
           
            //get both objects positions
            glm::vec3 position1 = collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnPosition();
            glm::vec3 position2 = collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ReturnPosition();

            //if the current object is static, dont move him and move the other one
            if(collisionInformations[i].colliders[0]->gameObjectOfCollider->movable==true)
                //fix interpenetration, by moving the object the amount of penetration both objects have, it will use the normal to know where it needs to move
                collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->SetPosition(position1 - ((normal * (penetrationDepth))));
            else
                collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->SetPosition(position2 + ((normal * (penetrationDepth))));

            //std::cout << collisionInformations[i].penetrationDepth << " Rigid body" << std::endl;

            //collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->ResetForcesForCollision();
            //collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->ResetForcesForCollision();

            //if the current object is static, dont move him and move the other one
            if (collisionInformations[i].colliders[0]->gameObjectOfCollider->movable == true)
            {
                //change the velocity directly for instant speed
                collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->SetVelocity(velocityAfterCol1);

                //if this object is a sphere rotate the sphere since we collided, and in real life if a sphere collides with something it will rotate
                //if(collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnBodyType() == BodyTypeOfGameObject::circle)
                  //  collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->AddRotationalMotionWithoutAddingForce(velocityAfterCol1/20.f, normal);

                //change the angular velocity directly for instant angular speed
                collisionInformations[i].colliders[0]->gameObjectOfCollider->ReturnPhysicsBody()->SetAngularVelocity(angularVelocityAfterCol1);
            }
            //if the current object is static, dont move him and move the other one
            if (collisionInformations[i].colliders[1]->gameObjectOfCollider->movable == true)
            {
                //change the velocity directly for instant speed
                collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->SetVelocity(velocityAfterCol2);

                //if this object is a sphere rotate the sphere since we collided, and in real life if a sphere collides with something it will rotate
                //if (collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnBodyType() == BodyTypeOfGameObject::circle)
                  //  collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->AddRotationalMotionWithoutAddingForce(velocityAfterCol2 / 20.f, -normal);

                //change the angular velocity directly for instant angular speed
                collisionInformations[i].colliders[1]->gameObjectOfCollider->ReturnPhysicsBody()->SetAngularVelocity(angularVelocityAfterCol2);

            }

            
        }

        
    }
    
    collisionInformations.clear();
}

//this will create the grid for the broad phase
void GameEngine::InitBroadPhaseGrid()
{

    int counter = -1;
    //this 2 for loops will create the grid for the broad Phase
    for (int x = 0; x < 3; x++)
    {
        //Create a new row
        broadPhaseGrid.push_back(std::vector<CollisionGrid>());
        for (int y = 0; y < 7; y++)
        {
            //this will populate the grid with the correct xmin, xmax and ymin and ymax data, this will create a square
            CollisionGrid tempGrid = {};
            //get the xMin of the square
            tempGrid.xMin = x * sizeOfEachGridSquare;
            //get the xpos (center of the x)
            tempGrid.xPos = tempGrid.xMin + (sizeOfEachGridSquare / 2);
            //get the xMax of the square
            tempGrid.xMax = tempGrid.xMin + sizeOfEachGridSquare;
            //get the y min of the square
            tempGrid.yMin = y * sizeOfEachGridSquare;
            //get the ypos (center of the y)
            tempGrid.yPos = tempGrid.yMin + (sizeOfEachGridSquare / 2);
            //get the ymax
            tempGrid.yMax = tempGrid.yMin + sizeOfEachGridSquare;

            //if the game engine is on debug mode add the spheres
           // if (IsDebugModeOn())
           // {
                //create a cube for the visual representation of the grid
                GameObject* gridCube = new Cube("Textures/SkyboxBack.jpg", glm::vec3(tempGrid.xPos, -10, tempGrid.yPos), glm::vec3((sizeOfEachGridSquare / 2) - 0.1, 1, (sizeOfEachGridSquare / 2) - 0.1), glm::vec3(0), 0.2f, true, 0.f, 0.0f, true);
                AddGameObject(gridCube);
                tempGrid.debugGridCube = gridCube;
           // }
            //add the temporary grid to the grid list, to the current row, basically we fill all of the frow first the we increment x and we add to another row
            broadPhaseGrid[x].push_back(tempGrid);
            counter += 1;
        }
    }

    std::cout << "grid has : " << counter << " squares" << std::endl;
    // std::cout << "grid square " << broadPhaseGrid.size()-1 << " x : " << broadPhaseGrid[broadPhaseGrid.size()-1].xMin << " y : " << broadPhaseGrid[broadPhaseGrid.size()-1].yMin << std::endl;

   
}

//this will do the broad phase for the collision
void GameEngine::BroadPhase()
{
    //go trough every grid item and remove every collider from it since we will populate this grid later
    for (int x = 0; x < broadPhaseGrid.size(); x++)
    {
        for (int y = 0; y < broadPhaseGrid[x].size(); y++)
        {
            broadPhaseGrid[x][y].collidersOnThisGridSpace.clear();
        }
    }

    //this will go trough every object and check on wich grid the object is
    for (int i = 0; i < colliders.size(); i++)
    {
        //if we dont have a intatiated collider continue, since we dont want to check collision of a nullptr, it will give an error
        if (colliders[i] == nullptr)
            continue;

        //this will store the range of the rows where the collider is (x value, right to left)
        glm::u8vec2 wichRowsTheColliderIs = BroadPhaseCheckColliderIsInWichRowRange(colliders[i]);
        
        //this will store the range of the columns where the collider is (y value, up to down)
        glm::u8vec2 wichColumnsTheColliderIs = BroadPhaseCheckColliderIsInWichColumnRange(colliders[i]);

        //std::cout << "the collider is at rows from : " << (int)wichRowsTheColliderIs.x << " to " << (int)wichRowsTheColliderIs.y;
        //std::cout << " and is on the columns from : " << (int)wichColumnsTheColliderIs.x << " to " << (int)wichColumnsTheColliderIs.y <<std::endl;

        //this function will add the colliders to the broad phase grid, it runs after we check where the collider is in terms of column and row of the grid 
        BroadPhaseAddCollidersToGrids(colliders[i], wichRowsTheColliderIs, wichColumnsTheColliderIs);
    }
    
    //make it only run once and write on the console the number of loops this function does 
    if (d_runedOnce == false)
        std::cout << "BIG O OF THE BROAD PHASE " << d_counterOfBigOBroadPhase << std::endl;
    
    //if we are on debug mode check what gridcubes have a collider on them and change their color
    if (IsDebugModeOn())
    {
        //go trough every grid item 
        for (int x = 0; x < broadPhaseGrid.size(); x++)
        {
            for (int y = 0; y < broadPhaseGrid[x].size(); y++)
            {
                //if theres atleast on collider on the grid change the grid cube color
                if (broadPhaseGrid[x][y].collidersOnThisGridSpace.size() > 0)
                    broadPhaseGrid[x][y].debugGridCube->ChangeTexture(1);
                //if theres no collider on the grid reset the grid cube color
                else
                    broadPhaseGrid[x][y].debugGridCube->ChangeTexture(0);

            }
        }
    }
}

//this will check in which range the collider is, it will check only the rows so it will now how much has changed for the x axis,with this it will optimize the big o of the broadphase
glm::u8vec2 GameEngine::BroadPhaseCheckColliderIsInWichRowRange(Collider* colliderTocheck)
{
    //this will have 2 int, the first one is on the first row we know the collider is and the last one is on the last row the collider is
    glm::u8vec2 rangeOfGridSquaresWhereColliderIs = glm::u8vec2(99, 99);

    //if the collider is a cube 
    if (colliderTocheck->colliderType == colliderTocheck->BOXCOLLIDER) {
        //get the xmin and zmin of the collider
        float xMin2 = colliderTocheck->positionOfCollider.x - colliderTocheck->ReturnSize().x;
        float zMin2 = colliderTocheck->positionOfCollider.z - colliderTocheck->ReturnSize().z;

        //Get the max positions from the collider
        float xMax2 = colliderTocheck->positionOfCollider.x + colliderTocheck->ReturnSize().x;
        float zMax2 = colliderTocheck->positionOfCollider.z + colliderTocheck->ReturnSize().z;

        for (int x = 0; x < broadPhaseGrid.size(); x++)
        {
            //increase the big o counter
            d_counterOfBigOBroadPhase += 1;
            //this will check if the collider is inside the pos of the grid
            if ((broadPhaseGrid[x][0].xMin <= xMax2 && broadPhaseGrid[x][broadPhaseGrid[0].size() - 1].xMax >= xMin2) &&
                (broadPhaseGrid[x][0].yMin <= zMax2 && broadPhaseGrid[x][broadPhaseGrid[0].size() - 1].yMax >= zMin2))
            {
                //if we havent initialized the x (if its the first time running this code, store x, this means we now say that the collider starts on the row x
                if (rangeOfGridSquaresWhereColliderIs.x == 99)
                    rangeOfGridSquaresWhereColliderIs.x = x;
                //if the x has been initialized, start storing y, it will be stored until theres a row where theres no collider and there we will break from this
                else
                {
                    rangeOfGridSquaresWhereColliderIs.y = x;
                }
            }
            //if the x has been initialized, this means i have already found one row containing the collider, so i just break since if its not on this row its not on any other row aswell
            else if (rangeOfGridSquaresWhereColliderIs.x != 99)
                break;
        }
    }

    //if the collider is a sphere
    else if (colliderTocheck->colliderType == colliderTocheck->SPHERECOLLIDER)
    {
        for (int x = 0; x < broadPhaseGrid.size(); x++)
        {
            //increase the big o counter
            d_counterOfBigOBroadPhase += 1;
            // get box closest point to sphere center by clamping
            float xPoint = std::max(broadPhaseGrid[x][0].xMin, std::min(colliderTocheck->positionOfCollider.x, broadPhaseGrid[x][broadPhaseGrid[0].size() - 1].xMax));
            float yPoint = std::max(broadPhaseGrid[x][0].yMin, std::min(colliderTocheck->positionOfCollider.z, broadPhaseGrid[x][broadPhaseGrid[0].size() - 1].yMax));

            // this is the same as isPointInsideSphere
            float distance = std::sqrt((xPoint - colliderTocheck->positionOfCollider.x) * (xPoint - colliderTocheck->positionOfCollider.x) +
                (yPoint - colliderTocheck->positionOfCollider.z) * (yPoint - colliderTocheck->positionOfCollider.z));
            
            //if the distance is smaller then the radius is because we have a collision
            if (distance < colliderTocheck->ReturnRadius())
            {
                //if we havent initialized the x (if its the first time running this code, store x, this means we now say that the collider starts on the row x
                if (rangeOfGridSquaresWhereColliderIs.x == 99)
                    rangeOfGridSquaresWhereColliderIs.x = x;
                //if the x has been initialized, start storing y, it will be stored until theres a row where theres no collider and there we will break from this
                else
                {
                    rangeOfGridSquaresWhereColliderIs.y = x;
                }

            }

            //if the x has been initialized, this means i have already found one row containing the collider, so i just break since if its not on this row its not on any other row aswell
            else if (rangeOfGridSquaresWhereColliderIs.x != 99)
                break;
        }
    }

    //if the collider is a cube 
    else if (colliderTocheck->colliderType == colliderTocheck->PLANECOLLIDER) {
        //get the xmin and zmin of the collider
        float xMin2 = colliderTocheck->positionOfCollider.x - colliderTocheck->ReturnSize().x;
        float zMin2 = colliderTocheck->positionOfCollider.z - colliderTocheck->ReturnSize().z;

        //Get the max positions from the collider
        float xMax2 = colliderTocheck->positionOfCollider.x + colliderTocheck->ReturnSize().x;
        float zMax2 = colliderTocheck->positionOfCollider.z + colliderTocheck->ReturnSize().z;

        for (int x = 0; x < broadPhaseGrid.size(); x++)
        {
            //increase the big o counter
            d_counterOfBigOBroadPhase += 1;
            //this will check if the collider is inside the pos of the grid
            if ((broadPhaseGrid[x][0].xMin <= xMax2 && broadPhaseGrid[x][broadPhaseGrid[0].size() - 1].xMax >= xMin2) &&
                (broadPhaseGrid[x][0].yMin <= zMax2 && broadPhaseGrid[x][broadPhaseGrid[0].size() - 1].yMax >= zMin2))
            {
                //if we havent initialized the x (if its the first time running this code, store x, this means we now say that the collider starts on the row x
                if (rangeOfGridSquaresWhereColliderIs.x == 99)
                    rangeOfGridSquaresWhereColliderIs.x = x;
                //if the x has been initialized, start storing y, it will be stored until theres a row where theres no collider and there we will break from this
                else
                {
                    rangeOfGridSquaresWhereColliderIs.y = x;
                }
            }
            //if the x has been initialized, this means i have already found one row containing the collider, so i just break since if its not on this row its not on any other row aswell
            else if (rangeOfGridSquaresWhereColliderIs.x != 99)
                break;
        }
    }

    return rangeOfGridSquaresWhereColliderIs;
}

//this will check in which range the collider is, it will check only the columnts so it will now how much has changed for the y axis (itsz axis for the game objects but for the grid is th y), with this it will optimize the big o of the 
glm::u8vec2 GameEngine::BroadPhaseCheckColliderIsInWichColumnRange(Collider* colliderTocheck)
{
    //this will have 2 int, the first one is on the first row we know the collider is and the last one is on the last row the collider is
    glm::u8vec2 rangeOfGridSquaresWhereColliderIs = glm::u8vec2(99, 99);
    
    //if the collider is a cube 
    if (colliderTocheck->colliderType == colliderTocheck->BOXCOLLIDER)
    {
        //get the xmin and zmin of the collider
        float xMin2 = colliderTocheck->positionOfCollider.x - colliderTocheck->ReturnSize().x;
        float zMin2 = colliderTocheck->positionOfCollider.z - colliderTocheck->ReturnSize().z;

        //Get the max positions from the collider
        float xMax2 = colliderTocheck->positionOfCollider.x + colliderTocheck->ReturnSize().x;
        float zMax2 = colliderTocheck->positionOfCollider.z + colliderTocheck->ReturnSize().z;

       

        for (int y = 0; y < broadPhaseGrid[0].size(); y++)
        {
            //increase the big o counter
            d_counterOfBigOBroadPhase += 1;
            //this will check if the collider is inside the pos of the grid
            if ((broadPhaseGrid[0][y].xMin <= xMax2 && broadPhaseGrid[broadPhaseGrid.size() - 1][y].xMax >= xMin2) &&
                (broadPhaseGrid[0][y].yMin <= zMax2 && broadPhaseGrid[broadPhaseGrid.size() - 1][y].yMax >= zMin2))
            {
               
                //if we havent initialized the x (if its the first time running this code, store x, this means we now say that the collider starts on the row x
                if (rangeOfGridSquaresWhereColliderIs.x == 99)
                    rangeOfGridSquaresWhereColliderIs.x = y;
                //if the x has been initialized, start storing y, it will be stored until theres a row where theres no collider and there we will break from this
                else
                {
                    rangeOfGridSquaresWhereColliderIs.y = y;
                }
            }
            //if the x has been initialized, this means i have already found one row containing the collider, so i just break since if its not on this row its not on any other row aswell
            else if (rangeOfGridSquaresWhereColliderIs.x != 99)
                break;
        }
    }

    //if the collider is a sphere
    else if (colliderTocheck->colliderType == colliderTocheck->SPHERECOLLIDER)
    {
        for (int y = 0; y < broadPhaseGrid[0].size(); y++)
        {
            //increase the big o counter
            d_counterOfBigOBroadPhase += 1;
            // get box closest point to sphere center by clamping
            float xPoint = std::max(broadPhaseGrid[0][y].xMin, std::min(colliderTocheck->positionOfCollider.x, broadPhaseGrid[broadPhaseGrid.size() - 1][y].xMax));
            float yPoint = std::max(broadPhaseGrid[0][y].yMin, std::min(colliderTocheck->positionOfCollider.z, broadPhaseGrid[broadPhaseGrid.size() - 1][y].yMax));

            // this is the same as isPointInsideSphere
            float distance = std::sqrt((xPoint - colliderTocheck->positionOfCollider.x) * (xPoint - colliderTocheck->positionOfCollider.x) +
                (yPoint - colliderTocheck->positionOfCollider.z) * (yPoint - colliderTocheck->positionOfCollider.z));

            //if the distance is smaller then the radius is because we have a collision
            if (distance < colliderTocheck->ReturnRadius())
            {
                //if we havent initialized the x (if its the first time running this code, store x, this means we now say that the collider starts on the row x
                if (rangeOfGridSquaresWhereColliderIs.x == 99)
                    rangeOfGridSquaresWhereColliderIs.x = y;
                //if the x has been initialized, start storing y, it will be stored until theres a row where theres no collider and there we will break from this
                else
                {
                    rangeOfGridSquaresWhereColliderIs.y = y;
                }

            }

            //if the x has been initialized, this means i have already found one row containing the collider, so i just break since if its not on this row its not on any other row aswell
            else if (rangeOfGridSquaresWhereColliderIs.x != 99)
                break;
        }
    }

    //if the collider is a Plane 
    else if (colliderTocheck->colliderType == colliderTocheck->PLANECOLLIDER)
    {
        //get the xmin and zmin of the collider
        float xMin2 = colliderTocheck->positionOfCollider.x - colliderTocheck->ReturnSize().x;
        float zMin2 = colliderTocheck->positionOfCollider.z - colliderTocheck->ReturnSize().z;

        //Get the max positions from the collider
        float xMax2 = colliderTocheck->positionOfCollider.x + colliderTocheck->ReturnSize().x;
        float zMax2 = colliderTocheck->positionOfCollider.z + colliderTocheck->ReturnSize().z;



        for (int y = 0; y < broadPhaseGrid[0].size(); y++)
        {
            //increase the big o counter
            d_counterOfBigOBroadPhase += 1;
            //this will check if the collider is inside the pos of the grid
            if ((broadPhaseGrid[0][y].xMin <= xMax2 && broadPhaseGrid[broadPhaseGrid.size() - 1][y].xMax >= xMin2) &&
                (broadPhaseGrid[0][y].yMin <= zMax2 && broadPhaseGrid[broadPhaseGrid.size() - 1][y].yMax >= zMin2))
            {

                //if we havent initialized the x (if its the first time running this code, store x, this means we now say that the collider starts on the row x
                if (rangeOfGridSquaresWhereColliderIs.x == 99)
                    rangeOfGridSquaresWhereColliderIs.x = y;
                //if the x has been initialized, start storing y, it will be stored until theres a row where theres no collider and there we will break from this
                else
                {
                    rangeOfGridSquaresWhereColliderIs.y = y;
                }
            }
            //if the x has been initialized, this means i have already found one row containing the collider, so i just break since if its not on this row its not on any other row aswell
            else if (rangeOfGridSquaresWhereColliderIs.x != 99)
                break;
        }
    }

    

    return rangeOfGridSquaresWhereColliderIs;
}

//this function will add the colliders to the broad phase grid, it runs after we check where the collider is in terms of column and row of the grid 
void GameEngine::BroadPhaseAddCollidersToGrids(Collider* colliderTocheck, glm::u8vec2 wichRowsTheColliderIs_, glm::u8vec2 wichColumnsTheColliderIs_)
{
    //this means the x values havent been initialized, so it means we are out of bounds of the broad phase
    if (wichRowsTheColliderIs_.x == 99 || wichColumnsTheColliderIs_.x == 99 || colliderTocheck->gameObjectOfCollider->ReturnPhysicsBody()->ReturnPosition().y < -25.f)
    {
        std::cout << "gameobject collidER is out of bopunds of the broad phase grid, this means its outside of the grid, this std::cout is on the function BroadPhaseCheckGrids" << std::endl;
        colliderTocheck->gameObjectOfCollider->ReturnPhysicsBody()->SetPosition(colliderTocheck->gameObjectOfCollider->initialPosition);
        colliderTocheck->gameObjectOfCollider->ReturnPhysicsBody()->ResetForcesForCollision();
        return;
    }
  
    //if the y havent been initialized, this means the object isnt in between multiple rows (is only on one row)
    if (wichRowsTheColliderIs_.y == 99)
    {
        //if the y havent been initialized, this means the object isnt in between multiple columns (is only in one column) 
        if (wichColumnsTheColliderIs_.y == 99)
        {
            broadPhaseGrid[wichRowsTheColliderIs_.x][wichColumnsTheColliderIs_.x].collidersOnThisGridSpace.push_back(colliderTocheck);
        }
        //since the y has been initialized, this means the column is in between multiple columns
        else{
            //since we are in only one row, and we are in multple columns (y value, left to right), we need tto go trough every columns we are in and add the object to the corresponding grid cube
            for (int i = wichColumnsTheColliderIs_.x; i <= wichColumnsTheColliderIs_.y; i++)
            {
                broadPhaseGrid[wichRowsTheColliderIs_.x][i].collidersOnThisGridSpace.push_back(colliderTocheck);
            }
        }
    }
    //since the y has been initialized the object is in between multiple rows
    else
    {
        //if the y havent been initialized, this means the object isnt in between multiple columns (is only in one column) 
        if (wichColumnsTheColliderIs_.y == 99)
        {
            //since we are in multiple rows, and we are in only one column (y value, left to right), we need tto go trough every row we are in and add the object to the corresponding grid cube
            for (int i = wichRowsTheColliderIs_.x; i <= wichRowsTheColliderIs_.y; i++)
            {
                broadPhaseGrid[i][wichColumnsTheColliderIs_.x].collidersOnThisGridSpace.push_back(colliderTocheck);
            }
        }
        //since the y has been initialized, this means the column is in between multiple columns and multiple rows
        else {
            //this double loop will go through every row and column the object is in
            for (int x = wichRowsTheColliderIs_.x; x <= wichRowsTheColliderIs_.y; x++)
            {
                for (int y = wichColumnsTheColliderIs_.x; y <= wichColumnsTheColliderIs_.y; y++)
                {
              
                    broadPhaseGrid[x][y].collidersOnThisGridSpace.push_back(colliderTocheck);
                }
            }
        }
    }
}

// Drawing routine. ISTO ESTA SEMPRE A SER CHAMADO
void GameEngine::DrawGame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
   
    // Position the objects for viewing.
    //gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //this will move the camera, update the eye value for the and specular lighitng
    GraphicsEngine::UpdateCamera();
    
    //FieldObject::Draw();
    SkyBox::Draw();


    //do a loop to draw every object inside the objects vector "array"
    for (int i = 0; i < objects.size(); ++i)
    {
        objects[i]->Draw();
    }

    //Draw collisison info and colliders if debug mode is on
    if (GameEngine::IsDebugModeOn())
    {
        //do a loop to draw every collider
        for (int i = 0; i < colliders.size(); ++i)
        {
            //check if the collider is correctly filled, if it is, draw it
            if (colliders[i] != nullptr)
            {
               //draw the colliders by calling the gameobject function that calls the collider function to draw
               colliders[i]->Draw();
               //make the colliders texture back to default, since we will change it below if they are colliding with anyone
               colliders[i]->currentTextureId = colliders[i]->initialTextureId;
            }
       
        }
    
        //draw all of the collision information to the screen
        for (int i = 0; i < collisionInformations.size(); ++i)
        {
            //change the colliders texture, since they are colliding
            collisionInformations[i].colliders[0]->currentTextureId = 0;
            collisionInformations[i].colliders[1]->currentTextureId = 0;

            glPushMatrix();
                glPointSize(5.0f); // so we can see the point better

                //this is going to draw a point on the midle of the object
                glColor3f(0.f, 1.f, 0.f);
                glBegin(GL_POINTS);
                //at the middle of object
                glVertex3f(collisionInformations[i].collisionPoint.x, collisionInformations[i].collisionPoint.y, collisionInformations[i].collisionPoint.z);

                glEnd();

                glColor3f(0, 0, 1);
                glBegin(GL_LINES);
                //at the middle of object
                glVertex3f(collisionInformations[i].collisionPoint.x, collisionInformations[i].collisionPoint.y, collisionInformations[i].collisionPoint.z);
                glVertex3f(collisionInformations[i].collisionPoint.x + collisionInformations[i].collisionNormal.x, 
                    collisionInformations[i].collisionPoint.y + collisionInformations[i].collisionNormal.y,
                    collisionInformations[i].collisionPoint.z + collisionInformations[i].collisionNormal.z);
                glEnd();
              glPopMatrix();

      
        }
    }


    glutSwapBuffers();
}

//this is going to delete every pointer to avoid memory leaks
void GameEngine::CleanupEngine()
{
    //cleanup / end of the program, delete every object pointer
    for (int i = 0; i < objects.size(); ++i)
    {
        delete objects[i];
    }
    delete forceGenerator;
}

// OpenGL window reshape routine, assigned this routine on the InitEngine
void GameEngine::ResizeWindow(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

//The function to set up/initialize opengl and GLUT and the function to get things ready (but not run)., it also sets up the key pressed function
void GameEngine::InitEngine(int argc, char** argv, const char* windowTitle, int width, int height)
{

    //this is why we need to use argc and argv 
   /* glutInit(&argc, argv);

    glutInitContextVersion(2, 0);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(windowTitle);
    
    glewExperimental = GL_TRUE;
    glewInit();*/

    //call the graphics initializer
    GraphicsEngine::init(argc, argv, windowTitle, width, height);
    //setup the shaders, creating the program
    GraphicsEngine::SetupShaders();
    //get the projection matrix, set the projection matrix and get the uniforms for the modelview matrix and objectloc 
    GraphicsEngine::ObtainProjectionAndModelMatrix();

    glutDisplayFunc(DrawGame);
    glutReshapeFunc(ResizeWindow);
    glutIdleFunc(UpdateGame);

    //THESE 4 AUTOS ARE LAMBDAS, WICH ARE BASICALLY A 1 LINE FUNCTION, THAT ARE USED AS VARIABLES
    /*this lambda is gonna be used when we click a normal key, and it will add the key clicked to the key map and set it to true
    /, we use a map because it doesnt let him have repeated values*/
    auto addNormalKeyIfClicked = [](unsigned char key, int x, int y) 
    { 
        ButtonsPressed::keys[key] = true; 
        if (key == 27)
        {
            CleanupEngine();
            exit(0);
        }
    };
    //this lambda is gonna be used when we stop clicking a normal key, and it will set it to false, because we are no longer pressing the key
    auto removeNormalKeyIfClicked = [](unsigned char key, int x, int y) { ButtonsPressed::keys[key] = false; };
    /*this lambda is gonna be used when we click a special key, and it will add the special key clicked to the key map and set it to true
   /, we use a map because it doesnt let him have repeated values*/
    auto addSpecialKeyIfClicked = [](int key, int x, int y) { ButtonsPressed::specialKeys[key] = true; };
    //this lambda is gonna be used when we stop clicking a special key, and it will set it to false, because we are no longer pressing the special key
    auto removeSpecialKeyIfClicked = [](int key, int x, int y) { ButtonsPressed::specialKeys[key] = false; };
    
  

    //calls the lambda addNormalKeyIfClicked every time a normal key is pressed 
    glutKeyboardFunc(addNormalKeyIfClicked);
    //calls the lambda removeNormalKeyIfClicked every time a normal key stops being pressed
    glutKeyboardUpFunc(removeNormalKeyIfClicked);

    //calls the lambda addSpecialKeyIfClicked every time a special key is pressed
    glutSpecialFunc(addSpecialKeyIfClicked);
    //calls the lambda removeSpecialKeyIfClicked every time a special key stops being pressed
    glutSpecialUpFunc(removeSpecialKeyIfClicked);
    //this will call the mouseCLickFunction everytime a mouse button is pressed, or released
    glutMouseFunc(mouseClickFunction);
    //this will call the mouseMoveFunction everytime the mouse moves whitout a click
    glutPassiveMotionFunc(mouseMoveFunction);
    //this will call the mouseMoveFunction everytime the mouse moves while clicking
    glutMotionFunc(mouseMoveFunction);

    //initialize the forceGenerator
    forceGenerator = new ForceGenerator();

    //FieldObject::Init("Textures/grass.bmp");
    
    
    //this is gonna call every start functions of every gameplay scripts
    scriptManager::Start();

    //this will set the siz of each square  of the grid
    sizeOfEachGridSquare = 6;

    //this will create the grid for the broad phase
    InitBroadPhaseGrid();
}

//this will be called when the mouse clicks
void GameEngine::mouseClickFunction(int button, int state, int x, int y)
{
 

    //if the left mouse is clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        ButtonsPressed::SetLeftMouseButtonClicking(true);
    //if the left mouse stops being called
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        ButtonsPressed::SetLeftMouseButtonClicking(false);

    //if the right mouse is clicked
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        ButtonsPressed::SetRightMouseButtonClicking(true);
    //if the right mouse stops being called
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
        ButtonsPressed::SetRightMouseButtonClicking(false);

    //if the middle is clicked
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        ButtonsPressed::SetMiddleMouseButtonClicking(true);
    //if the middle mouse stops being called
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
        ButtonsPressed::SetMiddleMouseButtonClicking(false);
        
    
    //this is gonna call every mouse click function fro gameplay scripts
    scriptManager::OnMouseClick();
}


//gonna be used when the mouse moves, it will send the position of the mouse to the buttons pressed, it will be a value from 0 to 1
void GameEngine::mouseMoveFunction(int x, int y)
{
    ButtonsPressed::SetMousePos(glm::vec2((float)x / glutGet(GLUT_WINDOW_WIDTH), (float)y / glutGet(GLUT_WINDOW_HEIGHT)));
  
}


//A way to add objects to the game world.
void GameEngine::AddGameObject(GameObject* object)
{
    objects.push_back(object);
    object->Setup();
    
    //if the debug mode is on, do the draw Setup for the collider
    if (GameEngine::IsDebugModeOn() == true)
    {
        object->CallSetupDrawFunctionFromColliders();
    }

    //if the object has colliders, add them to the vector of all colliders
    if (object->ReturnColliders().size() != 0)
    {
        //store every collider from the gameobject
        std::vector<Collider*> tempCollidersOfGameObject = object->ReturnColliders();
        //add the colliders to the list of all colliders
        for(int i=0; i<tempCollidersOfGameObject.size();i++)
            colliders.push_back(tempCollidersOfGameObject[i]);
    }
}

//a way to remove objects from the game world
void GameEngine::RemoveGameObject(GameObject* objectToRemove)
{
    //this loop will delete the object to remove
    for (int i = 0; i < objects.size(); i++)
    {
        //if the object is correct, remove the corresponding collider from the collider list and delete the game object (which will delete the collider automatically), and then remove the game object from the gameobject list
        if (objects[i] == objectToRemove)
        {
            //if the object has a collider delete it
            if (objectToRemove->ReturnColliders().size() != 0)
            {
                //this will do a loop trough all of the colliders for it to be able to delete the collider aswell
                for (int j = 0; j < colliders.size(); j++)
                {
                    //store every collider from the gameobject
                    std::vector<Collider*> tempCollidersOfGameObject = objectToRemove->ReturnColliders();
                    
                    //do a loop trough every collider of the game object and remove them all
                    for (int i = 0; i < tempCollidersOfGameObject.size(); i++)
                    {
                        //this will cherck if the current collider is the same as the one we want to delete if it is we delete it
                        if (colliders[j]== tempCollidersOfGameObject[i])
                        {
                            colliders.erase(colliders.begin() + j);
                            
                        }
                    }
                }
            }

            //remove the gameobject from receiving forces
            forceGenerator->RemoveObjectFromReceivingForce(objectToRemove);
            //delete the object (which will call the collidewr destructor autiomatically
            delete objects[i];
            //this will erase the game object from the gameobject list
            objects.erase(objects.begin() + i);
            break;
        }
    }
}

//this is going to initialize the engine by calling the glut main loop
void GameEngine::StartEngine()
{
    std::cout << "Press escape to exit the game." << std::endl;
    glutMainLoop();
}

//this will return if the game engine is on debug mode or not
bool GameEngine::IsDebugModeOn()
{
    return debugMode;
}



