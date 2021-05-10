#version 410 core

in vec2 f_tex_coord;

layout(location = 0) out vec4 color;

uniform sampler2D flame;
uniform sampler2D pnoise;
//uniform sampler2D wnoise;

void main() {
    float flame_value = texture(flame, f_tex_coord).x;
    float noise_value = texture(pnoise, f_tex_coord).x;
    //float wnoise_value = texture(wnoise, f_tex_coord).x;
    
    float s1 = step(noise_value, flame_value - 0.01f);
    //float s2 = step(wnoise_value, s1);
    
    if (s1 > 0.1f) {
        color = vec4(s1, s1, s1, 1.0f);
    } else {
        color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
}

