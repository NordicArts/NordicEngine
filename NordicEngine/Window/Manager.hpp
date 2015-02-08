#ifndef NordicArts_NordicEngine_WindowMaker_Manager_H
#define NordicArts_NordicEngine_WindowMaker_Manager_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/OS/OpenGL.hpp>
#include <NordicEngine/Color/Color.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace WindowMaker {
            class Manager {
            // Varaibles
            public:
            protected:
            private:
                bool m_bSetDepthAndCull;

            // Methods
            public:
                virtual ~Manager();
                
                virtual int initalize(int iWidth, int iHeight, std::string cTitle, bool bFullScreen = false) = 0;

                virtual bool processInput(bool bContinue) = 0;

                virtual void swapBuffers() = 0;
                virtual void destroy() = 0;
                virtual void setCursorLocation(int iX, int iY) = 0;
                virtual void setCursorDisabled() = 0;

                void clearColor(Color oColor);
                void clearWindow();
                void depthAndCull();

            protected:
            private:

            };
        };
    };
};

#endif
