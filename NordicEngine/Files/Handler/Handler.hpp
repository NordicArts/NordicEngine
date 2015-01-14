#ifndef NordicArts_NordicEngine_Files_Handler_H
#define NordicArts_NordicEngine_Files_Handler_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Utils.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class FileHandler {
        // Variables
        public:
            std::string     m_cFilePath;
        protected:
            std::fstream    m_cFileStream;

            std::string     m_cFileName;

        private:
            bool            m_bSaveException;

        // Methods
        public:
            virtual ~FileHandler();
            
            std::string getFilePath() const;

            void handlerDeleteFile();
            
        protected:
            FileHandler(bool bSaveException);
            FileHandler(std::string cFileName, bool bSaveException);

            void throwError(const std::string &cMessage) const;
            void throwError(const std::ostringstream &cMessage) const;

        private:
        };
    };
};

#endif
