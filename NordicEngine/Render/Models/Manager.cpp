#include <NordicEngine/Render/Models/Manager.hpp>
#include <NordicEngine/Files/Format/Obj/Obj.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Models {
                Manager::Manager() : m_pLogger(nullptr), m_iModels(0) {
                }
                Manager::Manager(Logger *pLogger) : m_pLogger(pLogger), m_iModels(0) {
                }

                void Manager::destroy() {
                    for (size_t i = 0; i < m_iModels; i++) {
                        m_pModels[i]->destroy();
                    }
                }

                Model *Manager::addModel(std::string cName, std::string cFile, std::string cVertex, std::string cFragment) {
                    // Load the OBJ file
                    Files::Obj oObj(cFile);
                    
                    std::vector<glm::vec3> vVerticies;
                    std::vector<glm::vec3> vNormals;
                    std::vector<glm::vec2> vUVs;

                    oObj.loadModel(vVerticies, vUVs, vNormals);

                    Model *pModel = new Model(cName);
                    pModel->setup(vVerticies, vUVs, vNormals, cVertex, cFragment);

                    m_pModels[m_iModels] = pModel;

                    m_iModels++;

                    return pModel;
                }

                Model *Manager::getModel(std::string cName) {
                    for (size_t i = 0; i < m_iModels; i++) {
                        if (cName.compare(m_pModels[i]->getName()) == 0) {
                            return m_pModels[i];
                        }
                    }

                    return nullptr;
                }
            };
        };
    };
};
