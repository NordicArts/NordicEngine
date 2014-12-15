#ifndef NordicArts_NordicEngine_Time_H
#define NordicArts_NordicEngine_Time_H

#include <NordicEngine/Engine.hpp>

// Time Defs
#ifndef NA_TIME
    #if defined(nonWindows)
        #define NA_TIME time_t
        #define NA_TIMEINFO tm
    #else
        #define NA_TIME SYSTEMTIME
        #define NA_TIMEINFO NULL
    #endif
#endif

namespace NordicArts {
    namespace NordicEngine {
        class Time {
        // Variables
        public:
        protected:
        private:
            NA_TIME m_oTime;
            NA_TIMEINFO *m_sTimeInfo;

            std::chrono::system_clock::time_point           m_tpSystemTime;
            std::chrono::system_clock::time_point           m_tpSystemTimeStart;
            std::chrono::system_clock::time_point           m_tpSystemTimeReset;

            std::chrono::high_resolution_clock::time_point  m_tpHighClock;
            std::chrono::high_resolution_clock::time_point  m_tpHighClockStart;
            std::chrono::high_resolution_clock::time_point  m_tpHighClockReset;

        // Methods
        public:
            Time();
            Time(NA_TIME &oTime);

            int getDay() const;
            int getMonth() const;
            int getYear() const;
            int getHour() const;
            int getMinute() const;
            int getSecond() const;
            int getMilliSecond() const;
            int getNanoSecond() const;

            float getMilliSeconds() const;
            float getNanoSeconds() const;

            float sinceStart() const;
            float sinceStartHigh() const;

            float reset();
            float resetHigh();

        protected:
        private:
        };
    };
};

#endif
