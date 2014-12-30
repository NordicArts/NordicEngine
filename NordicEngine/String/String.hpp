#ifndef NordicArts_NordicEngine_String_H
#define NordicArts_NordicEngine_String_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Time/Time.hpp>

namespace NordicArts {
    namespace NordicEngine {
        std::string getString(const char *cChar);
        std::string getString(const char cChar);
        std::string getString(float fFloat);
        std::string getString(int iInt);
        std::string getString(bool bValue);
        std::string getString(long lValue);

        std::string randString();
        std::string randString(int iLength);

        std::string toUpper(std::string &cString);
        std::string toLower(std::string &cString);

        unsigned covertToUnsigned(std::string &cString, std::ios_base &(*pFormat)(std::ios_base&));

        // Inline
        #include <NordicEngine/String/String.inl>
    };
};

#endif
