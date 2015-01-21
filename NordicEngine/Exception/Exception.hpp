#ifndef NordicArts_NordicEngine_Exception_H
#define NordicArts_NordicEngine_Exception_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {        
        class Exception final {
        // Variables
        public:
            Exception    *m_pSingleton;

        protected:
        private:
            std::string    m_cMessage;

        // Methods
        public:
            explicit Exception(const std::string &cMessage, int iError, bool bSaveToFile = true);
            explicit Exception(const std::string &cMessage, bool bSaveToFile = true);
            explicit Exception(const std::ostringstream &cMessage, bool bSaveToFile = true);
            explicit Exception(const char *cMessage, bool bSaveToFile = true);
            explicit Exception(const unsigned char *cMessage, bool bSaveToFile = true);

            const std::string &what() const;
            const std::string &getMessage() const;

        protected:
        private:
            Exception &operator=(const Exception &cConst);
        };
    };
};

#endif
