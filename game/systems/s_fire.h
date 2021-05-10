//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#pragma once

#include "dtypes.h"
#include "log.h"
#include "c_fire.h"
#include "scene.h"
#include "config.h"

namespace Verse::System::Fire
{
    void init(Component::Fire* fire);
    void render(Scene &scene, Config &c);
}
