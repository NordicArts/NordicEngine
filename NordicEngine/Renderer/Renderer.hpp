#ifndef NordicArts_NordicEngine_Renderer_H
#define NordicArts_NordicEngine_Renderer_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Window/Window.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Renderer {
        // Variables
        public:
        protected:
        private:
            Logger *m_pLogger;
            Window *m_pWindow;

        // Methods
        public:
            Renderer(Window *pWindow);
            Renderer(Logger *pLogger, Window *pWindow);

            ~Renderer();

            void setViewPort();
            void setViewPort(int iX, int iY);
            void setViewPort(int iX, int iY, int iWidth, int iHeight);

            void loadIdentity();
            void clear();
            void setProjectionMode();
            void setModelMode();
            void view2d(float fLeft, float fRight, float fBottom, float fTop, float fNear, float fFar);
            void rotate(float fAngle, float fX, float fY, float fZ);
            void beginTriangles();
            void end();
            void setColor(float fRed, float fBlue, float fGreen);
            void setVertex(float fX, float fY, float fZ);
            
        protected:
        private:

        };
    };
};

#endif
