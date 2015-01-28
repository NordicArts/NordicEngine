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
                    Program oProgram;
                    m_pProgram      = &oProgram;
                    m_iProgramID    = m_pProgram->getID();

                    printIt("Blank Constructor");
                    printIt(m_pProgram->getID());
                }

                Loader::Loader(std::string cVertex, std::string cFragment) : m_iProgramID(0), m_pLogger(nullptr) {
                    Program oProgram;
                    m_pProgram      = &oProgram;
                    m_iProgramID    = m_pProgram->getID();

                    printIt("Value Constructor");
                    printIt(m_pProgram->getID());

                    addShader(cFragment, "FRAGMENT");
                    addShader(cVertex, "VERTEX");

                    printIt("End Constructor");
                    printIt(m_pProgram->getID());
                }

                Loader::~Loader() {
                    m_pLogger   = nullptr;
                    //m_pProgram  = nullptr;
                }

                void Loader::addShader(std::string cShader, std::string cType) {
                    printIt("Adding Shader");
                    printIt(m_pProgram->getID());

                    m_mShaders.insert(std::pair<std::string, std::string>(cType, cShader));

                    printIt("Added Shader");
                    printIt(m_pProgram->getID());
                }

                void Loader::attachFragmentData(int iColor, std::string cLocation) {
                    m_mData.insert(std::pair<int, std::string>(iColor, cLocation));
                }

                void Loader::buildFragmentData() {
                    printIt("Building Fragment");
                    printIt(m_pProgram->getID());

                    for (std::map<int, std::string>::iterator it = m_mData.begin(); it != m_mData.end(); it++) {
                        m_pProgram->attachData(it->first, it->second);
                    }

                    printIt("Built Fragment");
                    printIt(m_pProgram->getID());
                }

                unsigned int Loader::buildShader() {
                    bool bVertex;
                    bool bFragment;

                    std::string cKey;
                    printIt("Building Shader");
                    printIt(m_pProgram->getID());

                    for (std::map<std::string, std::string>::iterator it = m_mShaders.begin(); it != m_mShaders.end(); it++) {
                        ShaderType eType = getShaderType(it->first);

                        switch (eType) { 
                            case NES_VERTEX: {
                                Shader oShader(NES_VERTEX, it->second);
                                m_pProgram->attachShader(&oShader);
                                break;
                            }

                            case NES_FRAGMENT: {
                                Shader oShader(NES_FRAGMENT, it->second);
                                m_pProgram->attachShader(&oShader);
                                break;
                            }

                            case NES_GEOMETRY: {
                                Shader oShader(NES_GEOMETRY, it->second);
                                m_pProgram->attachShader(&oShader);
                                break;
                            }

                            case NES_COMPUTE:
                            case NES_TESS_CONTROL:
                            case NES_TESS_EVAL:
                            default:
                                break;
                        }
                    }

                    buildFragmentData();
                    m_pProgram->link();

                    printIt("Built Shader");
                    printIt(m_pProgram->getID());

                    return m_pProgram->getID();
                }

                int Loader::getAttrib(std::string cLocation) {
                    return m_pProgram->getAttributeID(cLocation);
                }

                int Loader::getUniform(std::string cLocation) {
                    return m_pProgram->getUniformID(cLocation);
                }
            
                unsigned int Loader::getProgramID() const {
                    return m_iProgramID;
                }
            };
        };
    };
};
