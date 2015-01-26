#include <NordicEngine/Render/Shaders/Loader.hpp>
#include <NordicEngine/Render/Shaders/Program.hpp>
#include <NordicEngine/Render/Shaders/Shader.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                Loader::Loader() : m_iProgramID(0), m_pLogger(nullptr) {
                }

                Loader::Loader(std::string cVertex, std::string cFragment) : m_iProgramID(0), m_pLogger(nullptr) {
                    addShader(cFragment, "FRAGMENT");
                    addShader(cVertex, "VERTEX");
                }

                Loader::~Loader() {
                    m_pLogger   = nullptr;
                }

                void Loader::addShader(std::string cShader, std::string cType) {
                    m_vShaders.push_back(std::vector<std::string, std::string>(cShader, cType));
                }

                unsigned int Loader::buildShader() {
                    bool bVertex;
                    for (std::vector<std::string, std::string>::iterator it = m_vShaders.begin(); it != m_vShaders.end(); it++) {
                        std::string cType = toUpper(it->second);

                        if (cType == "VERTEX") {

                        }
                    }

                    Shader *pShader = m_pVertex;

                    Program oProgram;
                    oProgram.attachShader(m_pVertex);
                    oProgram.link();
                    return oProgram.getID();
                }
            
                unsigned int Loader::getProgramID() const {
                    return m_iProgramID;
                }
            };
        };
    };
};
