#include <systems/physics.hpp>

// include standard library for debugging
#include <iostream>

// init resources

//std::vector<TriggerObject*>     Physics::triggerObjs;
//std::vector<PhysicsObject*>     Physics::rigidbodyObjs;
int32_t                         Physics::velocityIterations = 8;
int32_t                         Physics::positionIterations = 4;
b2World*                        Physics::world = nullptr;
//State                           Physics::mState;
bool                            Physics::isAutoClearSet = false;


void Physics::Init(glm::vec2 gravity){
    // set up automatic clear()
    SetUpAutoClear();
    // set up box 2d world
    if(world == nullptr){
        world = new b2World({gravity.x, gravity.y});
    }else{
        // display error
        std::cout << "WARNING: Physics initialization must only be called once!" << "\n";
        //std::cout << "HINT: If more than one Physics initialization is called with intention make sure to clearWorld() before calling init() again" << std::endl;
        // cause crash to program that uses this physics engine
        return;
    }
    /*
    // check if there is an empty list of rigidbodies
    if(rigidbodyObjs.size() <= 0){
        //TODO: Create debug options for the Physics class to display a console to show any errors or messages
        //std::cout << "Warning: list of physics objects is ZERO!!!" << "\n";
    }else{
        // loop through list of rigidbodies and add them to the box2d world
        for (PhysicsObject* obj : rigidbodyObjs){

            // set up rigidbody and boxcollider
            b2BodyDef bodyDef;
            bodyDef.type = RbToB2Types(obj->rb.Type);
            bodyDef.position.Set(obj->position.x, obj->position.y);
            bodyDef.angle = obj->getRotationRadians();

            // create body
            b2Body* body = world->CreateBody(&bodyDef);
            body->SetFixedRotation(obj->rb.fixedRotation);
            obj->rb.runtimeBody = body;

            // set up box collider
            b2PolygonShape boxShape;
            boxShape.SetAsBox(obj->collider.size.x * obj->size.x, obj->collider.size.y * obj->size.y,
             {obj->collider.offset.x, obj->collider.offset.y}, obj->collider.rotationOffset);

            // set up physics material
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &boxShape;
            fixtureDef.density = obj->collider.density;
            fixtureDef.friction = obj->collider.friction;
            fixtureDef.restitution = obj->collider.restitution;
            fixtureDef.restitutionThreshold = obj->collider.restitutionThreshold;
            body->CreateFixture(&fixtureDef);
        }
    }

    // check if there are any trigger object
    if(triggerObjs.size() <= 0){
        //TODO: Create debug options for the Physics class to display a console to show any errors or messages
        //std::cout << "Warning: list of trigger objects is ZERO!!!" << "\n";
    }
    */
}

/*
TriggerObject* Physics::AddTriggerObject(TriggerObject* obj){
    // set up automatic clear()
    SetUpAutoClear();
    // check if the object is valid
    if(obj && obj != nullptr){
        // check if object already exists in the list
        for(int i = 0; i < triggerObjs.size(); i++){
            if(triggerObjs[i] == obj){
                return nullptr; // object already exists so stop function and return nothing
            }
        }

        // object is valid then add to list
        triggerObjs.push_back(obj);

    }else{
        //TODO: Create debug options for the Physics class to display a console to show any errors or messages
        // return nothing
        return nullptr;
    }

    // return the same object given
    return obj;
}

PhysicsObject* Physics::AddPhysicsObject(PhysicsObject* obj){
    // set up automatic clear()
    SetUpAutoClear();
    // check if the object is valid
    if(obj && obj != nullptr){
        // check if object already exists in the list
        for(int i = 0; i < rigidbodyObjs.size(); i++){
            if(rigidbodyObjs[i] == obj){
                return nullptr; // object already exists so stop function and return nothing
            }
        }

        // create body and insert it into physics world only if world is initialized
        if(world != nullptr){
            // set up rigidbody and boxcollider
            b2BodyDef bodyDef;
            bodyDef.type = RbToB2Types(obj->rb.Type);
            bodyDef.position.Set(obj->position.x, obj->position.y);
            bodyDef.angle = obj->getRotationRadians();

            // create body
            b2Body* body = world->CreateBody(&bodyDef);
            body->SetFixedRotation(obj->rb.fixedRotation);
            obj->rb.runtimeBody = body;

            // set up box collider
            b2PolygonShape boxShape;
            boxShape.SetAsBox(obj->collider.size.x * obj->size.x, obj->collider.size.y * obj->size.y,
             {obj->collider.offset.x, obj->collider.offset.y}, obj->collider.rotationOffset);

            // set up physics material
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &boxShape;
            fixtureDef.density = obj->collider.density;
            fixtureDef.friction = obj->collider.friction;
            fixtureDef.restitution = obj->collider.restitution;
            fixtureDef.restitutionThreshold = obj->collider.restitutionThreshold;
            body->CreateFixture(&fixtureDef);
        }

        // object is valid then add to list
        rigidbodyObjs.push_back(obj);

    }else{
        //TODO: Create debug options for the Physics class to display a console to show any errors or messages
        // return nothing
        return nullptr;
    }

    // return the same object given
    return obj;
}
*/

void Physics::SetPhysicsVelocityIterations(int32_t iter){
    // set up automatic clear()
    SetUpAutoClear();
    // check if given value is less than 1
    if(iter < 1){
        return; // stop function
    }

    // set given value 
    velocityIterations = iter;
}

void Physics::SetPhysicsPositionIterations(int32_t iter){
    // set up automatic clear()
    SetUpAutoClear();
    // check if given value is less than 1
    if(iter < 1){
        return; // stop function
    }

    // set given value 
    positionIterations = iter;
}

void Physics::UpdateWorld(float deltaTime){
    /*
    if(rigidbodyObjs.size() > 0 && world != nullptr){
        // update any collisions detection, but not update the rigidbodies position
        world->Step(deltaTime, velocityIterations, positionIterations);
    }
    */
}

void Physics::UpdatePhysics(){
    /*
    if(rigidbodyObjs.size() <= 0 && world != nullptr){
        //TODO: Create debug options for the Physics class to display a console to show any errors or messages
        return; //stop function
    }

    for (PhysicsObject *obj : rigidbodyObjs){
        // retrieve the body from each rigidbody
        b2Body *body = obj->physicBody();
        
        //update previous state
        obj->setPreviousInterpolatedState(obj->getCurrentInterpolatedState());

        // check for any changed
        const b2Vec2 position = body->GetPosition();

        // update each rigidbody their position
        obj->position.x = position.x;
        obj->position.y = position.y;
        obj->setRotationRadians(body->GetAngle());


        // update each rigidbody's state position
        mState.posX = position.x;
        mState.posY = position.y;

        obj->setCurrentInterpolatedState(mState);
    }

    //TODO: Create a memory safe system to create and delete rigidbody objects 

    
    // Remove rigidbodies that are set to be destroyed
    for (PhysicsObject *obj : rigidbodyObjs){
        if (obj->isDestroyed)
        {
            // Find object in list
            auto index = std::find(rigidbodyObjs.begin(), rigidbodyObjs.end(), obj);

            // Remove object from list
            if (index != rigidbodyObjs.end())
            {                               // Ensure the object is found
                rigidbodyObjs.erase(index); // Erase
            }
        }
    }
    */
}

void Physics::UpdateTriggers(){
    //TODO: Refactor checking for trigger collsion using space partitioning
    /*
    if(triggerObjs.size() <= 0){
        //TODO: Create debug options for the Physics class to display a console to show any errors or messages
        return; // stop function
    }

    // loop use each trigger will collide only with rigidbody objects
    for (TriggerObject *trigObj : triggerObjs){
        for (PhysicsObject *rigidObj : rigidbodyObjs){
            // check for aabb colllision
            if (AABBCollision(trigObj, rigidObj)){
                // call the trigger's collision callback
                trigObj->triggerCollisionCallback(rigidObj);
            }
        }
        // check if trigger is a exit trigger
        if (trigObj->getTriggerType() == TriggerType::Exit){
            // call to check objects that collided with the exit trigger
            trigObj->exitTriggerObjectCheck();
        }
    }

    //TODO: Create a memory safe system to create and delete trigger objects 
    */
}

void Physics::Clear(){
    // remove reference to objects
    //triggerObjs.clear();
    //rigidbodyObjs.clear();

    // delete the physics world
    delete world;
}

/*
//TODO: Make it able to detect collision for rotation and rotation offsets
bool Physics::AABBCollision(GameObject* a, GameObject* b){
    // calculate the sides of the quad with the offset considered

    // check for no overlap
    bool collisionX = (a->position.x + a->size.x / 2.0f) >= (b->position.x - b->size.x / 2.0f) && (a->position.x - a->size.x / 2.0f) <= (b->position.x + b->size.x / 2.0f);
    bool collisionY = (a->position.y + a->size.y / 2.0f) >= (b->position.y - b->size.y / 2.0f) && (a->position.y - a->size.y / 2.0f) <= (b->position.y + b->size.y / 2.0f);

    // if the quad overlap on both axes, a collision is detected
    return collisionX && collisionY;
}

b2BodyType Physics::RbToB2Types(BodyType bodyType){
    switch (bodyType){
        case BodyType::Static:
            return b2_staticBody;
        case BodyType::Dynamic:
            return b2_dynamicBody;
        case BodyType::Kinematic:
            return b2_kinematicBody;
    }

    // no type was set or there is a unknown body type being passed
    std::cout << "Warning: Unknown RB Body Type being passed!" << "\n";
    return b2_staticBody;
}
*/

void Physics::SetUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(Clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}