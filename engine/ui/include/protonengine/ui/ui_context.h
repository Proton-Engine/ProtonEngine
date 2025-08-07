/*
 * Copyright © 2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/ui/export.h"

#include "GLFW/glfw3.h"

namespace ProtonEngine::Ui
{

class PROTONENGINE_UI_EXPORT UiContext
{
public:
    explicit UiContext(GLFWwindow * window);
    ~UiContext();

    UiContext(const UiContext &) = delete;
    UiContext & operator=(const UiContext &) = delete;
    UiContext(UiContext &&) = delete;
    UiContext & operator=(UiContext &&) = delete;
};

} // namespace ProtonEngine::Ui