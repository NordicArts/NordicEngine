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

                void Model::setup(std::vector<glm::vec3> vVertices, std::vector<glm::vec2> vUVs, std::vector<glm::vec3> vNormals, std::string cVertex, std::string cFragment) {
                    m_vVertices         = vVertices;
                    m_vNormals          = vNormals;
                    m_vUVs              = vUVs;
                    m_cFragmentShader   = cFragment;
                    m_cVertexShader     = cVertex;
                }

                void Model::initalize() {
                    m_oShader.initalize(m_cVertexShader, m_cFragmentShader);
                    GLenum eError;

                    // Buffer
                    glGenVertexArrays(1, &m_iVertexArrayID);
                    glBindVertexArray(m_iVertexArrayID);

                    eError = glGetError();
                    if (eError != GL_NO_ERROR) {
                        throwError(__FUNCTION__, std::string("Couldnt create the VAO, VBO,  Error Buffer: ") + getGLError(eError));
                    }

                    // Vertex
                    if (m_vVertices.size() >= 1) {
                        glGenBuffers(1, &m_iVertexID);
                        glBindBuffer(GL_ARRAY_BUFFER, m_iVertexID);
                        glBufferData(GL_ARRAY_BUFFER, (m_vVertices.size() * sizeof(glm::vec3)), &m_vVertices[0], GL_STATIC_DRAW);
                        glVertexAttribPointer(m_iVertexIndex, 3, GL_FLOAT, GL_FALSE, sizeof(m_vVertices[0]), 0);

                        eError = glGetError();
                        if (eError != GL_NO_ERROR) {
                            throwError(__FUNCTION__, std::string("Couldnt create the VAO, VBO,  Error Vertex: ") + getGLError(eError));
                        }
                    }

                    // UVs
                    if (m_vUVs.size() >= 1) {
                        glGenBuffers(1, &m_iUVID);
                        glBindBuffer(GL_ARRAY_BUFFER, m_iUVID);
                        glBufferData(GL_ARRAY_BUFFER, (m_vUVs.size() * sizeof(glm::vec2)), &m_vUVs[0], GL_STATIC_DRAW);
                        glVertexAttribPointer(m_iUVID, 2, GL_FLOAT, GL_FALSE, sizeof(m_vUVs[0]), 0);

                        eError = glGetError();
                        if (eError != GL_NO_ERROR) {
                            throwError(__FUNCTION__, std::string("Couldnt create the VAO, VBO,  Error UV: ") + getGLError(eError));
                        }
                    }
                }

                void Model::render() {
                    m_oShader.turnOn();

                    // Send Model
                    glBindVertexArray(m_iVertexArrayID);

                    // Vertex
                    glEnableVertexAttribArray(m_iVertexIndex);
                    glBindBuffer(GL_ARRAY_BUFFER, m_iVertexArrayID);


                    // UVs
                    if (m_iUVID) {
                        glEnableVertexAttribArray(m_iUVID);
                        glBindBuffer(GL_ARRAY_BUFFER, m_iUVID);
                    }

                    // Draw
                    glDrawArrays(GL_TRIANGLES, 0, m_vVertices.size());

                    // Disable
                    if (m_iUVID) { glDisableVertexAttribArray(m_iUVID); }
                    if (m_iVertexIndex) { glDisableVertexAttribArray(m_iVertexIndex); }

                    glBindVertexArray(0);

                    m_oShader.turnOff();
                }

                void Model::destroy() {
                    if (m_iVertexID) {
                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                        glDeleteBuffers(1, &m_iVertexID);
                        m_iVertexID = 0;
                    }

                    if (m_iUVID) {
                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                        glDeleteBuffers(1, &m_iUVID);
                        m_iUVID = 0;
                    }

                    if (m_iVertexArrayID) {
                        glBindVertexArray(0);
                        glDeleteVertexArrays(1, &m_iVertexArrayID);
                        m_iVertexArrayID = 0;
                    }

                    m_oShader.destroy();
                }

                std::string Model::getName() const {
                    return m_cName;
                }
            };
        };
    };
};
