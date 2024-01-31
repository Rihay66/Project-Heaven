#include <engine/physics.hpp>

//init resources

std::vector<TriggerObject*> Physics::triggerObjs;
std::vector<PhysicsObject*> Physics::rigidbodyObjs;
int32_t Physics::velocityIterations = 8;
int32_t Physics::positionIterations = 4;

b2World* Physics::world = nullptr;

void Physics::init(glm::vec2 gravity){
    //Set up box 2d world
    world = new b2World({gravity.x, gravity.y});

    //Check if there is an empty list of rigidbodies
    if(rigidbodyObjs.size() <= 0){
        std::cout << "Warning: list of physics objects is ZERO!!!" << "\n";
    }else{
        // Loop through list of rigidbodies and add them to the box2d world
        for (PhysicsObject* obj : rigidbodyObjs){

            // set up rigidbody and boxcollider
            b2BodyDef bodyDef;
            bodyDef.type = RbToB2Types(obj->rb.Type);
            bodyDef.position.Set(obj->position.x, obj->position.y);
            bodyDef.angle = obj->rotation;

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

    //Check if there are any trigger object
    if(triggerObjs.size() <= 0){
        std::cout << "Warning: list of trigger objects is ZERO!!!" << "\n";
    }
}

void Physics::updateWorld(float deltaTime){

    if(rigidbodyObjs.size() > 0){
        //update rigidbodies
        world->Step(deltaTime, velocityIterations, positionIterations);
    }
}

void Physics::updatePhysics(){
    for (PhysicsObject *obj : rigidbodyObjs){
        // retrieve the body from each rigidbody
        b2Body *body = obj->physicBody();
        
        //update previous state
        obj->previousState = obj->currentState;

        // Check for any changed
        const b2Vec2 position = body->GetPosition();

        // update each rigidbody their position
        obj->position.x = position.x;
        obj->position.y = position.y;
        obj->rotation = body->GetAngle();


        // update each rigidbody's state position
        //obj->currentState.posX = position.x;
        //obj->currentState.posY = position.y;
    }

    //TODO: Create a memory safe system to create and delete rigidbody objects 

    /*
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

void Physics::updateTriggers(){
    //TODO: Refactor checking for trigger collsion using space partitioning
    //Check trigger objects
    if(triggerObjs.size() > 0){
        //loop use each trigger will collide only with rigidbody objects
        for(TriggerObject* trigObj : triggerObjs){
            for(PhysicsObject* rigidObj : rigidbodyObjs){
                //check for aabb colllision
                if(aabbCollision(trigObj, rigidObj)){
                    //call the trigger's collision callback
                    trigObj->triggerCollisionCallback(rigidObj);
                }
            }
            //Check if trigger is a exit trigger
            if(trigObj->trigType == TriggerType::Exit){
                //Call to check objects that collided with the exit trigger
                trigObj->exitTriggerObjectCheck();
            }
        }
    }
}

void Physics::clearAll(){

    //TODO: Properly refactor how the objects are free from memory
    
    //Remove pointer from all lists

    //Remove all PhysicsObjects attached to the physics engine
    for(PhysicsObject* obj : rigidbodyObjs){
        delete obj;
    }

    rigidbodyObjs.clear();

    //Remove all TriggerObject attached to the physics engine
    for(TriggerObject* obj : triggerObjs){
        delete obj;
    }

    triggerObjs.clear();

    //Properly delete box 2d world
    delete world;
}

void Physics::clearWorld(){
    //Properly delete box 2d world
    delete world;
}

void Physics::clearReference(){
    //Remove reference to pointers in all lists
    rigidbodyObjs.clear();
    triggerObjs.clear();
}

//TODO: Make it able to detect collision for rotation and rotation offsets
bool Physics::aabbCollision(GameObject* a, GameObject* b){
    // Calculate the sides of the rectangles with the offset considered

    // Check for no overlap
    bool collisionX = (a->position.x + a->size.x / 2.0f) >= (b->position.x - b->size.x / 2.0f) && (a->position.x - a->size.x / 2.0f) <= (b->position.x + b->size.x / 2.0f);
    bool collisionY = (a->position.y + a->size.y / 2.0f) >= (b->position.y - b->size.y / 2.0f) && (a->position.y - a->size.y / 2.0f) <= (b->position.y + b->size.y / 2.0f);

    // If the rectangles overlap on both axes, a collision is detected
    return collisionX && collisionY;
}