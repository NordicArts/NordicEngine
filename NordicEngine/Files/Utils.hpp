#ifndef NordicArts_NordicEngine_Files_Utils_H
#define NordicArts_NordicEngine_Files_Utils_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        bool fileExists(std::string cFileName);
        bool fileExists(const char *cFileName);
    };
};

#endif
