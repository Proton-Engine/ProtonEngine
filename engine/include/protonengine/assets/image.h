/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"

#include <cinttypes>
#include <vector>

namespace ProtonEngine::Assets
{

class PROTON_API Image
{
public:
    Image(const uint8_t * data, int width, int height, int channels);

    [[nodiscard]] auto getData() const noexcept -> const uint8_t *;
    [[nodiscard]] auto getWidth() const noexcept -> int;
    [[nodiscard]] auto getHeight() const noexcept -> int;
    [[nodiscard]] auto getChannels() const noexcept -> int;

private:
    std::vector<uint8_t> m_data;
    int m_width;
    int m_height;
    int m_channels;
};

} // namespace ProtonEngine::Assets