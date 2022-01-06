#version 300 es


layout(location = 0u) in mediump vec4 in_Position;
layout(location = 1u) in lowp vec4 in_Color;
layout(location = 2u) in lowp vec3 in_Normal;

out lowp vec4 ex_Color;

uniform highp mat4 ProjectionMatrix;
uniform mediump mat4 ViewMatrix;
uniform mediump mat4 matrUmbra;
uniform mediump vec3 lightPos;
uniform mediump vec3 viewPos;
uniform lowp vec3 objectColor;
uniform lowp vec4 lightColor;
uniform lowp int ColourCode;


void main() {
    switch (ColourCode) {
        case 1:
            gl_Position = ProjectionMatrix * ViewMatrix * matrUmbra * in_Position;
            break;

        default: {
            gl_Position = ProjectionMatrix * ViewMatrix * in_Position;
            vec3 Normal = mat3(ProjectionMatrix * ViewMatrix) * in_Normal;
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

            ex_Color = (ambient + diffuse) * in_Color;
        }
    }
}
