#ifndef NordicArts_NordicEngine_Player_H
#define NordicArts_NordicEngine_Player_H

#include <NordicEngine/Engine.hpp>
#include <NordicEngine/Files/Handler/Lua/Lua.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Player {
        // Variables   
        public:
        protected:
        private:
            int m_iLife;

            bool m_bSetupDone;
        
            std::string m_cName;
            std::string m_cGameName;

        // Methods
        public:
            Player();
            Player(std::string cGameName);
            Player(int iLife);

            void setup();
            void setupGame(std::string cGameName);

            void setName(std::string cName);
            std::string getName() const;

            void setLife(int iLife);
            int getLife() const;
            
            int incrementLife();
            int incrementLifeAmount(int iLife);
            
            int decrementLife();
            int decrementLifeAmount(int iLife);

            bool isAlive() const;
            bool alive() const;

            std::string getDetails() const;

            static void registerLua(Lua *pLua);

        protected:
        private:

        };
    };
};

#endif
