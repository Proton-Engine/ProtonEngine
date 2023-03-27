/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/renderer.h"
#include "protonengine/renderer/shader_program.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ProtonEngine::Renderer
{

void setWindowContext(GLADloadfunc func)
{
    gladLoadGL(func);
}

void update()
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

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    shaderProgram.disable();
}

} // namespace ProtonEngine::Renderer
