//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#pragma once

#include "component_list.h"

//Base
#include "s_collider.h"
#include "s_actor.h"
#include "s_state.h"
#include "s_texture.h"
#include "s_animation.h"
#include "s_tilemap.h"
#include "s_text.h"
#include "s_camera.h"
#include "s_light.h"
#include "s_timer.h"
#include "s_patrol.h"
#include "s_scene_transition.h"
#include "s_noise.h"

//Extra
#include "s_player.h"

#define PHYSICS_UPDATE_SYSTEMS System::Actor::update(c); \
                               System::Noise::update(c); \
                               System::Camera::update(c);

#define RENDER_SYSTEMS System::Camera::prerender(c); \
                       System::Tilemap::render(c); \
                       if (not c.tme_active) { \
                           System::Texture::render(c); \
                           System::Text::render(c); \
                           System::Noise::render(c); \
                       }
                       
