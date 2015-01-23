#ifndef NordicArts_NordicEngine_Render_Shaders_Loader_H
#define NordicArts_NordicEngine_Render_Shaders_Loader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Window/Window.hpp>

// Not using GL 4.0
#ifndef GL_TESS_EVALUATION_SHADER
    #define GL_TESS_EVALUATION_SHADER NULL
    #define GL_TESS_CONTROL_SHADER NULL
#endif

// Not using GL 4.3
#ifndef GL_COMPUTE_SHADER
    #define GL_COMPUTE_SHADER NULL
#endif

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                class Shader;

                enum ShaderTypes {
                    NES_VERTEX          = GL_VERTEX_SHADER,
                    NES_FRAGMENT        = GL_FRAGMENT_SHADER,
                    NES_GEOMETRY        = GL_GEOMETRY_SHADER,
                    NES_COMPUTE         = GL_COMPUTE_SHADER,
                    NES_TESS_CONTROL    = GL_TESS_CONTOL_SHADER,
                    NES_TESS_EVAL       = GL_TESS_EVALUATION_SHADER
                };

                class Loader {
                // Variables
                public:
                protected:
                private:
                    unsigned int m_iProgramID;
                    unsigned int m_iVertexID;
                    unsigned int m_iFragmentID;

                    std::vector<Shader> m_vShaders;

                // Methods
                public:
                    Loader();
                    Loader(std::string cVertex, std::string cFragment);
    
                    unsigned int buildShader();
                    unsigned int addShader(std::string cFilename, ShaderTypes eType);
                    unsigned int getProgramID() const;

                    void unloadShader(unsigned int iShaderID);
                    void unloadProgram(unsigned int iProgramID);

                protected:
                private:
                    unsigned int checkRequiredShaders() const;
                };
            };
        };
    };
};

#endif
