#include <Misty/Core/ControlsModule.h>


namespace Misty::Core {
    void ControlsModule::ProcessKeyboardKeys(
            const unsigned char Key,
            [[maybe_unused]] const int X,
            [[maybe_unused]] const int Y
    ) noexcept {
        switch (Key) {
            case ESC:
                Engine->Listen(this, Utils::MistyEvent::QUIT);
                break;

            case '+':
                CameraDepth += 5.0f;
                break;

            case '-':
                CameraDepth -= 5.0f;
                break;

            default:
                break;
        }
    }

    void ControlsModule::ProcessSpecialKeys(
            const int Key,
            [[maybe_unused]] const int X,
            [[maybe_unused]] const int Y
    ) noexcept {
        switch (Key) {
            case GLUT_KEY_RIGHT:
                Horizontal += 0.01f;
                break;

            case GLUT_KEY_LEFT:
                Horizontal -= 0.01f;
                break;

            case GLUT_KEY_UP:
                Vertical += 0.05f;
                break;

            case GLUT_KEY_DOWN:
                Vertical -= 0.05f;
                break;

            default:
                break;
        }
    }
}