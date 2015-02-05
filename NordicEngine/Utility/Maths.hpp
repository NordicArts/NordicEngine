#ifndef NordicArts_NordicEngine_Utility_Maths_H
#define NordicArts_NordicEngine_Utility_Maths_H

#include <NordicEngine/Engine.hpp>

#include <NordicEngine/ThirdParty/glm/glm/gtc/quaternion.hpp>
#include <NordicEngine/ThirdParty/glm/glm/gtx/quaternion.hpp>
#include <NordicEngine/ThirdParty/glm/glm/gtx/euler_angles.hpp>
#include <NordicEngine/ThirdParty/glm/glm/gtx/norm.hpp>

namespace NordicArts {
    namespace NordicEngine {
        glm::quat rotationBetweenVectors(glm::vec3 vStart, glm::vec3 vDest);
        glm::quat lookAt(glm::vec3 vDirection, glm::vec3 vDesiredUp);
        glm::quat rotateTowards(glm::quat q1, glm::quat q2, float fMaxAngle);
    };
};

#endif
