//
// Created by Max Hooton on 09/10/15.
//

#ifndef NordicArts_NordicEngine_Markov_H
#define NordicArts_NordicEngine_Markov_H

#include <NordicEngine/Includes.hpp>
#include <NordicEngine/Logger/Logger.hpp>

//#include <boost/locale.hpp>

namespace NordicArts {
    namespace NordicEngine {
        class Markov {
        // Variables
        public:
        protected:
        private:
            std::map<std::string, double>                           m_mFirstLetterChance;
            std::map<std::string, double>                           m_mLastLetterChance;

            std::map<std::string, std::map<std::string, double> >   m_mLetterToLetterChance;

            std::vector<std::string>                                m_vNames;

            char                                                    m_cAlphabet[28]     = "abcdefghijklmnopqrstuvqwxyz";
            float                                                   m_fVariance         = 0.0f;

            std::string                                             m_cNamesList;

            Logger                                                  *m_pLogger           = nullptr;
            bool                                                    m_bDebug;

        // Methods
        public:
            Markov();
            Markov(Logger *pLogger);
            virtual ~Markov();

            std::string generateWord();
            std::string generateWord(int iSeed);

            void generate();
            void setVariance(float fVariance);
            void setNamesList(std::string cNamesList);

        protected:
        private:
            void fillNameList();

            void generateFirstLetterMap();
            void generateLastLetterMap();
            void generateLetterToLetterMap();

            std::map<std::string, double> getAlphabetMap();

            //std::locale m_pLocale;

        };
    };
};


#endif
