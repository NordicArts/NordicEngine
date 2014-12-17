#include <NordicEngine/Shaders/Shaders.hpp>
#include <NordicEngine/Files/Files.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Shaders::Shaders(const std::string &cShaderCode, GLenum eShaderType) : m_iObject(0), m_pRefCount(NULL) {
            m_iObject = glCreateShader(eShaderType);
            if (m_iObject == 0) {
                throw std::runtime_error("glCreateShader failed");
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

                throw std::runtime_error(cMsg);
            }

            m_pRefCount     = new unsigned;
            *m_pRefCount    = 1;
        }

        Shaders::Shaders(const Shaders &oOther) : m_iObject(oOther.m_iObject), m_pRefCount(oOther.m_pRefCount) {
            retain();
        }

        Shaders::~Shaders() {
            if (m_pRefCount) {
                release();
            }
        }

        unsigned int Shaders::getObject() const {
            return m_iObject;
        }

        Shaders &Shaders::operator =(const Shaders &oOther) {
            release();

            m_iObject   = oOther.m_iObject;
            m_pRefCount = oOther.m_pRefCount;

            retain();

            return *this;
        }

        Shaders Shaders::shaderFromFile(const std::string &cFilePath, GLenum eShaderType) {
            Files oFile(cFilePath, true);

            Shaders oShader(oFile.read(), eShaderType);
            return oShader;
        }

        void Shaders::retain() {
            assert(m_pRefCount);

            *m_pRefCount += 1;
        }

        void Shaders::release() {
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
