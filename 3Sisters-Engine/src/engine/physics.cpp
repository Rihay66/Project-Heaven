#include <engine/physics.hpp>

// include standard library for debugging
#include <iostream>

#include <cmath>
#include <memory>
#include <stdexcept>

// incldue GLM
#include <glm/trigonometric.hpp>

// init resources

std::vector<PhysicsObject>      Physics::physicsObjs;
int32_t                         Physics::substepIterations = 4;
b2WorldId                        Physics::world = b2_nullWorldId;
bool                            Physics::isAutoClearSet = false;

// template function 
template < typename T, typename U > bool have_same_address( const T& a, const U& b ) 
{ return reinterpret_cast<const char*>( std::addressof(a) ) == reinterpret_cast<const char*>( std::addressof(b) ) ; }

void Physics::Init(glm::vec2 gravity){
    // set up automatic clear()
    SetUpAutoClear();
    // set up box 2d world
    if(!b2World_IsValid(world)){
        // physics is not set, then set it

        //? Create a default world definition
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {gravity.x, gravity.y};

        // create the physics world
        world = b2CreateWorld(&worldDef);
    }else{
        // display error when world is set
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
    if(!b2World_IsValid(world)){
        throw std::invalid_argument("ERROR: Physics hasn't been initialized");
    }

    //* set up transform, collider, and rigidbody of object

    // create body
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = RbToB2Types(rigidbody.bodyType);
    bodyDef.position = (b2Vec2){transform.position.x, transform.position.y};
    //! rotation set is in radians
    bodyDef.rotation = b2MakeRot(glm::radians(transform.rotation));
    bodyDef.fixedRotation = rigidbody.fixedRotation;

    // create body 
    b2BodyId body = b2CreateBody(world, &bodyDef);
    rigidbody.runtimeBody = body;

    //TODO: Create options to make either a box or circle collider

    // set up box collider
    b2Polygon boxShape = b2MakeOffsetBox(collider.size.x * abs(transform.size.x), collider.size.y * abs(transform.size.y),
     {collider.offset.x, collider.offset.y}, collider.rotationOffset);

    // set up physics material
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = collider.density;

    // check that given friction is within a value range [0,1]
    if(collider.friction > 0.0f && collider.friction <= 1.0f){
        shapeDef.friction = collider.friction;
    }else{
        // give a default value
        shapeDef.friction = 0.5f;
    }

    // check that given restitution is within a value range [0,1]
    if(collider.restitution > 0.0f && collider.restitution <= 1.0f){
        shapeDef.restitution = collider.restitution;
    }else{
        // give a default value
        shapeDef.restitution = 0.0f;
    }
    
    // create shape
    b2CreatePolygonShape(body, &shapeDef, &boxShape);

    // create Physics object
    PhysicsObject obj;
    obj.transform = &transform;
    obj.collider = &collider;
    obj.rb = &rigidbody;

    // store object
    physicsObjs.push_back(obj);

    return obj;
}


PhysicsObject Physics::CreatePhysicsObject(Transform2D& transform, BoxCollider2D& collider, Rigidbody2D& rigidbody, Interpolation& interpolation){
    // check if object already exists
    for(PhysicsObject& obj: physicsObjs){
        if(have_same_address(transform, obj.transform) 
         || have_same_address(collider, obj.collider)
         || have_same_address(rigidbody, obj.rb)
         || have_same_address(interpolation, obj.inter)){
            throw std::invalid_argument("ERROR: Object already created!");
        }
    }

    // check if world has been initialized
    if(!b2World_IsValid(world)){
        throw std::invalid_argument("ERROR: Physics hasn't been initialized");
    }

    //* set up transform, collider, and rigidbody of object

    // create body
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = RbToB2Types(rigidbody.bodyType);
    bodyDef.position = (b2Vec2){transform.position.x, transform.position.y};
    //! rotation set is in radians
    bodyDef.rotation = b2MakeRot(glm::radians(transform.rotation));
    bodyDef.fixedRotation = rigidbody.fixedRotation;

    // create body 
    b2BodyId body = b2CreateBody(world, &bodyDef);
    rigidbody.runtimeBody = body;

    //TODO: Create options to make either a box or circle collider

    // set up box collider
    b2Polygon boxShape = b2MakeOffsetBox(collider.size.x * abs(transform.size.x), collider.size.y * abs(transform.size.y),
     {collider.offset.x, collider.offset.y}, collider.rotationOffset);

    // set up physics material
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = collider.density;

    // check that given friction is within a value range [0,1]
    if(collider.friction > 0.0f && collider.friction <= 1.0f){
        shapeDef.friction = collider.friction;
    }else{
        // give a default value
        shapeDef.friction = 0.5f;
    }

    // check that given restitution is within a value range [0,1]
    if(collider.restitution > 0.0f && collider.restitution <= 1.0f){
        shapeDef.restitution = collider.restitution;
    }else{
        // give a default value
        shapeDef.restitution = 0.0f;
    }
    
    // create shape
    b2CreatePolygonShape(body, &shapeDef, &boxShape);

    // set the interpolation current state
    interpolation.current.posX = transform.position.x;
    interpolation.current.posY = transform.position.y;

    // set the previous state to be current as well
    interpolation.previous = interpolation.current;

    // create Physics object
    PhysicsObject obj;
    obj.transform = &transform;
    obj.collider = &collider;
    obj.rb = &rigidbody;
    obj.inter = &interpolation;

    // store object
    physicsObjs.push_back(obj);

    return obj;
}

void Physics::RegisterPhysicsObject(Transform2D &transform, BoxCollider2D &collider, Rigidbody2D &rigidbody){
    // check if world has been initialized
    if(!b2World_IsValid(world)){
        throw std::invalid_argument("ERROR: Physics hasn't been initialized");
    }

    //* set up transform, collider, and rigidbody of object

    // check if body is not null
    if(b2Body_IsValid(rigidbody.runtimeBody))
        return; // stop function

    // create body
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = RbToB2Types(rigidbody.bodyType);
    bodyDef.position = (b2Vec2){transform.position.x, transform.position.y};
    //! rotation set is in radians
    bodyDef.rotation = b2MakeRot(glm::degrees(transform.rotation));
    bodyDef.fixedRotation = rigidbody.fixedRotation;

    // create body 
    b2BodyId body = b2CreateBody(world, &bodyDef);
    rigidbody.runtimeBody = body;

    //TODO: Create options to make either a box or circle collider

    // set up box collider
    b2Polygon boxShape = b2MakeOffsetBox(collider.size.x * abs(transform.size.x), collider.size.y * abs(transform.size.y),
     {collider.offset.x, collider.offset.y}, collider.rotationOffset);

    // set up physics material
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = collider.density;

    // check that given friction is within a value range [0,1]
    if(collider.friction > 0.0f && collider.friction <= 1.0f){
        shapeDef.friction = collider.friction;
    }else{
        // give a default value
        shapeDef.friction = 0.5f;
    }

    // check that given restitution is within a value range [0,1]
    if(collider.restitution > 0.0f && collider.restitution <= 1.0f){
        shapeDef.restitution = collider.restitution;
    }else{
        // give a default value
        shapeDef.restitution = 0.0f;
    }

    // create shape
    b2CreatePolygonShape(body, &shapeDef, &boxShape);

    // create Physics object
    PhysicsObject obj;
    obj.transform = &transform;
    obj.collider = &collider;
    obj.rb = &rigidbody;

    // store object
    physicsObjs.push_back(obj);
}

void Physics::RegisterPhysicsObject(Transform2D &transform, BoxCollider2D &collider, Rigidbody2D &rigidbody, Interpolation& interpolation){
    // check if world has been initialized
    if(!b2World_IsValid(world)){
        throw std::invalid_argument("ERROR: Physics hasn't been initialized");
    }

    //* set up transform, collider, and rigidbody of object

    // check if body is not null
    if(b2Body_IsValid(rigidbody.runtimeBody))
        return; // stop function

    // create body
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = RbToB2Types(rigidbody.bodyType);
    bodyDef.position = (b2Vec2){transform.position.x, transform.position.y};
    //! rotation set is in radians
    bodyDef.rotation = b2MakeRot(glm::radians(transform.rotation));
    bodyDef.fixedRotation = rigidbody.fixedRotation;

    // create body 
    b2BodyId body = b2CreateBody(world, &bodyDef);
    rigidbody.runtimeBody = body;

    //TODO: Create options to make either a box or circle collider

    // set up box collider
    b2Polygon boxShape = b2MakeOffsetBox(collider.size.x * abs(transform.size.x), collider.size.y * abs(transform.size.y),
     {collider.offset.x, collider.offset.y}, collider.rotationOffset);

    // set up physics material
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = collider.density;

    // check that given friction is within a value range [0,1]
    if(collider.friction > 0.0f && collider.friction <= 1.0f){
        shapeDef.friction = collider.friction;
    }else{
        // give a default value
        shapeDef.friction = 0.5f;
    }

    // check that given restitution is within a value range [0,1]
    if(collider.restitution > 0.0f && collider.restitution <= 1.0f){
        shapeDef.restitution = collider.restitution;
    }else{
        // give a default value
        shapeDef.restitution = 0.0f;
    }

    // create shape
    b2CreatePolygonShape(body, &shapeDef, &boxShape);

    // set the interpolation current state
    interpolation.current.posX = transform.position.x;
    interpolation.current.posY = transform.position.y;

    // set the previous state to be current as well
    interpolation.previous = interpolation.current;

    // create Physics object
    PhysicsObject obj;
    obj.transform = &transform;
    obj.collider = &collider;
    obj.rb = &rigidbody;
    obj.inter = &interpolation;

    // store object
    physicsObjs.push_back(obj);
}

void Physics::SetPhysicsSubStepIterations(int32_t iter){
    // set up automatic clear()
    SetUpAutoClear();
    // check if given value is less than 1
    if(iter < 1){
        return; // stop function
    }

    // set given value 
    substepIterations = iter;
}

void Physics::UpdateWorld(float deltaTime){
    if(b2World_IsValid(world)){
        // update any collisions detection, but not update the rigidbodies position
        b2World_Step(world, deltaTime, substepIterations);
    }
}

void Physics::UpdatePhysics(){
    // check if world has been initialized
    if(!b2World_IsValid(world))
        return; // stop function

    // update each physics object
    for(PhysicsObject& obj : physicsObjs){
        // retrieve the body
        b2BodyId id = obj.rb->runtimeBody;
        // get position change
        const b2Vec2 position = b2Body_GetPosition(id);

        // update each object's transform
        obj.transform->position.x = position.x;
        obj.transform->position.y = position.y;
        obj.transform->rotation = glm::degrees(b2Rot_GetAngle(b2Body_GetRotation(id)));

        // check if interpolation is set
        if(obj.inter != nullptr){
            // update previous state 
            obj.inter->previous = obj.inter->current;

            //update the position as the current state
            obj.inter->current.posX = position.x;
            obj.inter->current.posY = position.y;
        }
    }
}

void Physics::UpdateRegisteredObject(Transform2D &transform, Rigidbody2D &rigidbody){
    // check if body is not null
    if(!b2Body_IsValid(rigidbody.runtimeBody))
        return; // stop function

    // update the registered object
    b2BodyId id = rigidbody.runtimeBody;

    // get position change
    const b2Vec2 position = b2Body_GetPosition(id);

    // update component transform
    transform.position.x = position.x;
    transform.position.y = position.y;
    transform.rotation = glm::degrees(b2Rot_GetAngle(b2Body_GetRotation(id)));
}

void Physics::UpdateRegisteredObject(Transform2D &transform, Rigidbody2D &rigidbody, Interpolation& inter){
    // check if body is not null
    if(!b2Body_IsValid(rigidbody.runtimeBody))
        return; // stop function

    // update the registered object
    b2BodyId id = rigidbody.runtimeBody;

    // get position change
    const b2Vec2 position = b2Body_GetPosition(id);

    // update component transform
    transform.position.x = position.x;
    transform.position.y = position.y;
    transform.rotation = glm::degrees(b2Rot_GetAngle(b2Body_GetRotation(id)));

    // update previous state 
    inter.previous = inter.current;

    //update the position as the current state
    inter.current.posX = position.x;
    inter.current.posY = position.y;
}

void Physics::Clear(){
    // remove reference to components of each Physics object
    for(PhysicsObject& obj : physicsObjs){
        obj.transform = nullptr;
        obj.collider = nullptr;
        obj.rb = nullptr;
        obj.inter = nullptr;

        delete obj.transform;
        delete obj.collider;
        delete obj.rb;
        delete obj.inter;
    }

    // destroy the world
    b2DestroyWorld(world);
}

bool Physics::AABBCollision(Transform2D& a, Transform2D& b){
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