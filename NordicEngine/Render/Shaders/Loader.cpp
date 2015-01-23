#include <NordicEngine/Render/Shaders/Loader.hpp>
#include <NordicEngine/Render/Shaders/Shader.hpp>
#include <NordicEngine/Render/Shaders/Program.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                Loader::Loader() : m_iProgramID(0) {
                }

                Loader::Loader(std::string cVertex, std::string cFragment) : m_iProgramID(0) {
                }

                unsigned int Loader::buildShader() {
                    if (checkRequiredShaders() < 2) { 
                        throwError(__FUNCTION__ + ", You need at least 2 shaders to build a program");

                        return 0;
                    }

                    Program oProgram;
                    for (std::vector<Shader>::iterator it = m_vShaders.begin(); it != m_vShaders.end(); it++) {
                        oProgram.attachShader(it->first.getID(), it->first.getType());
                    }
                    oProgram.link();
                    m_iProgramID = oProgram.getID();

                    return m_iProgramID;
                }

                unsigned int Loader::addShader(std::string cShader, ShaderType eType) {
                    Shader oShader;
                    oShader.create(cShader, eType);
                    
                    m_vShaders.push_back(oShader);
                    
                    return oShader.getID();
                }
            
                unsigned int Loader::getProgramID() const {
                    return m_iProgramID;
                }

                unsigned int Loader::checkRequiredShaders() const {
                    return m_vShaders.size();
                }

                void Loader::unloadShader(unsigned int iShaderID) {
                    glDeleteShader(iShaderID);
                }
            
                void Loader::unloadProgram(unsigned int iProgramID) {
                    glDeleteProgramID(iProgramID);
                }
            };
        };
    };
};
