//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#include <SDL2/SDL.h>

#include "log.h"
#include "config.h"
#include "game.h"
#include "serialization.h"

#include "r_textures.h"

//#include "state_machines_list.h"
//#include "state_table.h"

using namespace Verse;
//using namespace State;
//using namespace Player;

int main(int argc, const char * argv[]) {
    
    Config config = {
        .name = "Proxecto Lume",
        .version = "0.1.8",
        
        .resolution = Vec2(256, 180),
        .window_size = Vec2(1024, 720),
        .render_scale = 4,
        .enable_gui = true,
        .use_vsync = true,
        
        .game_speed = 1.0f,
        
        .use_grayscale = false,
        .use_light = true,
        .palette_index = 0,
        .num_palettes = 4,
        .background_color = {0.0, 0.0, 0.0, 1.0},
        
        .gravity = 800,
        .gravity_dir = Vec2f(0, 1)
    };
    
    Serialization::initYAML();
    bool running = Game::init(config);
    Component::registerComponents();
    
    
    Scene* scene = new Scene();
    
    Serialization::loadScene("test_scene", scene, config); //Always scene before player, if not camera no bounds
    EntityID player = Serialization::loadPlayer(scene, config);
    
    for (EntityID e : SceneView<Component::SceneTransition>(*scene)) {
        Component::SceneTransition* t = scene->getComponent<Component::SceneTransition>(e);
        t->to_scene = new Scene();
        Serialization::loadScene(t->scene_name, t->to_scene, config);
    }
    
    config.active_camera = scene->getComponent<Component::Camera>(player);
    if (config.active_camera == nullptr)
        log::error("Failed to get the active camera!");
    
    config.active_scene = scene;
    
    
    //Types eventTypes = Types<JumpEvent, ReleaseJumpEvent, PeakJumpEvent, FallEvent, DownEvent, ReleaseDownEvent, TouchGroundEvent, TimeoutEvent>{};
    //std::cout << generatePrettyTransitionTable(JumpSM::getStateTypes(), eventTypes).c_str() << std::endl;
    //Types eventTypes = Types<MoveEvent, StopMovingEvent>{};
    //std::cout << generatePrettyTransitionTable(MoveSM::getStateTypes(), eventTypes).c_str() << std::endl;
    
    
    while (running)
        running = Game::update(config);
    
    
    Game::stop();
    
    return EXIT_SUCCESS;
}
