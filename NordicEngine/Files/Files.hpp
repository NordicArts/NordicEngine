#ifndef NordicArts_NordicEngine_Files_H
#define NordicArts_NordicEngine_Files_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Files {
        // Variables
        public:
        protected:
        private:
            std::string m_cFile;

            bool m_bAppend;
            bool m_bFilePath;
            bool m_bSaveException;
        
        // Methods
        public:
            Files();
            Files(std::string cFile);
            Files(std::string cFile, bool bFilePath);
            Files(std::string cFile, bool bFilePath, bool bAppend);
            Files(std::string cFile, bool bFilePath, bool bAppend, bool bSaveException);
            
            ~Files();

            void setFile(std::string cFile);
            
            std::string read();
            void write(std::string cString);

        protected:
        private:

        };
    };
};

#endif
