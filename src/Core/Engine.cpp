#include <Misty/Core/Engine.h>


namespace Misty::Core {
    bool Engine::bIsRunning = false;


    void RedrawCallback(const int Value = 1) {
        if (Value == 0)
            return;

        if (Engine::Get()->GetWindowId() != -1) {
            glutPostRedisplay();
        }

        glutTimerFunc(0u, RedrawCallback, 1);
    }


    Engine::Engine() {
        Clock->SetListener(this);
        Input->SetListener(this);
        Renderer->SetListener(this);
    }

    void Engine::Initialise(int* const Argcp, char** const Argv) {
        glutInit(Argcp, Argv);

        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
        glutInitWindowSize((int) WindowWidth, (int) WindowHeight);
        glutInitWindowPosition(100, 30);
        glutInitDisplayMode(GLUT_RGBA | bDoubleBuffer * GLUT_DOUBLE | GLUT_DEPTH);
        CHECK(WindowId = glutCreateWindow("Misty Engine"), "GLUT failed to create a window!");

        glewExperimental = GL_TRUE;
        CHECK(glewInit() == GLEW_OK, "GLEW failed to initialise!");

        glutTimerFunc(0u, RedrawCallback, 1);
        glutTimerFunc(0u, TimeModule::CalculateFpsCallback, 1);

        glutKeyboardFunc([](const unsigned char Key, const int X, const int Y) noexcept {
            ControlsModule::Get()->ProcessKeyboardKeys(Key, X, Y);
        });
        glutSpecialFunc([](const int Key, const int X, const int Y) noexcept {
            ControlsModule::Get()->ProcessSpecialKeys(Key, X, Y);
        });

        glutDisplayFunc([]() { RenderModule::Get()->Draw(); });
        glutReshapeFunc([](const int Width, const int Height) {
            Engine::Get()->SetWindowWidth(Width);
            Engine::Get()->SetWindowHeight(Height);
            glViewport(0, 0, (GLsizei) Engine::Get()->GetWindowWidth(), (GLsizei) Engine::Get()->GetWindowHeight());
        });
        glutCloseFunc([]() { Engine::Get()->Quit(); });
    }

    void Engine::Start(int* const Argcp, char** const Argv) {
        CHECK(!bIsRunning, "Engine has already started!");
        Initialise(Argcp, Argv);

        Clock->Start();
        Input->Start();
        Renderer->Start();

        bIsRunning = true;
    }

    void Engine::Update() noexcept {
        Clock->Tick();
        glutMainLoopEvent();
    }

    void Engine::Quit() noexcept {
        Renderer->DestroyShaders();
        Renderer->DestroyVbo();

        WindowId = -1;
        bIsRunning = false;
        Registry.clear();
    }

    void* Engine::Listen(Utils::IModule* const Module, const Utils::MistyEvent& Event) noexcept {
        std::fprintf(stdout, "Event: %s ---> %s\n", typeid(*Module).name(), MistyEventNames.at(Event).c_str());

        switch (Event) {
            case Utils::MistyEvent::GET_CAMERA_DEPTH:
                return (void*) &Input->GetCameraDepth();

            case Utils::MistyEvent::GET_HORIZONTAL:
                return (void*) &Input->GetHorizontal();

            case Utils::MistyEvent::GET_VERTICAL:
                return (void*) &Input->GetVertical();

            case Utils::MistyEvent::GET_AVERAGE_FPS:
                return (void*) &TimeModule::GetAverageFps();

            case Utils::MistyEvent::QUIT:
                Quit();
                break;

            case Utils::MistyEvent::NONE:
            default:
                break;
        }

        return nullptr;
    }
}
