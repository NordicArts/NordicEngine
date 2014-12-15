#ifndef NordicArts_NordicEngine_FileUtils_H
#define NordicArts_NordicEngine_FileUtils_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        bool fileExists(std::string cFileName);
        bool fileExists(const char *cFileName);
    };
};

#endif
