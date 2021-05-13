//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#pragma once

#include "dtypes.h"
#include "log.h"

#include "scene.h"
#include "config.h"

namespace Verse::Controller::FreeActor
{
    bool controller(Scene &s, Config &c, EntityID eid);
}

