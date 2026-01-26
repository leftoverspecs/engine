#version 330 core

in vec3 normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 color = (ambient + diffuse) * objectColor;
    FragColor = vec4(color, 1.0);
    /*if (norm.x > 0) {
       FragColor = vec4(norm.x, 0.0, 0.0, 1.0);
    } else {
       FragColor = vec4(0.0, -norm.x, 0.0, 1.0);
    }*/
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
