/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

namespace ProtonEngine::Core
{

class Application
{
public:
    Application();
    virtual ~Application();
    Application(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;
};

} // namespace ProtonEngine