//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#pragma once

#include "dtypes.h"
#include "log.h"
#include "ecs.h"
#include "scene.h"
#include "config.h"

namespace Verse::System::Light
{
    void init(SDL_Renderer* renderer, Config &c);
    void render(Scene &scene, Config &c);
    void passToShader(ui8 pid, Config &c);
    void clean();
}
