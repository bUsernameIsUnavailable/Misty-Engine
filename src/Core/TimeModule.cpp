#include <Misty/Core/TimeModule.h>


namespace Misty::Core {
    unsigned int TimeModule::TicksPerSecond = 0u;
    float TimeModule::TotalFpsSumPerSecond = 0.0f;
    float TimeModule::AverageFps = 0.0f;


    void TimeModule::Tick() {
        ++TicksPerSecond;

        const float& CurrentFrame = (float) glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        DeltaFrame = CurrentFrame - LastFrame;
        LastFrame = CurrentFrame;

        TotalFpsSumPerSecond += 1.0f / DeltaFrame;
    }

    void TimeModule::CalculateFpsCallback(const int Value = 1) noexcept {
        if (Value == 0)
            return;

        if (TicksPerSecond != 0u) {
            AverageFps = TotalFpsSumPerSecond / (float) TicksPerSecond;
        }
        TotalFpsSumPerSecond = 0.0f;
        TicksPerSecond = 0u;

        glutTimerFunc(100u, CalculateFpsCallback, 1);
    }
}
