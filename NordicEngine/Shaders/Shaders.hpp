#ifndef NordicArts_NordicEngine_Shaders_H
#define NordicArts_NordicEngine_Shaders_H

#include <NordicEngine/Engine.hpp>

#include <GL/glew.h>

namespace NordicArts {
    namespace NordicEngine {
        namespace Shaders {
            class Shader {
            // Variables
            public:
            protected:
            private:
                unsigned int m_iObject;
                unsigned int *m_pRefCount;

            // Methods
            public:
                static Shader shaderFromFile(const std::string &cFilePath, GLenum eShaderType);

                Shader(const Shader &oOther);
                Shader(const std::string &cShaderCode, GLenum eShaderType);

                Shader &operator =(const Shader &oOther);

                ~Shader();

                unsigned int getObject() const;

            protected:
            private:
                void retain();
                void release();

            };
        };
    };
};

#endif
