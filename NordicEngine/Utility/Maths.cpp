#include <NordicEngine/Utility/Maths.hpp>

namespace NordicArts {
    namespace NordicEngine {
        glm::quat rotationBetweenVectors(glm::vec3 vStart, glm::vec3 vDest) {
            vStart  = glm::normalize(vStart);
            vDest   = glm::normalize(vDest);

            float fCosTheta = glm::dot(vStart, vDest);
            glm::vec3 vRotationAxis;

            if (fCosTheta < -1 + 0.001f) {
                vRotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), vStart);
                if (glm::length2(vRotationAxis) < 0.01) {
                    vRotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), vStart);
                }
                vRotationAxis = glm::normalize(vRotationAxis);
                
                return glm::angleAxis(180.0f, vRotationAxis);
            }

            vRotationAxis = glm::cross(vStart, vDest);
        
            float fS    = glm::sqrt((1 + fCosTheta) * 2);
            float fInvs = (1 / fS);

            return glm::quat((fS * 0.5f), (vRotationAxis.x * fInvs), (vRotationAxis.y * fInvs), (vRotationAxis.z * fInvs));
        }

        glm::quat lookAt(glm::vec3 vDirection, glm::vec3 vDesiredUp) {
            if (glm::length2(vDirection) < 0.0001f) { return glm::quat(); }

            glm::vec3 vRight    = glm::cross(vDirection, vDesiredUp);
            vDesiredUp          = glm::cross(vRight, vDirection);

            glm::quat qRot1     = rotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), vDirection);
            glm::vec3 vNewUp    = (qRot1 * glm::vec3(0.0f, 1.0f, 0.0f));
            glm::quat qRot2     = rotationBetweenVectors(vNewUp, vDesiredUp);

            return (qRot2 * qRot1);
        }

        glm::quat rotateTowards(glm::quat q1, glm::quat q2, float fMaxAngle) {
            if (fMaxAngle < 0.001f) { return q1; }
            
            float fCosTheta = glm::dot(q1, q2);
            if (fCosTheta > 0.9999f) { return q2; }
            if (fCosTheta < 0) {
                q1          = (q1*-1.0f);
                fCosTheta  *= -1.0f;
            }

            float fAngle = glm::acos(fCosTheta);
            if (fAngle < fMaxAngle) { return q2; }

            float fT    = (fMaxAngle / fAngle);
            fAngle      = fMaxAngle;

            glm::quat qRes  = (((glm::sin((1.0f - fT) * fAngle) * q1) + (glm::sin(fT * fAngle) * q2)) / glm::sin(fAngle));
            qRes            = glm::normalize(qRes);

            return qRes;
        }

        int getRandom(int iMax) {
            return getRandom(0, iMax);
        }

        int getRandom(int iMin, int iMax) {
            iMax -= 1; // Make it less than max by 1, e.g. vector.size = 3, but you want 0-2 not 0-3
            int iTotal = (iMax - iMin + 1);
            int iLeft = (RAND_MAX % iResult);
            int iResult;
            do {
                iResult = std::rand();
            } while (iTotal > (RAND_MAX - iLeft));
            return ((iMin + iResult) % iTotal);
        }
    };
};
