#include <NordicEngine/Windows/Windows.hpp>

namespace NordicArts {
    namespace NordicEngine {
        std::string OSSpecific::ResourcePath(std::string cFileName) {
            std::string cFilePath;

            std::string::size_type iLastIndex = cFileName.find_last_of("/\\");
            if (iLastIndex != std::string::npos) {
                cFilePath = cFileName.substr(0, iLastIndex);
            } else {
                cFilePath = ("./" + cFileName);
            }

            return cFilePath;
        }
    };
};
