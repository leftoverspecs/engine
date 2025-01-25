#version 330 core
in vec2 frag_texture_coord;

uniform sampler2D source_texture;
uniform vec4 tint;
uniform float gamma;
uniform float exposure;

out vec4 FragColor;

void main() {
    vec3 color = texture(source_texture, frag_texture_coord).rgb * tint.rgb;
    vec3 result = vec3(1.0) - exp(-(color) * exposure);
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, tint.a);
}
