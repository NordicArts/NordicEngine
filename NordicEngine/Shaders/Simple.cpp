#include <NordicEngine/Shaders/Simple.hpp>
#include <NordicEngine/Files/Files.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Shaders {
            Simple::Simple() {
            }

            GLuint Simple::LoadShaders(std::string cVertex, std::string cFragment) {
GLuint iRet;                

//                GLuint iVertexID    = glCreateShader(GL_VERTEX_SHADER);
//                GLuint iFragmentID  = glCreateShader(GL_FRAGMENT_SHADER);

                // get code
                Files oVertex(cVertex);
                std::string cVertexCode = oVertex.read();

                printIt(cVertexCode);

                Files oFragment(cFragment);
                std::string cFragmentCode = oFragment.read();
            
                printIt(cFragmentCode);

return iRet;    
            }        
        };
    };
};
