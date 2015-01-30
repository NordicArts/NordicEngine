#include <NordicEngine/Window/Layer.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Window {
            Layer::Layer() {
            }
            Layer::Layer(Logger *pLogger) : m_pLogger(pLogger) {
            }

            Layer::~Layer() {
                destroy();
            }

            int Layer::initalize(int iWidth, int iHeight, std::string cTitle, bool bFullScreen) {
                m_pLogger->log("Starting Layer");

                if (!glfwInit()) {
                    throwError(__FUNCTION__, "Failed to initalize GLFW");
                }

                // Get the settings
                Settings oSettings(cTitle);

                glfwWindowHint(GLFW_SAMPLES, oSettings.getFSAA());
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, oSettings.getOpenGLMajor());
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, oSettings.getOpenGLMinor());
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                if (bFullScreen) {
                    oSettings.setWindowMode(false);
                    m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
                } else {
                    m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), nullptr, nullptr);
                }

                // failed to launch window
                if (m_pWindow) {
                    destroy();
                    throwError(__FUNCTION__, std::string("Failed to launch window, your system doesnt support OpenGL") + getString(oSettings.getOpenGLMajor()));
                }

                glfwMakeContextCurrent(m_pWindow);
                
                glfwSetInputMode(m_pWindow, GLFW_STICKY_KEYS, GL_TRUE);

                if (oSettings.getVSync()) {
                    glfwSwapInterval(60);
                } else {
                    glfwSwapInterval(0);
                }

                glewExperimental = GL_TRUE;

                GLenum eError = glewInit();
                if (GLEW_OK != eError) {
                    destroy();
                    throwError(__FUNCTION__, "Failed to initalize GLEW");
                }

                return 0;
            }

            bool Layer::processInput(bool bContinue = true) {
                if ((glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) || (glfwWindowShouldClose(m_pWindow) != 0)) {
                    return false;
                }

                glfwPollEvents();

                return bContinue;
            }

            void Layer::swapBuffers() {
                glfwSwapBuffers(m_pWindow);
            }

            void Layer::destroy() {
                glfwTerminate();    

                SAFE_DELETE(m_pLogger);
            }
        };
    };
};
