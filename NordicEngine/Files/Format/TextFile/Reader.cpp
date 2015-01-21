#include <NordicEngine/Files/Format/TextFile/Reader.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            namespace TextFile {
                Reader::Reader() : Handler(true) {
                }
                Reader::Reader(const std::string &cFileName) : Handler(cFileName, true) {
                    openFile();
                    closeFile();
                }
                Reader::Reader(const std::string &cFileName, bool bFilePath) : Handler(cFileName, true) {
                    openFile();
                    closeFile();
                }

                void Reader::openFile() {
                    m_cFileStream.open(getFilePath().c_str(), std::ios_base::in);

                    if (!m_cFileStream.is_open()) {
                        throwError(__FUNCTION__ + std::string(" failed to open file for reading"));
                    }
                }

                void Reader::closeFile() {
                    if (m_cFileStream.is_open()) {
                        m_cFileStream.close();
                    }
                }

                std::string Reader::read() const {
                    return readAll();
                }
                
                std::string Reader::readAll() const {
                    openFile();

                    std::ostringstream cStream;

                    cStream << m_cFileStream.rdbuf();
                    if (cStream.str().length() < 1) {
                        closeFile();
                        throwError(__FUNCTION__ + std::string(" file is empty"));
                    }

                    closeFile();

                    return cStream.str();
                }
            };
        };
    };
};
