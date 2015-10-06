#ifndef NordicArts_Game_Seeder_H
#define NordicArts_Game_Seeder_H

#include <NordicEngine/Includes.hpp>
#include <NordicEngine/Time/Time.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Seeder {
        // Variables
        public:
        protected:
        private:
            int m_iSeed;

        // Methods
        public:
            Seeder();
            ~Seeder();

            int getSeed() const;
            int getSeedTime() const;
            int getSeedTime(NordicEngine::Time *pTime) const;

            void setSeed(std::string cSeed);
            void setSeed(int iSeed);

        protected:
        private:
            int getCommand(const char cChar);
            int getCharacter(const char cChar);

        };
    };
};

#endif
