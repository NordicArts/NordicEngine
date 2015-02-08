#ifndef NordicArts_NordicEngine_Render_Manager_H
#define NordicArts_NordicEngine_Render_Manager_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/OS/OpenGL.hpp>
#include <NordicEngine/Color/Color.hpp>
#include <NordicEngine/Logger/Logger.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            class Manager {
            // Variables
            public:
            protected:
            private:
                bool m_bDepthAndCull;

                Logger *m_pLogger;

            // Methods
            public:
                Manager();
                Manager(Logger *pLogger);

                void clear();
                void clearColor(Color oColor);
                void depthAndCull();

                void destroy();
                ~Manager();

            protected:
            private:

            };
        };
    };
};

#endif