/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/ui/ilayer.h"

namespace ProtonEngine::Ui
{

Layer::Layer(const std::string & layerName)
    : m_layerName(layerName)
{
}

auto Layer::layerName() const noexcept -> const std::string &
{
    return m_layerName;
}
} // namespace ProtonEngine::Ui