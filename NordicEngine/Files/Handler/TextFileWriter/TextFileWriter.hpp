#ifndef NordicArts_NordicEngine_Files_Handler_TextFileWriter_H
#define NordicArts_NordicEngine_Files_Handler_TextFileWriter_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler/Handler.hpp>

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
