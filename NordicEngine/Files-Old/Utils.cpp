//
//  Utils.cpp
//  NordicEngine
//
//  Created by Max Hooton on 25/08/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include <NordicEngine/Files/Utils.hpp>

namespace NordicArts {
    namespace NordicEngine {
        bool fileExists(std::string cFileName) {
            return fileExists(cFileName.c_str());
        }

        bool fileExists(const char *cFileName) {
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
