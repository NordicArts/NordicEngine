#ifndef NordicArts_NordicEngine_Camera_H
#define NordicArts_NordicEngine_Camera_H

#include <NordicEngine/Engine.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class Lua;
        };

        class Camera {
        // Variables
        public:
        protected:
        private:
            glm::vec3 m_vPosition;

            float m_fHorizontalAngle;
            float m_fVerticalAngle;
            float m_fFieldOfView;
            float m_fNearPlane;
            float m_fFarPlane;
            float m_fViewPortAspectRatio;

        // Methods
        public:
            Camera();
        
            // Camera Positions
            const glm::vec3 &getPosition() const;
            
            void setPosition(const glm::vec3 &vPosition);
            void setPositionVerbose(float fX, float fY, float fZ);
            void setOffsetPosition(const glm::vec3 &vOffset);
            void setOffsetPositionVerbose(float fX, float fY, float fZ);

            // Field of view
            float getFieldOfView() const;
            
            void setFieldOfView(float fFieldOfView);

            // Planes
            float getNearPlane() const;
            float getFarPlane() const;
    
            void setNearAndFarPlanes(float fNearPlane, float fFarPlane);
            
            // Orientation
            glm::mat4 getOrientation() const;

            void setOffsetOrientation(float fAngleUp, float fAngleRight);

            void lookAt(glm::vec3 vPosition);
            void lookAtVerbose(float fX, float fY, float fZ);

            // View Port
            float getViewPortAspectRatio() const;

            void setViewPortAspectRatio(float fViewPortAspectRatio);

            // Direction of camera
            glm::vec3 getForward() const;
            glm::vec3 getRight() const;
            glm::vec3 getUp() const;

            glm::mat4 getMatrix() const;
            glm::mat4 getProjection() const;
            glm::mat4 getView() const;

            // Lua integration
            static void registerLua(Files::Lua *pLua);

        protected:
        private:
            void normalizeAngles();

        };
    };
};

#endif
