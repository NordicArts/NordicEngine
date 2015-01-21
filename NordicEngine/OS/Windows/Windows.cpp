#include <NordicEngine/OS/Windows/Windows.hpp>

namespace NordicArts {
    namespace NordicEngine {
        std::string OSSpecific::getPath(std::string cFileName) {
            return getResourcePath(cFileName);
        }

        std::string OSSpecific::getResourcePath(std::string cFileName) {
            std::string cFilePath;

            std::string::size_type iLastIndex = cFileName.find_last_of("/\\");
            if (iLastIndex != std::string::npos) {
                cFilePath = cFileName.substr(0, iLastIndex);
            } else {
                cFilePath = ("./" + cFileName);
            }

            return cFilePath;
        }

        bool OSSpecific::deleteFile(std::string cFileName) {
            if (remove(m_cFileName.c_str()) != 0) {
                return false;
            }

            return true;
        }
    };
};
