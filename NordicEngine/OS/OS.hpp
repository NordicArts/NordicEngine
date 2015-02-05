#ifndef NordicArts_NordicEngine_OS_H
#define NordicArts_NordicEngine_OS_H

#include <NordicEngine/Engine.hpp>

#define NA_INTERNAL 1

namespace NordicArts {
    // Signed Types
    typedef int8_t  int8;
    typedef int16_t int16;
    typedef int32_t int32;
    typedef int64_t int64;

    // UnSigned Types
    typedef uint8_t     uint8;
    typedef uint16_t    uint16;
    typedef uint32_t    uint32;
    typedef uint64_t    uint64;

    // Misc Types
    typedef int32   bool32;
    typedef float   real32;
    typedef double  real54;
    typedef size_t  memoryIndex;

    #define internal static
    #define localPersist static
    #define globalVariable static

    // Maths
    #ifndef PI32
        #define PI32 3.14159265359f
    #endif 

    // Custom Assert
    #if NA_SLOW
        #define Assert(Expression) if (!(Expression)) { *(int *)0 = 0; }
    #else
        #define Assert(Expression)
    #endif

    #ifndef InvalidCodePath
        #define InvalidCodePath Assert(!"InvalidCodePath");
    #endif

    // Sizes
    #ifndef Kilobytes
        #define Kilobytes(nValue) ((nValue) * 1024LL)
    #endif
    #ifndef Megabytes
        #define Megabytes(nValue) (Kilobytes(nValue) * 1024LL)
    #endif
    #ifndef Gigabytes
        #define Gigabytes(nValue) (Megabytes(nValue) * 1024LL)
    #endif
    #ifndef Terabytes
        #define Terabytes(nValue) (Gigabytes(nValue) * 1024LL)
    #endif

    #ifndef arrayCount
        #define arrayCount(aArray) (sizeof(aArray) / sizeof((aArray)[0]))
    #endif

    inline uint32 safeTruncateUInt64(uint64 iValue) {
        Assert(iValue <= 0xFFFFFFFF);

        uint32 iResult = (uint32)iValue;
        return iResult;
    }

    typedef struct threadContext {
        int iPlaceHolder;
    } threadContext;

    #if NA_INTERNAL
        typedef struct debugReadFileResult {
            uint32 iContentsSize;
            void *Contents;
        } debugReadFileResult;

        #ifndef DEBUG_PLATFORM_FREE_FILE_MEMORY
            #define DEBUG_PLATFORM_FREE_FILE_MEMORY(name) void name(threadContext *pThread, void *pMemory)
        #endif
        typedef DEBUG_PLATFORM_FREE_FILE_MEMORY(debugPlatformFreeFileMemory);

        #ifndef DEBUG_PLATFORM_READ_ENTIRE_FILE
            #define DEBUG_PLATFORM_READ_ENTIRE_FILE(name) debugReadFileResult name(threadContext *pThread, char *cFileName)
        #endif
        typedef DEBUG_PLATFORM_READ_ENTIRE_FILE(debugPlatformReadEntireFile);

        #ifndef DEBUG_PLATFORM_WRITE_ENTIRE_FILE
            #define DEBUG_PLATFORM_WRITE_ENTIRE_FILE(name) bool32 name(threadContext *pThread, char *cFileName, uint32 iMemorySize, void *pMemory)
        #endif
        typedef DEBUG_PLATFORM_WRITE_ENTIRE_FILE(debugPlatformWriteEntireFile);
    #endif

    typedef struct gameOffScreenBuffer {
        void *pMemory;
        int iWidth;
        int iHeight;
        int iPitch;
        int iBytesPerPixel;
    } gameOffScreenBuffer;

    typedef struct gameSoundOutputBuffer {
        int iSamplePerSecond;
        int iSampleCount;
        int16 *iSamples;
    } gameSoundOutputBuffer;

    typedef struct gameButtonState {
        int iHalfTransitionCount;
        bool32 bEndedDown;
    } gameButtonState;

    typedef struct gameControllerInput {
        bool32 bIsConnected;
        bool32 bIsAnalog;
        real32 fStickAverageX;
        real32 fStickAverageY;

        union {
            gameButtonState Buttons[12];
            struct {
                gameButtonState MoveUp;
                gameButtonState MoveDown;
                gameButtonState MoveLeft;
                gameButtonState MoveRight;

                gameButtonState ActionUp;
                gameButtonState ActionDown;
                gameButtonState ActionLeft;
                gameButtonState ActionRight;

                gameButtonState LeftShoulder;
                gameButtonState RightShoulder;

                gameButtonState Terminator;
            };
        };
    } gameControllerInput;

    typedef struct gameInput {
        gameButtonState sMouseButtons[5];
        int32 iMouseX;
        int32 iMouseY;
        int32 iMouseZ;

        real32 fDateTimeForFrame;

        gameControllerInput sControllers[5];
    } gameInput;

    typedef struct gameMemory {
        bool32 bIsInitalized;

        uint64 iPermanentStorageSize;
        void *pPermanentStorage;

        uint64 iTransientStorageSize;
        void *pTransientStorage;

        debugPlatformFreeFileMemory     *pDebugPlatformFreeFileMemory;
        debugPlatformReadEntireFile     *pDebugPlatformReadEntireFile;
        debugPlatformWriteEntireFile    *pDebugPlatformWriteEntireFile;
    } gameMemory;

    #ifndef GAME_UPDATE_AND_RENDER
        #define GAME_UPDATE_AND_RENDER(gameUpdateAndRender) void name(threadContext *pThread, gameMemory *pMemory, gameInput *pInput, gameOffScreenBuffer *pBuffer)
        typedef GAME_UPDATE_AND_RENDER(gameUpdateAndRender);
    #endif

    #ifndef GAME_GET_SOUND_SAMPLES
        #define GAME_GET_SOUND_SAMPLES(name) void name(threadContext *pThread, gameMemory *pMemory, gameSoundOutputBuffer *pSoundBuffer)
        typedef GAME_GET_SOUND_SAMPLES(gameGetSoundSamples);
    #endif

    inline gameControllerInput *getController(gameInput *pInput, int unsigned iControllerIndex) {
        Assert(iControllerIndex < arrayCount(pInput->sControllers));

        gameControllerInput *pResult = &pInput->sControllers[iControllerIndex];

        return pResult;
    }

    // Namespace OS stuff
    namespace NordicEngine {
    };
};

// OS Specific Includes
#if defined (__WIN32__) || defined(_WIN32) || defined(_WIN64)
    #include <NordicEngine/OS/Windows/Windows.hpp>
#else
    #define nonWindows

    #include <NordicEngine/OS/nonWindows/nonWindows.hpp>

    #if defined(__APPLE__) || defined(__APPLE_CC__)
        #include <NordicEngine/OS/nonWindows/OSX/OSX.hpp>
    #else
        #include <NordicEngine/OS/nonWindows/Linux/Linux.hpp>
    #endif
#endif

#endif
