#ifndef NordicArts_NordicEngine_Files_BMP_H
#define NordicArts_NordicEngine_Files_BMP_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class BitMap : public Handler {
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
                BitMap();
                BitMap(std::string cFileName);

                unsigned int loadBitMap();
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
