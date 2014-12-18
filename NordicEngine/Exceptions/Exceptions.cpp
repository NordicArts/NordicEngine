#include <NordicEngine/Exceptions/Exceptions.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Exceptions::Exceptions(const std::string &cMessage, int iError, bool bSaveToFile) : m_cMessage(cMessage) {
            m_cMessage = (m_cMessage + " - " + getString(iError));
            
            if (bSaveToFile) {
                Logger::log(Logger::TYPE_ERROR, m_cMessage);
            } else {
                printIt(cMessage);
            }
        }
        Exceptions::Exceptions(const std::string &cMessage, bool bSaveToFile) : m_cMessage(cMessage) {
            if (bSaveToFile) {
                Logger::log(Logger::TYPE_ERROR, m_cMessage);
            } else {
                printIt(cMessage);
            }
        }
        Exceptions::Exceptions(const std::ostringstream &cMessage, bool bSaveToFile) : m_cMessage(cMessage.str().c_str()) {
            if (bSaveToFile) {
                Logger::log(Logger::TYPE_ERROR, m_cMessage);
            } else {
                printIt(cMessage.str());
            }
        }
        Exceptions::Exceptions(const char *cMessage, bool bSaveToFile) {
            m_cMessage = getString(cMessage);

            if (bSaveToFile) {
                Logger::log(Logger::TYPE_ERROR, m_cMessage);
            } else {
                printIt(cMessage);
            }
        }
        Exceptions::Exceptions(const unsigned char *cMessage, bool bSaveToFile) {
            m_cMessage = getString(cMessage);

            if (bSaveToFile) {
                Logger::log(Logger::TYPE_ERROR, m_cMessage);
            } else {
                printIt(cMessage);
            }
        }            

        const std::string &Exceptions::getMessage() const {
            return m_cMessage;
        }
    };
};
