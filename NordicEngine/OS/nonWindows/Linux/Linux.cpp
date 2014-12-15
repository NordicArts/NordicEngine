#include <NordicEngine/OS/nonWindows/Linux/Linux.hpp>

namespace NordicArts {
    namespace NordicEngine {
        std::string OSSpecific::ResourcePath(std::string cFileName) {
            return cFileName;
        }
    };
};
