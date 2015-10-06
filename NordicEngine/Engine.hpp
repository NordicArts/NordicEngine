#ifndef NordicArts_NordicEngine_H
#define NordicArts_NordicEngine_H

#include <NordicEngine/buildNumber.hpp>
#include <NordicEngine/Includes.hpp>

// Errors
#ifndef printStuff
#define printStuff
#define printIt(variable) { std::cout << #variable << " : " << variable << std::endl; }
#endif

// Safe Delete
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if (p) { delete(p); p = NULL; }}
#endif

// Safe Delete Array
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[](p); p = NULL; }}
#endif

// Swap Pointers
#ifndef NE_SWAP_POINTERS
#define NE_SWAP_POINTERS(x, y) { void *t; t = x, x = y; y = t; }
#endif

// Exceptions
#include <NordicEngine/Exception/Exception.hpp>

namespace NordicArts {
    // signed types
    typedef signed char     NA_INT8;
    typedef signed short    NA_INT16;
    typedef int             NA_INT32;
    #if defined(_MSC_VER)
        typedef signed __int64  NA_INT64;
    #else
        typedef signed long long NA_INT64;
    #endif
    
    // unsigned types
    typedef unsigned char   NA_UINT8;
    typedef unsigned short  NA_UINT16;
    typedef unsigned int    NA_UINT32;
    #if defined(_MSC_VER)
        typedef unsigned __int64 NA_UINT64;
    #else
        typedef unsigned long long NA_UINT64;
    #endif

    namespace NordicEngine {
        const char *getBuildNumber();

        void throwError(const std::ostringstream &cMessage);
        void throwError(const std::string &cMessage);
        void throwError(const std::string &cFunction, const std::string &cMessage);
    };
};

// OS
#include <NordicEngine/OS/OS.hpp>
#endif
