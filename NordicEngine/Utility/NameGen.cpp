#include <NordicEngine/Utility/NameGen.hpp>
#include <NordicEngine/Utility/Maths.hpp>
#include <NordicEngine/NordicEngine/Files/Format/TextFile/Reader.hpp>

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

        std::string NameGen::generateName(int iLength) {
            std::string cName;

            for (int i = 0; i != iLength; i++) {
                int iRand = getRandom(0, 6, m_iSeed);

                switch (iRand) {
                    case 0: {
                        cName.append(getBeginningSyllable());
                        break;
                    }

                    case 1: {
                        cName.append(getConsonant());
                        break;
                    }

                    case 2: {
                        cName.append(getVowel());
                        break;
                    }

                    case 3: {
                        cName.append(getSyllable());
                        break;
                    }

                    case 4: {
                        cName.append(getLongVowel());
                        break;
                    }

                    case 5: {
                        cName.append(getLongConsonant());
                        break;
                    }

                    case 6:
                    default: {
                        cName.append("'");
                        break;
                    }
                }
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