#include <NordicEngine/Files/Format/Obj/Obj.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            Obj::Obj() : Handler(true) {
            }
            Obj::Obj(std::string cFile) : Handler(cFile, true) {
            }

            bool Obj::loadModel(std::vector<glm::vec3> &vOutVerticies, std::vector<glm::vec2> &vOutUVs, std::vector<glm::vec3> &vOutNormals) {
                std::vector<unsigned int> vVertexIndicies;
                std::vector<unsigned int> vUVIndicies;
                std::vector<unsigned int> vNormalIndicies;

                std::vector<glm::vec3> vTempVerticies;
                std::vector<glm::vec2> vTempUVs;
                std::vector<glm::vec3> vTempNormals;

                std::string cFile = getFilePath();

                FILE *pFile = fopen(cFile.c_str(), "r");
                if (pFile == NULL) {
                    throwError(__FUNCTION__ + std::string(" Can't open the OBJ file"));
                    
                    return false;
                }

                // Parse file
                while (true) {
                    char cLineHeader[128];
                    int iRes = fscanf(pFile, "%s", cLineHeader);
                    if (iRes == EOF) { break; }

                    // Get Vertex
                    if (strcmp(cLineHeader, "v") == 0) {
                        glm::vec3 vVertex;
                    
                        fscanf(pFile, "%f %f %f\n", &vVertex.x, &vVertex.y, &vVertex.z);
                    
                        vTempVerticies.push_back(vVertex);
                    } else if (strcmp(cLineHeader, "vt") == 0) {
                        glm::vec2 vUV;
                    
                        fscanf(pFile, "%f %f\n", &vUV.x, &vUV.y);
                    
                        vTempUVs.push_back(vUV);
                    } else if (strcmp(cLineHeader, "vn") == 0) {
                        glm::vec3 vNormal;
                    
                        fscanf(pFile, "%f %f %f\n", &vNormal.x, &vNormal.y, &vNormal.z);
                    
                        vTempNormals.push_back(vNormal);
                    } else if (strcmp(cLineHeader, "f") == 0) {
                        std::string cVertex1;
                        std::string cVertex2;
                        std::string cVertex3;

                        unsigned int iVertexIndex[3];
                        unsigned int iUVIndex[3];
                        unsigned int iNormalIndex[3];
                        
                        int iMatches = fscanf(pFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &iVertexIndex[0], &iUVIndex[0], &iNormalIndex[0], &iVertexIndex[1], &iUVIndex[1], &iNormalIndex[1], &iVertexIndex[2], &iUVIndex[2], &iNormalIndex[2]);
                        printIt("Equal 9");
                        printIt(iMatches);

                        if (iMatches == 9) {
                            vVertexIndicies.push_back(iVertexIndex[0]);
                            vVertexIndicies.push_back(iVertexIndex[1]);
                            vVertexIndicies.push_back(iVertexIndex[2]);

                            vUVIndicies.push_back(iUVIndex[0]);
                            vUVIndicies.push_back(iUVIndex[1]);
                            vUVIndicies.push_back(iUVIndex[2]);

                            vNormalIndicies.push_back(iNormalIndex[0]);
                            vNormalIndicies.push_back(iNormalIndex[1]);
                            vNormalIndicies.push_back(iNormalIndex[2]);
                        } else {
                            iMatches = fscanf(pFile, "%d %d %d\n", &iVertexIndex[0], &iVertexIndex[1], &iVertexIndex[2]);
                            printIt("Less than 9")
                            printIt(iMatches);
                            printIt(iVertexIndex[0]);

                            if (iMatches == 3) {
                                vVertexIndicies.push_back(iVertexIndex[0]);
                                vVertexIndicies.push_back(iVertexIndex[1]);
                                vVertexIndicies.push_back(iVertexIndex[2]);
                            } else {
                                throwError(__FUNCTION__ + std::string(" cant read the OBJ file properlly"));

                                return false;
                            }
                        }
                    } else {
                        // Comment
                        char commentBuffer[1000];
                        fgets(commentBuffer, 1000, pFile);
                    }
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
