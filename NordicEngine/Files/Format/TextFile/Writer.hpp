#ifndef NordicArts_NordicEngine_Files_TextFile_Writer_H
#define NordicArts_NordicEngine_Files_TextFile_Writer_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            namespace TextFile {
                class Writer : public Handler {
                // Variables
                public:
                protected:
                private:

                // Methods
                public:
                    Writer();
                    Writer(const std::string &cFileName, bool bFilePath, bool bAppend);
                    Writer(const std::string &cFileName, bool bFilePath, bool bAppend, bool bSaveException);

                    void openStream(bool bAppend);
                    void write(const std::string &cMessage);

                    bool deleteFile();

                protected:
                private:

                };
            };
        };
    };
};

#endif
