#ifndef NordicArts_NordicEngine_Files_Obj_H
#define NordicArts_NordicEngine_Files_Obj_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Files {
            class Obj : public Handler {
            // Variables
            public:
            protected:
            private:
                std::string m_cFile;

            // Methods
            public:
                Obj();
                Obj(std::string cFile);

                void setModelFile(std::string cFile);
 
                bool loadModel(std::vector<glm::vec3> &vVertices, std::vector<glm::vec2> &vUVs, std::vector<glm::vec3> &vNormals);

            protected:
            private:

            };
        };
    };
};

#endif
