#include <WindowConfig.h>


WindowConfig::WindowConfig(
        const std::string& Title,
        const glm::ivec2& Size,
        const glm::ivec2& Position,
        const unsigned int DisplayMode
) {
    this->Title = Title;
    this->Size = Size;
    this->Position = Position;
    this->DisplayMode = DisplayMode;
}
