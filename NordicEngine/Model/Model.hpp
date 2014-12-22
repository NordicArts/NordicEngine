#ifndef NordicArts_NordicEngine_Model_H
#define NordicArts_NordicEngine_Model_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Shaders/Program.hpp>
#include <NordicEngine/Files/Texture/Texture.hpp>

#include <NordicEngine/glm/glm/glm.hpp>

namespace NordicArts {
    namespace NordicEngine {
        struct ModelAsset {
            Shaders::Program *pShaders;
            Texture *pTexture;

            unsigned int iVBO;
            unsigned int iVAO;
            unsigned int iDrawType;

            int iDrawStart;
            int iDrawCount;

            float fShininess;
            float fModelData;

            glm::vec3 vSpecularColor;

            ModelAsset() : pShaders(nullptr), pTexture(nullptr), iVBO(0), iVAO(0), iDrawType(GL_TRIANGLES), iDrawStart(0), iDrawCount(0), fShininess(0.0f), vSpecularColor(1.0f, 1.0f, 1.0f), fModelData(0.0f) { }
        };

        struct ModelInstance {
            ModelAsset *sAsset;

            glm::mat4 mTransform;

            ModelInstance() : sAsset(nullptr), mTransform() {}
        };

        class Model {
        // Variables
        public:
        protected:
        private:
            std::vector<ModelAsset> m_vModels;

        // Methods
        public:
            Model();

            ~Model();

            float loadModelFromFile(const std::string &cFilePath);

            std::vector<ModelAsset> getModels() const;

            ModelAsset addModel(Shaders::Program *pShaders, Texture *pTexture, int iDrawStart, int iDrawCount, float fShininess, glm::vec3 vSpecular, float fModelData);

        protected:
        private:

        };
    };
};

#endif