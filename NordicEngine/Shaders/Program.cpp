#include <NordicEngine/Shaders/Program.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Program::Program(const std::vector<Shaders> &oShaders) : m_iObject(0) {
            if (oShaders.size() <= 0) {
                throw std::runtime_error("No shaders were provided");
            }

            m_iObject = glCreateProgram();
            if (m_iObject == 0) {
                throw std::runtime_error("glCreateProgram failed");
            }

            // Attach shaders
            for (unsigned i = 0; i < oShaders.size(); ++i) {
                glAttachShader(m_iObject, oShaders[i].getObject());
            }

            // link program with attached shaders
            glLinkProgram(m_iObject);

            // detach shaders now program linked
            for (unsigned i = 0; i < oShaders.size(); ++i) {
                glDetachShader(m_iObject, oShaders[i].getObject());
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

                throw std::runtime_error(cMsg);
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
                throw std::runtime_error("Attribute name was NULL");
            }

            int iAttrib = glGetAttribLocation(m_iObject, cName);
            if (iAttrib == -1) {
                throw std::runtime_error(std::string("Program attribute not found ") + cName);
            }

            return iAttrib;
        }

        int Program::getUniform(const char *cName) const {
            if (!cName) {
                throw std::runtime_error("Uniform name was NULL");
            }

            int iUniform = glGetUniformLocation(m_iObject, cName);
            if (iUniform == -1) {
                throw std::runtime_error(std::string("Program uniform not found ") + cName);
            }

            return iUniform;
        }
    };
};