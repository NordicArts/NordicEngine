#ifndef NordicArts_NordicOS_FileHandler_H
#define NordicArts_NordicOS_FileHandler_H

#include <NordicOS/FileHandler/FileUtils.hpp>
#include <NordicOS/OS.hpp>
#include <NordicOS/ExceptionHandler/ExceptionHandler.hpp>

namespace NordicArts {
    namespace NordicOS {
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
            
        protected:
            FileHandler(std::string cFileName, bool bSaveException);

            void throwError(const std::string &cMessage) const;
            void throwError(const std::ostringstream &cMessage) const;

        private:
        };
    };
};

#endif
