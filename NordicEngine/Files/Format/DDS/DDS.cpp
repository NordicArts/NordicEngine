#include <NordicEngine/Files/Format/DDS/DDS.hpp>
#include <NordicEngine/Window/Window.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            DDS::DDS() : Handler(true) {
            }
            DDS::DDS(std::string cFileName) : Handler(cFileName, true) {
            }

            unsigned int DDS::loadDDS() {
                unsigned char cHeader[124];

                std::string cFile = getFilePath();
                m_cFile = cFile;

                FILE *pFile;
                pFile = fopen(cFile.c_str(), "rb");
                if (pFile == NULL) {
                    throwError(__FUNCTION__ + std::string(" cant open file"));
                    
                    return 0;
                }

                // Verify file
                char cFileCode[4];
                fread(cFileCode, 1, 4, pFile);
                if (strncmp(cFileCode, "DDS", 4) != 0) {
                    fclose(pFile);

                    throwError(__FUNCTION__ + std::string(" not a valid file"));
                
                    return 0;
                }

                // get the surface description
                fread(&cHeader, 124, 1, pFile);

                m_iHeight   = *(unsigned int *)&(cHeader[8]);
                m_iWidth    = *(unsigned int *)&(cHeader[12]);

                unsigned int iLinearSize    = *(unsigned int *)&(cHeader[16]);
                unsigned int iMipMapCount   = *(unsigned int *)&(cHeader[24]);
                unsigned int iFourCC        = *(unsigned int *)&(cHeader[80]);

                // Get the content
                unsigned char *cBuffer;
                unsigned int iBufferSize;
                iBufferSize = ((iMipMapCount > 1) ? (iLinearSize * 2) : iLinearSize);
                cBuffer = (unsigned char *)malloc(iBufferSize * sizeof(unsigned char));
                fread(cBuffer, 1, iBufferSize, pFile);

                // Close the file
                fclose(pFile);

                // Which type is it
                unsigned int iComponents = ((iFourCC == FOURCC_DXT1) ? 3 : 4);
                unsigned int iFormat;
                switch (iFourCC) {
                    case FOURCC_DXT1: {
                        iFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                        break;
                    }
                    case FOURCC_DXT3: {
                        iFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                        break;
                    }
                    case FOURCC_DXT5: {
                        iFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                        break;
                    }
                    default: {
                        free(cBuffer);
                        
                        return 0;
                    }
                }

                // Generate OpenGL Texture
                glGenTextures(1, &m_iTextureID);

                // Bind texture
                glBindTexture(GL_TEXTURE_2D, m_iTextureID);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                unsigned int iBlockSize = ((iFormat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16);
                unsigned int iOffset    = 0;

                // MipMaps
                for (unsigned int iLevel = 0; iLevel < (iMipMapCount && (m_iWidth || m_iHeight)); ++iLevel) {
                    unsigned int iSize = (((m_iWidth + 3) / 4) * ((m_iHeight + 3) / 4) * iBlockSize);

                    glCompressedTexImage2D(GL_TEXTURE_2D, iLevel, iFormat, m_iWidth, m_iHeight, 0, iSize, (cBuffer + iOffset));

                    iOffset += iSize;

                    m_iWidth  /= 2;
                    m_iHeight /= 2;

                    if (m_iWidth < 1) { m_iWidth = 1; }
                    if (m_iHeight < 1) { m_iHeight = 1; }
                }

                free(cBuffer);

                return m_iTextureID;
            }

            unsigned int DDS::getTextureID() const {
                return m_iTextureID;
            }

            unsigned int DDS::getWidth() const {
                return m_iWidth;
            }

            unsigned int DDS::getHeight() const {
                return m_iHeight;
            }
        };
    };
};
