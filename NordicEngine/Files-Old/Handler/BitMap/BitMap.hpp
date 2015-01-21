#ifndef NordicArts_NordicEngine_Files_Handler_BitMap_H
#define NordicArts_NordicEngine_Files_Handler_BitMap_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class BitMap {
        // Variables
        public:
            enum Format {
                Format_Grayscale = 1,
                Format_GrayscaleAlpha = 2,
                Format_RGB = 3,
                Format_RGBA = 4
            };

        protected:
        private:
            Format m_eFormat;

            unsigned int m_iWidth;
            unsigned int m_iHeight;

            unsigned char *m_cPixels;

        // Methods
        public:
            BitMap(unsigned int iWidth, unsigned int iHeight, Format eFormat, const unsigned char *cPixels = NULL);
            BitMap(const BitMap &oOther);
            ~BitMap();

            static BitMap bitMapFromFile(std::string cFile);

            unsigned int getWidth() const;
            unsigned int getHeight() const;

            Format getFormat() const;

            unsigned char *getPixelBuffer() const;
            unsigned char *getPixel(unsigned int iColumn, unsigned int iRow) const;

            void setPixel(unsigned int iColumn, unsigned int iRow, const unsigned char *cPixel);
            void flipVertically();
            void rotate90CounterClockwise();
            void copyRectFromBitMap(const BitMap &oSrc, unsigned int iSrcCol, unsigned int iSrcRow, unsigned int iDestCol, unsigned int iDestRow, unsigned int iWidth, unsigned int iHeight);

            BitMap &operator =(const BitMap &oOther);

        protected:
        private:
            void set(unsigned int iWidth, unsigned int iHeight, Format eFormat, const unsigned char *cPixels);

            static void getPixelOffset(unsigned int iCol, unsigned int iRow, unsigned int iWidth, unsigned int iHeight, Format eFormat);

        };
    };
};

#endif
