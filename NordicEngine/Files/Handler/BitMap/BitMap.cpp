#include <NordicEngine/Files/Handler/BitMap/BitMap.hpp>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <NordicEngine/stb/stb_image.h>

namespace NordicArts {
    namespace NordicEngine {
        inline unsigned char AverageRGB(unsigned char rgb[3]) {
            return (unsigned char)(((double)rgb[0] + (double)rgb[1] + (double)rgb[2]) / 3.0);
        }

        static void Grayscale2GrayscaleAlpha(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = cSrc[0];
            cDest[1] = 255;
        }
        static void Grayscale2RGB(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = cSrc[0];
            cDest[1] = cSrc[0];
            cDest[2] = cSrc[0];
        }
        static void Grayscale2RGBA(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = cSrc[0];
            cDest[1] = cSrc[0];
            cDest[2] = cSrc[0];
            cDest[3] = 255;
        }
        static void GrayscaleAlpha2Grayscale(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = cSrc[0];
        }
        static void GrayscaleAlpha2RGB(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = cSrc[0];
            cDest[1] = cSrc[0];
            cDest[2] = cSrc[0];
        }
        static void GrayscaleAlpha2RGBA(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = cSrc[0];
            cDest[1] = cSrc[0];
            cDest[2] = cSrc[0];
            cDest[3] = cSrc[1];
        }
        static void RGB2Grayscale(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = AverageRGB(cSrc);
        }
        static void RGB2GrayscaleAlpha(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = AverageRGB(cSrc);
            cDest[1] = 255;
        }
        static void RGB2RGBA(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = cSrc[0];
            cDest[1] = cSrc[1];
            cDest[2] = cSrc[2];
            cDest[3] = 255;
        }
        static void RGBA2Grayscale(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = AverageRGB(cSrc);
        }
        static void RGBA2GrayscaleAlpha(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = AverageRGB(cSrc);
            cDest[1] = cSrc[3];
        }
        static void RGBA2RGB(unsigned char *cSrc, unsigned char *cDest) {
            cDest[0] = cSrc[0];
            cDest[1] = cSrc[1];
            cDest[2] = cSrc[2];
        }

        typedef void(*FormatConverterFunc)(unsigned char *, unsigned char *);
        static FormatConverterFunc ConverterFuncForFormats(BitMap::Format eSrcFormat, BitMap::Format eDestFormat) {
            if (eSrcFormat == eDestFormat) {
                throw Exceptions("Just use memcpy if pixel formats are the same");
            }

            switch (eSrcFormat) {
                case BitMap::Format_Grayscale: {
                    switch (eDestFormat) {
                        case BitMap::Format_GrayscaleAlpha: return Grayscale2GrayscaleAlpha;
                        case BitMap::Format_RGB: return Grayscale2RGB;
                        case BitMap::Format_RGBA: return Grayscale2RGBA;
                        default: {
                            throw Exceptions("Unhandled BitMap Format 1");
                        }
                    }
                    break;
                };

                case BitMap::Format_GrayscaleAlpha: {
                    switch (eDestFormat) {
                        case BitMap::Format_GrayscaleAlpha: return Grayscale2GrayscaleAlpha;
                        case BitMap::Format_RGB: return Grayscale2RGB;
                        case BitMap::Format_RGBA: return Grayscale2RGBA;
                        default: {
                            throw Exceptions("Unhandled BitMap Format 2");
                        }
                    }
                    break;
                };

                case BitMap::Format_RGB: {
                    switch (eDestFormat) {
                        case BitMap::Format_Grayscale: return RGB2Grayscale;
                        case BitMap::Format_GrayscaleAlpha: return RGB2GrayscaleAlpha;
                        case BitMap::Format_RGBA: return RGB2RGBA;
                        default: {
                            throw Exceptions("Unhandled BitMap Format 3");
                        }
                    }
                    break;
                };

                case BitMap::Format_RGBA: {
                    switch (eDestFormat) {
                        case BitMap::Format_Grayscale: return RGBA2Grayscale;
                        case BitMap::Format_GrayscaleAlpha: return RGBA2GrayscaleAlpha;
                        case BitMap::Format_RGB: return RGB2RGBA;
                        default: {
                            throw Exceptions("Unhandled BitMap Format 4");
                        }
                    }
                    break;
                };

                default: {
                    throw Exceptions("Unhandled BitMap Format 5");
                }
            }
        }

        inline unsigned int GetPixelOffset(unsigned int iCol, unsigned int iRow, unsigned int iWidth, unsigned int iHeight, BitMap::Format eFormat) {
            return (((iRow * iWidth) + iCol) * eFormat);
        }

        inline bool RectsOverlap(unsigned int iSrcCol, unsigned int iSrcRow, unsigned int iDestCol, unsigned int iDestRow, unsigned int iWidth, unsigned int iHeight) {
            unsigned int iColDiff = ((iSrcCol > iDestCol) ? (iSrcCol - iDestCol) : (iDestCol - iSrcCol));
            if (iColDiff < iWidth) {
                return true;
            }

            unsigned int iRowDiff = ((iSrcRow > iDestRow) ? (iSrcRow - iDestRow) : (iDestRow - iSrcRow));
            if (iRowDiff < iHeight) {
                return true;
            }

            return false;
        }

        BitMap::BitMap(unsigned int iWidth, unsigned int iHeight, Format eFormat, const unsigned char *cPixels) : m_cPixels(NULL) {
            set(iWidth, iHeight, eFormat, cPixels);
        }
        BitMap::BitMap(const BitMap &oOther) : m_cPixels(NULL) {
            set(oOther.m_iWidth, oOther.m_iHeight, oOther.m_eFormat, oOther.m_cPixels);
        }

        BitMap::~BitMap() {
            if (m_cPixels) {
                free(m_cPixels);
            }
        }

        BitMap BitMap::bitMapFromFile(std::string cFile) {
            int iWidth;
            int iHeight;
            int iChannels;

            unsigned char *cPixels = stbi_load(cFile.c_str(), &iWidth, &iHeight, &iChannels, 0);
            if (!cPixels) {
                throw Exceptions(stbi_failure_reason());
            }

            BitMap bmp(iWidth, iHeight, (Format)iChannels, cPixels);
            stbi_image_free(cPixels);
        
            return bmp;
        }
        
        BitMap &BitMap::operator =(const BitMap &oOther) {
            set(oOther.m_iWidth, oOther.m_iHeight, oOther.m_eFormat, oOther.m_cPixels);

            return *this;
        }

        unsigned int BitMap::getWidth() const {
            return m_iWidth;
        }

        unsigned int BitMap::getHeight() const {
            return m_iHeight;
        }

        BitMap::Format BitMap::getFormat() const {
            return m_eFormat;
        }

        unsigned char *BitMap::getPixelBuffer() const {
            return m_cPixels;
        }

        unsigned char *BitMap::getPixel(unsigned int iColumn, unsigned int iRow) const {
            if ((iColumn >= m_iWidth) || (iRow >= m_iHeight)) {
                throw Exceptions("Pixel coordinate out of bounds");
            }

            return (m_cPixels + GetPixelOffset(iColumn, iRow, m_iWidth, m_iHeight, m_eFormat));
        }

        void BitMap::setPixel(unsigned int iColumn, unsigned int iRow, const unsigned char *cPixel) {
            unsigned char *newPixel = getPixel(iColumn, iRow);
        
            memcpy(newPixel, cPixel, m_eFormat);
        }

        void BitMap::flipVertically() {
            unsigned long lRowSize = (m_eFormat * m_iWidth);
            unsigned char *cBuffer = new unsigned char[lRowSize];
            unsigned int iHalfRows = (m_iHeight / 2);

            for (unsigned int iRow = 0; iRow < iHalfRows; ++iRow) {
                unsigned char *cRow         = (m_cPixels + GetPixelOffset(0, iRow, m_iWidth, m_iHeight, m_eFormat));
                unsigned char *cOpposite    = (m_cPixels + GetPixelOffset(0, (m_iHeight - iRow - 1), m_iWidth, m_iHeight, m_eFormat));

                memcpy(cBuffer, cRow, lRowSize);
                memcpy(cRow, cOpposite, lRowSize);
                memcpy(cOpposite, cBuffer, lRowSize);
            }

            SAFE_DELETE(cBuffer);
        }

        void BitMap::rotate90CounterClockwise() {
            unsigned char *cNewPixels = (unsigned char *)malloc(m_eFormat * m_iWidth * m_iHeight);

            for (unsigned int iRow = 0; iRow < m_iHeight; ++iRow) {
                for (unsigned int iCol = 0; iCol < m_iWidth; ++iCol) {
                    unsigned int iSrcOffset     = GetPixelOffset(iCol, iRow, m_iWidth, m_iHeight, m_eFormat);
                    unsigned int iDestOffset    = GetPixelOffset(iRow, (m_iWidth - iCol - 1), m_iHeight, m_iWidth, m_eFormat);

                    memcpy((cNewPixels + iDestOffset), (m_cPixels + iSrcOffset), m_eFormat);
                }
            }

            free(m_cPixels);
            m_cPixels = cNewPixels;

            unsigned int iTmp   = m_iHeight;
            m_iHeight           = m_iWidth;
            m_iWidth            = iTmp;
        }

        void BitMap::copyRectFromBitMap(const BitMap &oSrc, unsigned int iSrcCol, unsigned int iSrcRow, unsigned int iDestCol, unsigned int iDestRow, unsigned int iWidth, unsigned int iHeight) {
            if ((iSrcCol == 0) && (iSrcRow == 0) && (iWidth == 0) && (iHeight == 0)) {
                iWidth  = oSrc.getWidth();
                iHeight = oSrc.getHeight();
            }

            if ((iWidth == 0) || (iHeight == 0)) {
                throw Exceptions("Can't copy zero height / width rectangle");
            }

            if (((iSrcCol + iWidth) >= oSrc.getWidth()) || ((iSrcRow + iHeight) >= oSrc.getHeight())) {
                throw Exceptions("Rectangle doesn't fit with source bitmap");
            }

            if ((m_cPixels == oSrc.m_cPixels) && RectsOverlap(iSrcCol, iSrcRow, iDestCol, iDestRow, iWidth, iHeight)) {
                throw Exceptions("Source and destination are the same bitmap, and rects overlap, not allowed");
            }
        
            FormatConverterFunc converter = NULL;
            if (m_eFormat != oSrc.m_eFormat) {
                converter = ConverterFuncForFormats(m_eFormat, oSrc.m_eFormat);
            }

            for (unsigned int iRow = 0; iRow < iHeight; ++iRow) {
                for (unsigned int iCol = 0; iCol < iWidth; ++iCol) {
                    unsigned char *cSrcPixel    = (oSrc.m_cPixels + GetPixelOffset((iSrcCol + iCol), (iSrcRow + iRow), oSrc.m_iWidth, oSrc.m_iHeight, oSrc.m_eFormat));
                    unsigned char *cDestPixel   = (m_cPixels + GetPixelOffset((iDestCol + iCol), (iDestRow + iRow), m_iWidth, m_iHeight, m_eFormat));
        
                    if (converter) {
                        converter(cSrcPixel, cDestPixel);
                    } else {
                        memcpy(cDestPixel, cSrcPixel, m_eFormat);
                    }
                }
            }
        }

        void BitMap::set(unsigned int iWidth, unsigned int iHeight, Format eFormat, const unsigned char *cPixels) {
            if (iWidth == 0) { throw Exceptions("Zero width bitmap"); }
            if (iHeight == 0) { throw Exceptions("Zero height bitmap"); }
            if ((eFormat <= 0) || (eFormat > 4)) {
                throw Exceptions("Invalid bitmap format");
            }

            m_iWidth    = iWidth;
            m_iHeight   = iHeight;
            m_eFormat   = eFormat;

            size_t newSize = (m_iWidth * m_iHeight * m_eFormat);
            if (m_cPixels) {
                m_cPixels = (unsigned char *)realloc(m_cPixels, newSize);
            } else {
                m_cPixels = (unsigned char *)malloc(newSize);
            }

            if (m_cPixels) {
                memcpy(m_cPixels, cPixels, newSize);
            }
        }
    };
};
