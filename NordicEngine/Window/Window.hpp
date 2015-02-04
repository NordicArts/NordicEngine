#ifndef NordicArts_NordicEngine_WindowMaker_Window_H
#define NordicArts_NordicEngine_WindowMaker_Window_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Window/Manager.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/OS/OpenGL.hpp>

#include <NordicEngine/ThirdParty/glfw/include/GLFW/glfw3.h>

namespace NordicArts {
    namespace NordicEngine {
        namespace WindowMaker {
            class Window : public Manager {
            // Variables
            public:
            protected:
                GLFWwindow  *m_pWindow;

                Logger      *m_pLogger;
                Settings    *m_pSettings;

            private:

            // Methods
            public:
                Window();
                Window(Logger *pLogger, Settings *pSettings);

                ~Window();

                virtual int initalize(int iWidth, int iHeight, std::string cTitle, bool bFullScreen = false);

                virtual bool processInput(bool bContinue);

                virtual void swapBuffers();
                virtual void destroy();
                virtual void setCursorLocation(int iX, int iY);

                static void errorHandler(int iError, const char *cError);

            protected:
            private:
            };
        };
    };
};

#endif
