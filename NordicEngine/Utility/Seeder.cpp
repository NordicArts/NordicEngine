#include <NordicEngine/Utility/Seeder.hpp>
#include <NordicEngine/String/String.hpp>

namespace NordicArts {
    namespace NordicEngine {
        Seeder::Seeder() {
        }

        Seeder::~Seeder() {
        }
    
        int Seeder::getCommand(const char cChar) {
            std::string cResult = getString(cChar);

            // Characters
            std::string cSpace = " "; 
            std::string cDash = "-"; 
            std::string cUnder = "_"; 
            std::string cPlus = "+"; 
            std::string cEquals = "="; 
            std::string cStar = "*"; 
            std::string cBackSlash = "\\"; 
            std::string cForwardSlash = "/"; 
            std::string cExplination = "!"; 
            std::string cDollar = "$"; 
            std::string cPercentage = "%";
            std::string cHat = "^";
            std::string cLeftParenthesis = "(";
            std::string cRightParenthesis = ")";
            std::string cDot = ".";
            std::string cColon = ":";
            std::string cSemiColon = ";";
            std::string cCurlLeft = "{";
            std::string cCurlRight = "}";
            std::string cLeftBraket = "[";
            std::string cRightBraket = "]";
            std::string cHash = "#";
            std::string cAt = "@";
            std::string cPipe = "|";
            std::string cLeft = "<";
            std::string cRight = ">";
            std::string cQuestion = "?";
            std::string cComma = ",";

            // Matches Times
            if (cResult.compare(cSpace) == 0) { return 1; }
            if (cResult.compare(cStar) == 0) { return 1; }
            if (cResult.compare(cExplination) == 0) { return 1; }
            if (cResult.compare(cLeftParenthesis) == 0) { return 1; }
            if (cResult.compare(cSemiColon) == 0) { return 1; }
            if (cResult.compare(cRightBraket) == 0) { return 1; }
            if (cResult.compare(cLeft) == 0) { return 1; }

            // Matches Divide
            if (cResult.compare(cBackSlash) == 0) { return 2; }
            if (cResult.compare(cForwardSlash) == 0) { return 2; }
            if (cResult.compare(cDollar) == 0) { return 2; }
            if (cResult.compare(cRightParenthesis) == 0) { return 2; }
            if (cResult.compare(cCurlLeft) == 0) { return 2; }
            if (cResult.compare(cHash) == 0) { return 2; }
            if (cResult.compare(cRight) == 0) { return 2; }

            // Matches Minus
            if (cResult.compare(cDash) == 0) { return 3; }
            if (cResult.compare(cUnder) == 0) { return 3; }
            if (cResult.compare(cPercentage) == 0) { return 3; }
            if (cResult.compare(cDot) == 0) { return 3; }
            if (cResult.compare(cCurlRight) == 0) { return 3; }
            if (cResult.compare(cAt) == 0) { return 3; }
            if (cResult.compare(cQuestion) == 0) { return 3; }

            // Matches Plus
            if (cResult.compare(cPlus) == 0) { return 4; }
            if (cResult.compare(cEquals) == 0) { return 4; }
            if (cResult.compare(cHat) == 0) { return 4; }
            if (cResult.compare(cColon) == 0) { return 4; }
            if (cResult.compare(cLeftBraket) == 0) { return 4; }
            if (cResult.compare(cComma) == 0) { return 4; }
            if (cResult.compare(cPipe) == 0) { return 4; }

            // Not Matched
            return 0;
        }

        int Seeder::getCharacter(const char cChar) {
            std::string cResult = getString(cChar);

            // LowerCase
            if (cResult.compare(std::string("a")) == 0) { return 1; }
            if (cResult.compare(std::string("b")) == 0) { return 2; }
            if (cResult.compare(std::string("c")) == 0) { return 3; }
            if (cResult.compare(std::string("d")) == 0) { return 4; }
            if (cResult.compare(std::string("e")) == 0) { return 5; }
            if (cResult.compare(std::string("f")) == 0) { return 6; }
            if (cResult.compare(std::string("g")) == 0) { return 7; }
            if (cResult.compare(std::string("h")) == 0) { return 8; }
            if (cResult.compare(std::string("i")) == 0) { return 9; }
            if (cResult.compare(std::string("j")) == 0) { return 10; }
            if (cResult.compare(std::string("k")) == 0) { return 11; }
            if (cResult.compare(std::string("l")) == 0) { return 12; }
            if (cResult.compare(std::string("m")) == 0) { return 13; }
            if (cResult.compare(std::string("n")) == 0) { return 14; }
            if (cResult.compare(std::string("o")) == 0) { return 15; }
            if (cResult.compare(std::string("p")) == 0) { return 16; }
            if (cResult.compare(std::string("q")) == 0) { return 17; }
            if (cResult.compare(std::string("r")) == 0) { return 18; }
            if (cResult.compare(std::string("s")) == 0) { return 19; }
            if (cResult.compare(std::string("t")) == 0) { return 20; }
            if (cResult.compare(std::string("u")) == 0) { return 21; }
            if (cResult.compare(std::string("v")) == 0) { return 22; }
            if (cResult.compare(std::string("w")) == 0) { return 23; }
            if (cResult.compare(std::string("x")) == 0) { return 24; }
            if (cResult.compare(std::string("y")) == 0) { return 25; }
            if (cResult.compare(std::string("z")) == 0) { return 26; }

            // UpperCase
            if (cResult.compare(std::string("A")) == 0) { return 27; }
            if (cResult.compare(std::string("B")) == 0) { return 28; }
            if (cResult.compare(std::string("C")) == 0) { return 29; }
            if (cResult.compare(std::string("D")) == 0) { return 30; }
            if (cResult.compare(std::string("E")) == 0) { return 31; }
            if (cResult.compare(std::string("F")) == 0) { return 32; }
            if (cResult.compare(std::string("G")) == 0) { return 33; }
            if (cResult.compare(std::string("H")) == 0) { return 34; }
            if (cResult.compare(std::string("I")) == 0) { return 35; }
            if (cResult.compare(std::string("J")) == 0) { return 36; }
            if (cResult.compare(std::string("K")) == 0) { return 37; }
            if (cResult.compare(std::string("L")) == 0) { return 38; }
            if (cResult.compare(std::string("M")) == 0) { return 39; }
            if (cResult.compare(std::string("N")) == 0) { return 40; }
            if (cResult.compare(std::string("O")) == 0) { return 41; }
            if (cResult.compare(std::string("P")) == 0) { return 42; }
            if (cResult.compare(std::string("Q")) == 0) { return 43; }
            if (cResult.compare(std::string("R")) == 0) { return 44; }
            if (cResult.compare(std::string("S")) == 0) { return 45; }
            if (cResult.compare(std::string("T")) == 0) { return 46; }
            if (cResult.compare(std::string("U")) == 0) { return 47; }
            if (cResult.compare(std::string("V")) == 0) { return 48; }
            if (cResult.compare(std::string("W")) == 0) { return 49; }
            if (cResult.compare(std::string("X")) == 0) { return 50; }
            if (cResult.compare(std::string("Y")) == 0) { return 51; }
            if (cResult.compare(std::string("Z")) == 0) { return 52; }

            return 53;
        }

        void Seeder::setSeed(std::string cSeed) {
            int iSeed = 1;

            int iCommand;

            for (size_t i = 0; i != cSeed.length(); ++i) {
                iSeed += getCharacter(cSeed.at(i));

                iCommand = getCommand(cSeed.at(i));
                switch (iCommand) {
                    case 1: {
                        iSeed += (iSeed * 10);
                        break;
                    }
                    case 2: {
                        iSeed += (iSeed / 10);
                        break;
                    }
                    case 3: {
                        iSeed += (iSeed - 10);
                        break;
                    }
                    case 4: {
                        iSeed += (iSeed + 10);
                    }
                    default: {
                        break;
                    }
                }    
            }

            setSeed(iSeed);
        }

        void Seeder::setSeed(int iSeed) {
            m_iSeed = iSeed;
        }

        int Seeder::getSeed() const {
            return m_iSeed;
        }

        int Seeder::getSeedTime() const {
            int iSeedTime;

            NordicEngine::Time oTime;
            NordicEngine::Time *pTime = &oTime;

            iSeedTime = (int)pTime->sinceStartHigh();
            iSeedTime += m_iSeed;

            return iSeedTime;
        }

        int Seeder::getSeedTime(NordicEngine::Time *pTime) const {
            return (m_iSeed + (int)pTime->sinceStart());
        }
    };
};
