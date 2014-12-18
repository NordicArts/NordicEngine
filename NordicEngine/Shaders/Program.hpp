#ifndef NordicArts_NordicEngine_Shaders_Program_H
#define NordicArts_NordicEngine_Shaders_Program_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Shaders/Shaders.hpp>

#include <NordicEngine/glm/glm/glm.hpp>

namespace NordicArts{
    namespace NordicEngine {
        namespace Shaders {
            class Program {
            // Variables
            public:
            protected:
            private:
                unsigned int m_iObject;

            // Methods
            public:
                Program(const std::vector<Shader> &vShaders);    
                ~Program();

                unsigned int getObject() const;

                void use() const;
                void stopUsing() const;
        
                bool isInUse() const;
    
                int getAttrib(const char *cName) const;
                int getUniform(const char *cName) const;

                #define NordicArts_NordicEngine_Shaders_Program_Attrib_N_Uniform_Setters(OGL_TYPE) \
                void setAttrib(const char *cName, OGL_TYPE v0); \
                void setAttrib(const char *cName, OGL_TYPE v0, OGL_TYPE v1); \
                void setAttrib(const char *cName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
                void setAttrib(const char *cName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
                \
                void setAttrib1v(const char *cName, const OGL_TYPE *v); \
                void setAttrib2v(const char *cName, const OGL_TYPE *v); \
                void setAttrib3v(const char *cName, const OGL_TYPE *v); \
                void setAttrib4v(const char *cName, const OGL_TYPE *v); \
                \
                void setUniform(const char *cName, OGL_TYPE v0); \
                void setUniform(const char *cName, OGL_TYPE v0, OGL_TYPE v1); \
                void setUniform(const char *cName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
                void setUniform(const char *cName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
                \
                void setUniform1v(const char *cName, const OGL_TYPE *v, int iCount = 1); \
                void setUniform2v(const char *cName, const OGL_TYPE *v, int iCount = 1); \
                void setUniform3v(const char *cName, const OGL_TYPE *v, int iCount = 1); \
                void setUniform4v(const char *cName, const OGL_TYPE *v, int iCount = 1); \
                
                NordicArts_NordicEngine_Shaders_Program_Attrib_N_Uniform_Setters(float)
                NordicArts_NordicEngine_Shaders_Program_Attrib_N_Uniform_Setters(double)
                NordicArts_NordicEngine_Shaders_Program_Attrib_N_Uniform_Setters(int)
                NordicArts_NordicEngine_Shaders_Program_Attrib_N_Uniform_Setters(unsigned int)

                void setUniformMatrix2(const char *cName, const float *v, int iCount = 1, bool bTranspose = false);
                void setUniformMatrix3(const char *cName, const float *v, int iCount = 1, bool bTranspose = false);
                void setUniformMatrix4(const char *cName, const float *v, int iCount = 1, bool bTranspose = false);
                void setUniform(const char *cName, const glm::mat2 &m, bool bTranspose = false);
                void setUniform(const char *cName, const glm::mat3 &m, bool bTranspose = false);
                void setUniform(const char *cName, const glm::mat4 &m, bool bTranspose = false);
                void setUniform(const char *cName, const glm::vec3 &v);
                void setUniform(const char *cName, const glm::vec4 &v);

            protected:
            private:
                Program(const Program &);
    
                const Program &operator =(const Program &);

            };
        };
    };
};

#endif
