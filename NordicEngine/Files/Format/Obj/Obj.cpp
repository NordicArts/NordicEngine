#include <NordicEngine/Files/Format/Obj/Obj.hpp>

/*
* OBJ Format
*
* Comment
* # comment
*
* Verticies
* v [x,y,z,[w]]
* v 1.0 2.0 3.0 [1.0]
*
* Texture Coords
* vt [x, y, [z]]
* vt 1.0 1.0 [0.0]
*
* Normals
* vn [x, y, z]
* vn 1.0 1.0 1.0
*
* Parameter Space
* vp [x, [y, [z]]]
* vp 1.0 [1.0 [1.0]]
*
* Faces
* f 1 2 3
* f 1/2 3/4 5/6
* f 1/2/3 4/5/6 7/8/9
*
*/

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            Obj::Obj() : Handler(true) {
            }
            Obj::Obj(std::string cFile) : Handler(cFile, true) {
            }

            bool Obj::loadModel(std::vector<glm::vec3> &vOutVerticies, std::vector<glm::vec2> &vOutUVs, std::vector<glm::vec3> &vOutNormals) {
                bool bValid = true;

                std::vector<unsigned int> vVertexIndicies;
                std::vector<unsigned int> vUVIndicies;
                std::vector<unsigned int> vNormalIndicies;

                std::vector<glm::vec3> vTempVerticies;
                std::vector<glm::vec2> vTempUVs;
                std::vector<glm::vec3> vTempNormals;

                std::string cFile = getFilePath();
                
                std::string cLine;
                m_cFileStream.open(cFile.c_str(), std::ios_base::in);

                // Stream file
                while(std::getline(m_cFileStream, cLine)) {
                    // Parse File
                    if (cLine.compare(0, 1, "v") == 0) { // Vertex
                        glm::vec3 vVertex;
                        std::sscanf(cLine.c_str(), "v %f %f %f\n", &vVertex.x, &vVertex.y, &vVertex.z);

                        vTempVerticies.push_back(vVertex);
                    } else if (cLine.compare(0, 2, "vt") == 0) { // Texture Positions
                        glm::vec2 vUV;
                        std::sscanf(cLine.c_str(), "vt %f %f\n", &vUV.x, &vUV.y);
                        
                        vTempUVs.push_back(vUV);
                    } else if (cLine.compare(0, 2, "vn") == 0) { // Normals
                        glm::vec3 vNormal;
                        std::sscanf(cLine.c_str(), "vn %f %f %f\n", &vNormal.x, &vNormal.y, &vNormal.z);
        
                        vTempNormals.push_back(vNormal);
                    } else if (cLine.compare(0, 1, "f") == 0) { // Faces
                        bool bFound = false;

                        // Temp Vertex Index
                        int iVIndexA[3];
                        int iVIndexB[3];
                        int iVIndexC[3];
                        int iVIndexD[3];

                        // Temp UV Index
                        int iUIndexA[3];
                        int iUIndexB[3];
                        int iUIndexC[3];
                        int iUIndexD[3];

                        // Temp Normal Index
                        int iNIndexA[3];
                        int iNIndexB[3];
                        int iNIndexC[3];
                        int iNIndexD[3];

                        // Parse the values
                        int iAll            = std::sscanf(cLine.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &iVIndexA[0], &iUIndexA[0], &iNIndexA[0], &iVIndexA[1], &iUIndexA[1], &iNIndexA[1], &iVIndexA[2], &iUIndexA[2], &iNIndexA[2]);
                        int iVertexNormal   = std::sscanf(cLine.c_str(), "f %d//%d %d//%d %d//%d\n", &iVIndexB[0], &iNIndexB[0], &iVIndexB[1], &iNIndexB[1], &iVIndexB[2], &iNIndexB[2]);
                        int iVertexTexture  = std::sscanf(cLine.c_str(), "f %d/%d %d/%d %d/%d\n", &iVIndexC[0], &iUIndexC[0], &iVIndexC[1], &iUIndexC[1], &iVIndexC[2], &iUIndexC[2]);
                        int iVertex         = std::sscanf(cLine.c_str(), "f %d %d %d\n", &iVIndexD[0], &iVIndexD[1], &iVIndexD[2]);

                        // Make sure there is some
                        if (iAll == 9) {
                            vVertexIndicies.push_back(iVIndexA[0]);
                            vVertexIndicies.push_back(iVIndexA[1]);
                            vVertexIndicies.push_back(iVIndexA[2]);
    
                            vUVIndicies.push_back(iUIndexA[0]);
                            vUVIndicies.push_back(iUIndexA[1]);
                            vUVIndicies.push_back(iUIndexA[2]);

                            vNormalIndicies.push_back(iNIndexA[0]);
                            vNormalIndicies.push_back(iNIndexA[1]);
                            vNormalIndicies.push_back(iNIndexA[2]);

                            bFound = true; 
                        }
                        if (iVertexNormal == 6) { 
                            vVertexIndicies.push_back(iVIndexB[0]);
                            vVertexIndicies.push_back(iVIndexB[1]);
                            vVertexIndicies.push_back(iVIndexB[2]);

                            vNormalIndicies.push_back(iNIndexB[0]);
                            vNormalIndicies.push_back(iNIndexB[1]);
                            vNormalIndicies.push_back(iNIndexB[2]);

                            bFound = true; }
                        if (iVertexTexture == 6) { 
                            vVertexIndicies.push_back(iVIndexC[0]);
                            vVertexIndicies.push_back(iVIndexC[1]);
                            vVertexIndicies.push_back(iVIndexC[2]);

                            vUVIndicies.push_back(iUIndexC[0]);
                            vUVIndicies.push_back(iUIndexC[1]);
                            vUVIndicies.push_back(iUIndexC[2]);

                            bFound = true; 
                        }
                        if (iVertex == 3) { 
                            vVertexIndicies.push_back(iVIndexD[0]);
                            vVertexIndicies.push_back(iVIndexD[1]);
                            vVertexIndicies.push_back(iVIndexD[2]);

                            bFound = true; 
                        }

                        // There are no faces so this file is invalid
                        if (!bFound) { 
                            bValid = false;
                            break;
                        }
                    } else { // Comments
                    }
                }
                m_cFileStream.close();

                // Not a valid file
                if (!bValid) {
                    throwError(__FUNCTION__, std::string("OBJ file is invalid: ") + cFile);
                } 

                // do the vertexs
                for (unsigned int i = 0; i < vVertexIndicies.size(); i++) {
                    // get the index of attributes
                    unsigned int iVertexIndex   = vVertexIndicies[i];

                    // get the attribute
                    glm::vec3 vVertex   = vTempVerticies[iVertexIndex - 1];

                    // put arrays into buffers
                    vOutVerticies.push_back(vVertex);
                }

                // UV
                for (unsigned int i = 0; i < vUVIndicies.size(); i++) {
                    // get the index of attributes
                    unsigned int iUVIndex       = vUVIndicies[i];

                    // get the attribute
                    glm::vec2 vUV       = vTempUVs[iUVIndex - 1];

                    // put arrays into buffers
                    vOutUVs.push_back(vUV);
                }

                // Normals
                for (unsigned int i = 0; i < vNormalIndicies.size(); i++) {
                    // get the index of attributes
                    unsigned int iNormalIndex   = vNormalIndicies[i];

                    // get the attribute
                    glm::vec3 vNormal   = vTempNormals[iNormalIndex - 1];

                    // put arrays into buffers
                    vOutNormals.push_back(vNormal);
                }

                return true;
            }
        };
    };
};
