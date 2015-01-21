#ifndef NordicArts_NordicEngine_Files_TextFile_Reader_H
#define NordicArts_NordicEngine_Files_TextFile_Reader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            namespace TextFile {
                class Reader : public FileHandler {
                // Variables
                public:
                protected:
                private:

                // Methods
                public:
                    explicit Reader();
                    explicit Reader(const std::string &cFileName);
                    explicit Reader(const std::string &cFileName, bool bFilePath);

                    std::string readAll() const;
                    std::string read() const;

                protected:
                private:
                    void openFile();
                    void closeFile();

                };
            };
        };
    };
};

#endif
