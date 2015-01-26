#ifndef NordicArts_NordicEngine_Render_Shaders_Shader_H
#define NordicArts_NordicEngine_Render_Shaders_Shader_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/OS/OpenGL.hpp>

namespace NordicArts {
    namespace NordicEngine {
        namespace Render {
            namespace Shaders {
                std::string getShaderType(ShaderType eType);

                class Shader {
                // Variables
                public:
                protected:
                private:
                    unsigned int m_iID;                    

                    ShaderType m_eType;

                    std::string m_cType;

                // Methods
                public:
                    Shader(ShaderType eType, std::string cFile);

                    ~Shader();

                    unsigned int getID() const;
                    ShaderType getType() const;

                protected:
                private:

                };
            };
        };
    };
};

#endif
