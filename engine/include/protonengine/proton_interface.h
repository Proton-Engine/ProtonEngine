/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#ifdef _WIN32
    #ifdef PROTON_BUILDING_ENGINE
        #define PROTON_API __declspec(dllexport)
    #else
        #define PROTON_API __declspec(dllimport)
    #endif // PROTON_BUIDLING_ENGINE
#else
    #define PROTON_API
#endif // _WIN32