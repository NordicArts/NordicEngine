#ifndef NordicArts_NordicEngine_Window_H
#define NordicArts_NordicEngine_Window_H

#include <NordicEngine/Engine.hpp>

#include <GL/glew.h>
#include <NordicEngine/ThirdParty/glfw/include/GLFW/glfw3.h>

namespace NordicArts {
    namespace NordicEngine {
        class Logger;
        class Settings;
        class Color;

        class Window {
        // Variables
        public:
            int m_iWidth;
            int m_iHeight;

        protected:
        private:
			GLFWwindow  *m_pWindow;

            Logger      *m_pLogger;
            Settings    *m_pSettings;

        // Methods
        public:
            Window();
            Window(Logger *pLogger);
            Window(Logger *pLogger, Settings *pSettings);

            void setup();
            void doGLEW();
            void makeContext();
            void setCallback();
            
            virtual ~Window();

            int createWindow();
            int createWindow(int iWidth, int iHeight, std::string cTitle);

            bool isWindowOpen() const;
            void closeWindow();

            void setVSync(bool bEnable);

            void setOpenGL();
            void setOpenGL(int iMajor, int iMinor);

            void setFSAA();
            void setFSAA(int iFSAA);

            void getFrameBufferSize(int *iWidth, int *iHeight);
            void draw();
            void display();

            void initColor(Color oColor) const;
            void clear() const;

            static void errorHandler(int iError, const char *cDescription);

        protected:
        private:
        
        };
    };
};

#endif
