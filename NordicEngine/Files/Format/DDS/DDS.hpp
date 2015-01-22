#ifndef NordicArts_NordicEngine_Files_DDS_H
#define NordicArts_NordicEngine_Files_DDS_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler.hpp>

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class DDS : public Handler {
            // Variables
            public:
            protected:
            private:
                unsigned int m_iTextureID;
                unsigned int m_iImageSize;
                unsigned int m_iWidth;
                unsigned int m_iHeight;

                std::string m_cFile;

            // Methods
            public:
                DDS();
                DDS(std::string cFileName);

                unsigned int loadDDS();
                unsigned int getTextureID() const;
                unsigned int getWidth() const;
                unsigned int getHeight() const;

            protected:
            private:

            };
        };
    };
};

#endif
