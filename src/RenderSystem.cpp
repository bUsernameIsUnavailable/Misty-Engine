#include <RenderSystem.h>
#include <Scene.h>

#include <glm/gtc/matrix_transform.hpp>


namespace MsT {
    ShaderManager* RenderSystem::ShaderManager = nullptr;
    std::vector<MeshComponent> RenderSystem::Prefabs = std::vector<MeshComponent>();


    void RenderSystem::Update(Scene* const Scene) {
        glUseProgram((*ShaderManager)[0u]->GetId());
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glUniformMatrix4fv(
                (*(*ShaderManager)[0u])["ViewMatrix"],
                1u,
                GL_FALSE,
                &glm::lookAt(
                        glm::vec3(100.0f, -600.0f, 300.0f),
                        glm::vec3(0.0f, 1000.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                )[0u][0u]
        );

        glUniformMatrix4fv(
                (*(*ShaderManager)[0u])["ProjectionMatrix"],
                1u,
                GL_FALSE,
                &glm::infinitePerspective(45.0f, 4.0f / 3.0f, 0.1f)[0u][0u]
        );

        for (const auto& [
            Entity,
            Mesh
        ]: (*Scene)->view<const MeshComponent>().each()
        ) {
            glDepthMask(GL_FALSE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

            glDrawElements(GL_TRIANGLES, (GLsizei) Mesh.Indices.size(), GL_UNSIGNED_INT, nullptr);

            glDisable(GL_BLEND);
            glDepthMask(GL_TRUE);
        }

        glutSwapBuffers();
        glFlush();
    }

    void RenderSystem::MakePrefab(MeshComponent& Mesh) {
        glGenVertexArrays(1u, &Mesh.Vao);
        glBindVertexArray(Mesh.Vao);

        glGenBuffers(1u, &Mesh.Vbo);
        glGenBuffers(1u, &Mesh.Ebo);

        glBindBuffer(GL_ARRAY_BUFFER, Mesh.Vbo);
        glBufferData(GL_ARRAY_BUFFER, Mesh.GetVertexByteSize(), Mesh.Vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh.Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mesh.GetIndexByteSize(), Mesh.Indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0u);
        glVertexAttribPointer(0u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), nullptr);

        glEnableVertexAttribArray(1u);
        glVertexAttribPointer(1u, 4u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (4u * sizeof(GLfloat)));

        glEnableVertexAttribArray(2u);
        glVertexAttribPointer(2u, 3u, GL_FLOAT, GL_FALSE, 11u * sizeof(GLfloat), (GLvoid*) (8u * sizeof(GLfloat)));

        Prefabs.push_back(Mesh);
    }

    void RenderSystem::Cleanup() {
        const GLsizei& PrefabCount = (GLsizei) Prefabs.size();
        auto* const Vaos = new GLuint[PrefabCount];
        auto* const Vbos = new GLuint[PrefabCount];
        auto* const Ebos = new GLuint[PrefabCount];

        for (GLsizei Index = 0u; Index < PrefabCount; ++Index) {
            Vaos[Index] = Prefabs[Index].Vao;
            Vbos[Index] = Prefabs[Index].Vbo;
            Ebos[Index] = Prefabs[Index].Ebo;
        }

        glDisableVertexAttribArray(2u);
        glDisableVertexAttribArray(1u);
        glDisableVertexAttribArray(0u);
        glBindBuffer(GL_ARRAY_BUFFER, 0u);

        glDeleteBuffers(PrefabCount, Ebos);
        glDeleteBuffers(PrefabCount, Vbos);

        glBindVertexArray(0u);
        glDeleteVertexArrays(PrefabCount, Vaos);

        delete[] Ebos;
        delete[] Vbos;
        delete[] Vaos;

        delete ShaderManager;
    }
}
