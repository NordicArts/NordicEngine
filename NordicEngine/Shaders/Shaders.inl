#ifndef NordicArts_NordicEngine_Shaders_INL
#define NordicArts_NordicEngine_Shaders_INL

#include <NordicEngine/Exception/Exception.hpp>

template <typename T>
void SetLightUniform(Shaders::Program *pShaders, const char *cPropertyName, size_t lightIndex, const T &value) {
    std::ostringstream ss;
    ss << "allLights[" << lightIndex << "]." << cPropertyName;
    std::string cUniformName = ss.str();

    pShaders->setUniform(cUniformName.c_str(), value);
}

#endif
