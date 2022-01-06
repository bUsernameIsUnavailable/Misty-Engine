#ifndef MISTY_ENGINE_H
#define MISTY_ENGINE_H

#include <Misty/Core/ClockModule.h>
#include <Misty/Core/InputModule.h>
#include <Misty/Core/RendererModule.h>


namespace Misty::Core {
    class Engine final : public Singleton<Engine>, public IEventListener {
        ClockModule* const Clock = ClockModule::Get();
        InputModule* const Input = InputModule::Get();
        RendererModule* const Renderer = RendererModule::Get();

        static bool bIsRunning;
        static int WindowID;

        static void Initialise(int*, char**);
        static void Quit() noexcept;

        Engine() noexcept;
        friend class Singleton<Engine>;

    public:
        void Start(int*, char**);
        void Update();

        void Listen(IModule*, const std::string&) const noexcept override;

        static inline const bool& IsRunning() noexcept { return bIsRunning; }
        static inline const int& GetWindow() noexcept { return WindowID; }

        Engine(const Engine&) noexcept = delete;
        Engine& operator= (const Engine&) noexcept = delete;


        static GLuint vaoId;
        static GLuint vboId1;
        static GLuint vboId2;
        static GLuint eboId1;
        static GLuint eboId2;
        static GLuint programId;
        static GLuint matrUmbraLocation;
        static GLuint viewLocation;
        static GLuint projLocation;
        static GLuint codColLocation;
        static GLuint lightColorLoc;
        static GLuint lightPosLoc;
        static GLuint viewPosLoc;
        static GLuint ColourCode;

        // elemente pentru matricea de vizualizare si matricea de proiectie
        static float obsx, obsy, obsz;
        static float refx, refy, refz;
        static float vx, vy, vz;
        static float alpha, beta, dist;
        static float width, height, znear, fov;

        // sursa de lumina
        static float xL, yL, zL;

        // matrice
        static glm::mat4 ViewMatrix, ProjectionMatrix, matrUmbra;

        static void createVbo();
        static void associateAttributePointers();
        static void destroyVbo();
        static GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath);
        static void createShaders();
        static void destroyShaders();
        static void initialize();
        static void renderFunction();
    };
}


#endif //MISTY_ENGINE_H
