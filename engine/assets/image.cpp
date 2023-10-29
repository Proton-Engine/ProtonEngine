/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#include "protonengine/assets/image.h"

namespace ProtonEngine::Assets
{

Assets::Image::Image(const uint8_t * data, int width, int height, int channels) :
    m_width(width), m_height(height), m_channels(channels)
{
    m_data.reserve(width * height * channels);

    for(int i = 0; i < width * height * channels; i++)
    {
        m_data[i] = data[i];
    }
}

auto Image::getData() const noexcept -> const uint8_t *
{
    return m_data.data();
}

auto Image::getWidth() const noexcept -> int
{
    return m_width;
}

auto Image::getHeight() const noexcept -> int
{
    return m_height;
}

auto Image::getChannels() const noexcept -> int
{
    return m_channels;
}

} // namespace ProtonEngine::Assets