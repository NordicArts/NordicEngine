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
                class Program;

                class Loader {
                // Variables
                public:
                protected:
                private:
                    Logger *m_pLogger;

                    std::map<std::string, std::string> m_mShaders;
                    std::map<int, std::string> m_mData;

                // Methods
                public:
                    Loader();
                    Loader(Logger *pLogger);
                    Loader(std::string cVertex, std::string cFragment);

                    ~Loader();

                    void addShader(std::string cFilename, std::string cType);
                    void addFragmentData(int iColor, std::string cLocation);
    
                    unsigned int buildShader();

                    int getAttrib(int iProgramID, std::string cLocation);
                    int getUniform(int iProgramID, std::string cLocation);

                protected:
                private:
                    void buildFragmentData(Program *pProgram);
                    void buildShaders(Program *pProgram);

                    unsigned int build();
                };
            };
        };
    };
};

#endif
