#include <engine/physics.hpp>

// include standard library for debugging
#include <iostream>

#include <cmath>
#include <memory>
#include <stdexcept>

// init resources

std::vector<PhysicsObject>      Physics::physicsObjs;
int32_t                         Physics::velocityIterations = 8;
int32_t                         Physics::positionIterations = 4;
b2World*                        Physics::world = nullptr;
bool                            Physics::isAutoClearSet = false;

// template function 
template < typename T, typename U > bool have_same_address( const T& a, const U& b ) 
{ return reinterpret_cast<const char*>( std::addressof(a) ) == reinterpret_cast<const char*>( std::addressof(b) ) ; }

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
}

PhysicsObject Physics::CreatePhysicsObject(Transform2D& transform, BoxCollider2D& collider, Rigidbody2D& rigidbody){
    // check if object already exists
    for(PhysicsObject& obj: physicsObjs){
        if(have_same_address(transform, obj.transform) 
         || have_same_address(collider, obj.collider)
         || have_same_address(rigidbody, obj.rb)){
            throw std::invalid_argument("ERROR: Object already created!");
        }
    }

    // check if world has been initialized
    if(world == nullptr){
        throw std::invalid_argument("ERROR: Physics hasn't been initialized");
    }

    //* set up transform, collider, and rigidbody of object

    // create body
    b2BodyDef bodyDef;
    bodyDef.type = RbToB2Types(rigidbody.Type);
    bodyDef.position.Set(transform.position.x, transform.position.y);
    //! rotation set is in radians
    bodyDef.angle = transform.rotation;
    b2Body* body = world->CreateBody(&bodyDef);
    body->SetFixedRotation(rigidbody.fixedRotation);
    rigidbody.runtimeBody = body;

    //TODO: Create options to make either a box or circle collider

    // set up box collider
    b2PolygonShape boxShape;
    boxShape.SetAsBox(collider.size.x * abs(transform.size.x), collider.size.y * abs(transform.size.y),
     {collider.offset.x, collider.offset.y}, collider.rotationOffset);

    // set up physics material
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = collider.density;
    fixtureDef.friction = collider.friction;
    fixtureDef.restitution = collider.restitution;
    fixtureDef.restitutionThreshold = collider.restitutionThreshold;
    body->CreateFixture(&fixtureDef);

    // create Physics object
    PhysicsObject obj;
    obj.transform = &transform;
    obj.collider = &collider;
    obj.rb = &rigidbody;

    // store object
    physicsObjs.push_back(obj);

    return obj;
}

void Physics::RegisterPhysicsObject(Transform2D &transform, BoxCollider2D &collider, Rigidbody2D &rigidbody){
    // check if world has been initialized
    if(world == nullptr){
        throw std::invalid_argument("ERROR: Physics hasn't been initialized");
    }

    //* set up transform, collider, and rigidbody of object

    // check if body is not null
    if(rigidbody.runtimeBody != nullptr)
        return; // stop function

    // create body
    b2BodyDef bodyDef;
    bodyDef.type = RbToB2Types(rigidbody.Type);
    bodyDef.position.Set(transform.position.x, transform.position.y);
    //! rotation set is in radians
    bodyDef.angle = transform.rotation;
    b2Body* body = world->CreateBody(&bodyDef);
    body->SetFixedRotation(rigidbody.fixedRotation);
    rigidbody.runtimeBody = body;

    //TODO: Create options to make either a box or circle collider

    // set up box collider
    b2PolygonShape boxShape;
    boxShape.SetAsBox(collider.size.x * abs(transform.size.x), collider.size.y * abs(transform.size.y),
     {collider.offset.x, collider.offset.y}, collider.rotationOffset);

    // set up physics material
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = collider.density;
    fixtureDef.friction = collider.friction;
    fixtureDef.restitution = collider.restitution;
    fixtureDef.restitutionThreshold = collider.restitutionThreshold;
    body->CreateFixture(&fixtureDef);
}

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
    if(world != nullptr){
        // update any collisions detection, but not update the rigidbodies position
        world->Step(deltaTime, velocityIterations, positionIterations);
    }
}

void Physics::UpdatePhysics(){
    // check if world has been initialized
    if(world == nullptr)
        return; // stop function

    // update each physics object
    for(PhysicsObject& obj : physicsObjs){
        // retrieve the body
        b2Body* body = (b2Body*)obj.rb->runtimeBody;

        // get position change
        const b2Vec2 position = body->GetPosition();

        // update each object's transform
        obj.transform->position.x = position.x;
        obj.transform->position.y = position.y;
        obj.transform->rotation = body->GetAngle();
    }
}

void Physics::UpdateRegisteredObject(Transform2D &transform, Rigidbody2D &rigidbody){
    // check if body is not null
    if(rigidbody.runtimeBody == nullptr)
        return; // stop function

    // update the registered object
    b2Body* body = (b2Body*)rigidbody.runtimeBody;

    // get position change
    const b2Vec2 position = body->GetPosition();

    // update component transform
    transform.position.x = position.x;
    transform.position.y = position.y;
    transform.rotation = body->GetAngle();
}

void Physics::Clear(){
    // remove reference to components of each Physics object
    for(PhysicsObject& obj : physicsObjs){
        obj.transform = nullptr;
        obj.collider = nullptr;
        obj.rb = nullptr;

        delete obj.transform;
        delete obj.collider;
        delete obj.rb;
    }

    // delete the physics world
    delete world;
}

bool Physics::AABBCollision(Transform2D& a, Transform2D& b){
    //TODO: calculate the sides of the quad with the offset considered

    // check for no overlap
    bool collisionX = (a.position.x + a.size.x / 2.0f) >= (b.position.x - b.size.x / 2.0f) && (a.position.x - a.size.x / 2.0f) <= (b.position.x + b.size.x / 2.0f);
    bool collisionY = (a.position.y + a.size.y / 2.0f) >= (b.position.y - b.size.y / 2.0f) && (a.position.y - a.size.y / 2.0f) <= (b.position.y + b.size.y / 2.0f);

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

void Physics::SetUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(Clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}