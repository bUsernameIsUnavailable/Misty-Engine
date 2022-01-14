#ifndef MISTY_MACROS_H
#define MISTY_MACROS_H


#ifndef PI
#define PI 3.14159265359
#endif

#ifndef NDEBUG
#include <exception>


#define CHECK(Condition, Message, ...)                                                              \
do {                                                                                                \
    if (!(Condition)) {                                                                             \
        std::fprintf(stderr, "Assertion `%s` failed in %s(%d):\n", #Condition, __FILE__, __LINE__); \
        std::fprintf(stderr, Message, ##__VA_ARGS__);                                               \
        std::fprintf(stderr, "\n");                                                                 \
        std::terminate();                                                                           \
    }                                                                                               \
} while(false)

#else
#define CHECK(Condition, Message, ...) do if(!(Condition)) {} while(false)
#endif


#endif //MISTY_MACROS_H
