#ifndef NordicArts_NordicEngine_Exceptions_H
#define NordicArts_NordicEngine_Exceptions_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {        
        class Exceptions final {
        // Variables
        public:
            Exceptions    *m_pSingleton;

        protected:
        private:
            std::string    m_cMessage;

        // Methods
        public:
            explicit Exceptions(const std::string &cMessage, int iError, bool bSaveToFile = true);
            explicit Exceptions(const std::string &cMessage, bool bSaveToFile = true);
            explicit Exceptions(const std::ostringstream &cMessage, bool bSaveToFile = true);
            explicit Exceptions(const char *cMessage, bool bSaveToFile = true);
            explicit Exceptions(const unsigned char *cMessage, bool bSaveToFile = true);

            const std::string &getMessage() const;

        protected:
        private:
            Exceptions &operator=(const Exceptions &cConst);
        };
    };
};

#endif
