#include <NordicEngine/Time/Time.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Time::Time() {
            m_tpSystemTime      = std::chrono::system_clock::now();
            m_tpSystemTimeStart = m_tpSystemTime;
            m_tpSystemTimeReset = m_tpSystemTime;

            m_tpHighClock       = std::chrono::high_resolution_clock::now();
            m_tpHighClockStart  = m_tpHighClock;
            m_tpHighClockReset  = m_tpHighClock;
        }

        Time::Time(NA_TIME &oTime) {
            m_oTime = oTime;

            #if defined(nonWindows)
                time(&m_oTime);
                m_sTimeInfo = localtime(&m_oTime);
            #else
                GetLocalTime(m_oTime);
            #endif
        }

        float Time::sinceStart() const {
            return std::chrono::nanoseconds(std::chrono::system_clock::now() - m_tpSystemTimeStart).count();
        }
        float Time::sinceStartHigh() const {
            return std::chrono::nanoseconds(std::chrono::high_resolution_clock::now() - m_tpHighClockStart).count();
        }

        float Time::reset() {
            float ret = std::chrono::nanoseconds(std::chrono::system_clock::now() - m_tpSystemTimeReset).count();

            m_tpSystemTimeReset = std::chrono::system_clock::now();

            return ret;
        }
        float Time::resetHigh() {
            float ret = std::chrono::nanoseconds(std::chrono::high_resolution_clock::now() - m_tpHighClockReset).count();

            m_tpHighClockReset = std::chrono::high_resolution_clock::now();    
            
            return ret;
        }

        int Time::getDay() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_mday;
            #else
                return m_oTime.wDay;
            #endif

            return -1;
        }

        int Time::getMonth() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_mon;
            #else
                return m_oTime.wMonth;
            #endif

            return -1;
        }


        int Time::getYear() const {
            #if defined(nonWindows)
                return (1900 + m_sTimeInfo->tm_year);
            #else
                return m_oTime.wYear;
            #endif

            return -1;
        }

        int Time::getHour() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_hour;
            #else
                return m_oTime.wHour;
            #endif

            return -1;
        }

        int Time::getMinute() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_min;
            #else
                return m_oTime.wMinute;
            #endif

            return -1;
        }

        int Time::getSecond() const {
            #if defined(nonWindows)
                return m_sTimeInfo->tm_sec;
            #else
                return m_oTime.wSecond;
            #endif

            return -1;
        }

        int Time::getMilliSecond() const {
            std::chrono::milliseconds timeDuration  = std::chrono::duration_cast<std::chrono::milliseconds>(m_tpHighClock.time_since_epoch());
            return (int)timeDuration.count();
        }

        int Time::getNanoSecond() const {
            std::chrono::nanoseconds timeDuration   = std::chrono::duration_cast<std::chrono::nanoseconds>(m_tpHighClock.time_since_epoch());
            return (int)timeDuration.count();
        }

        float Time::getMilliSeconds() const {
            std::chrono::milliseconds timeDuration  = std::chrono::duration_cast<std::chrono::milliseconds>(m_tpHighClock.time_since_epoch());
            return timeDuration.count();
        }

        float Time::getNanoSeconds() const {
            std::chrono::nanoseconds timeDuration   = std::chrono::duration_cast<std::chrono::nanoseconds>(m_tpHighClock.time_since_epoch());
            return timeDuration.count();
        }
    };
};
