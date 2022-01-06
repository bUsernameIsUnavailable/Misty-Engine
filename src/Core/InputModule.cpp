#include <Misty/Core/InputModule.h>


namespace Misty::Core {
    void InputModule::ProcessKeyboardKeys(
            const unsigned char Key,
            [[maybe_unused]] const int X,
            [[maybe_unused]] const int Y
    ) noexcept {
        switch (Key) {
            case EscKey:
                Engine->Listen(this, "Quit");
                break;

            case '+':
                // dist += 5.0f;
                break;

            case '-':
                // dist -= 5.0f;
                break;

            default:
                break;
        }
    }

    void InputModule::ProcessSpecialKeys(
            const int Key,
            [[maybe_unused]] const int X,
            [[maybe_unused]] const int Y
    ) noexcept {
        switch (Key) {
            case GLUT_KEY_UP:
                // alpha += 0.05f;
                break;

            case GLUT_KEY_DOWN:
                // alpha -= 0.05f;
                break;

            case GLUT_KEY_RIGHT:
                // beta += 0.01f;
                break;

            case GLUT_KEY_LEFT:
                // beta -= 0.01f;
                break;

            default:
                break;
        }
    }
}
