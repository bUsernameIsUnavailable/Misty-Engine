#include <Misty/Core/Engine.h>


namespace Misty::Core {
    void RedrawCallback(const int Value = 0) {
        if (Value == -1)
            return;

        if (Engine::Get()->GetWindowId() != -1) {
            glutPostRedisplay();
        }

        glutTimerFunc(0u, RedrawCallback, Value);
    }


    Engine::Engine() {
        Clock->SetListener(this);
        Input->SetListener(this);
        Renderer->SetListener(this);
    }

    void Engine::Initialise() {
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
        glutInitWindowSize((int) WindowWidth, (int) WindowHeight);
        glutInitWindowPosition(100, 30);
        glutInitDisplayMode(bDoubleBuffer * GLUT_DOUBLE | GLUT_DEPTH | GLUT_WINDOW_RGBA);
        CHECK(WindowId = glutCreateWindow("Misty Engine"), "GLUT failed to create a window!");

        glewExperimental = GL_TRUE;
        CHECK(glewInit() == GLEW_OK, "GLEW failed to initialise!");

        glutTimerFunc(0u, RedrawCallback, 0);
        glutTimerFunc(0u, TimeModule::CalculateFpsCallback, 0);

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
        glutInit(Argcp, Argv);
        CHECK(!bRunning, "Engine has already started!");
        Initialise();

        Clock->Start();
        Input->Start();
        Renderer->Start();

        bRunning = true;
    }

    void Engine::Update() noexcept {
        Clock->Tick();
        glutMainLoopEvent();
    }

    void Engine::Quit() noexcept {
        Renderer->DestroyShaders();
        Renderer->DestroyVbo();

        WindowId = -1;
        bRunning = false;
        Registry.clear();
    }

    void* Engine::Listen(Utils::IModule* const Module, const Utils::MistyEvent& Event) noexcept {
        const std::string& ModuleName = Module ? Module->GetName() : "Client";
        std::fprintf(stdout, "Event: %s ---> %s\n", ModuleName.c_str(), MistyEventNames.at(Event).c_str());

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
