#ifndef NordicArts_NordicEngine_Files_Utils_H
#define NordicArts_NordicEngine_Files_Utils_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            bool doesFileExist(std::string cFileName);
            bool doesFileExist(const char *cFileName);
        };
    };
};

#endif
