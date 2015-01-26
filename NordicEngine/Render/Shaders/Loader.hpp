#ifndef NordicArts_NordicEngine_Render_Shaders_Loader_H
#define NordicArts_NordicEngine_Render_Shaders_Loader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/OS/OpenGL.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Logger;

        namespace Render {
            namespace Shaders {
                ShaderType getShaderType(std::string cType);

                class Shader;

                class Loader {
                // Variables
                public:
                protected:
                private:
                    unsigned int m_iProgramID;

                    Logger *m_pLogger;

                    std::map<std::string, std::string> m_mShaders;

                // Methods
                public:
                    Loader();
                    Loader(Logger *pLogger);
                    Loader(std::string cVertex, std::string cFragment);

                    ~Loader();

                    void addShader(std::string cFilename, std::string cType);
    
                    unsigned int buildShader();
                    unsigned int getProgramID() const;

                protected:
                private:
                };
            };
        };
    };
};

#endif
