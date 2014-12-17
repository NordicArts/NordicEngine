#ifndef NordicArts_NordicEngine_Shaders_H
#define NordicArts_NordicEngine_Shaders_H

#include <NordicEngine/Engine.hpp>

#include <GL/glew.h>

namespace NordicArts {
    namespace NordicEngine {
        class Shaders {
        // Variables
        public:
        protected:
        private:
            unsigned int m_iObject;
            
            unsigned *m_pRefCount;

        // Methods
        public:
            static Shaders shaderFromFile(const std::string &cFilePath, GLenum eShaderType);

            Shaders(const Shaders &oOther);
            Shaders(const std::string &cShaderCode, GLenum eShaderType);

            Shaders &operator =(const Shaders &oOther);

            ~Shaders();

        protected:
        private:
            void retain();
            void release();

        };
    };
};

#endif
