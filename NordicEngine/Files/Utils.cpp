#include <NordicEngine/Files/Utils.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            bool doesFileExist(std::string cFileName) {
                return doesFileExist(cFileName.c_str());
            }
            bool doesFileExist(const char *cFileName) {
                bool bExists = false;

                std::ifstream pFile(cFileName);
                if (pFile) {
                    bExists = true;

                    pFile.close();
                }

                return bExists;
            }
        };
    };
};

