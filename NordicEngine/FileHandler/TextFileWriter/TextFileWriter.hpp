#ifndef NordicArts_NordicOS_FileHandler_TextFileWriter_H
#define NordicArts_NordicOS_FileHandler_TextFileWriter_H

#include <NordicOS/OS.hpp>
#include <NordicOS/FileHandler/FileHandler.hpp>

namespace NordicArts {
    namespace NordicOS {
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
