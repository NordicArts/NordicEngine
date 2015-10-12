#include <NordicEngine/Utility/NameGen.hpp>
#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/Files/Format/TextFile/Reader.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        NameGen::NameGen(int iSeed) : m_iSeed(iSeed) {
        }

        NameGen::~NameGen() {
        }

        void NameGen::generateLists() {
            Files::TextFile::Reader oVowels("GameFiles/Proc/Names/Vowels");
            oVowels.readFile();
            m_vVowels = oVowels.getContent();

            Files::TextFile::Reader oSyllables("GameFiles/Proc/Names/Syllables");
            oSyllables.readFile();
            m_vSyllables = oSyllables.getContent();

            Files::TextFile::Reader oLongVowels("GameFiles/Proc/Names/LongVowels");
            oLongVowels.readFile();
            m_vLongVowels = oLongVowels.getContent();

            Files::TextFile::Reader oConsonants("GameFiles/Proc/Names/Consonants");
            oConsonants.readFile();
            m_vConsonants = oConsonants.getContent();

            Files::TextFile::Reader oLongConsonants("GameFiles/Proc/Names/LongConsonants");
            oLongConsonants.readFile();
            m_vLongConsonants = oLongConsonants.getContent();

            Files::TextFile::Reader oBeginningSyllabals("GameFiles/Proc/Names/BeginningSyllabals");
            oBeginningSyllabals.readFile();
            m_vBeginningSyllables = oBeginningSyllabals.getContent();
        }

        std::string NameGen::getLetter(int iNum) {
            switch (iNum) {
                case 0: {
                    return getBeginningSyllable();
                }
                case 1: {
                    return getConsonant();
                }
                case 2: {
                    return getVowel();
                }
                case 3: {
                    return getSyllable();
                }
                case 4: {
                    return getLongVowel();
                }
                case 5: {
                    return getLongConsonant();
                }
                default: {
                    return "'";
                }
            }

            return "'";
        }

        std::string NameGen::generateName(int iLength) {
            std::string cName;
            int iRand;

            iRand = getRandom(0, 1, m_iSeed);
            cName.append(getLetter(iRand));

            for (int i = 0; i != (iLength - 1); i++) {
                iRand = getRandom(0, 6, m_iSeed);
                cName.append(getLetter(iRand));
            }

            return cName;
        }

        std::string NameGen::getBeginningSyllable() {
            return m_vBeginningSyllables.at(getRandom(0, m_vBeginningSyllables.size(), m_iSeed));
        }

        std::string NameGen::getConsonant() {
            return m_vConsonants.at(getRandom(0, m_vConsonants.size(), m_iSeed));
        }

        std::string NameGen::getVowel() {
            return m_vVowels.at(getRandom(0, m_vVowels.size(), m_iSeed));
        }

        std::string NameGen::getSyllable() {
            return m_vSyllables.at(getRandom(0, m_vSyllables.size(), m_iSeed));
        }

        std::string NameGen::getLongVowel() {
            return m_vLongVowels.at(getRandom(0, m_vLongVowels.size(), m_iSeed));
        }

        std::string NameGen::getLongConsonant() {
            return m_vLongConsonants.at(getRandom(0, m_vLongConsonants.size(), m_iSeed));
        }
    };
};
