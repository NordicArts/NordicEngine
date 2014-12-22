#include <NordicEngine/Model/Model.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Model::Model() {

        }

        Model::~Model() {
            m_vModels.clear();
        }

        float Model::loadModelFromFile(const std::string &cFile) {
            float fReturn;

            return fReturn;
        }

        ModelAsset Model::addModel(Shaders::Program *pShaders, Texture *pTexture, int iDrawStart, int iDrawCount, float fShininess, glm::vec3 vSpecular, float fModelData) {
            ModelAsset oAsset;
            oAsset.pShaders         = pShaders;
            oAsset.pTexture         = pTexture;
            oAsset.iDrawCount       = iDrawCount;
            oAsset.iDrawStart       = iDrawStart;
            oAsset.fShininess       = fShininess;
            oAsset.vSpecularColor   = vSpecular;
            oAsset.fModelData       = fModelData;
            oAsset.iDrawType        = GL_TRIANGLES;

            m_vModels.push_back(oAsset);

            return oAsset;
        }

        std::vector<ModelAsset> Model::getModels() const {
            return m_vModels;
        }
    };
};