#ifndef NordicArts_NordicEngine_Render_Text_H
#define NordicArts_NordicEngine_Render_Text_H

#include <NordicEngine/Engine.hpp>

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
                int     m_iTextureID;
                int     m_iVertexBufferID;
                int     m_iUVBufferID;
                int     m_iShaderID;
                int     m_iUniformID;

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
