#include <NordicEngine/Render/Manager.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            Manager::Manager() {
            }
            Manager::Manager(Logger *pLogger) : m_pLogger(pLogger) {
            }

            void Manager::destroy() {
                if (m_bDepthAndCull) {
                    glDisable(GL_CULL_FACE);
                    glDisable(GL_DEPTH_TEST);
                }
            }
            Manager::~Manager() {
                destroy();
            }

            void Manager::depthAndCull() {
                m_bDepthAndCull = true;

                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);

                glEnable(GL_CULL_FACE);
            }

            void Manager::clearColor(Color oColor) {
                glClearColor(oColor.getRed(), oColor.getGreen(), oColor.getBlue(), oColor.getAlpha());
            }

            void Manager::clear() {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
        };
    };
};