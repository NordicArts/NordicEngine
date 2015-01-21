#include <NordicEngine/Camera/Camera.hpp>
#include <NordicEngine/Files/Format/Lua/Lua.hpp>

#include <NordicEngine/ThirdParty/glm/glm/gtc/matrix_transform.hpp>

namespace NordicArts {
    namespace NordicEngine {
        static const float fMaxVerticalAngle = 85.0f;

        Camera::Camera() : m_vPosition(0.0f, 0.0f, 1.0f), m_fHorizontalAngle(0.0f), m_fVerticalAngle(0.0f), m_fFieldOfView(50.0f), m_fNearPlane(0.01f), m_fFarPlane(100.0f), m_fViewPortAspectRatio(4.0f / 3.0f) {
        }

        const glm::vec3 &Camera::getPosition() const {
            return m_vPosition;
        }

        void Camera::setPosition(const glm::vec3 &vPosition) {
            m_vPosition = vPosition;
        }
        void Camera::setPositionVerbose(float fX, float fY, float fZ) {
            glm::vec3 vPosition;
            
            vPosition.x = fX;
            vPosition.y = fY;
            vPosition.z = fZ;
        
            return setPosition(vPosition);
        }

        void Camera::setOffsetPosition(const glm::vec3 &vOffset) {
            m_vPosition += vOffset;
        }
        void Camera::setOffsetPositionVerbose(float fX, float fY, float fZ) {
            glm::vec3 vOffset;

            vOffset.x = fX;
            vOffset.y = fY;
            vOffset.z = fZ;
    
            return setOffsetPosition(vOffset);
        }

        float Camera::getFieldOfView() const {
            return m_fFieldOfView;
        }

        void Camera::setFieldOfView(float fFieldOfView) {
            assert((fFieldOfView > 0.0f) && (fFieldOfView < 180.0f));

            m_fFieldOfView = fFieldOfView;
        }

        float Camera::getNearPlane() const {
            return m_fNearPlane;
        }
    
        float Camera::getFarPlane() const {
            return m_fFarPlane;
        }

        void Camera::setNearAndFarPlanes(float fNearPlane, float fFarPlane) {
            assert(fNearPlane > 0.0f);
            assert(fFarPlane > fNearPlane);

            m_fNearPlane    = fNearPlane;
            m_fFarPlane     = fFarPlane;
        }

        glm::mat4 Camera::getOrientation() const {
            glm::mat4 mOrientation;
            mOrientation = glm::rotate(mOrientation, glm::radians(m_fVerticalAngle), glm::vec3(1, 0, 0));
            mOrientation = glm::rotate(mOrientation, glm::radians(m_fHorizontalAngle), glm::vec3(0, 1, 0));

            return mOrientation;
        }

        void Camera::setOffsetOrientation(float fAngleUp, float fAngleRight) {
            m_fHorizontalAngle += fAngleRight;
            m_fVerticalAngle += fAngleUp;

            normalizeAngles();
        }

        void Camera::lookAt(glm::vec3 vPosition) {
            assert(vPosition != m_vPosition);

            glm::vec3 vDirection    = glm::normalize(vPosition - m_vPosition);
            
            m_fVerticalAngle        = glm::radians(asinf(-vDirection.y));
            m_fHorizontalAngle      = glm::radians(atan2f(-vDirection.x, vDirection.z));

            normalizeAngles();
        }
        void Camera::lookAtVerbose(float fX, float fY, float fZ) {
            glm::vec3 vPosition;

            vPosition.x = fX;
            vPosition.y = fY;
            vPosition.z = fZ;
    
            return lookAt(vPosition);
        }

        float Camera::getViewPortAspectRatio() const {
            return m_fViewPortAspectRatio;
        }

        void Camera::setViewPortAspectRatio(float fViewPortAspectRatio) {
            assert(fViewPortAspectRatio > 0.0);

            m_fViewPortAspectRatio = fViewPortAspectRatio;
        }

        glm::vec3 Camera::getForward() const {
            glm::vec4 vForward = (glm::inverse(getOrientation()) * glm::vec4(0, 0, -1, 1));

            return glm::vec3(vForward);
        }

        glm::vec3 Camera::getRight() const {
            glm::vec4 vRight = (glm::inverse(getOrientation()) * glm::vec4(1, 0, 0, 1));
        
            return glm::vec3(vRight);
        }

        glm::vec3 Camera::getUp() const {
            glm::vec4 vUp = (glm::inverse(getOrientation()) * glm::vec4(0, 1, 0, 1));
        
            return glm::vec3(vUp);
        }

        glm::mat4 Camera::getMatrix() const {
            return (getProjection() * getView());
        }

        glm::mat4 Camera::getProjection() const {
            return glm::perspective(glm::radians(m_fFieldOfView), m_fViewPortAspectRatio, m_fNearPlane, m_fFarPlane);
        }

        glm::mat4 Camera::getView() const {
            return (getOrientation() * glm::translate(glm::mat4(), -m_vPosition));
        }

        void Camera::normalizeAngles() {
            m_fHorizontalAngle = fmodf(m_fHorizontalAngle, 360.0f);
        
            if (m_fHorizontalAngle < 0.0f) {
                m_fHorizontalAngle += 360.0f;
            }

            if (m_fVerticalAngle > fMaxVerticalAngle) {
                m_fVerticalAngle = fMaxVerticalAngle;
            } else if (m_fVerticalAngle < -fMaxVerticalAngle) {
                m_fVerticalAngle = -fMaxVerticalAngle;
            }
        }

        void Camera::registerLua(Files::Lua *pLua) {
            lua_State *pState = pLua->getLua();

            luabridge::getGlobalNamespace(pState)
                .beginNamespace("NordicArts")
                    .beginClass<Camera>("Camera")
                        .addConstructor<void (*)(void)>()
                        .addFunction("setFieldOfView", &Camera::setFieldOfView)
                        .addFunction("setPosition", &Camera::setPositionVerbose)
                        .addFunction("setOffsetPosition", &Camera::setOffsetPositionVerbose)
                        .addFunction("setOffsetOrientation", &Camera::setOffsetOrientation)
                        .addFunction("setAspectRatio", &Camera::setViewPortAspectRatio)
                        .addFunction("lookAt", &Camera::lookAtVerbose)
                        .addFunction("setPlanes", &Camera::setNearAndFarPlanes)
                    .endClass()
                .endNamespace();
        }
    };
};
