#include <NordicEngine/Shaders/Program.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Shaders {
            Program::Program(const std::vector<Shader> &vShaders) : m_iObject(0) {
                if (vShaders.size() <= 0) {
                    throw new Exceptions("No shaders were provided", true);
                }

                m_iObject = glCreateProgram();
                if (m_iObject == 0) {
                    throw new Exceptions("glCreateProgram failed", true);
                }

                // Attach shaders
                for (unsigned i = 0; i < vShaders.size(); ++i) {
                    glAttachShader(m_iObject, vShaders[i].getObject());
                }

                // link program with attached shaders
                glLinkProgram(m_iObject);

                // detach shaders now program linked
                for (unsigned i = 0; i < vShaders.size(); ++i) {
                    glDetachShader(m_iObject, vShaders[i].getObject());
                }

                // if linking failed throw error
                int iStatus;
                glGetProgramiv(m_iObject, GL_LINK_STATUS, &iStatus);
                if (iStatus == GL_FALSE) {
                    std::string cMsg("Program linking failed \n");

                    int iLogLength;
                    glGetProgramiv(m_iObject, GL_INFO_LOG_LENGTH, &iLogLength);

                    char *cInfoLog = new char[iLogLength + 1];
                    glGetProgramInfoLog(m_iObject, iLogLength, NULL, cInfoLog);
                    cMsg += cInfoLog;
                    SAFE_DELETE_ARRAY(cInfoLog);

                    glDeleteShader(m_iObject);
                    m_iObject = 0;
    
                    throw new Exceptions(cMsg, true);
                }
            }

            Program::~Program() {
                if (m_iObject != 0) {
                    glDeleteProgram(m_iObject);
                }
            }

            unsigned int Program::getObject() const {
                return m_iObject;
            }

            int Program::getAttrib(const char *cName) const {
                if (!cName) {
                    throw new Exceptions("Attribute name was NULL", true);
                }

                int iAttrib = glGetAttribLocation(m_iObject, cName);
                if (iAttrib == -1) {
                    throw new Exceptions((std::string("Program attribute not found") + cName), true);
                }

                return iAttrib;
            }

            int Program::getUniform(const char *cName) const {
                if (!cName) {
                    throw new Exceptions("Unform name was NULL", true);
                }

                int iUniform = glGetUniformLocation(m_iObject, cName);
                if (iUniform == -1) {
                    throw new Exceptions((std::string("Program unform not found") + cName), true);
                }

                return iUniform;
            }
        };
    };
};
