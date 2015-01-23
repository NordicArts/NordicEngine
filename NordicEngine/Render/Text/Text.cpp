#include <NordicEngine/Render/Text/Text.hpp>
#include <NordicEngine/Files/Texture/Texture.hpp>
#include <NordicEngine/Shaders/Simple.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>
#include <NordicEngine/ThirdParty/glm/glm/gtc/matrix_transform.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            Text::Text() {
            };
    
            Text::~Text() {
            }

            void Text::setup(std::string cFileName) {
                Files::Texture oTexture(cFileName);
                m_iTextureID = oTexture.loadTexture();

                glGenBuffers(1, &m_iVertexBufferID);
                glGenBuffers(1, &m_iUVBufferID);

                Shaders::Simple oShaders;
                m_iShaderID     = oShaders.LoadShaders("GameFiles/Shaders/Text.vertex", "GameFiles/Shaders/Text.fragment");
                m_iUniformID    = glGetUniformLocation(m_iShaderID, "myTextureSampler");
            }

            void Text::render(std::string cText, int iX, int iY, int iSize) {
                unsigned int iLength = cText.length();

                std::vector<glm::vec2> vVerticies;
                std::vector<glm::vec2> vUVs;
                for (unsigned int i = 0; i < iLength; i++) {
                    glm::vec2 vVertexUpLeft       = glm::vec2((iX + (i * iSize)), (iY * iSize));
                    glm::vec2 vVertexUpRight      = glm::vec2((iX + (i * iSize) + iSize), (iY * iSize));
                    glm::vec2 vVertexDownRight    = glm::vec2((iX + (i * iSize) + iSize), iY);
                    glm::vec2 vVertexDownLeft     = glm::vec2((iX + (i * iSize)), iY);

                    vVerticies.push_back(vVertexUpLeft);
                    vVerticies.push_back(vVertexDownLeft);
                    vVerticies.push_back(vVertexUpRight);
                    vVerticies.push_back(vVertexDownRight);
                    vVerticies.push_back(vVertexUpRight);
                    vVerticies.push_back(vVertexDownLeft);

                    char cCharacter = cText[i];

                    float fX = ((cCharacter % 16) / 16.0f);
                    float fY = ((cCharacter / 16) / 16.0f);

                    glm::vec2 vUVUpLeft     = glm::vec2(fX, fY);
                    glm::vec2 vUVUpRight    = glm::vec2((fX + (1.0f / 16.0f)), fY);
                    glm::vec2 vUVDownRight  = glm::vec2((fX + (1.0f / 16.0f)), (fY + (1.0f / 16.0f)));
                    glm::vec2 vUVDownLeft   = glm::vec2(fX, (fY + (1.0f / 16.0f)));
                
                    vUVs.push_back(vUVUpLeft);
                    vUVs.push_back(vUVDownLeft);
                    vUVs.push_back(vUVUpRight);
                    vUVs.push_back(vUVDownRight);
                    vUVs.push_back(vUVUpRight);
                    vUVs.push_back(vUVDownLeft);
                }

                // Bind the buffers
                glBindBuffer(GL_ARRAY_BUFFER, m_iVertexBufferID);
                glBufferData(GL_ARRAY_BUFFER, (vVerticies.size() * sizeof(glm::vec2)), &vVerticies[0], GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, m_iUVBufferID);
                glBufferData(GL_ARRAY_BUFFER, (vUVs.size() * sizeof(glm::vec2)), &vUVs[0], GL_STATIC_DRAW);

                // Bind the shader
                glUseProgram(m_iShaderID);

                // Bind texture
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, m_iTextureID);
                glUniform1i(m_iUniformID, 0);

                // Vertex buffer
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, m_iVertexBufferID);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

                // UV buffer
                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, m_iUVBufferID);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

                // Enable Blend
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                // Draw
                glDrawArrays(GL_TRIANGLES, 0, vVerticies.size());

                // Disable Bend
                glDisable(GL_BLEND);

                // Drop the attribs
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
            }

            void Text::cleanup() {
                // Delete buffers
                glDeleteBuffers(1, &m_iVertexBufferID);
                glDeleteBuffers(1, &m_iUVBufferID);

                // Delete texture
                glDeleteTextures(1, &m_iTextureID);

                // Delete shader
                glDeleteProgram(m_iShaderID);
            }
        };
    };
};
