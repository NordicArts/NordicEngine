#ifndef NordicArts_NordicEngine_Window_H
#define NordicArts_NordicEngine_Window_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Color/Color.hpp>
#include <NordicEngine/glfw/include/GLFW/glfw3.h>

namespace NordicArts {
    namespace NordicEngine {
        class Window {
        // Variables
        public:
        protected:
        private:
			GLFWwindow *m_pWindow;

        // Methods
        public:
            Window();
            
            virtual ~Window();

            int createWindow(int iWidth = 800, int iHeight = 600, std::string cTitle = "Hello World");

            bool isWindowOpen() const;

            void clear(Color oColor);
            void setVSync(bool bEnable);
            void setOpenGL(int iMajor = 3, int iMinor = 2);
            void draw();
            void display();

            static void errorHandler(int iError, const char *cDescription);

        protected:
        private:

        };
    };
};

#endif
