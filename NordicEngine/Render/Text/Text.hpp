#ifndef NordicArts_NordicEngine_Render_Text_H
#define NordicArts_NordicEngine_Render_Text_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/OS/OpenGL.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class Texture;
        };

        namespace Render {
            class Text {
            // Variables
            public:
            protected:
            private:
                unsigned int     m_iTextureID;
                unsigned int     m_iVertexBufferID;
                unsigned int     m_iUVBufferID;
                unsigned int     m_iShaderID;
                unsigned int     m_iUniformID;

            // Methods
            public:
                Text();

                ~Text();

                void setup(std::string cTexture);
                void setup(Files::Texture oTexture);

                void cleanup();

                void render(std::string cText, int iX, int iY, int iSize);                

            protected:
            private:

            };
        };
    };
};

#endif
