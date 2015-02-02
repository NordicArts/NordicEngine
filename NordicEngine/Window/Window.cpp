#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace WindowMaker {
            Window::Window() {
            }
            Window::Window(Logger *pLogger) : m_pLogger(pLogger) {
            }

            Window::~Window() {
                destroy();
            }

            void Window::errorHandler(int iError, const char *cError) {
                throw Exception(cError, iError, true);
            }

            int Window::initalize(int iWidth, int iHeight, std::string cTitle, bool bFullScreen) {
                if (m_pLogger) { m_pLogger->log("Starting Layer"); }

                // Set the error handler
                glfwSetErrorCallback(Window::errorHandler);

                // Initalize GLFW ready to send stuff
                if (!glfwInit()) {
                    throwError(__FUNCTION__, "Failed to initalize GLFW");
                }

                // Get the settings
                Settings oSettings(m_pLogger, cTitle);
                oSettings.setup();
                if (m_pLogger) { m_pLogger->log("Got Settings Object"); }

                glfwWindowHint(GLFW_SAMPLES, oSettings.getFSAA());
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, oSettings.getOpenGLMajor());
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, oSettings.getOpenGLMinor());

                if (m_pLogger) { m_pLogger->log("Got Hints"); }

                if (bFullScreen) {
                    oSettings.setWindowMode(false);
                    m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
                } else {
                    m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), nullptr, nullptr);
                }

                if (m_pLogger) { m_pLogger->log("Created Window"); }

                // failed to launch window
                if (m_pWindow == nullptr) {
                    throwError(__FUNCTION__, std::string("Failed to launch window, your system doesnt support OpenGL ") + getString(oSettings.getOpenGLMajor()));
                    destroy();
                }

                if (m_pLogger) { m_pLogger->log("Making Context"); }
                glfwMakeContextCurrent(m_pWindow);
                if (m_pLogger) { m_pLogger->log("Made Context"); }

                if (m_pLogger) { m_pLogger->log("Setting Input"); }
                glfwSetInputMode(m_pWindow, GLFW_STICKY_KEYS, GL_TRUE);
                if (m_pLogger) { m_pLogger->log("Set Input"); }

                if (m_pLogger) { m_pLogger->log("Setting VSync"); }
                if (oSettings.getVSync()) {
                    glfwSwapInterval(60);
                } else {
                    glfwSwapInterval(0);
                }
                if (m_pLogger) { m_pLogger->log("Set VSync"); }

                if (m_pLogger) { m_pLogger->log("Starting GLEW"); }
                glewExperimental = GL_TRUE;
                GLenum eError = glewInit();
                if (GLEW_OK != eError) {
                    throwError(__FUNCTION__, "Failed to initalize GLEW");
                }
                if (m_pLogger) { m_pLogger->log("Started GLEW"); }

                return 0;
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
                m_pLogger->log("Terminating");

                glfwTerminate();

                m_pLogger->log("Terminated");

                SAFE_DELETE(m_pLogger);
            }
        };
    };
};
