#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Exception/Exception.hpp>
#include <NordicEngine/Files/Loader.hpp>
#include <NordicEngine/Threading/Threads/Threads.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        static Logger *s_pLogger = nullptr;

        Logger::Logger(std::string cFile) : Singleton(TYPE_LOGGER), m_ulFileLength(0), m_cUnknownLogType("UNKNOWN") {
            m_aLogTypes[0] = "Info";
            m_aLogTypes[1] = "Warning";
            m_aLogTypes[2] = "Error";

            // File Length
            m_ulFileLength = m_cUnknownLogType.size();
            for (const std::string &cType : m_aLogTypes) {
                if (m_ulFileLength < cType.size()) {
                    m_ulFileLength = cType.size();
                }
            }

            // Set the logfile to have a log filetype
            std::size_t nFound = cFile.find(".log");
            if (nFound == std::string::npos) { cFile += ".log"; }
            m_cLogFile = cFile;

            createCritical(m_Critical);
            BlockThread blockThread(m_Critical);
    
            Files::Loader oFile(m_cLogFile, false, false, false);

            s_pLogger = this;
        }

        Logger::~Logger() {
            destroy();
        }

        void Logger::destroy() {
            SAFE_DELETE(s_pLogger);

            deleteCritical(m_Critical);
        }

        // Logger polymorph
        void Logger::log(const char *cLog) {
            log(Logger::TYPE_INFO, cLog);
        }
        void Logger::log(std::string cLog) {
            log(cLog.c_str());
        }
        void Logger::log(float fLog) {
            log(getString(fLog).c_str());
        }
        void Logger::log(int iUnknown, const char *cLog) {
            log(static_cast<LoggerType>(iUnknown), cLog);
        }
        void Logger::log(LoggerType eLogType, const std::string &cLog) {
            log(eLogType, cLog.c_str());
        }
        void Logger::log(LoggerType eLogType, const std::ostringstream &cLog) {
            log(eLogType, cLog.str().c_str());
        }

        // Real Logger
        void Logger::log(LoggerType eLogType, const char *cLog) {
            if (s_pLogger == nullptr) {
                char *cError;
                std::sprintf(cError, "Logger not started, %s", cLog);

                printIt(cError);
            
                return;
            }

            BlockThread oBlockThread(s_pLogger->m_Critical);

            std::ostringstream cStream;
            cStream << std::setfill(' ') << std::setw((int)s_pLogger->m_ulFileLength);

            try {
                cStream << s_pLogger->m_aLogTypes.at(eLogType);
            } catch( ... ) {
                cStream << s_pLogger->m_cUnknownLogType;
            }

            NA_TIME sTime;
            Time oTime(sTime);
    
            // Output the time
            cStream << " [ " << oTime.getYear() << "/";
            cStream << std::setfill('0') << std::setw(2) << oTime.getMonth() << "/";
            cStream << std::setfill('0') << std::setw(2) << oTime.getDay() << " ";
            cStream << std::setfill(' ') << std::setw(2) << oTime.getHour() << ":";
            cStream << std::setfill('0') << std::setw(2) << oTime.getMinute() << ":";
            cStream << std::setfill('0') << std::setw(2) << oTime.getSecond() << ".";
            cStream << std::setfill('0') << std::setw(5) << oTime.getMilliSeconds() << "] ";

            // Message
            cStream << cLog << std::endl;

            // Write to file
            try {
                Files::Loader oFile(s_pLogger->m_cLogFile, true, true, false);
                oFile.write(cStream.str());
            } catch( ... ) {
                char *cError;
                std::sprintf(cError, "%s using logger failed to write, %s", __FUNCTION__, cStream.str().c_str());

                printIt(cError);
            }
        }
    };
};
