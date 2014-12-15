#ifndef NordicArts_NordicEngine_H
#define NordicArts_NordicEngine_H

#include <NordicEngine/buildNumber.hpp>
#include <NordicEngine/Includes.hpp>

// Errors
#ifndef printStuff
#define printStuff
#define printIt(variable) { std::cout << #variable << " " << variable << std::endl; }
#endif

// OS Specific Includes
#if defined (__WIN32__) || defined(_WIN32) || defined(_WIN64)
    #include <NordicEngine/Windows/Windows.hpp>
#else
    #define nonWindows

    #include <NordicEngine/nonWindows/nonWindows.hpp>

    #if defined(__APPLE__) || defined(__APPLE_CC__)
        #include <NordicEngine/OSX/OSX.hpp>
    #else
        #include <NordicEngine/Linux/Linux.hpp>
    #endif
#endif

// ExceptionHandler
#include <NordicEngine/ExceptionHandler/ExceptionHandler.hpp>

namespace NordicArts {
    namespace NordicEngine {
        const char *getBuildNumber();
    };
};
#endif
