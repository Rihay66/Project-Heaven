#include <engine/physics.hpp>

Physics::Physics(){}

Physics::~Physics(){
    //delete any pointer 
    rigidbodyObjs.clear();
    triggerObjs.clear();

    world = nullptr;
    delete world;
}

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

void Physics::CheckCollisions(float deltaTime){

    if(rigidbodyObjs.size() > 0){
        //Check rigidbodies
        world->Step(deltaTime, velocityIterations, positionIterations);
        for (PhysicsObject* obj : rigidbodyObjs){
            //retrieve the body from each rigidbody
            b2Body* body = obj->physicBody();

            //Check for any changed
            const b2Vec2 position = body->GetPosition();

            //update each rigidbody their position
            obj->position.x = position.x;
            obj->position.y = position.y;
            obj->rotation = body->GetAngle();
        }

        //Remove rigidbodies that are set to be destroyed
        for(PhysicsObject* obj : rigidbodyObjs){
            if(obj->isDestroyed){
                //Find object in list
                auto index = std::find(rigidbodyObjs.begin(), rigidbodyObjs.end(), obj);

                //Remove object from list
                if (index != rigidbodyObjs.end()){  // Ensure the object is found
                    rigidbodyObjs.erase(index); // Erase 
                }
            }
        }
    }

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

//TODO: Make it able to detect collision for rotation and rotation offsets
bool Physics::aabbCollision(GameObject* a, GameObject* b){
    // collision x-axis?
    bool collisionX = a->position.x + a->size.x >= b->position.x &&
        b->position.x + b->size.x >= a->position.x;
    // collision y-axis?
    bool collisionY = a->position.y + a->size.y >= b->position.y &&
        b->position.y + b->size.y >= a->position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}