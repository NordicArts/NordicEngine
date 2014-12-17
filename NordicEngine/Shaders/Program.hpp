#ifndef NordicArts_NordicEngine_Shaders_Program_H
#define NordicArts_NordicEngine_Shaders_Program_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Shaders/Shaders.hpp>

namespace NordicArts{
    namespace NordicEngine {
        class Program {
        // Variables
        public:
        protected:
        private:
            unsigned int m_iObject;

        // Methods
        public:
            Program(const std::vector<Shaders> &oShaders);

            ~Program();

            unsigned int getObject() const;

            int getAttrib(const char *cName) const;
            int getUniform(const char *cName) const;

        protected:
        private:
            Program(const Program &);

            const Program &operator =(const Program &);

        };
    };
};

#endif