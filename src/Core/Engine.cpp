#include <Misty/Core/Engine.h>


namespace Misty::Core {
    bool Engine::bIsRunning = false;
    int Engine::WindowID = -1;
    float Fps = 0.0f;


    void TimedCallback(int Value = 1) {
        if (Value == 0)
            return;

        Fps = 1.0f / ClockModule::Get()->DeltaTime();
        glutTimerFunc(1000u, TimedCallback, 1);
    }

    void RedisplayCallback(int Value = 1) {
        if (Value == 0)
            return;

        if (Engine::GetWindow() != -1) {
            glutPostRedisplay();
        }
        glutTimerFunc(0u, RedisplayCallback, 1);
    }

    Engine::Engine() noexcept {
        Clock->SetListener(this);
        Input->SetListener(this);
        Renderer->SetListener(this);
    }

    void Engine::Initialise(int* const Argcp, char** const Argv) {
        glutInit(Argcp, Argv);
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

        glutInitWindowSize(1280, 720);
        glutInitWindowPosition(100, 30);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        CHECK(WindowID = glutCreateWindow("Misty Engine"), "GLUT failed to create a window!");

        CHECK(glewInit() == GLEW_OK, "GLEW failed to initialise!");

        glutIdleFunc([]() {}); //TODO
        glutDisplayFunc(renderFunction); //TODO
        glutKeyboardFunc(processNormalKeys); //TODO
        glutSpecialFunc(processSpecialKeys); //TODO
        glutTimerFunc(0u, TimedCallback, 1);
        glutTimerFunc(0u, RedisplayCallback, 1);
        glutCloseFunc(Quit); //TODO
    }

    void Engine::Start(int* const Argcp, char** const Argv) {
        CHECK(!bIsRunning, "Engine has already started!");

        Initialise(Argcp, Argv);
        initialize(); //TODO
        bIsRunning = true;

        Clock->Start();
    }

    void Engine::Update() {
        Clock->Tick();
        glutMainLoopEvent(); //TODO
    }

    void Engine::Quit() noexcept {
        destroyShaders(); //TODO
        destroyVbo(); //TODO

        WindowID = -1;
        bIsRunning = false;
    }

    void Engine::Listen(IModule* const Module, const std::string& Event) const noexcept {

    }


    GLuint Engine::vaoId;
    GLuint Engine::vboId1;
    GLuint Engine::vboId2;
    GLuint Engine::eboId1;
    GLuint Engine::eboId2;
    GLuint Engine::programId;
    GLuint Engine::matrUmbraLocation;
    GLuint Engine::viewLocation;
    GLuint Engine::projLocation;
    GLuint Engine::codColLocation;
    GLuint Engine::lightColorLoc;
    GLuint Engine::lightPosLoc;
    GLuint Engine::viewPosLoc;
    GLuint Engine::ColourCode;

    // elemente pentru matricea de vizualizare si matricea de proiectie
    float Engine::obsx, Engine::obsy, Engine::obsz;
    float Engine::refx = 0.0f, Engine::refy = 0.0f, Engine::refz = 100.0f;
    float Engine::vx = 0.0f, Engine::vy = 0.0f, Engine::vz = 1.0f;
    float Engine::alpha = 0.0f, Engine::beta = 0.0f, Engine::dist = 60.0f;
    float Engine::width = 1280.0f, Engine::height = 720.0f, Engine::znear = 0.1f, Engine::fov = 45.0f;

    // sursa de lumina
    float Engine::xL = 500.0f, Engine::yL = 0.0f, Engine::zL = 400.0f;

    // matrice
    glm::mat4 Engine::ViewMatrix, Engine::ProjectionMatrix, Engine::matrUmbra;


    void Engine::processNormalKeys(const unsigned char key, [[maybe_unused]] const int x, [[maybe_unused]] const int y)
    {
        switch (key)
        {
            case 27u:
                Quit(); //TODO
                break;

            case '-':
                dist -= 5.0f;
                break;

            case '+':
                dist += 5.0f;
                break;

            default:
                break;
        }
    }

    void Engine::processSpecialKeys(const int key, [[maybe_unused]] const int xx, [[maybe_unused]] const int yy)
    {
        switch (key)
        {
            case GLUT_KEY_LEFT:
                beta -= 0.01f;
                break;

            case GLUT_KEY_RIGHT:
                beta += 0.01f;
                break;

            case GLUT_KEY_UP:
                alpha += 0.05f;
                break;

            case GLUT_KEY_DOWN:
                alpha -= 0.05f;
                break;

            default:
                break;
        }
    }

    void Engine::createVbo() // sunt folosite doua buffere
    {
        // varfurile pentru cub si "ground"
        GLfloat vertices1[] = {
                // coordonate                   // culori			    // normale
                -50.0f, -50.0f, 50.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, -1.0f, -1.0f,

                50.0f, -50.0f, 50.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, -1.0f, -1.0f,

                50.0f, 50.0f, 50.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, 1.0f, -1.0f,

                -50.0f, 50.0f, 50.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, 1.0f, -1.0f,

                -50.0f, -50.0f, 150.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, -1.0f, 1.0f,

                50.0f, -50.0f, 150.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, -1.0f, 1.0f,

                50.0f, 50.0f, 150.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                1.0f, 1.0f, 1.0f,

                -50.0f, 50.0f, 150.0f, 1.0f,
                0.0f, 0.5f, 0.9f, 0.5f,
                -1.0f, 1.0f, 1.0f,

                //
                -1000.0f, -1000.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.5f, 1.0f,
                0.0f, 0.0f, 1.0f,

                1000.0f, -1000.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.5f, 1.0f,
                0.0f, 0.0f, 1.0f,

                1000.0f, 1000.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.5f, 1.0f,
                0.0f, 0.0f, 1.0f,

                -1000.0f, 1000.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 0.5f, 1.0f,
                0.0f, 0.0f, 1.0f
        };

        // indicii pentru varfuri
        GLubyte indices1[] = {
                1u, 2u, 0u, 2u, 0u, 3u,
                2u, 3u, 6u, 6u, 3u, 7u,
                7u, 3u, 4u, 4u, 3u, 0u,
                4u, 0u, 5u, 5u, 0u, 1u,
                1u, 2u, 5u, 5u, 2u, 6u,
                5u, 6u, 4u, 4u, 6u, 7u,
                9u, 10u, 8u, 10u, 8u, 11u
        };

        // varfurile pentru piramida
        GLfloat vertices2[] = {
                // coordonate                   // culori			     // normale
                -40.0f, -69.28f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                -40.0f, -69.28f, 80.0f,

                40.0f, -69.28f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                40.0f, -69.28f, 80.0f,

                80.0f, 0.0f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                80.0f, 0.0f, 80.0f,

                40.0f, 69.28f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                40.0f, 69.28f, 80.0f,

                -40.0f, 69.28f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                -40.0f, 69.28f, 80.0f,

                -80.0f, 0.0f, 70.0f, 1.0f,
                0.1f, 1.0f, 0.2f, 1.0f,
                -80.0f, 0.0f, 80.0f,

                0.0f, 0.0f, 170.0f, 1.0f,
                0.3f, 1.0f, 0.2f, 1.0f,
                0.0f, 0.0f, 1.0f
        };

        // indicii pentru piramida
        GLubyte indices2[] = {
                0u, 1u, 6u,
                1u, 2u, 6u,
                2u, 3u, 6u,
                3u, 4u, 6u,
                4u, 5u, 6u,
                5u, 0u, 6u
        };

        // se creeaza un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
        glGenVertexArrays(1u, &vaoId);
        glBindVertexArray(vaoId);
        glGenBuffers(1u, &vboId1);
        glGenBuffers(1u, &eboId1);
        glGenBuffers(1u, &vboId2);
        glGenBuffers(1u, &eboId2);

        glBindBuffer(GL_ARRAY_BUFFER, vboId1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId1);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vboId2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId2);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

        // se activeaza atributele
        glEnableVertexAttribArray(0u); // atributul 0 = pozitie
        glEnableVertexAttribArray(1u); // atributul 1 = culoare
        glEnableVertexAttribArray(2u); // atributul 2 = normale
    }

    void Engine::associateAttributePointers()
    {
        glVertexAttribPointer(0u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), nullptr);
        glVertexAttribPointer(1u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (4u * sizeof(GLfloat)));
        glVertexAttribPointer(2u, 3u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (8u * sizeof(GLfloat)));
    }

    void Engine::destroyVbo()
    {
        glDisableVertexAttribArray(2u);
        glDisableVertexAttribArray(1u);
        glDisableVertexAttribArray(0u);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glDeleteBuffers(1u, &vboId1);
        glDeleteBuffers(1u, &eboId1);
        glDeleteBuffers(1u, &vboId2);
        glDeleteBuffers(1u, &eboId2);

        glBindVertexArray(0u);
        glDeleteVertexArrays(1u, &vaoId);
    }

    GLuint Engine::loadShaders(const char* const vertexFilePath, const char* const fragmentFilePath)
    {
        // Creaza shadere
        GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        // Citeste din fisier shader-ul de varf
        std::string vertexShaderCode;
        std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
        if (vertexShaderStream.is_open())
        {
            std::string line;
            while (getline(vertexShaderStream, line)) {
                vertexShaderCode += line + "\n";
            }
            vertexShaderStream.close();
        }

        // Citeste din fisier shader-ul de fragment
        std::string fragmentShaderCode;
        std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
        if (fragmentShaderStream.is_open())
        {
            std::string line;
            while (getline(fragmentShaderStream, line)) {
                fragmentShaderCode += line + "\n";
            }
            fragmentShaderStream.close();
        }

        GLint result = GL_FALSE;
        int infoLogLength;

        // Compileaza shader-ul de varf
        const char* const vertexSourcePointer = vertexShaderCode.c_str();
        std::fprintf(stdout, "Compiling shader: %s\n", vertexFilePath);
        glShaderSource(vertexShaderId, 1u, &vertexSourcePointer, nullptr);
        glCompileShader(vertexShaderId);

        // Verifica
        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
        glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> vertexShaderErrorMessage(infoLogLength);
        if (!result)
        {
            glGetShaderInfoLog(vertexShaderId, infoLogLength, nullptr, &vertexShaderErrorMessage[0u]);
            std::fprintf(stdout, "%s\n", &vertexShaderErrorMessage[0u]);
        }

        // Compileaza shader-ul de fragemnt
        const char* const fragmentSourcePointer = fragmentShaderCode.c_str();
        std::fprintf(stdout, "Compiling shader: %s\n", fragmentFilePath);
        glShaderSource(fragmentShaderId, 1u, &fragmentSourcePointer, nullptr);
        glCompileShader(fragmentShaderId);

        // Verifica
        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
        glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> fragmentShaderErrorMessage(infoLogLength);
        if(!result)
        {
            glGetShaderInfoLog(fragmentShaderId, infoLogLength, nullptr, &fragmentShaderErrorMessage[0u]);
            std::fprintf(stdout, "%s\n", &fragmentShaderErrorMessage[0u]);
        }

        // Leaga programul
        GLuint program = glCreateProgram();
        std::fprintf(stdout, "Binding program: %u\n", program);
        glAttachShader(program, vertexShaderId);
        glAttachShader(program, fragmentShaderId);
        glLinkProgram(program);

        // Verifica
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> programErrorMessage(std::max(infoLogLength, 1));
        if(!result)
        {
            glGetProgramInfoLog(program, infoLogLength, nullptr, &programErrorMessage[0u]);
            std::fprintf(stdout, "%s\n", &programErrorMessage[0u]);
        }

        glDeleteShader(fragmentShaderId);
        glDeleteShader(vertexShaderId);

        return program;
    }

    void Engine::createShaders()
    {
        programId = loadShaders(
                "../resources/shaders/shader.vert",
                "../resources/shaders/shader.frag"
        );
        glUseProgram(programId);
    }

    void Engine::destroyShaders()
    {
        glDeleteProgram(programId);
    }

    void Engine::initialize()
    {
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
        createShaders();
        createVbo();

        viewLocation = glGetUniformLocation(programId, "ViewMatrix");
        projLocation = glGetUniformLocation(programId, "ProjectionMatrix");
        matrUmbraLocation = glGetUniformLocation(programId, "matrUmbra");
        lightColorLoc = glGetUniformLocation(programId, "lightColor");
        lightPosLoc = glGetUniformLocation(programId, "lightPos");
        viewPosLoc = glGetUniformLocation(programId, "viewPos");
        codColLocation = glGetUniformLocation(programId, "ColourCode");
    }

    void Engine::renderFunction()
    {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glWindowPos2f(0.0f, 0.0f);

        // reperul de vizualizare + proiectie
        obsx = refx + dist * (10.0f + std::cos(alpha)) * std::cos(beta);
        obsy = refy + dist * (10.0f + std::cos(alpha)) * std::sin(beta);
        obsz = refz + dist * std::sin(alpha);

        glm::vec3 obs = glm::vec3(obsx, obsy, obsz);
        glm::vec3 pctRef = glm::vec3(refx, refy, refz);
        glm::vec3 vert = glm::vec3(vx, vy, vz);
        ViewMatrix = glm::lookAt(obs, pctRef, vert);
        glUniformMatrix4fv((GLint) viewLocation, 1u, GL_FALSE, &ViewMatrix[0u][0u]);

        ProjectionMatrix = glm::infinitePerspective(fov, (GLfloat) width / (GLfloat) height, znear);
        glUniformMatrix4fv((GLint) projLocation, 1u, GL_FALSE, &ProjectionMatrix[0u][0u]);

        // Variabile uniforme pentru iluminare
        glUniform4f((GLint) lightColorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
        glUniform3f((GLint) lightPosLoc, xL, yL, zL);
        glUniform3f((GLint) viewPosLoc, obsx, obsy, obsz);

        // matricea pentru umbra
        const float d = -5.0f;

        matrUmbra[0u][0u] = zL + d;
        matrUmbra[0u][1u] = 0.0f;
        matrUmbra[0u][2u] = 0.0f;
        matrUmbra[0u][3u] = 0.0f;

        matrUmbra[1u][0u] = 0.0f;
        matrUmbra[1u][1u] = zL + d;
        matrUmbra[1u][2u] = 0.0f;
        matrUmbra[1u][3u] = 0.0f;

        matrUmbra[2u][0u] = -xL;
        matrUmbra[2u][1u] = -yL;
        matrUmbra[2u][2u] = d;
        matrUmbra[2u][3u] = -1.0f;

        matrUmbra[3u][0u] = -d * xL;
        matrUmbra[3u][1u] = -d * yL;
        matrUmbra[3u][2u] = -d * zL;
        matrUmbra[3u][3u] = zL;

        glUniformMatrix4fv((GLint) matrUmbraLocation, 1, GL_FALSE, &matrUmbra[0u][0u]);

        // desenare obiecte opace
        ColourCode = 0;
        glUniform1i((GLint) codColLocation, (GLint) ColourCode);
        // buffer 2
        glBindBuffer(GL_ARRAY_BUFFER, vboId2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId2);
        associateAttributePointers();
        glDrawElements(GL_TRIANGLES, 18u, GL_UNSIGNED_BYTE, nullptr); // piramida

        // buffer 1
        glBindBuffer(GL_ARRAY_BUFFER, vboId1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId1);
        associateAttributePointers();
        glDrawElements(GL_TRIANGLES, 6u, GL_UNSIGNED_BYTE, (void*) (36u)); // "ground"
        ColourCode = 1;
        glUniform1i((GLint) codColLocation, (GLint) ColourCode);
        glDrawElements(GL_TRIANGLES, 36u, GL_UNSIGNED_BYTE, nullptr); // umbra

        // desenare obiecte transparente
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA); // de testat alte variante https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBlendFunc.xhtml si factori-destinatie: GL_ONE, GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA
        ColourCode = 0;
        glUniform1i((GLint) codColLocation, (GLint) ColourCode);
        glDrawElements(GL_TRIANGLES, 36u, GL_UNSIGNED_BYTE, nullptr); // cubul
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);

        std::ostringstream FpsLabel;
        FpsLabel.precision(2u);
        FpsLabel << std::fixed << Fps;
        glWindowPos2f(width * 0.01f, height * 0.9f);
        glutBitmapString(
                GLUT_BITMAP_9_BY_15,
                reinterpret_cast<const unsigned char* const>(
                        ("FPS: " + FpsLabel.str()).c_str()
                )
        );

        glutSwapBuffers();
        glFlush();
    }
}
