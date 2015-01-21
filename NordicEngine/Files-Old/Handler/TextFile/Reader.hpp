#ifndef NordicArts_NordicEngine_Files_Handler_TextFile_Reader_H
#define NordicArts_NordicEngine_Files_Handler_TextFile_Reader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler/Handler.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace TextFile {
            class Reader : public FileHandler {
            // Variables
            public:
            protected:
            private:

            // Methods
            public:
                explicit Reader();
                explicit Reader(const std::string &cFileName);
                explicit Reader(const std::string &cFileName, bool bFilePath);
        
                std::string readAll() const;
    
            protected:
            private:
            };
        };
    };
};

#endif
