#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Input/Input.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Window::Window() {
            initWindow();
        }
        Window::Window(Logger *pLogger) : m_pLogger(pLogger), m_pSettings(nullptr) {
            initWindow();
        }
        Window::Window(Logger *pLogger, Settings *pSettings) : m_pLogger(pLogger), m_pSettings(pSettings) {
            initWindow();
        }

        void Window::initWindow() {
            glfwSetErrorCallback(Window::errorHandler);

            // GLFW
            if (!glfwInit()) {
                throw Exceptions("Can't initalize GLFW", true);
            }
        }

        Window::~Window() {
            glfwDestroyWindow(m_pWindow);
            glfwTerminate();

            m_pWindow   = nullptr;
            m_pLogger   = nullptr;
            m_pSettings = nullptr;
        }

        int Window::createWindow() {
            if (m_pSettings) {
                glm::uvec2 vResolution  = m_pSettings->getResolution();
                glm::uvec2 vOpenGL      = m_pSettings->getOpenGL();

                std::string cTitle      = m_pSettings->getGameName();

                int iFSAA               = m_pSettings->getFSAA();

                glfwWindowHint(GLFW_SAMPLES, iFSAA);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, vOpenGL.x);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, vOpenGL.y);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                m_pWindow = glfwCreateWindow(vResolution.x, vResolution.y, cTitle.c_str(), NULL, NULL);
                if (!m_pWindow) {
                    glfwTerminate();
            
                    throw Exceptions("Can't create the window", true);
                }

                glfwMakeContextCurrent(m_pWindow);

                // GLEW
                glewExperimental = true;
                GLenum glewStatus = glewInit();
                if (glewStatus != GLEW_OK) {
                    throw Exceptions(glewGetErrorString(glewStatus), true);
                }

                return 0;
            } else {
                throw Exceptions("Settings Class not in use", true);
            }
        }
        int Window::createWindow(int iWidth, int iHeight, std::string cTitle) {
            m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), NULL, NULL);
            if (!m_pWindow) {
                glfwTerminate();
        
                throw Exceptions("Can't create the window", true);
            }

            glfwMakeContextCurrent(m_pWindow);
            glfwSetKeyCallback(m_pWindow, Input::handleInput);

            // GLEW
            glewExperimental = GL_TRUE;
            GLenum glewStatus = glewInit();
            if (glewStatus != GLEW_OK) {
                throw Exceptions(glewGetErrorString(glewStatus), true);
            }

            return 0;
        }

        void Window::setOpenGL() {
            setOpenGL(3, 2);
        }
        void Window::setOpenGL(int iMajor, int iMinor) {
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, iMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, iMinor);
            glfwWindowHint(GLFW_RESIZABLE, false);
        }

        void Window::setVSync(bool bEnable) {
            if (bEnable) {
                glfwSwapInterval(1);
            }
        }

        bool Window::isWindowOpen() const {
            return !glfwWindowShouldClose(m_pWindow);
        }

        void Window::draw() {
            return display();
        }
        void Window::display() {
            // Do Movements before redraw
            glfwPollEvents();

            // Redraw
            glfwSwapBuffers(m_pWindow);
        }

        void Window::errorHandler(int iError, const char *cDescription) {
            throw Exceptions(cDescription, iError, true);
        }

        void Window::getFrameBufferSize(int *iWidth, int *iHeight) {
            m_iWidth    = *iWidth;
            m_iHeight   = *iHeight;

            glfwGetFramebufferSize(m_pWindow, iWidth, iHeight);
        }
        
        void Window::closeWindow() {
            glfwSetWindowShouldClose(m_pWindow, true);
        }
    }; 
};
