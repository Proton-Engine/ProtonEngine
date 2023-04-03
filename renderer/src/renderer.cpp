/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/renderer.h"
#include "protonengine/renderer/shader_program.h"
#include "protonengine/renderer/mesh.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace ProtonEngine::Renderer
{

void setWindowContext(GLADloadfunc func)
{
    gladLoadGL(func);
}

void renderFrame(const Mesh & mesh)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderProgram shaderProgram("shader");
    shaderProgram.enable();

    glm::mat4 projection = glm::perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.0f);
//    glm::mat4 projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(0,0,-3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    static float offset = 0.1f;
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, offset += 0.1f));

    auto mvp = projection * view * model;

    shaderProgram.setUniformValue("MVP", mvp);

    mesh.enableForDrawing();
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertices()); // Starting from vertex 0; 3 vertices total -> 1 triangle
    mesh.disableForDrawing();

    shaderProgram.disable();
}

} // namespace ProtonEngine::Renderer
