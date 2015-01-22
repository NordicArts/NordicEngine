#ifndef NordicArts_NordicEngine_Files_Texture_H
#define NordicArts_NordicEngine_Files_Texture_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Format/BitMap/BitMap.hpp>

#include <GL/glew.h>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class Texture {
            // Variables
            public:
            protected:
            private:
                unsigned int m_iObject;
            
                float m_fOriginalWidth;
                float m_fOriginalHeight;

            // Methods
            public:
                Texture(const BitMap &oBitMap, int iMinMagFilter = GL_LINEAR, int iWrapMode = GL_CLAMP_TO_EDGE);
                ~Texture();

                unsigned int getObject() const;
                
                float getOriginalWidth() const;
                float getOriginalHeight() const;

            protected:
            private:
                Texture(const Texture &);

                const Texture &operator =(const Texture &);

            };
        };
    };
};

#endif
