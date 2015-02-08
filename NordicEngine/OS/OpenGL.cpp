#include <NordicEngine/OS/OpenGL.hpp>

namespace NordicArts {
    namespace NordicEngine {
        std::string getGLError(GLenum eError) {
            std::string cError = "";

            switch (eError) {
                case GL_NO_ERROR: {
                    cError = "GL_NO_ERROR: No error has been recorded. The value of this symbolic constant is guaranteed to be 0";
                    break;
                };
                case GL_INVALID_ENUM: {
                    cError = "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag";
                    break;
                };
                case GL_INVALID_VALUE: {
                    cError = "GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag";
                    break;
                };
                case GL_INVALID_OPERATION: {
                    cError = "GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag";
                    break;
                };
                case GL_INVALID_FRAMEBUFFER_OPERATION: {
                    cError = "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag";
                    break;
                };
                case GL_OUT_OF_MEMORY: {
                    cError = "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded";
                    break;
                };
                default: {
                    cError = "Unknown Error";
                    break;
                }
            }

            return cError;
        }
    };
};