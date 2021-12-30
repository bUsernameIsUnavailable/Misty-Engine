#version 460


layout(location = 0u) in vec4 in_Position;
layout(location = 1u) in vec4 in_Color;
layout(location = 2u) in vec3 in_Normal;

out vec4 gl_Position;
out vec4 ex_Color;

uniform mat4 matrUmbra;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec4 lightColor;
uniform int ColourCode;


void main() {
    switch (ColourCode) {
        case 1:
            gl_Position = ProjectionMatrix * ViewMatrix * matrUmbra * in_Position;
            break;

        default: {
            gl_Position = ProjectionMatrix * ViewMatrix * in_Position;/*
            vec3 Normal = mat3(ProjectionMatrix * ViewMatrix) * in_Normal;
            vec3 Normal = in_Normal;
            vec3 inLightPos = vec3(ProjectionMatrix * ViewMatrix * vec4(lightPos, 1.0f));
            vec3 inViewPos = vec3(ProjectionMatrix * ViewMatrix * vec4(viewPos, 1.0f));
            vec3 FragPos = vec3(gl_Position);

            // Ambient
            float ambientStrength = 0.2f;
            vec4 ambient = ambientStrength * lightColor;

            // Diffuse
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(inLightPos - FragPos);
            // vec3 lightDir = normalize(-inLightPos); // pentru sursa directionala
            float diff = max(dot(norm, lightDir), 0.0);
            // vec3 diffuse = diff * lightColor;
            vec4 diffuse = pow(diff, 0.2f) * lightColor; // varianta de atenuare

            // Specular
            float specularStrength = 0.5f;
            vec3 viewDir = normalize(inViewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 1.0f);
            vec4 specular = specularStrength * spec * lightColor;

            ex_Color = (ambient + diffuse) * in_Color;*/
            ex_Color = in_Color;
        }
    }
}
