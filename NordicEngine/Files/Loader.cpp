#include <NordicEngine/Files/Loader.hpp>
#include <NordicEngine/Files/Format/TextFile/Writer.hpp>
#include <NordicEngine/Files/Format/TextFile/Reader.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            Loader::Loader() : m_cFile(NULL), m_bFilePath(false), m_bAppend(false), m_bSaveException(false) {
            }
            Loader::Loader(std::string cFile) : m_cFile(cFile), m_bFilePath(false), m_bAppend(false), m_bSaveException(false) {
            }
            Loader::Loader(std::string cFile, bool bFilePath) : m_cFile(cFile), m_bFilePath(bFilePath), m_bAppend(false), m_bSaveException(false) {
            }
            Loader::Loader(std::string cFile, bool bFilePath, bool bAppend) : m_cFile(cFile), m_bFilePath(bFilePath), m_bAppend(bAppend), m_bSaveException(false) {
            }
            Loader::Loader(std::string cFile, bool bFilePath, bool bAppend, bool bSaveException) : m_cFile(cFile), m_bFilePath(bFilePath), m_bAppend(bAppend), m_bSaveException(bSaveException) {
            }

            Loader::~Loader() {
            }

            void Loader::setFile(std::string cFile) {
                m_cFile     = cFile;
                m_eFormat   = Format::NE_TEXT;
            }
            void Loader::setFile(std::string cFile, Format eFormat) {
                m_cFile     = cFile;
                m_eFormat   = eFormat;
            }

            std::string Loader::read() {
                TextFile::Reader oReader(m_cFile, m_bAppend);
        
                return oReader.readAll();
            }

            void Loader::write(std::string cString) {
                TextFile::Writer oWriter(m_cFile, m_bFilePath, m_bAppend, m_bSaveException);
            
                return oWriter.write(cString);
            }

            bool Loader::deleteFile() {
                TextFile::Writer oWriter(m_cFile, m_bFilePath, false, m_bSaveException);

                return oWriter.deleteFile();
            }
        };
    };
};
