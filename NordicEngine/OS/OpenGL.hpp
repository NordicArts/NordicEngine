#ifndef NordicArts_NordicEngine_OS_OpenGL_H
#define NordicArts_NordicEngine_OS_OpenGL_H

#include <GL/glew.h>

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

// Types of shader
#ifndef GL_COMPUTE_SHADER
    #define GL_COMPUTE_SHADER NULL
#endif

#ifndef GL_TESS_CONTROL_SHADER
    #define GL_TESS_CONTROL_SHADER NULL
#endif

#ifndef GL_TESS_EVALUATION_SHADER
    #define GL_TESS_EVALUATION_SHADER NULL
#endif

namespace NordicArts {
    namespace NordicEngine {
        enum ShaderType {
            NES_VERTEX          = GL_VERTEX_SHADER,
            NES_FRAGMENT        = GL_FRAGMENT_SHADER,
            NES_GEOMETRY        = GL_GEOMETRY_SHADER,
            NES_COMPUTE         = GL_COMPUTE_SHADER,
            NES_TESS_CONTROL    = GL_TESS_CONTROL_SHADER,
            NES_TESS_EVAL       = GL_TESS_EVALUATION_SHADER
        };
    };
};

#endif
