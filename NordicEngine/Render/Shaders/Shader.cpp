#include <NordicEngine/Render/Shaders/Shader.hpp>
#include <NordicEngine/Files/Loader.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                std::string getShaderType(ShaderType eType) {
                    std::string cReturn;

                    switch (eType) {
                        case NES_VERTEX: {
                            cReturn = "vertex";
                            break;
                        }
                        
                        case NES_FRAGMENT: {
                            cReturn = "fragment";
                            break;
                        }
                    
                        case NES_GEOMETRY: {
                            cReturn = "geometry";
                            break;
                        }

                        case NES_COMPUTE: {
                            cReturn = "compute";
                            break;
                        }

                        case NES_TESS_CONTROL: {
                            cReturn = "tesselation control";
                            break;
                        }

                        case NES_TESS_EVAL: {
                            cReturn = "tesselation evaluation";
                            break;
                        }

                        default: {
                            cReturn = "unknown";
                            break;
                        }
                    }

                    return cReturn;
                }

                Shader::Shader(ShaderType eType, std::string cFile) {
                    m_iID   = glCreateShader(eType);
                    m_eType = eType;
                    m_cType = getShaderType(eType);

                    // load the file
                    Files::Loader oFile(cFile);
                    std::string cShader = oFile.read();
                    const char *cSource = cShader.c_str();
                    
                    glShaderSource(m_iID, 1, &cSource, NULL);
                    glCompileShader(m_iID);

                    int iStatus;
                    glGetShaderiv(m_iID, GL_COMPILE_STATUS, &iStatus);
                    if (iStatus != GL_TRUE) {
                        int iLength;
                        glGetShaderiv(m_iID, GL_INFO_LOG_LENGTH, &iLength);

                        char *cLog = new char[iLength];
                        glGetShaderInfoLog(m_iID, iLength, NULL, cLog);

                        throwError(__FUNCTION__ + std::string(" shader failed, ") + cFile + std::string(", ") + getShaderType(eType));
                        
                        SAFE_DELETE_ARRAY(cLog);
                    
                        glDeleteShader(m_iID);
                    }
                }

                Shader::~Shader() {
                    glDeleteShader(m_iID);
                }

                unsigned int Shader::getID() const {
                    return m_iID;
                }

                ShaderType Shader::getType() const {
                    return m_eType;
                }

                std::string Shader::getStringType() const {
                    return m_cType;
                }
            };
        };
    };
};
