#ifndef NordicArts_NordicEngine_String_INL
#define NordicArts_NordicEngine_String_INL

#include <NordicEngine/ExceptionHandler/ExceptionHandler.hpp>

template<typename T>
T convertToType(const std::string &cString, std::ios_base &(*pFormat)(std::ios_base&)) {
    T output;

    std::istringstream input(cString);
    input >> pFormat >> output;

    if (!input) {
        std::ostringstream cStream;
        cStream << __FUNCTION__ << ": Bad conversion of [" << cString << "] to " << typeid(output).name();
        throw NordicArts::NordicEngine::ExceptionHandler(cStream);
    }    

    char cChar;
    if (input.get(cChar)) {
        std::ostringstream cStream;
        cStream << __FUNCTION__ << ": Conversion of [" << cString << "] to " << typeid(output).name() << " - [" << output << "] Failed";
        
        throw NordicArts::NordicEngine::ExceptionHandler(cStream);
    }

    return output;
}

#endif
