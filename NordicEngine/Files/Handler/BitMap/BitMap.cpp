#include <NordicEngine/Files/Handler/BitMap/BitMap.hpp>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <NordicEngine/stb/stb_image.h>
#include <NordicEngine/glfw/deps/GL/wglext.h>
#include "BitMap.hpp"

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

                case BitMap::Foramt_RGBA: {
                    switch (eDestFormat) {
                        case BitMap::Format_Grayscale: return RGBA2Grayscale;
                        case BitMap::Format_GrayscaleAlpha: return RGBA2GrayscaleAlpha;
                        case BitMap::Foramt_RGB: return RGB2RGBA;
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
    };
};
