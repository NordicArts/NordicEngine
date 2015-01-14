#ifndef NordicArts_NordicEngine_OS_NonWindows_OSX_H
#define NordicArts_NordicEngine_OS_NonWindows_OSX_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class OSSpecific {
        // Variables
        public:
        protected:
        private:

        // Methods
        public:
            std::string ResourcePath(std::string cFileName);
            
            bool deleteFile(std::string cFileName);

        protected:
        private:

        };
    };
};

#endif
