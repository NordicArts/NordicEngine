#ifndef NordicArts_NordicEngine_Files_TextFile_Reader_H
#define NordicArts_NordicEngine_Files_TextFile_Reader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            namespace TextFile {
                class Reader : public Handler {
                // Variables
                public:
                protected:
                private:

                // Methods
                public:
                    Reader();
                    Reader(const std::string &cFileName);
                    Reader(const std::string &cFileName, bool bFilePath);

                    std::string read() const;
                    std::string readAll() const;

                protected:
                private:

                };
            };
        };
    };
};

#endif
