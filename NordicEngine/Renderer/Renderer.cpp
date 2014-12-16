#include <NordicEngine/Renderer/Renderer.hpp>

#include <NordicEngine/glfw/include/GLFW/glfw3.h>

namespace NordicArts {
    namespace NordicEngine {
        Renderer::Renderer(Window *pWindow) : m_pWindow(pWindow) {
        }
        Renderer::Renderer(Logger *pLogger, Window *pWindow) : m_pLogger(pLogger), m_pWindow(pWindow) {
        }

        Renderer::~Renderer() {
            m_pLogger = nullptr;
            m_pWindow = nullptr;
        }

        void Renderer::setViewPort() {
            setViewPort(0, 0, m_pWindow->m_iWidth, m_pWindow->m_iHeight);
        }
        void Renderer::setViewPort(int iX, int iY) {
            setViewPort(iX, iY, m_pWindow->m_iWidth, m_pWindow->m_iHeight);
        }
        void Renderer::setViewPort(int iX, int iY, int iWidth, int iHeight) {
            glViewport(iX, iY, iWidth, iHeight);
        }

        void Renderer::clear() {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void Renderer::setProjectionMode() {
            glMatrixMode(GL_PROJECTION);
        }
        void Renderer::setModelMode() {
            glMatrixMode(GL_MODELVIEW);
        }

        void Renderer::view2d(float fLeft, float fRight, float fBottom, float fTop, float fNear, float fFar) {
            glOrtho(fLeft, fRight, fBottom, fTop, fNear, fFar);
        }

        void Renderer::loadIdentity() {
            glLoadIdentity();
        }

        void Renderer::rotate(float fAngle, float fX, float fY, float fZ) {
            glRotatef(fAngle, fX, fY, fZ);
        }

        void Renderer::setColor(float fRed, float fBlue, float fGreen) {
            glColor3f(fRed, fBlue, fGreen);
        }

        void Renderer::setVertex(float fX, float fY, float fZ) {
            glVertex3f(fX, fY, fZ);
        }

        void Renderer::beginTriangles() {
            glBegin(GL_TRIANGLES);
        }

        void Renderer::end() {
            glEnd();
        }
    };
};
