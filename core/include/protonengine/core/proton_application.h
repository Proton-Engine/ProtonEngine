/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

namespace ProtonEngine::Core
{

class ProtonApplication
{
public:
    ProtonApplication();
    virtual ~ProtonApplication();
    ProtonApplication(const ProtonApplication&) = delete;
    ProtonApplication(ProtonApplication&&) = delete;
    ProtonApplication &operator=(const ProtonApplication &) = delete;
    ProtonApplication &operator=(ProtonApplication &&) = delete;
};

} // namespace ProtonEngine