#include <NordicEngine/Color/Color.hpp>

namespace NordicArts {
    namespace NordicEngine {
        const Color Color::Black(0, 0, 0);
        const Color Color::White(255, 255, 255);
        const Color Color::Red(255, 0, 0);
        const Color Color::Green(0, 255, 0);
        const Color Color::Blue(0, 0, 255);
        const Color Color::Yellow(255, 255, 0);
        const Color Color::Magenta(255, 0, 255);
        const Color Color::Cyan(0, 255, 255);
        const Color Color::Transparent(0, 0, 0, 0);

        Color::Color() : m_iRed(0), m_iGreen(0), m_iBlue(0), m_iAlpha(255) {
        }
        Color::Color(uint8_t iRed, uint8_t iGreen, uint8_t iBlue, uint8_t iAlpha) : m_iRed(iRed), m_iGreen(iGreen), m_iBlue(iBlue), m_iAlpha(iAlpha) {
        }
        Color::Color(std::string cHex) {
            // Remove the hash
            size_t nFound = cHex.find("#");
            if (nFound != std::string::npos) { cHex = cHex.erase(0, 1); }

            int iColor  = (int)std::strtol(cHex.c_str(), NULL, 16);
            m_iRed      = (iColor >> 16);
            m_iGreen    = (iColor >> (8 & 0xFF));
            m_iBlue     = (iColor & 0xFF);
            m_iAlpha    = 255;
        }

        float Color::getRed() const {
            return (float)m_iRed;
        }
        
        float Color::getGreen() const {
            return (float)m_iGreen;
        }

        float Color::getBlue() const {
            return (float)m_iBlue;
        }
        
        float Color::getAlpha() const {
            return (float)m_iAlpha;
        }

        bool operator ==(const Color &oLeft, const Color &oRight) {
            return (
                (oLeft.m_iRed == oRight.m_iRed) &&
                (oLeft.m_iGreen == oRight.m_iGreen) &&
                (oLeft.m_iBlue == oRight.m_iBlue) &&
                (oLeft.m_iAlpha == oRight.m_iAlpha)
            );
        }
        bool operator !=(const Color &oLeft, const Color &oRight) {
            return !(oLeft == oRight);
        }

        Color operator +(const Color &oLeft, const Color &oRight) {
            return Color(
                (uint8_t(std::min(int(oLeft.m_iRed) + oRight.m_iRed, 255))),
                (uint8_t(std::min(int(oLeft.m_iGreen) + oRight.m_iGreen, 255))),
                (uint8_t(std::min(int(oLeft.m_iBlue) + oRight.m_iBlue, 255))),
                (uint8_t(std::min(int(oLeft.m_iAlpha) + oRight.m_iAlpha, 255)))
            );
        }
        Color operator -(const Color &oLeft, const Color &oRight) {
            return Color(
                (uint8_t(std::max(int(oLeft.m_iRed) - oRight.m_iRed, 0))),
                (uint8_t(std::max(int(oLeft.m_iGreen) - oRight.m_iGreen, 0))),
                (uint8_t(std::max(int(oLeft.m_iBlue) - oRight.m_iBlue, 0))),
                (uint8_t(std::max(int(oLeft.m_iAlpha) - oRight.m_iAlpha, 0)))
            );
        }        
        Color operator *(const Color &oLeft, const Color &oRight) {
            return Color(
                (uint8_t((int(oLeft.m_iRed) * oRight.m_iRed) / 255)),
                (uint8_t((int(oLeft.m_iGreen) * oRight.m_iGreen) / 255)),
                (uint8_t((int(oLeft.m_iBlue) * oRight.m_iBlue) / 255)),
                (uint8_t((int(oLeft.m_iAlpha) * oRight.m_iAlpha) / 255))
            );
        }        

        Color &operator +=(Color &oLeft, const Color &oRight) {
            return oLeft = (oLeft + oRight);
        }
        Color &operator -=(Color &oLeft, const Color &oRight) {
            return oLeft = (oLeft - oRight);
        }
        Color &operator *=(Color &oLeft, const Color &oRight) {
            return oLeft = (oLeft * oRight);
        }
    };
};
