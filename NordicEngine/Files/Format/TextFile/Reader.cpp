#include <NordicEngine/Files/Format/TextFile/Reader.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            namespace TextFile {
                Reader::Reader() : Handler(true) {
                }
                Reader::Reader(const std::string &cFileName) : Handler(cFileName, true) {
                    m_cFileStream.open(getFilePath().c_str(), std::ios_base::in);
                    if (!m_cFileStream.is_open()) {
                        throwError(__FUNCTION__ + std::string(" can't open file for reading 1, ") + m_cFileName);
                    }
                }
                Reader::Reader(const std::string &cFileName, bool bFilePath) : Handler(cFileName, true) {
                    m_cFileStream.open(getFilePath().c_str(), std::ios_base::in);
                    if (!m_cFileStream.is_open()) {
                        throwError(__FUNCTION__ + std::string(" can't open file for reading 2, ") + m_cFileName);
                    }
                }

                std::string Reader::read() const {
                    return readAll();
                }
                
                std::string Reader::readAll() const {
                    std::ostringstream cStream;

                    cStream << m_cFileStream.rdbuf();
                    if (cStream.str().length() < 1) {
                        throwError(__FUNCTION__ + std::string(" file is empty"));
                    }

                    return cStream.str();
                }
            };
        };
    };
};
