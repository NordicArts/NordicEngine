
#include <NordicEngine/Model/Model.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Model::Model() {
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

            glVertexAttribPointer(m_iVertexIndex, 3, GL_FLOAT, GL_FALSE, sizeof(m_vVertices[0]), 0);

            eError = glGetError();
            if (eError != GL_NO_ERROR) {
                printIt(eError);
                throwError(__FUNCTION__, std::string("Couldnt create the VAO, VBO,  Error: "));
            }
        }

        void Model::render() {
            m_oShader.turnOn();
            
            glBindVertexArray(m_iVertexArrayID);

            glEnableVertexAttribArray(m_iVertexIndex);

            glDrawArrays(GL_TRIANGLES, 0, m_iSize);

            glDisableVertexAttribArray(m_iVertexIndex);

            glBindVertexArray(0);

            m_oShader.turnOff();
        }

        void Model::destroy() {
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

            m_oShader.destroy();
        }
    };
};
