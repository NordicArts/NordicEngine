#ifndef NordicArts_NordicEngine_Input_H
#define NordicArts_NordicEngine_Input_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Input/Definitions.hpp>
#include <NordicEngine/glfw/include/GLFW/glfw3.h>

namespace NordicArts {
    namespace NordicEngine {
        class Input {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            static void handleInput(GLFWwindow *pWindow, int iKey, int iScanCode, int iAction, int iModifiers);

            Input();
    
            ~Input();

        protected:
        private:

        };
    };
};

#endif
