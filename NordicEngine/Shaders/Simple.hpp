#ifndef NordicArts_NordicEngine_Shaders_Simple_H
#define NordicArts_NordicEngine_Shaders_Simple_H

#include <NordicEngine/Engine.hpp>

#include <GL/glew.h>

namespace NordicArts {
    namespace NordicEngine {
        namespace Shaders {
            class Simple {
            // Variables
            public:
            protected:
            private:

            // Methods
            public:
                Simple();

                GLuint LoadShaders(std::string cVertex, std::string cFragment); 

            protected:
            private:

            };
        };
    };
};

#endif

