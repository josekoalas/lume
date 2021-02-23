//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#include "s_texture.h"

using namespace Verse;

void System::Texture::render(Scene &scene, SDL_Renderer* renderer) {
    for (EntityID e : SceneView<Component::Texture>(scene)) {
        Component::Texture* tex = scene.getComponent<Component::Texture>(e);
        
        SDL_Rect src = Rect(Vec2(), tex->transform.size).toSDL();
        SDL_Rect dst = Rect((tex->transform.pos + tex->offset) * RENDER_SCALE, tex->transform.size * RENDER_SCALE).toSDL();
        
        SDL_RenderCopy(renderer, tex->tex, &src, &dst);
    }
}
