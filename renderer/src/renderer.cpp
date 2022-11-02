/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/renderer.h"

#include <glad/gl.h>

namespace ProtonEngine::Renderer
{

void setWindowContext(GLADloadfunc func)
{
    gladLoadGL(func);
}

void update()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
}

} // namespace ProtonEngine::Renderer
