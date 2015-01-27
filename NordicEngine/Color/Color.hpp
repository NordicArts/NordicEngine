#ifndef NordicArts_NordicEngine_Color_H
#define NordicArts_NordicEngine_Color_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Color {
        // Variables
        public:
            static const Color Black;
            static const Color White;
            static const Color Red;
            static const Color Green;
            static const Color Blue;
            static const Color Yellow;
            static const Color Magenta;
            static const Color Cyan;
            static const Color Transparent;

            uint8_t m_iRed;
            uint8_t m_iBlue;
            uint8_t m_iGreen;
            uint8_t m_iAlpha;
        
        protected:
        private:

        // Methods
        public:
            Color();
            Color(uint8_t iRed, uint8_t iGreen, uint8_t iBlue, uint8_t iAlpha = 255);
            Color(std::string cHex);

            float getRed() const;
            float getGreen() const;
            float getBlue() const;
            float getAlpha() const;

        protected:
        private:

        };


        bool operator ==(const Color &oLeft, const Color &oRight);
        bool operator !=(const Color &oLeft, const Color &oRight);

        Color operator +(const Color &oLeft, const Color &oRight);
        Color operator -(const Color &oLeft, const Color &oRight);
        Color operator *(const Color &oLeft, const Color &oRight);

        Color &operator +=(const Color &oLeft, const Color &oRight);
        Color &operator -=(const Color &oLeft, const Color &oRight);
        Color &operator *=(const Color &oLeft, const Color &oRight);    
    };
};

#endif
