#include <NordicEngine/Light/Light.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Light::Light() {

        }

        Light::~Light() {
            m_vLights.clear();
        }


        LightStruct Light::createLight(glm::vec4 vPosition, glm::vec3 vColor, glm::vec3 vDirection, float fAttenuation, float fAmbientCoEfficient, float fConeAngle) {
            LightStruct oLight;

            oLight.vPosition            = vPosition;
            oLight.vColor               = vColor;
            oLight.vDirection           = vDirection;
            oLight.fAttenuation         = fAttenuation;
            oLight.fAmbientCoEfficient  = fAmbientCoEfficient;
            oLight.fConeAngle           = fConeAngle;

            m_vLights.push_back(oLight);

            return oLight;
        }
        LightStruct Light::createSpotLight(glm::vec4 vPosition, glm::vec3 vColor, glm::vec3 vDirection, float fAttenuation, float fAmbientCoEfficient, float fConeAngle) {
            return createLight(vPosition, vColor, vDirection, fAttenuation, fAmbientCoEfficient, fConeAngle);
        }
        LightStruct Light::createDirectional(glm::vec4 vPosition, glm::vec3 vColor, float fAmbientCoEfficient) {
            LightStruct oLight;

            oLight.vPosition            = vPosition;
            oLight.vColor               = vColor;
            oLight.fAmbientCoEfficient  = fAmbientCoEfficient;

            m_vLights.push_back(oLight);

            return oLight;
        }

        std::vector<LightStruct> Light::getLights() const {
            return m_vLights;
        }
    };
};