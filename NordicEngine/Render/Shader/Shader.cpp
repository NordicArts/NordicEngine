#include <NordicEngine/Render/Shader/Shader.hpp>
#include <string>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            Shader::Shader() {

            }

            Shader::~Shader() {
                destroy();
            }

            GLint Shader::getVariable(std::string cVariable) {
                if (!m_iShaderID) {
                    return -1;
                }

                return glGetUniformLocation(m_iShaderID, cVariable.c_str());
            }

            std::string Shader::loadShaderFile(std::string cFile) {
                Files::Loader oLoader(cFile);

                return oLoader.read();
            }

            void Shader::initalize(std::string cVertexFile, std::string cFragmentFile) {
                std::string cVertex;
                std::string cFragment;

                // Need both vertex and fragment
                if (!cVertexFile.length() || !cFragmentFile.length()) { return; }

                // Remove old references
                if (m_iShaderID || m_iVertexID || m_iFragmentID) { destroy(); }

                // Errors
                GLenum eValue = glGetError();

                // Start the shaders
                m_iVertexID     = glCreateShader(GL_VERTEX_SHADER);
                m_iFragmentID   = glCreateShader(GL_FRAGMENT_SHADER);

                // Load the shaders
                cVertex     = loadShaderFile(cVertexFile);
                cFragment   = loadShaderFile(cFragmentFile);

                // Shaders are const char
                const char *cVertexShader   = cVertex.c_str();
                const char *cFragmentShader = cFragment.c_str();

                // Put shaders into system memory
                glShaderSource(m_iVertexID, 1, &cVertexShader, nullptr);
                glShaderSource(m_iFragmentID, 1, &cFragmentShader, nullptr);

                // compile the shaders
                glCompileShader(m_iVertexID);
                glCompileShader(m_iFragmentID);

                // get the programid
                m_iShaderID = glCreateProgram();

                // attach the shaders to the program
                glAttachShader(m_iShaderID, m_iVertexID);
                glAttachShader(m_iShaderID, m_iFragmentID);

                // link the shaders
                glLinkProgram(m_iShaderID);

                // error
                eValue = glGetError();
                if (eError != GL_NO_ERROR) {
                    throwError(__FUNCTION__, std::string("Error: ") + getError(eValue));
                }
            }

            void Shader::setInt(GLint iID, int iValue) {
                glUniform1i(iID, iValue);
            }

            void Shader::setFloat(GLint iID, GLfloat f0) {
                glUniform1f(iID, f0);
            }
            void Shader::setFloat(GLint iID, GLfloat f0, GLfloat f1) {
                glUniform2f(iID, f0, f1);
            }
            void Shader::setFloat(GLint iID, GLfloat f0, GLfloat f1, GLfloat f2) {
                glUniform3f(iID, f0, f1, f2);
            }
            void Shader::setFloat(GLint iID, GLfloat f0, GLfloat f1, GLfloat f2, GLfloat f3) {
                glUniform4f(iID, f0, f1, f2, f3);
            }

            void Shader::setMatrix(GLint iID, GLsizei iCount, GLboolean bTranspose, const GLfloat *fValue) {
                glUniformMatrix4fv(iID, iCount, bTranspose, fValue);
            }

            void Shader::turnOn() {
                glUseProgram(m_iShaderID);
            }

            void Shader::turnOff() {
                glUseProgram(0);
            }

            void Shader::destroy() {
                if (m_iVertexID) {
                    glDetectShader(m_iShaderID, m_iVertexID);
                    glDeleteShader(m_iVertexID);
                    m_iVertexID = 0;
                }

                if (m_iFragmentID) {
                    glDetectShader(m_iShaderID, m_iFragmentID);
                    glDeleteShader(m_iFragmentID);
                    m_iFragmentID = 0;
                }

                if (m_iShaderID) {
                    glDeleteShader(m_iShaderID);
                    m_iShaderID = 0;
                }
            }
        };
    };
};
