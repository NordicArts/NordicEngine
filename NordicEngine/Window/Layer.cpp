#include <NordicEngine/Window/Layer.hpp>
#include <NordicEngine/Settings/Settings.hpp>

#include <GL/glew.h>

namespace NordicArts {
    namespace NordicEngine {
        namespace Window {
            Layer::Layer() {
            }

            Layer::~Layer() {
                destroy();
            }

            int Layer::initalize(int iWidth, int iHeight, std::string cTitle, bool bFullScreen) {
                if (!glfwInit()) {
                    throwError(__FUNCTION__, "Failed to initalize GLFW");
                }

                // Get the settings
                Settings oSettings(cTitle);

                glfwWindowHint(GLFW_SAMPLES, oSettings.getFSAA());
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, oSettings.getOpenGLMajor());
                glfwWindowHint(GLFW_CONTEX_VERSION_MINOR, oSettings.getOpenGLMinor());
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                if (bFullScreen) {
                    oSettings.setWindowMode(false);
                    m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
                } else {
                    m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), nullptr, nullptr);
                }

                // failed to launch window
                if (m_pWindow) {
                    destory();
                    throwError(__FUNCTION__, std::string("Failed to launch window, your system doesnt support OpenGL") + oSettings.getOpenGLMajor());
                }

                glfwMakeContextCurrent(m_pWindow);
                
                glfwSetInputMode(m_pWindow, GLFW_STICKY_KEYS, GL_TRUE);

                if (oSettings.getVSync()) {
                    glfwSwapInterval(60);
                } else {
                    glfwSwapInterval(0);
                }

                glfwExperimental = GL_TRUE;

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
                glwSwapBuffers(m_pWindow);
            }

            void Layer::destroy() {
                glfwTerminate();    
            }
        };
    };
};
