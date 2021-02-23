//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#include "player.h"
#include "game.h"
#include "input.h"
#include "time.h"

#define EPSILON 10

using namespace Verse;

namespace {
    Component::Actor* actor;
    ui64 jump_time = 0;
    ui64 coyote_time = 0;
    bool previouslyOnGround = false;
}

bool Controller::Player::controller(Scene &scene, EntityID eid) {
    actor = scene.getComponent<Component::Actor>(eid);
    
    //MOVE X
    if (Input::down(Input::Key::Left) or Input::down(Input::Key::A))
        actor->vel.x -= actor->acc_ground * DELTA;
    if (Input::down(Input::Key::Right) or Input::down(Input::Key::D))
        actor->vel.x += actor->acc_ground * DELTA;
    
    if (abs(actor->vel.x) > actor->max_move_speed)
        actor->vel.x = sign(actor->vel.x) * actor->max_move_speed;
    
    if (!Input::down(Input::Key::Left) && !Input::down(Input::Key::Right)) {
        if (abs(actor->vel.x) > EPSILON)
            actor->vel.x -= sign(actor->vel.x) * (1 / actor->friction_ground) * actor->max_move_speed * DELTA;
        else
            actor->vel.x = 0;
    }
    
    
    //JUMP
    if (Input::pressed(Input::Key::Space)) {
        
        if (actor->isOnGround or previouslyOnGround) {
            jump();
        } else {
            jump_time = Time::current;
        }
    }
    
    //Coyote Time
    if (actor->isOnGround)
        previouslyOnGround = true;
    if (!actor->isOnGround and previouslyOnGround and coyote_time == 0)
        coyote_time = Time::current;
    
    if (coyote_time != 0) {
        int diff = (int)(Time::current - coyote_time);
        
        if (diff > actor->jump_coyote) {
            previouslyOnGround = false;
            coyote_time = 0;
        }
    }
    
    //Jump Grace
    if (jump_time != 0) {
        int diff = (int)(Time::current - jump_time);
        
        if (actor->isOnGround)
            jump();
        
        if (diff > actor->jump_grace)
            jump_time = 0;
    }
    
    
    //RESPAWN
    Component::Collider* collider = scene.getComponent<Component::Collider>(eid);
    if (collider->transform.pos.y > 500) {
        collider->transform.pos = Vec2(40, 100); //TODO: Change for a propper spawn
    }
    
    
    return actor->vel != Vec2(0,0);
}

void Controller::Player::jump() {
    actor->vel.y = -actor->jump_impulse;
    jump_time = 0;
    
    actor->isOnGround = false;
    previouslyOnGround = false;
}
