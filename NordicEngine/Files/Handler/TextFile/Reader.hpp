#ifndef NordicArts_NordicEngine_Files_Handler_TextFile_Reader_H
#define NordicArts_NordicEngine_Files_Handler_TextFile_Reader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler/Handler.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class TextFileReader : public FileHandler {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            explicit TextFileReader(const std::string &cFileName);
            explicit TextFileReader(const std::string &cFileName, bool bFilePath);
        
            std::string readAll() const;
    
        protected:
        private:
        };
    };
};

#endif
