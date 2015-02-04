#include <NordicEngine/Window/Manager.hpp>
#include <NordicEngine/Exception/Exception.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace WindowMaker {
            Manager::~Manager() {
            }

            void Manager::clearWindow() {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
        };
    };
};
