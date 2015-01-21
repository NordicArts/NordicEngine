#include <NordicEngine/OS/nonWindows/Linux/Linux.hpp>

namespace NordicArts {
    namespace NordicEngine {
        std::string OSSpecific::getPath(std::string cFileName) {
            return getResourcePath(cFileName);
        }

        std::string OSSpecific::getResourcePath(std::string cFileName) {
            return cFileName;
        }

        bool OSSpecific::deleteFile(std::string cFileName) {
            if (remove(cFileName.c_str()) != 0) {
                return false;
            }

            return true;
        }
    };
};
