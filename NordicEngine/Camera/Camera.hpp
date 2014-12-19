#ifndef NordicArts_NordicEngine_Camera_H
#define NordicArts_NordicEngine_Camera_H

#include <NordicEngine/Engine.hpp>

#include <NordicEngine/glm/glm/glm.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Camera {
        // Variables
        public:
        protected:
        private:
            glm::vec3 m_vPosition;

            float m_fHorizontalAngle;
            float m_fVertialAngle;
            float m_fFieldOfView;
            float m_fNearPlane;
            float m_fFarPlane;
            float m_fViewPortAspectRatio;

        // Methods
        public:
        protected:
        private:
            void normalizeAngles();

        };
    };
};

#endif
