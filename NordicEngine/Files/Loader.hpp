#ifndef NordicArts_NordicEngine_Files_Loader_H
#define NordicArts_NordicEngine_Files_Loader_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class Loader {
            // Variables
            public:
                enum Format {
                    NE_TEXT = 1,
                    NE_BITMAP
                };

            protected:
            private:
                std::string m_cFile;
                
                bool m_bAppend;
                bool m_bFilePath;
                bool m_bSaveException;
        
                int m_eFormat;

            // Methods
            public:
                Loader();
                Loader(std::string cFile);
                Loader(std::string cFile, bool bFilePath);
                Loader(std::string cFile, bool bFilePath, bool bAppend);
                Loader(std::string cFile, bool bFilePath, bool bAppend, bool bSaveException);

                ~Loader();

                void setFile(std::string cFile);
                void setFile(std::string cFile, Format eFormat);
                void write(std::string cString);

                std::string read();

                bool deleteFile();

            protected:
            private:

            };
        };
    };
};

#endif
