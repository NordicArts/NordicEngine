#ifndef NordicArts_NordicEngine_Render_Shaders_Loader_H
#define NordicArts_NordicEngine_Render_Shaders_Loader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/OS/OpenGL.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                class Shader;

                class Loader {
                // Variables
                public:
                protected:
                private:
                    unsigned int m_iProgramID;
                    unsigned int m_iVertexID;
                    unsigned int m_iFragmentID;

                    std::vector<Shader*> m_vShaders;

                // Methods
                public:
                    Loader();
                    Loader(std::string cVertex, std::string cFragment);
    
                    unsigned int buildShader();
                    unsigned int addShader(std::string cFilename, ShaderType eType);
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
