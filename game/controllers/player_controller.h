//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#pragma once

#include "config.h"

typedef void (*actor_move_func)(Verse::Config&, Verse::EntityID);

namespace Verse::Controller::Player
{
    bool controller(Config &c, EntityID eid, actor_move_func move);
    void jump();
}
