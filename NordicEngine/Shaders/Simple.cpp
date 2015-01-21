#include <NordicEngine/Shaders/Simple.hpp>
#include <NordicEngine/Files/Loader.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Shaders {
            Simple::Simple() {
            }

            GLuint Simple::LoadShaders(std::string cVertex, std::string cFragment) {
                GLuint iVertexID    = glCreateShader(GL_VERTEX_SHADER);
                GLuint iFragmentID  = glCreateShader(GL_FRAGMENT_SHADER);

                // get code
                Files::Loader oVertex(cVertex);
                std::string cVertexCode = oVertex.read();

                Files::Loader oFragment(cFragment);
                std::string cFragmentCode = oFragment.read();

                GLint iResult = GL_FALSE;
                int iInfoLogLength;

                // Vertex
                char const *VertexSourcePointer = cVertexCode.c_str();
                glShaderSource(iVertexID, 1, &VertexSourcePointer, NULL);
                glCompileShader(iVertexID);

                glGetShaderiv(iVertexID, GL_COMPILE_STATUS, &iResult);
                glGetShaderiv(iVertexID, GL_INFO_LOG_LENGTH, &iInfoLogLength);
                if (iInfoLogLength > 0) {
                    std::vector<char> VertexShaderErrorMessage(iInfoLogLength + 1);
                    glGetShaderInfoLog(iVertexID, iInfoLogLength, NULL, &VertexShaderErrorMessage[0]);
                }

                // Fragment
                char const *FragmentSourcePointer = cFragmentCode.c_str();
                glShaderSource(iFragmentID, 1, &FragmentSourcePointer, NULL);
                glCompileShader(iFragmentID);

                glGetShaderiv(iFragmentID, GL_COMPILE_STATUS, &iResult);
                glGetShaderiv(iFragmentID, GL_INFO_LOG_LENGTH, &iInfoLogLength);
                if (iInfoLogLength > 0) {
                    std::vector<char> FragmentShaderErrorMessage(iInfoLogLength + 1);
                    glGetShaderInfoLog(iFragmentID, iInfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
                }

                // Program
                GLuint iProgramID = glCreateProgram();
                glAttachShader(iProgramID, iVertexID);
                glAttachShader(iProgramID, iFragmentID);
                glLinkProgram(iProgramID);

                glGetProgramiv(iProgramID, GL_LINK_STATUS, &iResult);
                glGetProgramiv(iProgramID, GL_INFO_LOG_LENGTH, &iInfoLogLength);
                if (iInfoLogLength > 0) {
                    std::vector<char> ProgramShaderErrorMessage(iInfoLogLength + 1);
                    glGetShaderInfoLog(iProgramID, iInfoLogLength, NULL, &ProgramShaderErrorMessage[0]);
                }

                glDeleteShader(iVertexID);
                glDeleteShader(iFragmentID);

                return iProgramID;
            }
        };
    };
};
