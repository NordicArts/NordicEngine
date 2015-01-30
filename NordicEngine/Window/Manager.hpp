#ifndef NordicArts_NordicEngine_Window_Manager_H
#define NordicArts_NordicEngine_Window_Manager_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Window {
            class Manager {
            // Varaibles
            public:
            protected:
            private:

            // Methods
            public:
                virtual ~Manager() = 0;
                
                virtual int initalize(int iWidth, int iHeight, std::string cTitle, bool bFullScreen = false) = 0;

                virtual bool processInput(bool bContinue) = 0;

                virtual void swapBuffers() = 0;
                virtual void destroy() = 0;

            protected:
            private:

            };
        };
    };
};

#endif
