#ifndef NordicArts_NordicEngine_Files_Texture_H
#define NordicArts_NordicEngine_Files_Texture_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class Texture {
            // Variables
            public:
            protected:
            private:
                unsigned int m_iTextureID;
                unsigned int m_iWidth;
                unsigned int m_iHeight;

                std::string m_cTexture;

            // Methods
            public:
                Texture();
                Texture(std::string cTexture);

                void setTexture(std::string cTexture);

                unsigned int loadTexture();
                unsigned int loadTexture(std::string cTexture);

                unsigned int getTextureID() const;
                unsigned int getWidth() const;
                unsigned int getHeight() const;

            protected:
            private:

            };
        };
    };
};

#endif
