#ifndef NordicArts_NordicEngine_Light_H
#define NordicArts_NordicEngine_Light_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Color/Color.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>

namespace NordicArts {
    namespace NordicEngine {
        struct LightStruct {
            glm::vec4 vPosition;

            glm::vec3 vColor;
            glm::vec3 vDirection;

            float fAttenuation;
            float fAmbientCoEfficient;
            float fConeAngle;
        };

        class Light {
        // Variables
        public:
        protected:
        private:
            std::vector<LightStruct> m_vLights;

        // Methods
        public:
            Light();

            ~Light();

            LightStruct createLight(glm::vec4 vPosition, glm::vec3 vColor, glm::vec3 vDirection, float fAttenuation, float fAmbientCoEfficient, float fConeAngle);
            LightStruct createSpotLight(glm::vec4 vPosition, glm::vec3 vColor, glm::vec3 vDirection, float fAttenuation, float fAmbientCoEfficient, float fConeAngle);
            LightStruct createDirectional(glm::vec4 vPosition, glm::vec3 vColor, float fAmbientCoEfficient);

            std::vector<LightStruct> getLights() const;

        protected:
        private:

        };
    };
};

#endif
