#version 460


in vec4 ex_Color;

out vec4 out_Color;

uniform int ColourCode;


void main() {
    switch (ColourCode) {
        case 1:
            out_Color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
            break;

        default:
            out_Color = ex_Color;
    }
}
