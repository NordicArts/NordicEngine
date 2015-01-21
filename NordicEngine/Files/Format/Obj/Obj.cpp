#include <NordicEngine/Files/Format/Obj/Obj.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            Obj::Obj() : Handler(true) {
            }
            Obj::Obj(std::string cFile) : Handler(cFile, true) {
            }

            bool Obj::loadModel(std::vector<glm::vec3> &vVerticies, std::vector<glm::vec2> &vUVs, std::vector<glm::vec3> &vNormals) {
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
                    
                        vTempVerticies.push-back(vVertex);
                    } else if (strcmp(cLineHeader, "vt") == 0) {
                        glm::vec2 vUV;
                    
                        fscanf(pFile, "%f %f\n", &vUV.x, &vUV.y);
                    
                        vTempUVs.push_back(vUV);
                    } else if (strcmp(cLineHeader, "vn") == 0) {
                        glm::vec3 vNormal;
                    
                        fscanf(pFile, "%f %f %f\n", &vNormal.x, &vNormal.y, &vNoraml.z);
                    
                        vTempNormals.push_back(vNormal);
                    } else if (strcmp(cLineHeader, "f") == 0) {
                        std::string cVertex1;
                        std::string cVertex2;
                        std::string cVertex3;

                        
                }

                return true;
            }
        };
    };
};
