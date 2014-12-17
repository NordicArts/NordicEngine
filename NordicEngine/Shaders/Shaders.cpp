#include <NordicEngine/Shaders/Shaders.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Shaders::Shaders(const std::string &cShaderCode, GLenum eShaderType) : m_iObject(0), m_pRefCount(NULL) {
            m_iObject = glCreateShader(eShaderType);
            if (m_iObject == 0) {
                throw std::runtime_error("glCreateShader failed");
            }

            
        }
    };
};
