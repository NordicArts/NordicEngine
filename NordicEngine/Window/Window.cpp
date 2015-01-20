#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Input/Input.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Logger/Logger.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Window::Window() {
        }
        Window::Window(Logger *pLogger) : m_pLogger(pLogger), m_pSettings(nullptr) {
        }
        Window::Window(Logger *pLogger, Settings *pSettings) : m_pLogger(pLogger), m_pSettings(pSettings) {
        }

        void Window::setup() {
            if (m_pLogger) { m_pLogger->log("Setting up Window"); }

            glfwSetErrorCallback(Window::errorHandler);

            // GLFW
            if (!glfwInit()) {
                throw Exceptions("Can't initalize GLFW", true);
            }

            if (m_pLogger) { m_pLogger->log("Setup Window"); }
        }

        Window::~Window() {
            if (m_pWindow) {
                glfwDestroyWindow(m_pWindow);
                glfwTerminate();
            }

            m_pWindow   = nullptr;
            m_pLogger   = nullptr;
            m_pSettings = nullptr;
        }

        void Window::setCallback() {
            if (m_pWindow) {
                if (m_pLogger) { m_pLogger->log("Setting Inputs to NA::Input from GLFW"); }
                
                glfwSetInputMode(m_pWindow, GLFW_STICKY_KEYS, GL_TRUE);
                glfwSetKeyCallback(m_pWindow, Input::handleInput);
                
                if (m_pLogger) { m_pLogger->log("Set Inputs to NA::Input from GLFW"); }
            }
        }

        void Window::doGLEW() {
            if (m_pWindow) {
                if (m_pLogger) { m_pLogger->log("Initalizing GLEW"); }
                
                glewExperimental = true;
                GLenum glewStatus = glewInit();
                if (glewStatus != GLEW_OK) {
                    throw Exceptions(glewGetErrorString(glewStatus), true);
                }

                if (m_pLogger) { m_pLogger->log("Initalized GLEW"); }
            }
        }

        void Window::makeContext() {
            if (m_pWindow) {
                if (m_pLogger) { m_pLogger->log("Making Context with GLFW"); }
                
                glfwMakeContextCurrent(m_pWindow);

                setCallback();
                doGLEW();
                
                if (m_pLogger) { m_pLogger->log("Made Context with GLFW"); }
            }
        }

        int Window::createWindow() {
            if (m_pSettings) {
                if (m_pLogger) { m_pLogger->log("Creating Window using NA::Settings"); }

                glm::uvec2 vResolution  = m_pSettings->getResolution();
                glm::uvec2 vOpenGL      = m_pSettings->getOpenGL();

                std::string cTitle      = m_pSettings->getGameName();

                int iFSAA               = m_pSettings->getFSAA();
                setFSAA(iFSAA);

                setOpenGL(vOpenGL.x, vOpenGL.y);
                createWindow(vResolution.x, vResolution.y, cTitle);

                if (m_pLogger) { m_pLogger->log("Created Window using NA::Settings"); }

                return 0;
            } else {
                throw Exceptions("Settings Class not in use", true);
            }
        }
        int Window::createWindow(int iWidth, int iHeight, std::string cTitle) {
            if (m_pLogger) { m_pLogger->log("Creating Window"); }

            if (m_pLogger) { m_pLogger->log("Creating Window with GLFW"); }

            m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), NULL, NULL);
            if (!m_pWindow) {
                glfwTerminate();
        
                throw Exceptions("Can't create the window", true);
            }

            if (m_pLogger) { m_pLogger->log("Created Window with GLFW"); }

            if (m_pLogger) { m_pLogger->log("Created Window"); }
            return 0;
        }

        void Window::setFSAA() {
            setFSAA(0);
        }
        void Window::setFSAA(int iFSAA) {
            glfwWindowHint(GLFW_SAMPLES, iFSAA);
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
            if (m_pWindow) {
                return !glfwWindowShouldClose(m_pWindow);
            }

            return false;
        }

        void Window::draw() {
            return display();
        }
        void Window::display() {
            if (m_pWindow) {
                // Do Movements before redraw
                glfwPollEvents();

                // Redraw
                glfwSwapBuffers(m_pWindow);
            }
        }

        void Window::errorHandler(int iError, const char *cDescription) {
            throw Exceptions(cDescription, iError, true);
        }

        void Window::getFrameBufferSize(int *iWidth, int *iHeight) {
            m_iWidth    = *iWidth;
            m_iHeight   = *iHeight;

            if (m_pWindow) {
                glfwGetFramebufferSize(m_pWindow, iWidth, iHeight);
            }
        }
        
        void Window::closeWindow() {
            if (m_pWindow) {
                glfwSetWindowShouldClose(m_pWindow, true);
            }
        }
    }; 
};
