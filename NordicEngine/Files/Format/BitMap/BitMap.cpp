#include <NordicEngine/Files/Format/BitMap/BitMap.hpp>
#include <NordicEngine/Window/Window.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            BitMap::BitMap() : Handler(true) {
            }
            BitMap::BitMap(std::string cFileName) : Handler(cFileName, true) {
            }

            unsigned int BitMap::loadBitMap() {
                std::string cFile = getFilePath();
                m_cFileName = cFile;

                unsigned char cHeader[54];

                unsigned int iDataPos;
                unsigned char *cData;

                // Open the file
                FILE *pFile = fopen(cFile.c_str(), "rb");
                if (!pFile) { 
                    throwError(__FUNCTION__ + std::string(" cant open file"));

                    return 0; 
                }

                // Needs to be at least 54 bytes
                if (fread(cHeader, 1, 54, pFile) != 54) {
                    throwError(__FUNCTION__ + std::string(" not a BMP file"));

                    return 0;
                }

                // BMPs have BM at start of file
                if ((cHeader[0] != 'B') || (cHeader[1] != 'M')) {
                    throwError(__FUNCTION__ + std::string(" not a valid BMP file"));

                    return 0;   
                }

                // 24bpp
                if ((*(int *)&(cHeader[0x1E]) != 0) || (*(int *)&(cHeader[0x1C]) != 24)) {
                    throwError(__FUNCTION__ + std::string(" not a valid BMP file"));

                    return 0;
                }

                // Read the info for file
                iDataPos        = *(int *)&(cHeader[0x0A]);
                m_iImageSize    = *(int *)&(cHeader[0x22]);
                m_iWidth        = *(int *)&(cHeader[0x12]);
                m_iHeight       = *(int *)&(cHeader[0x16]);

                // Realign the data
                if (m_iImageSize == 0) { m_iImageSize = (m_iWidth * m_iHeight * 3); }
                if (iDataPos == 0) { iDataPos = 54; }

                // Create buffer
                cData = new unsigned char[m_iImageSize];

                // Add data to buffer
                fread(cData, 1, m_iImageSize, pFile);

                // Close the file
                fclose(pFile);

                // OpenGL texture
                glGenTextures(1, &m_iTextureID);

                // Bind texture
                glBindTexture(GL_TEXTURE_2D, m_iTextureID);

                // Send Image to OpenGL
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, cData);

                // Delete data
                SAFE_DELETE_ARRAY(cData);

                // Filtering
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glGenerateMipmap(GL_TEXTURE_2D);

                // Get TextureID
                return m_iTextureID;
            }

            unsigned int BitMap::getTextureID() const {
                return m_iTextureID;
            }

            unsigned int BitMap::getWidth() const {
                return m_iWidth;
            }
    
            unsigned int BitMap::getHeight() const {
                return m_iHeight;
            }
        };
    };
};
