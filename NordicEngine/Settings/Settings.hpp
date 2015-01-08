#ifndef NordicArts_NordicEngine_Settings_H
#define NordicArts_NordicEngine_Settings_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Storage/Storage.hpp>
#include <NordicEngine/Files/Handler/Lua/Lua.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Settings {
        // Variables
        public:
        protected:
        private:
            unsigned int    m_iPhysicsRefreshRate;
            
            int8_t          m_iFSAA;

            int16_t         m_iRandomNumberSeed;

            bool            m_bWindowMode;
            bool            m_bStatsLogging;
            bool            m_bVSync;
        
            glm::uvec2      m_vResolution;
            glm::uvec2      m_vOpenGL;

            float           m_fFOV;

            Storage        *m_pStorage;

            std::string     m_cGameName;

        // Methods
        public:
            Settings();
            Settings(std::string cGameName);

            virtual ~Settings();

            void setRandomSeed(int16_t iSeed);
            int16_t getRandomSeed() const;

            void setGameName(std::string cName);
            std::string getGameName() const;

            void setWindowMode(bool bWindow);
            void setStats(bool bStats);
            void setFOV(float fFOV);
            void setVSync(bool bVSync);
            void setOpenGL(const glm::uvec2 &vOpenGL);
            void setFSAA(int8_t iFSAA);
            void createTable();

            double getPhysicsRefresh() const;

            const glm::uvec2 getResolution() const;

            bool getVSync() const;
            bool isWindowed() const;

            float getFOV() const;
            
            int8_t getFSAA() const;

            static void registerLua(Lua *pLua);

        protected:
        private:
            void setDefaults();

        };
    };
};

#endif
