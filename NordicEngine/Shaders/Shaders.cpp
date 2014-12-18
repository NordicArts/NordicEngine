#include <NordicEngine/Shaders/Shaders.hpp>
#include <NordicEngine/Files/Files.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Shaders {
            Shader::Shader(const std::string &cShaderCode, GLenum eShaderType) : m_iObject(0), m_pRefCount(NULL) {
                m_iObject = glCreateShader(eShaderType);
                if (m_iObject == 0) {
                    throw new Exceptions("glCreateShader failed", true);
                }

                const char *cCode = cShaderCode.c_str();
                glShaderSource(m_iObject, 1, (const GLchar **)&cCode, NULL);
                glCompileShader(m_iObject);

                GLint iStatus;
                glGetShaderiv(m_iObject, GL_COMPILE_STATUS, &iStatus);
                if (iStatus == GL_FALSE) {
                    std::string cMsg("Compile failed in shader: \n");

                    GLint iInfoLogLength;
                    glGetShaderiv(m_iObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
    
                    char *cInfoLog = new char[iInfoLogLength + 1];
                    glGetShaderInfoLog(m_iObject, iInfoLogLength, NULL, cInfoLog);
    
                    cMsg += cInfoLog;
                    SAFE_DELETE_ARRAY(cInfoLog);
    
                    glDeleteShader(m_iObject);
                    m_iObject = 0;
    
                    throw new Exceptions(cMsg, true);
                }

                m_pRefCount     = new unsigned;
                *m_pRefCount    = 1;
            }

            Shader::Shader(const Shader &oOther) : m_iObject(oOther.m_iObject), m_pRefCount(oOther.m_pRefCount) {
                retain();
            }

            Shader::~Shader() {
                if (m_pRefCount) {
                    release();
                }
            }

            unsigned int Shader::getObject() const {
                return m_iObject;
            }

            Shader &Shader::operator =(const Shader &oOther) {
                release();

                m_iObject   = oOther.m_iObject;
                m_pRefCount = oOther.m_pRefCount;

                retain();

                return *this;
            }

            Shader Shader::shaderFromFile(const std::string &cFilePath, GLenum eShaderType) {
                Files oFile(cFilePath, true);

                Shader oShader(oFile.read(), eShaderType);
                return oShader;
            }

            void Shader::retain() {
                assert(m_pRefCount);

                *m_pRefCount += 1;
            }

            void Shader::release() {
                assert(m_pRefCount && (*m_pRefCount > 0));

                *m_pRefCount -= 1;
                if (m_pRefCount == 0) {
                    glDeleteShader(m_iObject);
                    m_iObject = 0;

                    SAFE_DELETE(m_pRefCount);
                }
            }
        };
    };
};
