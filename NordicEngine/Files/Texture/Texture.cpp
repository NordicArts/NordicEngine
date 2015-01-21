#include <NordicEngine/Files/Texture/Texture.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            static unsigned int TextureFormatForBitMapFormat(BitMap::Format eFormat, bool bSRGB) {
                switch (eFormat) {
                    case BitMap::Format_Grayscale: return GL_LUMINANCE;
                    case BitMap::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
                    case BitMap::Format_RGB: return (bSRGB ? GL_SRGB : GL_RGB);
                    case BitMap::Format_RGBA: return (bSRGB ? GL_SRGB_ALPHA : GL_RGBA);
                    default: {
                        throw Exceptions("Unrecognised BitMap::Format");
                    };
                }
            }

            Texture::Texture(const BitMap &oBitMap, int iMinMagFiler, int iWrapMode) : m_fOriginalWidth((float)oBitMap.getWidth()), m_fOriginalHeight((float)oBitMap.getHeight()) {
                glGenTextures(1, &m_iObject);
                glBindTexture(GL_TEXTURE_2D, m_iObject);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, iMinMagFiler);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, iMinMagFiler);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, iWrapMode);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, iWrapMode);
                glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatForBitMapFormat(oBitMap.getFormat(), true), (int)oBitMap.getWidth(), (int)oBitMap.getHeight(), 0, TextureFormatForBitMapFormat(oBitMap.getFormat(), false), GL_UNSIGNED_BYTE, oBitMap.getPixelBuffer());
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            Texture::~Texture() {
                glDeleteTextures(1, &m_iObject);
            }

            unsigned int Texture::getObject() const {
                return m_iObject;
            }

            float Texture::getOriginalWidth() const {
                return m_fOriginalWidth;
            }
        
            float Texture::getOriginalHeight() const {
                return m_fOriginalHeight;
            }
        };
    };
};
