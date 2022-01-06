#include <Misty/Core/ClockModule.h>


namespace Misty::Core {
    void ClockModule::Tick() {
        const float& CurrentFrame = (float) glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        DeltaFrame = CurrentFrame - LastFrame;
        LastFrame = CurrentFrame;
    }
}
