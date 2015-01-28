#ifndef NordicArts_NordicEngine_Render_Shaders_Program_H
#define NordicArts_NordicEngine_Render_Shaders_Program_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/OS/OpenGL.hpp>
#include <NordicEngine/Render/Shaders/Shader.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                class Program {
                // Variables
                public:
                protected:
                private:
                    unsigned int m_iID;
                    unsigned int m_iPositionID;
                    unsigned int m_iMatrixID;
            
                    bool m_bIsLinked;

                    Shader *m_pVertex;
                    Shader *m_pFragment;
                    Shader *m_pGeometry;
                    Shader *m_pTessCtrl;
                    Shader *m_pTessEval;

                // Methods
                public:
                    Program();
                    Program(int iProgramID);
                    Program(Shader *pVertex, Shader *pFragment);
                    
                    ~Program();

                    void attachShader(Shader *pShader);
                    void attachData(int iColor, std::string cData);

                    void link();
                    void use();
                    void stopUsing();
                    void setAttributeID(std::string cName, unsigned int iID);
                    void dumpActiveAttributes();

                    int getUniformID(std::string cName);
                    int getAttributeID(std::string cName);

                    unsigned int getID() const;

                protected:
                private:
                    void check(GLenum eCheck);
                    void postLinkHook();
                };
            };            
        };
    };
};

#endif
