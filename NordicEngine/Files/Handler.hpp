#ifndef NordicArts_NordicEngine_Files_Handler_H
#define NordicArts_NordicEngine_Files_Handler_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Utils.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class Handler {
            // Variables
            public:
            protected:
                std::fstream    m_cFileStream;
    
                std::string     m_cFileName;

            private:
                std::string     m_cFilePath;

                bool m_bSaveException;

            // Methods
            public:
                virtual ~Handler();

                std::string getFilePath() const;
                
                bool handlerDeleteFile();

            protected:
                Handler(bool bSaveException);
                Handler(std::string cFileName, bool bSaveException);

                void throwError(const std::string &cMessage) const;
                void throwError(const std::ostringstream &cMessage) const;

            private:

            };
        };
    };
};

#endif
