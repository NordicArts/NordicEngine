#include <NordicEngine/Render/Models/Manager.hpp>
#include <NordicEngine/Files/Format/Obj/Obj.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Models {
                Manager::Manager() {
                }

                Manager::~Manager() {
                    destroy();
                }

                void Manager::destroy() {
                    for (std::map<std::string, Model>::iterator it = m_mModels.begin(); it != m_mModels.end(); it++) {
                        it->second.destroy();
                    }

                    m_mModels.empty();
                }

                Model Manager::addModel(std::string cName, std::string cFile, std::string cVertex, std::string cFragment) {
                    // Load the OBJ file
                    Files::Obj oObj(cFile);
                    
                    std::vector<glm::vec3> vVerticies;
                    std::vector<glm::vec3> vNormals;
                    std::vector<glm::vec2> vUVs;

                    oObj.loadModel(vVerticies, vUVs, vNormals);

                    Model oModel;
                    oModel.initalize(vVerticies, vVerticies.size(), cVertex, cFragment);

                    m_mModels.insert(std::pair<std::string, Model>(cName, oModel));

                    return oModel;
                }

                Model Manager::getModel(std::string cName) {
                    return m_mModels[cName];
                }
            };
        };
    };
};
