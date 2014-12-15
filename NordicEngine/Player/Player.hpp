#ifndef NordicArts_NordicEngine_Player_H
#define NordicArts_NordicEngine_Player_H

#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Player {
        // Variables   
        public:
        protected:
        private:
            int m_iLife;
        
            std::string m_cName;

        // Methods
        public:
            Player();
            Player(int iLife);

            void setName(std::string cName);
            std::string getName() const;

            void setLife(int iLife);
            int getLife() const;
            
            int incrementLife();
            int incrementLife(int iLife);
            
            int decrementLife();
            int decrementLife(int iLife);

            bool isAlive() const;
            bool alive() const;

        protected:
        private:

        };
    };
};

#endif
