/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/export.h"

#include <string>

namespace ProtonEngine::Ui
{

class PROTONENGINE_EXPORT Layer
{
public:
    explicit Layer(const std::string & layerName = "n/a");
    virtual ~Layer() = default;
    Layer(Layer &) = delete;
    Layer(Layer &&) = default;
    Layer & operator=(Layer &) = delete;
    Layer & operator=(Layer &&) = default;

    virtual void onAttach() = 0;
    virtual void onImGuiRender() = 0;
    virtual void onUpdate(float timeStep) = 0;
    [[nodiscard]] virtual auto wantsWindow() const noexcept -> bool { return true; }

    [[nodiscard]] auto layerName() const noexcept -> const std::string &;

private:
    std::string m_layerName;
};

} // namespace ProtonEngine::Ui