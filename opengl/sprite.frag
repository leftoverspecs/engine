#version 330 core
in vec4 frag_color;
in vec2 frag_texture_coord;

uniform sampler2D sprite_texture;

out vec4 FragColor;

void main() {
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    //vec4 color = texture(sprite_texture, frag_texture_coord);
    //if (color.a < 0.1) {
    //    discard;
    //} else {
    //    FragColor = color;
    //}
    //FragColor = vec4(texture(sprite_texture, vec2(0.75, 0.75)).rgb, 1.0);
    FragColor = texture(sprite_texture, frag_texture_coord) * frag_color;
}
