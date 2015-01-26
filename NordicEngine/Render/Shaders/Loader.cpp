#include <NordicEngine/Render/Shaders/Loader.hpp>
#include <NordicEngine/Render/Shaders/Program.hpp>
#include <NordicEngine/Render/Shaders/Shader.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                ShaderType getShaderType(std::string cType) {
                    std::string cKey = cType;
                    cKey = toUpper(cKey);

                    if (cKey == "VERTEX") { return NES_VERTEX; }
                    if (cKey == "FRAGMENT") { return NES_FRAGMENT; }
                    if (cKey == "GEOMETRY") { return NES_GEOMETRY; }
            
                    return NES_UNKNOWN;
                }

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
                    m_mShaders.insert(std::pair<std::string, std::string>(cType, cShader));
                }

                unsigned int Loader::buildShader() {
                    bool bVertex;
                    bool bFragment;

                    std::string cKey;

                    Program oProgram;

                    for (std::map<std::string, std::string>::iterator it = m_mShaders.begin(); it != m_mShaders.end(); it++) {
                        ShaderType eType = getShaderType(it->first);

                        switch (eType) { 
                            case NES_VERTEX: {
                                Shader oShader(NES_VERTEX, it->second);
                                oProgram.attachShader(&oShader);
                                break;
                            }

                            case NES_FRAGMENT: {
                                Shader oShader(NES_FRAGMENT, it->second);
                                oProgram.attachShader(&oShader);
                                break;
                            }

                            case NES_GEOMETRY: {
                                Shader oShader(NES_GEOMETRY, it->second);
                                oProgram.attachShader(&oShader);
                                break;
                            }

                            case NES_COMPUTE:
                            case NES_TESS_CONTROL:
                            case NES_TESS_EVAL:
                            default:
                                break;
                        }
                    }

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
