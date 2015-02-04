#include <NordicEngine/Render/Models/Manager.hpp>
#include <NordicEngine/Files/Format/Obj/Obj.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Models {
                Manager::Manager() : m_pLogger(nullptr) {
                }
                Manager::Manager(Logger *pLogger) : m_pLogger(pLogger) {
                }

                void Manager::destroy() {
                    if (m_pLogger) { m_pLogger->log("Destroying Models"); }

                    for (std::map<std::string, Model>::iterator it = m_mModels.begin(); it != m_mModels.end(); it++) {
                        it->second.destroy();
                    }

                    m_mModels.empty();

                    if (m_pLogger) { m_pLogger->log("Destroyed Models"); }
                }

                Model Manager::addModel(std::string cName, std::string cFile, std::string cVertex, std::string cFragment) {
                    // Load the OBJ file
                    Files::Obj oObj(cFile);

                    if (m_pLogger) {
                        m_pLogger->log("Starting Model");
                        m_pLogger->log(std::string("Vertex: ") + cVertex);
                        m_pLogger->log(std::string("Fragment: ") + cFragment);
                        m_pLogger->log(std::string("Model File: ") + cFile);
                    }
                    
                    std::vector<glm::vec3> vVerticies;
                    std::vector<glm::vec3> vNormals;
                    std::vector<glm::vec2> vUVs;

                    oObj.loadModel(vVerticies, vUVs, vNormals);

                    Model oModel;
                    oModel.initalize(vVerticies, vVerticies.size(), cVertex, cFragment);

                    m_mModels.insert(std::pair<std::string, Model>(cName, oModel));

                    if (m_pLogger) { m_pLogger->log("Started Model"); }

                    return oModel;
                }

                Model Manager::getModel(std::string cName) {
                    return m_mModels[cName];
                }
            };
        };
    };
};
