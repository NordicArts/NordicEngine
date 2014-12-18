#ifndef NordicArts_NordicEngine_Files_Handler_BitMap_H
#define NordicArts_NoridcEngine_Files_Handler_BitMap_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class BitMap {
        // Variables
        public:
            enum Format {
                Format_Greyscale = 1,
                Format_GreyscaleAlpha = 2,
                Format_RGB = 3,
                Format_RGBA = 4
            };

        protected:
        private:

        // Methods
        public:
            BitMap(unsigned int iWidth, unsigned int iHeight, Format eFormat, const unsigned char *cPixels = NULL);
            ~BitMap();

        protected:
        private:

        };
    };
};

#endif
