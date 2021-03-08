//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#include "imgui.h"
#ifndef USE_OPENGL
#include "imgui_sdl.h"
#endif
#include "gui.h"

#include "s_texture.h"
#include "s_tilemap.h"
#include "s_collider.h"
#include "s_light.h"

#include "r_pipeline.h"
#include "r_window.h"
#include "r_shader.h"
#include "r_opengl.h"
#include "r_renderer.h"
#include "r_textures.h"

using namespace Verse;
using namespace Graphics;

namespace {
    SDL_Window *window;
    int refresh_rate = 60;

    ui8* palette_tex;
}

void Graphics::init(Config &c) {
    
    //MODERN OPENGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    #ifndef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    #endif
    
    //CREATE A WINDOW
    window = Graphics::Window::createWindow(c);
    
    //REFRESH RATE
    Graphics::calculateRefreshRate();
    log::graphics("Refresh Rate: %d", refresh_rate);
    
    //RENDERER
    Renderer::GL::create(c, window);
    
    //PALETTE
    ui32 palette_pointer = 0;
    palette_tex = loadTexture("res/graphics/palette_multi.png", palette_pointer);
}


void Graphics::render(Scene &scene, Config &c, ui16 fps) {
    //CLEAR
    Renderer::GL::clear(c);
    
    //PRERENDER GUI
    if (c.enable_gui)
        Gui::prerender(scene, c, fps, window);
    
    //RENDER TEXTURES
    System::Tilemap::render(scene, c);
    System::Texture::render(scene, c);
    System::Light::render(scene, c);
    
    //RENDER DEBUG
    if (c.render_collision_boxes)
        System::Collider::render(scene, c);
    
    //RENDER FRAMEBUFFER
    Renderer::GL::render(c);
    
    //RENDER GUI
    if (c.enable_gui)
        Gui::render();
    
    //PRESENT
    Renderer::GL::present(window);
}


void Graphics::destroy() {
    Renderer::GL::destroy();
    SDL_DestroyWindow(window);
}


void Graphics::calculateRefreshRate() {
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    
    refresh_rate = mode.refresh_rate;
}


int Graphics::getRefreshRate() {
    return refresh_rate;
}
