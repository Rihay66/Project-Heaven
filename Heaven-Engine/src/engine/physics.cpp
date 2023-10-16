#include <engine/physics.hpp>

Physics::Physics(){}

Physics::~Physics(){
    //delete any pointer 
    pObjs.clear();
    rigidbodyObjs.clear();
    triggerObjs.clear();

    world = nullptr;
    delete world;
}

void Physics::init(glm::vec2 gravity){
    //Set up box 2d world
    world = new b2World({gravity.x, gravity.y});

    //Check if there is an empty list of rigidbodies
    if(pObjs.size() <= 0){
        std::cout << "ERROR: list of physics objects is ZERO!!!" << "\n";
        return;
    }

    //organize objects by flags sucha as non triggers and triggers
    for(physicsObject* obj : pObjs){
        if(obj->isTrigger)
            triggerObjs.push_back(obj);
        else
            rigidbodyObjs.push_back(obj);
    }

    //Loop through list of rigidbodies and add them to the box2d world
    for(physicsObject* obj : rigidbodyObjs){

        //set up rigidbody and boxcollider
        b2BodyDef bodyDef;
        bodyDef.type = RbToB2Types(obj->rb.Type);
        bodyDef.position.Set(obj->position.x, obj->position.y);
        bodyDef.angle = obj->rotation;

        //create body
        b2Body* body = world->CreateBody(&bodyDef);
        body->SetFixedRotation(obj->rb.fixedRotation);
        obj->rb.runtimeBody = body;

        //set up box collider
        b2PolygonShape boxShape;
        boxShape.SetAsBox(obj->collider.size.x * obj->size.x, obj->collider.size.y * obj->size.y, {obj->collider.offset.x, obj->collider.offset.y}, obj->collider.rotationOffset);

        //set up physics material
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = obj->collider.density;
        fixtureDef.friction = obj->collider.friction;
        fixtureDef.restitution = obj->collider.restitution;
        fixtureDef.restitutionThreshold = obj->collider.restitutionThreshold;
        body->CreateFixture(&fixtureDef);
    }
}

//TODO: When a physics object is destroyed remove from list
void Physics::CheckCollisions(float deltaTime){

    //Check rigidbodies
    world->Step(deltaTime, velocityIterations, positionIterations);
    for(physicsObject* obj : rigidbodyObjs){
        //retrieve the body from each rigidbody
        b2Body* body = obj->physicBody();

        //Check for any changed 
        const b2Vec2 position = body->GetPosition();

        //update each rigidbody their position
        obj->position.x = position.x;
        obj->position.y = position.y;
        obj->rotation = body->GetAngle();
    }
}

//TODO: Make a tag system for physics objects and also make approprite functions similar to unity C#
bool Physics::aabbCollision(physicsObject &a, physicsObject &b){
    // collision x-axis?
    bool collisionX = a.position.x + a.size.x >= b.position.x &&
        b.position.x + b.size.x >= a.position.x;
    // collision y-axis?
    bool collisionY = a.position.y + a.size.y >= b.position.y &&
        b.position.y + b.size.y >= a.position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}