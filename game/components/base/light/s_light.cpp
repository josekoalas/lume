//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#include "s_light.h"

#include <map>

#include "game.h"
#include "ftime.h"
#include "r_opengl.h"
#include "r_renderer.h"

#include "gui.h"
#include "gui_types.h"

#define LIGHT_PERIOD 5
#define LIGHT_VARIATION 5
#define LIGHT_CENTER_RADIUS 0.25

using namespace Verse;

std::vector<glm::vec4> System::Light::render(Config &c, ui8 pid) {
    std::vector<glm::vec4> light_data;
    
    for (EntityID e : SceneView<Component::Light>(*c.active_scene)) {
        Component::Light* light = c.active_scene->getComponent<Component::Light>(e);
        Component::Texture* tex = c.active_scene->getComponent<Component::Texture>(e);
        
        float variation = sin(time() * 0.001f * LIGHT_PERIOD * c.game_speed) * LIGHT_VARIATION;
        float radius_with_var = ((light->radius + variation) > 2.0f) ? light->radius + variation : 2.0f; //Prevent visual errors
        
        light->render_data = glm::vec4(light->pos.x, light->pos.y, radius_with_var, light->radius * LIGHT_CENTER_RADIUS);
        if (tex != nullptr)
            light->render_data += glm::vec4(tex->render_pos.x, tex->render_pos.y, 0, 0);
        
        light->render_data.x /= c.resolution.x + 2.0f*BORDER_WIDTH;
        light->render_data.y = 1.0f - light->render_data.y / (c.resolution.y + 2.0f*BORDER_WIDTH);
        light->render_data.z /= c.resolution.x + 2.0f*BORDER_WIDTH;
        light->render_data.w /= c.resolution.x + 2.0f*BORDER_WIDTH;
        
        light->render_data.x += (0.5f * c.resolution.x - BORDER_WIDTH - (float)floor(c.active_camera->render_pos.x)) / (c.resolution.x + 2.0f*BORDER_WIDTH);
        light->render_data.y -= (0.5f * c.resolution.y - BORDER_WIDTH - (float)floor(c.active_camera->render_pos.y)) / (c.resolution.y + 2.0f*BORDER_WIDTH);
        
        //TODO: IMPROVE THIS SYSTEM, it needs to be more elegant
        
        light_data.push_back(light->render_data);
    }
    
    return light_data;
}

void System::Light::load(EntityID eid, YAML::Node &entity, Scene *s, Config &c) {
    Component::Light* light = s->addComponent<Component::Light>(eid);
    if (entity["light"]["pos"])
        light->pos = entity["light"]["pos"].as<Vec2>();
    if (entity["light"]["radius"])
        light->radius = entity["light"]["radius"].as<int>();
}

void System::Light::save(Component::Light *light, str path, std::vector<str> &key) {
    key[2] = "light";
    
    key[3] = "pos";
    Serialization::appendYAML(path, key, light->pos, true);
    
    key[3] = "radius";
    Serialization::appendYAML(path, key, light->radius, true);
}

void System::Light::gui(Config &c, EntityID eid) {
#ifndef DISABLE_GUI
    Component::Light* light = c.active_scene->getComponent<Component::Light>(eid);
    if (light == nullptr)
        return;
    
    Verse::Gui::draw_vec2(light->pos.x, light->pos.y, "pos", eid);
    ImGui::TableNextRow();
    
    Verse::Gui::draw_float(light->radius, "radius", eid);
#endif
}
