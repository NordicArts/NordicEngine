#include <NordicEngine/Files/Handler.hpp>
#include <NordicEngine/Exception/Exception.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            Handler::Handler(bool bSaveException) : m_bSaveException(bSaveException) {
            }
            Handler::Handler(std::string cFileName, bool bSaveException) : m_bSaveException(bSaveException), m_cFileName(cFileName) {
                OSSpecific oOS;

                std::string cFilePath = oOS.getPath(cFileName);
                if (cFilePath.empty()) {
                    throw Exception(__FUNCTION__ + std::string(" Missing FileName"), m_bSaveException);
                }
                    
                m_cFilePath = cFilePath;
            }

            Handler::~Handler() {
                if (m_cFileStream.is_open()) {
                    m_cFileStream.close();
                }
            }

            bool Handler::handlerDeleteFile() {
                if (m_cFileStream.is_open()) {
                    m_cFileStream.close();
                }

                OSSpecific oOS;

                return oOS.deleteFile(m_cFilePath);
            }

            std::string Handler::getFilePath() const {
                return m_cFilePath;
            }
        };
    };
};
