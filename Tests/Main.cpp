#include "Main.hpp"

TEST_CAST("Player", "[player]") {
    NordicEngine::Player  oPlayer;
    NordicEngine::Player *pPlayer = &oPlayer;
    
    pPlayer->setLife(16);
    REQUIRE(pPlayer->getLife(), 16);
}
