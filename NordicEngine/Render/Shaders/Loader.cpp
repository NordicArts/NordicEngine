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
                    //m_pProgram  = nullptr;
                }

                void Loader::addShader(std::string cShader, std::string cType) {
                    m_mShaders.insert(std::pair<std::string, std::string>(cType, cShader));
                }

                void Loader::addFragmentData(int iColor, std::string cLocation) {
                    m_mData.insert(std::pair<int, std::string>(iColor, cLocation));
                }

                void Loader::buildFragmentData(Program *pProgram) {
                    for (std::map<int, std::string>::iterator it = m_mData.begin(); it != m_mData.end(); it++) {
                        pProgram->attachData(it->first, it->second);
                    }
                }

                void Loader::buildShaders(Program *pProgram) {
                    for (std::map<std::string, std::string>::iterator it = m_mShaders.begin(); it != m_mShaders.end(); it++) {
                        ShaderType eType = getShaderType(it->first);

                        switch (eType) {
                            case NES_VERTEX: {
                                Shader oShader(NES_VERTEX, it->second);
                                pProgram->attachShader(&oShader);
                                break;
                            }

                            case NES_FRAGMENT: {
                                Shader oShader(NES_FRAGMENT, it->second);
                                pProgram->attachShader(&oShader);
                                break;
                            }

                            case NES_GEOMETRY: {
                                Shader oShader(NES_GEOMETRY, it->second);
                                pProgram->attachShader(&oShader);
                                break;
                            }

                            case NES_COMPUTE:
                            case NES_TESS_CONTROL:
                            case NES_TESS_EVAL:
                            default:
                                break;
                        }
                    }
                }

                unsigned int Loader::buildShader() {
                    return build();
                }

                unsigned int Loader::build() {
                    Program  oProgram;
                    Program *pProgram = &oProgram;

                    m_iProgramID = pProgram->getID();

                    buildShaders(pProgram)
                    buildFragmentData(pProgram);
                    pProgram->link();

                    return m_iProgramID;
                }

                int Loader::getAttrib(int iProgramID, std::string cLocation) {
                    Program oProgram(iProgramID);
                    return oProgram.getAttributeID(cLocation);
                }

                int Loader::getUniform(int iProgramID, std::string cLocation) {
                    Program oProgram(iProgramID);
                    return oProgram.getUniformID(cLocation);
                }
            
                unsigned int Loader::getProgramID() const {
                    return m_iProgramID;
                }
            };
        };
    };
};
