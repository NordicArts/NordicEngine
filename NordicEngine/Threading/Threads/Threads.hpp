//
//  Threads.h
//  NordicEngine
//
//  Created by Max Hooton on 31/08/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicEngine_Threading_Threads_H
#define NordicArts_NordicEngine_Threading_Threads_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        // Mutex Thread
        #ifndef MUTEX_THREAD
            #if defined(nonWindows)
                #define MUTEX_THREAD pthread_mutex_t
            #else
                #define MUTEX_THREAD HANDLE
            #endif
        #endif
        
        // NA Critical
        #ifndef NA_CRITICAL
            #if defined(nonWindows)
                #define NA_CRITICAL pthread_mutex_t
            #else
                #define NA_CRITICAL CRITICAL_SECTION
            #endif
        #endif
        
        // Mutex
        int mutexInit(MUTEX_THREAD *pMutex);
        int mutexLock(MUTEX_THREAD *pMutex);
        int mutexUnLock(MUTEX_THREAD *pMutex);
        
        // Block Thread
        class BlockThread final {
        // Variables
        public:
        protected:
        private:
            NA_CRITICAL m_Critical;
            
        // Methods
        public:
            explicit BlockThread(NA_CRITICAL &oCritical);
            ~BlockThread();
            
        protected:
        private:
            
        };
        
        // Critical Section
        void createCritical(NA_CRITICAL &oCritical);
        void enterCritical(NA_CRITICAL &oCritical);
        void leaveCritical(NA_CRITICAL &oCritical);
        void deleteCritical(NA_CRITICAL &oCritical);
        
        // Block Process
        class BlockProcess final {
        // Variables
        public:
            MUTEX_THREAD m_pMutex;
            
        protected:
        private:
            std::string m_cName;
            
        // Methods
        public:
            explicit BlockProcess(const std::string &cName);
            ~BlockProcess();
            
            bool isBlocked();
            
        protected:
        private:
            BlockProcess(const BlockProcess &cConst);
            
        };
    };
};

#endif
