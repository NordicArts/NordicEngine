#ifndef NordicArts_NordicEngine_FileHandler_TextFileWriter_H
#define NordicArts_NordicEngine_FileHandler_TextFileWriter_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/FileHandler/FileHandler.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class TextFileWriter : public FileHandler {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            TextFileWriter(const std::string &cFileName, bool bAppend, bool bSaveException = true);
        
            void write(const std::string &cMessage);
    
        protected:
        private:
        };
    };
};

#endif
