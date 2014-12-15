#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Input/Input.hpp>
#include <NordicEngine/Exceptions/Exceptions.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Window::Window() {
            if (!glfwInit()) {
                throw new Exceptions("Can't initate GLFW", true);
            }

            glfwSetErrorCallback(Window::errorHandler);
        }

        Window::~Window() {
            glfwTerminate();

            m_pWindow = nullptr;
        }

        int Window::createWindow(int iWidth, int iHeight, std::string cTitle) {
            m_pWindow = glfwCreateWindow(iWidth, iHeight, cTitle.c_str(), NULL, NULL);
            if (!m_pWindow) {
                glfwTerminate();
        
                throw new Exceptions("Can't create the window", true);

                return -1;
            }

            glfwSetKeyCallback(m_pWindow, Input::handleInput);
            return 0;
        }

        void Window::clear(Color oColor) {
        }

        void Window::setOpenGL(int iMajor, int iMinor) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, iMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, iMinor);
        }

        void Window::setVSync(bool bEnable) {
            if (bEnable) {
                glfwSwapInterval(1);
            }
        }

        bool Window::isWindowOpen() const {
            if (!glfwWindowShouldClose(m_pWindow)) {
                return true;
            }
            return false;
        }

        void Window::draw() {
            return display();
        }
        void Window::display() {
            glfwSwapBuffers(m_pWindow);
        
            glfwPollEvents();
        }

        void Window::errorHandler(int iError, const char *cDescription) {
            throw new Exceptions(cDescription, iError, true);
        }
    };
};
