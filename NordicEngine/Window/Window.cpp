#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace WindowMaker {
            Window::Window() {
            }
            Window::Window(Logger *pLogger, Settings *pSettings) : m_pLogger(pLogger), m_pSettings(pSettings) {
            }

            Window::~Window() {
                destroy();
            }

            void Window::errorHandler(int iError, const char *cError) {
                throw Exception(cError, iError, true);
            }

            int Window::initalize(int iWidth, int iHeight, std::string cTitle, bool bFullScreen) {
                // Set the error handler
                glfwSetErrorCallback(Window::errorHandler);

                // Initalize GLFW ready to send stuff
                if (!glfwInit()) {
                    throwError(__FUNCTION__, "Failed to initalize GLFW");
                }

                // Get the settings
                if (!m_pSettings) {
                    if (m_pLogger) {
                        Settings oSettings(m_pLogger, cTitle);
                        m_pSettings = &oSettings;
                        m_pSettings->setup();
                    } else {
                        Settings oSettings(cTitle);
                        m_pSettings = &oSettings;
                        m_pSettings->setup();
                    }
                }

                // Hints
                glfwWindowHint(GLFW_SAMPLES, m_pSettings->getFSAA());
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_pSettings->getOpenGLMajor());
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_pSettings->getOpenGLMinor());

                // Setting full screen
                if (bFullScreen) {
                    m_pSettings->setWindowMode(false);
                    m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
                } else {
                    m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), nullptr, nullptr);
                }

                // failed to launch window
                if (m_pWindow == nullptr) {
                    throwError(__FUNCTION__, std::string("Failed to launch window, your system doesnt support OpenGL ") + getString(m_pSettings->getOpenGLMajor()));
                    destroy();
                }

                // Make Context
                glfwMakeContextCurrent(m_pWindow);

                // Set the input mode
                glfwSetInputMode(m_pWindow, GLFW_STICKY_KEYS, GL_TRUE);

                // Setting vSync
                if (m_pSettings->getVSync()) {
                    glfwSwapInterval(60);
                } else {
                    glfwSwapInterval(0);
                }

                // Starting GLEW
                glewExperimental = GL_TRUE;
                GLenum eError = glewInit();
                if (GLEW_OK != eError) {
                    throwError(__FUNCTION__, "Failed to initalize GLEW");
                }

                return 0;
            }

            void Window::setCursorLocation(int iX, int iY) {
                glfwSetCursorPos(m_pWindow, iX, iY);
            }

            bool Window::processInput(bool bContinue = true) {
                if ((glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) || (glfwWindowShouldClose(m_pWindow) != 0)) {
                    return false;
                }

                glfwPollEvents();

                return bContinue;
            }

            void Window::swapBuffers() {
                glfwSwapBuffers(m_pWindow);
            }

            void Window::destroy() {
                glfwTerminate();
            }

            void Window::setCursorDisabled() {
                glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }
        };
    };
};
