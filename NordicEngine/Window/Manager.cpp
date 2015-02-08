#include <NordicEngine/Window/Manager.hpp>
#include <NordicEngine/Exception/Exception.hpp>
#include <NordicEngine/Color/Color.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace WindowMaker {
            Manager::~Manager() {
            }

            void Manager::clearWindow() {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }

            void Manager::clearColor(Color oColor) {
                glClearColor(oColor.getRed(), oColor.getGreen(), oColor.getBlue(), oColor.getAlpha());
            }

            void Manager::depthAndCull() {
                m_bSetDepthAndCull = true;

                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
                glEnable(GL_CULL_FACE);
            }
        };
    };
};
