#include <NordicEngine/Renderer/Renderer.hpp>

#include <GL/glew.h>
#include <NordicEngine/glfw/include/GLFW/glfw3.h>

namespace NordicArts {
    namespace NordicEngine {
        Renderer::Renderer(Window *pWindow) : m_pWindow(pWindow) {
        }
        Renderer::Renderer(Logger *pLogger, Window *pWindow) : m_pLogger(pLogger), m_pWindow(pWindow) {
        }

        Renderer::~Renderer() {
            m_pLogger   = nullptr;
            m_pWindow   = nullptr;
            m_pProgram  = nullptr;
        }

        // New
        void Renderer::loadProgram(Shaders::Program *pProgram) {
            m_pProgram = pProgram;
        }
        
        void Renderer::clear(Color oColor) {
            glClearColor(oColor.m_iRed, oColor.m_iGreen, oColor.m_iBlue, oColor.m_iAlpha);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void Renderer::useProgram() {
            if (m_pProgram) {
                glUseProgram(m_pProgram->getObject());
            } else {
                throw Exceptions("No program loaded");
            }
        }
        void Renderer::clearProgram() {
            glUseProgram(0);
        }

        void Renderer::bindVertex(unsigned int iVAO) {
            glBindVertexArray(iVAO);
        }
    
        void Renderer::drawTriangle() {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        

        // Old
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

        void Renderer::setColor(Color oColor) {
            glColor3i(oColor.m_iRed, oColor.m_iGreen, oColor.m_iBlue);
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
