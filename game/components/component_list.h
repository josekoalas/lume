//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#pragma once

#include "c_collider.h"
#include "c_texture.h"
#include "c_animation.h"
#include "c_actor.h"
#include "c_tilemap.h"
#include "c_light.h"
#include "c_camera.h"
#include "c_fire.h"
#include "c_scene_transition.h"
#include "c_player.h"

#define COMPONENTS logComponentID(Collider); \
                   logComponentID(Texture); \
                   logComponentID(Animation); \
                   logComponentID(Actor); \
                   logComponentID(Tilemap); \
                   logComponentID(Light); \
                   logComponentID(Camera); \
                   logComponentID(Fire); \
                   logComponentID(SceneTransition); \
                   logComponentID(Player); \

#define COLLIDER
#define TEXTURE
#define ANIMATION
#define ACTOR
#define TILEMAP
#define LIGHT
#define CAMERA
#define FIRE
#define SCENE_TRANSITION
#define PLAYER
