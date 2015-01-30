#ifndef NordicArts_NordicEngine_Window_Layer_H
#define NordicArts_NordicEngine_Window_Layer_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Window/Manager.hpp>

#include <NordicEngine/ThirdParty/glfw/include/GLFW/glfw3.h>

namespace NordicArts {
    namespace NordicEngine {
        namespace Window {
            class Layer : public Manager {
            // Variables
            public:
            protected:
                GLFWwindow *m_pWindow;

            private:

            // Methods
            public:
                Layer();

                ~Layer();

                virtual int initalize(int iWidth, int iHeight, std::string cTitle, bool bFullScreen = false);

                virtual bool processInput(bool bContinue);

                virtual void swapBuffers();
                virtual void destroy();

            protected:
            private:

            };
        };
    };
};

#endif
