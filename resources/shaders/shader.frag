#version 300 es


in lowp vec4 ex_Color;

out lowp vec4 out_Color;

uniform lowp int ColourCode;


void main() {
    switch (ColourCode) {
        case 1:
            out_Color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
            break;

        case 2:
            out_Color = vec4(0.1f, 0.8f, 0.1f, 1.0f);
            break;

        default:
            out_Color = ex_Color;
    }
}
