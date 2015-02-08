#ifndef NordicArts_NordicEngine_Render_Model_Model_H
#define NordicArts_NordicEngine_Render_Model_Model_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Render/Shader/Shader.hpp>
#include <NordicEngine/Logger/Logger.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Models {
                class Model {
                // Variables
                public:
                    static const GLuint m_iVertexIndex  = 0;
                    static const GLuint m_iColorIndex   = 1;
                    static const GLuint m_iTextureID    = 2;
                    static const GLuint m_iNormalIndex  = 3;

                protected:
                private:
                    std::string m_cName;
                    std::string m_cVertexShader;
                    std::string m_cFragmentShader;

                    std::vector<glm::vec3> m_vVertices;

                    GLint m_iSize;
                
                    GLuint m_iVertexID;
                    GLuint m_iVertexArrayID;

                    Render::Shader m_oShader;
                    Logger *m_pLogger;

                // Methods
                public:
                    Model(std::string cName);
                    Model(std::string cName, Logger *pLogger);
            
                    ~Model();

                    void setup(std::vector<glm::vec3> vVerticies, int iLength, std::string cVertex, std::string cFragment);
                    void initalize();
                    void render();
                    void destroy();

                    std::string getName() const;

                protected:
                private:
              
                };
            };
        };
    };
};

#endif
