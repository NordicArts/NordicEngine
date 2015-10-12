#ifndef NordicArts_NordicEngine_NameGen_H
#define NordicArts_NordicEngine_NameGen_H

#include <NordicEngine/Includes.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class NameGen {
        // Variables
        public:
        protected:
        private:
            int m_iSeed;

            std::vector<std::string> m_vVowels;
            std::vector<std::string> m_vLongVowels;

            std::vector<std::string> m_vSyllables;
            std::vector<std::string> m_vBeginningSyllables;

            std::vector<std::string> m_vConsonants;
            std::vector<std::string> m_vLongConsonants;


        // Methods
        public:
            NameGen(int iSeed);
            ~NameGen();

            void generateLists();

            std::string generateName(int iLength);
        protected:
        private:
            std::string getBeginningSyllable();
            std::string getConsonant();
            std::string getVowel();
            std::string getSyllable();
            std::string getLongVowel();
            std::string getLongConsonant();
            std::string getLetter(int iLetter);            

        };
    };
};

#endif
