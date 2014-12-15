#include <NordicEngine/ExceptionHandler/ExceptionHandler.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
/*
        ExceptionHandler::ExceptionHandler(const std::string &cMessage, int iError, bool bSaveToFile) : m_cMessage(cMessage) {
            m_cMessage = (m_cMessage + " - " + getString(iError));
            
            if (bSaveToFile) {
                Logger::log(Logger::TYPE_ERROR, m_cMessage);
            } else {
                std::cout << "Exception: " << cMessage.c_str() << std::endl;
                //printIt(cMessage);
            }
        }
*/

        ExceptionHandler::ExceptionHandler(const std::string &cMessage, bool bSaveToFile) : m_cMessage(cMessage) {
            if (bSaveToFile) {
                Logger::log(Logger::TYPE_ERROR, m_cMessage);
            } else {
                std::cout << "Exception: " << cMessage.c_str() << std::endl;
                //printIt(cMessage);
            }
        }

        ExceptionHandler::ExceptionHandler(const std::ostringstream &cMessage, bool bSaveToFile) : m_cMessage(cMessage.str().c_str()) {
            if (bSaveToFile) {
                Logger::log(Logger::TYPE_ERROR, m_cMessage);
            } else {
                std::cout << "Exception: " << cMessage.str().c_str() << std::endl;
                //printIt(cMessage.str());
            }
        }

        const std::string &ExceptionHandler::getMessage() const {
            return m_cMessage;
        }
    };
};
