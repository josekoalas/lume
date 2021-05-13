//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#include "player_controller.h"
#include "game.h"
#include "input.h"
#include "time.h"

#define EPSILON 10

using namespace Verse;

namespace {
    int jump_impulse = 220;
    int min_jump_impulse = 70;
    int jump_grace = 150;
    int jump_coyote = 100;

    Component::Actor* actor;
    Component::Animation* anim;
    ui64 jump_time = 0;
    ui64 coyote_time = 0;
    bool on_jump = false;
    bool previously_on_ground = false;

    int flame_offsets[18] = { 0, 0, 0, 1, 0, 1, -1, 1, 1, 1, 1, -1, 0, 0, 1, 1, 1, 2 };
    int flame_horizonal_offset = 0;
    Vec2 flame_initial_offset = Vec2(-1, -1);
}

bool Controller::Player::controller(Scene &scene, EntityID eid) {
    actor = scene.getComponent<Component::Actor>(eid);
    anim = scene.getComponent<Component::Animation>(eid);
    
    //MOVE X
    if (Input::down(Input::Key::Left) or Input::down(Input::Key::A))
        actor->vel.x -= actor->acc_ground * DELTA;
    if (Input::down(Input::Key::Right) or Input::down(Input::Key::D))
        actor->vel.x += actor->acc_ground * DELTA;
    
    if (Input::down(Input::Key::Left) or Input::down(Input::Key::A) or Input::down(Input::Key::Right) or Input::down(Input::Key::D)) {
        anim->curr_key = "walk_1";
        flame_horizonal_offset = -sign(actor->vel.x);
    } else {
        anim->curr_key = "idle_1";
        flame_horizonal_offset = 0;
    }
    
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
        if (actor->is_on_ground or previously_on_ground) {
            jump();
        } else {
            jump_time = Time::current;
        }
    }
    //Stop Jump
    if (Input::released(Input::Key::Space) and on_jump) {
        on_jump = false;
        
        if (-actor->vel.y > min_jump_impulse)
            actor->vel.y = -min_jump_impulse;
    }
    //Coyote Time
    if (actor->is_on_ground) {
        previously_on_ground = true;
        on_jump = false;
    }
    if (!actor->is_on_ground and previously_on_ground and coyote_time == 0 and !on_jump)
        coyote_time = Time::current;
    
    if (coyote_time != 0) {
        int diff = (int)(Time::current - coyote_time);
        
        if (diff > jump_coyote) {
            previously_on_ground = false;
            coyote_time = 0;
        }
    }
    //Jump Grace
    if (jump_time != 0) {
        int diff = (int)(Time::current - jump_time);
        
        if (actor->is_on_ground)
            jump();
        
        if (diff > jump_grace)
            jump_time = 0;
    }
    
    //Jump Animation
    if (not actor->is_on_ground) {
        anim->curr_key = "jump_up";
    }
    
    //FLAME
    Component::Fire* fire = scene.getComponent<Component::Fire>(eid);
    fire->offset = flame_initial_offset - Vec2(flame_horizonal_offset, flame_offsets[anim->frames[anim->curr_key][anim->curr_frame]]);
    
    //RESPAWN
    Component::Collider* collider = scene.getComponent<Component::Collider>(eid);
    if (collider->transform.y > 500) {
        collider->transform = Vec2(32, 64); //TODO: Change for a propper spawn
    }
    
    return actor->vel != Vec2f(0,0);
}

void Controller::Player::jump() {
    actor->vel.y = -jump_impulse;
    jump_time = 0;
    on_jump = true;
    
    actor->is_on_ground = false;
    previously_on_ground = false;
}
