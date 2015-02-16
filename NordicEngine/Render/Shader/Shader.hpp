#ifndef NordicArts_NordicEngine_Render_Shader_H
#define NordicArts_NordicEngine_Render_Shader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Loader.hpp>
#include <NordicEngine/OS/OpenGL.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            class Shader {
            // Variables
            public:
            protected:
            private:
                GLuint m_iVertexID;
                GLuint m_iFragmentID;
                GLuint m_iShaderID;

            // Methods
            public:
                Shader();

                ~Shader();

                std::string loadShaderFile(std::string cFile);

                GLint getVariable(std::string cVariable);

                void initalize(std::string cVertex, std::string cFragment);
                void setInt(GLint iID, int iValue);
                void setFloat(GLint iID, GLfloat fValue);
                void setFloat(GLint iID, GLfloat f0, GLfloat f1);
                void setFloat(GLint iID, GLfloat f0, GLfloat f1, GLfloat f2);
                void setFloat(GLint iID, GLfloat f0, GLfloat f1, GLfloat f2, GLfloat v3);
                void setMatrix(GLint iID, GLsizei iCount, GLboolean bTranspose, const GLfloat *fValue);
                void turnOn();
                void turnOff();
                void destroy();

            protected:
            private:

            };
        };
    };
};

#endif
