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
                    unsigned int m_iProgramID;

                    Logger *m_pLogger;

                    Program *m_pProgram;

                    std::map<std::string, std::string> m_mShaders;
                    std::map<int, std::string> m_mData;

                // Methods
                public:
                    Loader();
                    Loader(Logger *pLogger);
                    Loader(std::string cVertex, std::string cFragment);

                    ~Loader();

                    void addShader(std::string cFilename, std::string cType);
                    void attachFragmentData(int iColor, std::string cLocation);
    
                    unsigned int buildShader();
                    unsigned int getProgramID() const;

                    int getAttrib(std::string cLocation);
                    int getUniform(std::string cLocation);

                protected:
                private:
                    void buildFragmentData();

                };
            };
        };
    };
};

#endif
