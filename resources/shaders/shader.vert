#version 300 es


layout(location = 0u) in mediump vec4 in_Position;
layout(location = 1u) in lowp vec3 in_Normal;
layout(location = 2u) in lowp vec4 in_Color;
layout(location = 3u) in mediump mat4 in_Model;

out lowp vec4 ex_Color;

uniform highp mat4 ProjectionMatrix;
uniform mediump mat4 ViewMatrix;
uniform mediump vec4 ShadowPosition;
uniform mediump vec4 LightPosition;
uniform mediump vec3 ViewPosition;
uniform lowp vec4 LightColour;
uniform lowp int ColourCode;


void main() {
    mat4 PerspectiveMatrix = ProjectionMatrix * ViewMatrix;
    vec4 ModelTransform = in_Model * in_Position;

    switch (ColourCode) {
        case 1:
            mat4 ShadowMatrix = mat4(
                -ShadowPosition.x * LightPosition,
                -ShadowPosition.y * LightPosition,
                -ShadowPosition.z * LightPosition,
                -ShadowPosition.w * LightPosition
            ) + mat4(dot(ShadowPosition * LightPosition, vec4(1.0f)));

            gl_Position = PerspectiveMatrix * ShadowMatrix * ModelTransform;
            break;

        default:
            gl_Position = PerspectiveMatrix * ModelTransform;

            vec3 Normal = normalize(mat3(PerspectiveMatrix) * in_Normal);
            vec3 LightDirection = normalize(vec3(PerspectiveMatrix * LightPosition - gl_Position));

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
