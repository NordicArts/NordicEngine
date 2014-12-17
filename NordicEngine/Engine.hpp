#ifndef NordicArts_NordicEngine_H
#define NordicArts_NordicEngine_H

#include <NordicEngine/buildNumber.hpp>
#include <NordicEngine/Includes.hpp>

// Errors
#ifndef printStuff
#define printStuff
#define printIt(variable) { std::cout << #variable << " " << variable << std::endl; }
#endif

// Safe Delete
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if (p) { delete(p); p = NULL; }}
#endif

// Safe Delete Array
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[](p); p = NULL; }}
#endif

// OS Specific Includes
#if defined (__WIN32__) || defined(_WIN32) || defined(_WIN64)
    #include <NordicEngine/OS/Windows/Windows.hpp>
#else
    #define nonWindows

    #include <NordicEngine/OS/nonWindows/nonWindows.hpp>

    #if defined(__APPLE__) || defined(__APPLE_CC__)
        #include <NordicEngine/OS/nonWindows/OSX/OSX.hpp>
    #else
        #include <NordicEngine/OS/nonWindows/Linux/Linux.hpp>
    #endif
#endif

// Exceptions
#include <NordicEngine/Exceptions/Exceptions.hpp>

namespace NordicArts {
    namespace NordicEngine {
        const char *getBuildNumber();
    };
};
#endif
