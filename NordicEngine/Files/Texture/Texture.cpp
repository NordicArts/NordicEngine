#include <NordicEngine/Files/Texture/Texture.hpp>
#include <NordicEngine/Files/Format/BitMap/BitMap.hpp>
#include <NordicEngine/Files/Format/DDS/DDS.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            Texture::Texture() {
            }

            Texture::Texture(std::string cTexture) : m_cTexture(cTexture) {
            }

            void Texture::setTexture(std::string cTexture) {
                m_cTexture = cTexture;
            }
            
            unsigned int Texture::getTextureID() const {
                return m_iTextureID;
            }

            unsigned int Texture::getHeight() const {
                return m_iHeight;
            }

            unsigned int Texture::getWidth() const {
                return m_iWidth;
            }

            unsigned int Texture::loadTexture(std::string cTexture) {
                setTexture(cTexture);

                return loadTexture();
            }
            unsigned int Texture::loadTexture() {
                // Texture file needs to be upper case in order to check its type
                std::string cCopy   = m_cTexture;
                cCopy               = toUpper(cCopy);

                // Format
                bool bDDS   = false;
                bool bBMP   = false;

                // Is it a DDS
                std::size_t nFound = cCopy.find(".DDS");
                if (nFound != std::string::npos) { bDDS = true; }

                // Is it a BMP
                nFound = cCopy.find(".BMP");
                if (nFound != std::string::npos) { bBMP = true; }

                // Is it a valid format
                if (bBMP || bDDS) {
                    if (bBMP) {
                        BitMap oBMP(m_cTexture);

                        m_iTextureID = oBMP.loadBitMap();
                    }

                    if (bDDS) {
                        DDS oDDS(m_cTexture);
                        m_iTextureID = oDDS.loadDDS();
                    }
                } else {
                    throwError(__FUNCTION__ + std::string(" Texture format isnt supported yet, ") + m_cTexture);
                
                    return 0;
                }

                return getTextureID();
            }
        };
    };
};
