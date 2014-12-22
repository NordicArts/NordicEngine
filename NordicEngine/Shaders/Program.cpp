#include <NordicEngine/Shaders/Program.hpp>

#include <NordicEngine/ThirdParty/glm/glm/gtc/type_ptr.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Shaders {
            Program::Program(const std::vector<Shader> &vShaders) : m_iObject(0) {
                if (vShaders.size() <= 0) {
                    throw Exceptions("No shaders were provided", true);
                }

                m_iObject = glCreateProgram();
                if (m_iObject == 0) {
                    throw Exceptions("glCreateProgram failed", true);
                }

                // Attach shaders
                for (unsigned int i = 0; i < vShaders.size(); ++i) {
                    glAttachShader(m_iObject, vShaders[i].getObject());
                }

                // link program with attached shaders
                glLinkProgram(m_iObject);

                // detach shaders now program linked
                for (unsigned int i = 0; i < vShaders.size(); ++i) {
                    glDetachShader(m_iObject, vShaders[i].getObject());
                }

                // if linking failed throw error
                int iStatus;
                glGetProgramiv(m_iObject, GL_LINK_STATUS, &iStatus);
                if (iStatus == false) {
                    std::string cMsg("Program linking failed \n");

                    int iLogLength;
                    glGetProgramiv(m_iObject, GL_INFO_LOG_LENGTH, &iLogLength);

                    char *cInfoLog = new char[iLogLength + 1];
                    glGetProgramInfoLog(m_iObject, iLogLength, NULL, cInfoLog);
                    cMsg += cInfoLog;
                    SAFE_DELETE_ARRAY(cInfoLog);

                    glDeleteShader(m_iObject);
                    m_iObject = 0;
    
                    throw Exceptions(cMsg, true);
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
                    throw Exceptions("Attribute name was NULL", true);
                }

                int iAttrib = glGetAttribLocation(m_iObject, cName);
                if (iAttrib == -1) {
                    throw Exceptions((std::string("Program attribute not found") + cName), true);
                }

                return iAttrib;
            }

            int Program::getUniform(const char *cName) const {
                if (!cName) {
                    throw Exceptions("Unform name was NULL", true);
                }

                int iUniform = glGetUniformLocation(m_iObject, cName);
                if (iUniform == -1) {
                    throw Exceptions((std::string("Program unform not found") + cName), true);
                }

                return iUniform;
            }

            void Program::use() const {
                glUseProgram(m_iObject);
            }
            
            void Program::stopUsing() const {
                assert(isInUse());
                
                glUseProgram(0);
            }
            
            bool Program::isInUse() const {
                int iCurrentProgram = 0;
            
                glGetIntegerv(GL_CURRENT_PROGRAM, &iCurrentProgram);
                
                return (iCurrentProgram == (int)m_iObject);
            }

            #define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
            \
            void Program::setAttrib(const char *cName, OGL_TYPE v0) { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (getAttrib(cName), v0); } \
            void Program::setAttrib(const char *cName, OGL_TYPE v0, OGL_TYPE v1) { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (getAttrib(cName), v0, v1); } \
            void Program::setAttrib(const char *cName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (getAttrib(cName), v0, v1, v2); } \
            void Program::setAttrib(const char *cName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (getAttrib(cName), v0, v1, v2, v3); } \
            \
            void Program::setAttrib1v(const char *cName, const OGL_TYPE *v) { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (getAttrib(cName), v); } \
            void Program::setAttrib2v(const char *cName, const OGL_TYPE *v) { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (getAttrib(cName), v); } \
            void Program::setAttrib3v(const char *cName, const OGL_TYPE *v) { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (getAttrib(cName), v); } \
            void Program::setAttrib4v(const char *cName, const OGL_TYPE *v) { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (getAttrib(cName), v); } \
            \
            void Program::setUniform(const char *cName, OGL_TYPE v0) { assert(isInUse()); glUniform1 ## TYPE_SUFFIX (getUniform(cName), v0); }\
            void Program::setUniform(const char *cName, OGL_TYPE v0, OGL_TYPE v1) { assert(isInUse()); glUniform2 ## TYPE_SUFFIX (getUniform(cName), v0, v1); } \
            void Program::setUniform(const char *cName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) { assert(isInUse()); glUniform3 ## TYPE_SUFFIX (getUniform(cName), v0, v1, v2); } \
            void Program::setUniform(const char *cName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) { assert(isInUse()); glUniform4 ## TYPE_SUFFIX (getUniform(cName), v0, v1, v2, v3); } \
            \
            void Program::setUniform1v(const char *cName, const OGL_TYPE *v, int iCount) { assert(isInUse()); glUniform1 ## TYPE_SUFFIX ## v (getUniform(cName), iCount, v); } \
            void Program::setUniform2v(const char *cName, const OGL_TYPE *v, int iCount) { assert(isInUse()); glUniform2 ## TYPE_SUFFIX ## v (getUniform(cName), iCount, v); } \
            void Program::setUniform3v(const char *cName, const OGL_TYPE *v, int iCount) { assert(isInUse()); glUniform3 ## TYPE_SUFFIX ## v (getUniform(cName), iCount, v); } \
            void Program::setUniform4v(const char *cName, const OGL_TYPE *v, int iCount) { assert(isInUse()); glUniform4 ## TYPE_SUFFIX ## v (getUniform(cName), iCount, v); }

            ATTRIB_N_UNIFORM_SETTERS(float, , f);
            ATTRIB_N_UNIFORM_SETTERS(double, , d);
            ATTRIB_N_UNIFORM_SETTERS(int, I, i);
            ATTRIB_N_UNIFORM_SETTERS(unsigned int, I, ui);

            void Program::setUniformMatrix2(const char *cName, const float *v, int iCount, bool bTranspose) {
                assert(isInUse());
                
                glUniformMatrix2fv(getUniform(cName), iCount, bTranspose, v);
            }
            void Program::setUniformMatrix3(const char *cName, const float *v, int iCount, bool bTranspose) {
                assert(isInUse());
        
                glUniformMatrix3fv(getUniform(cName), iCount, bTranspose, v);
            }
            void Program::setUniformMatrix4(const char *cName, const float *v, int iCount, bool bTranspose) {
                assert(isInUse());
            
                glUniformMatrix4fv(getUniform(cName), iCount, bTranspose, v);
            }

            void Program::setUniform(const char *cName, const glm::mat2 &m, bool bTranspose) {
                assert(isInUse());

                glUniformMatrix2fv(getUniform(cName), 1, bTranspose, glm::value_ptr(m));
            }
            void Program::setUniform(const char *cName, const glm::mat3 &m, bool bTranspose) {
                assert(isInUse());
        
                glUniformMatrix3fv(getUniform(cName), 1, bTranspose, glm::value_ptr(m));
            }
            void Program::setUniform(const char *cName, const glm::mat4 &m, bool bTranspose) {
                assert(isInUse());
    
                glUniformMatrix4fv(getUniform(cName), 1, bTranspose, glm::value_ptr(m));
            }
            void Program::setUniform(const char *cName, const glm::vec3 &v) {
                setUniform3v(cName, glm::value_ptr(v));
            }
            void Program::setUniform(const char *cName, const glm::vec4 &v) {
                setUniform4v(cName, glm::value_ptr(v));
            }
        };
    };
};
