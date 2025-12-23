// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#pragma once

#include "ilayer.h"

#include <memory>
#include <vector>

namespace ProtonEngine::Ui
{

class PROTONENGINE_UI_EXPORT Frame
{
public:
    Frame() = default;
    ~Frame() = default;
    Frame(Frame &) = delete;
    Frame(Frame &&) = delete;
    Frame & operator=(Frame &) = delete;
    Frame & operator=(Frame &&) = delete;

    void addLayer(std::unique_ptr<Layer> layer);
    void onUpdate(float timeStep);
    void render() const;

private:
    std::vector<std::unique_ptr<Layer>> m_layers;

    static void beginFrame();
    static void endFrame();
};

} // namespace ProtonEngine::Ui