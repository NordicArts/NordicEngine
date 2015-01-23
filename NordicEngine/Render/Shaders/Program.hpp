#ifndef NordicArts_NordicEngine_Render_Shaders_Program_H
#define NordicArts_NordicEngine_Render_Shaders_Program_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                class Shader;

                class Program {
                // Variables
                public:
                protected:
                private;
                    unsigned int m_iID;
                    unsigned int m_iPosID;
            
                    bool m_bIsLinked;

                    Shader *m_pVertex;
                    Shader *m_pFragment;
                    Shader *m_pGeometry;

                // Methods
                public:
                    Program();
                    Program(Shader *pVertex, Shader *pFragment);
                    
                    ~Program();

                    void attachShader(Shader *pShader);
                    void link();
                    void use();
                    void stopUsing();
                    void setAttributeId(std::string cName, unsigned int iID);
                    void dumpActiveAttributes();

                    int getUniformID(std::string cName);
                    int getAttributeID(std::string cName);

                protected:
                private:
                };
            };            
        };
    };
};

#endif
