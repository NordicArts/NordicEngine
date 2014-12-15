#include <NordicEngine/Input/Input.hpp>

namespace NordicArts {
    namespace NordicEngine {
        void Input::handleInput(GLFWwindow *pWindow, int iKey, int iScanCode, int iAction, int iMods) {
            // Close window
            if ((iKey == NEK_ESCAPE) && (iAction == NEK_PRESS)) {
                glfwSetWindowShouldClose(pWindow, true);
                printIt("Close");
            }

            printIt(iKey);
            printIt("Keys");
        }

        Input::Input() {
        }

        Input::~Input() {
        }
    };
};
