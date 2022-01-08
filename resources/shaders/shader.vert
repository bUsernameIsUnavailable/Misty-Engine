#version 300 es


layout(location = 0u) in mediump vec4 in_Position;
layout(location = 1u) in lowp vec4 in_Color;
layout(location = 2u) in lowp vec3 in_Normal;

out lowp vec4 ex_Color;

uniform highp mat4 ProjectionMatrix;
uniform mediump mat4 ViewMatrix;
uniform mediump mat4 ShadowMatrix;
uniform mediump vec3 LightPosition;
uniform mediump vec3 ViewPosition;
uniform lowp vec4 LightColour;
uniform lowp int ColourCode;


void main() {
    mat4 PerspectiveMatrix = ProjectionMatrix * ViewMatrix;

    switch (ColourCode) {
        case 1:
            gl_Position = PerspectiveMatrix * ShadowMatrix * in_Position;
            break;

        default:
            gl_Position = PerspectiveMatrix * in_Position;

            vec3 Normal = normalize(mat3(PerspectiveMatrix) * in_Normal);
            vec3 LightDirection = normalize(vec3(PerspectiveMatrix * vec4(LightPosition, 1.0f) - gl_Position));

            float AmbientValue = 0.2f;
            float DiffuseValue = pow(
                max(0.0f, dot(Normal, LightDirection)),
                0.2f
            );
            float SpecularValue = 0.5f * pow(
                max(0.0f, dot(
                    normalize(vec3(PerspectiveMatrix * vec4(ViewPosition, 1.0f) - gl_Position)),
                    reflect(-LightDirection, Normal)
                )),
                1.0f
            );

            ex_Color = (AmbientValue + DiffuseValue + SpecularValue) * LightColour * in_Color;
    }
}
