#include <NordicEngine/Render/Models/Model.hpp>
#include <NordicEngine/Render/Shader/Shader.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Models {
                Model::Model(std::string cName) : m_cName(cName) {
                }
                Model::Model(std::string cName, Logger *pLogger) : m_cName(cName), m_pLogger(pLogger) {
                }

                Model::~Model() {
                    destroy();
                }

                void Model::initalize(std::vector<glm::vec3> vVertices, int iLength, std::string cVertex, std::string cFragment) {
                    m_oShader.initalize(cVertex, cFragment);

                    m_vVertices     = vVertices;
                    m_iSize         = iLength;

                    GLenum eError = glGetError();
            
                    glGenVertexArrays(1, &m_iVertexArrayID);
                    glBindVertexArray(m_iVertexArrayID);

                    glGenBuffers(1, &m_iVertexID);
                    glBindBuffer(GL_ARRAY_BUFFER, m_iVertexID);
                    glBufferData(GL_ARRAY_BUFFER, (vVertices.size() * iLength), &vVertices[0], GL_STATIC_DRAW);

                    glVertexAttribPointer(m_iVertexIndex, 3, GL_FLOAT, GL_FALSE, sizeof(m_vVertices[0]), 0);

                    eError = glGetError();

                    if (eError != GL_NO_ERROR) {
                        printIt(eError);
                        throwError(__FUNCTION__, std::string("Couldnt create the VAO, VBO,  Error: "));
                    }
                }

                void Model::render() {
                    if (m_pLogger) { m_pLogger->log("Render Model Start"); }

                    m_oShader.turnOn();
            
                    glBindVertexArray(m_iVertexArrayID);

                    glEnableVertexAttribArray(m_iVertexIndex);

                    glDrawArrays(GL_TRIANGLES, 0, m_iSize);

                    glDisableVertexAttribArray(m_iVertexIndex);
    
                    glBindVertexArray(0);

                    m_oShader.turnOff();

                    if (m_pLogger) { m_pLogger->log("Render Model End"); }
                }

                void Model::destroy() {
                    if (m_pLogger) { m_pLogger->log("Destorying Model"); }

                    if (m_iVertexID) {
                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                
                        glDeleteBuffers(1, &m_iVertexID);
            
                        m_iVertexID = 0;
                    }

                    if (m_iVertexArrayID) {
                        glBindVertexArray(0);
            
                        glDeleteVertexArrays(1, &m_iVertexArrayID);
    
                        m_iVertexArrayID = 0;
                    }

                    if (m_pLogger) { m_pLogger->log("Destroyed Model"); }

                    m_oShader.destroy();
                }

                std::string Model::getName() const {
                    return m_cName;
                }
            };
        };
    };
};
