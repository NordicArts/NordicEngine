#ifndef NordicArts_NordicEngine_Threading_Singleton_H
#define NordicArts_NordicEngine_Threading_Singleton_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
	namespace NordicEngine {
		class Singleton {
        // Variables
        public:
            enum SingletonType {
                TYPE_LOGGER = 0,
                TYPE_SETTINGS,
                TYPE_ENGINE,
                TYPE_SHADER_MANAGER,
            };

        protected:
        private:
            SingletonType m_eType;

        // Methods
        public:
            virtual ~Singleton();

        protected:
            explicit Singleton(SingletonType eType);

        private:

		};
	};
};

#endif
