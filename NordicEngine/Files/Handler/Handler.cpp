#include <NordicEngine/Files/Handler/Handler.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>

namespace NordicArts {
    namespace NordicEngine {
        FileHandler::FileHandler(bool bSaveException) : m_bSaveException(bSaveException) {
        }
        FileHandler::FileHandler(std::string cFileName, bool bSaveException) : m_bSaveException(bSaveException), m_cFileName(cFileName) {
            OSSpecific oOS;
            std::string cFilePath = oOS.ResourcePath(cFileName);

            if (cFileName.empty()) {
                throw Exceptions(__FUNCTION__ + std::string(" Missing FileName"), bSaveException);
            } else {
                fileExists(cFilePath);

                m_cFilePath = cFilePath;
            }
        }

        FileHandler::~FileHandler() {
            if (m_cFileStream.is_open()) {
                m_cFileStream.close();
            }
        }

        void FileHandler::deleteFile() {
            if (m_cFileStream.is_open()) {
                m_cFileStream.close();

                OSSpecific oOS;
                oOS.deleteFile(m_cFilePath);
            }
        }                

        void FileHandler::throwError(const std::string &cMessage) const {
            throw Exceptions("File [" + m_cFileName + "] " + cMessage, m_bSaveException);      
        }

        void FileHandler::throwError(const std::ostringstream &cMessage) const {
            throwError(cMessage.str().c_str());
        }
        
        std::string FileHandler::getFilePath() const {
            return m_cFilePath;
        }
    };
};
