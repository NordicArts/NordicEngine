#include "Main.hpp"
#include <NordicEngine/Player/Player.hpp>

TEST_CASE("Player", "[player]") {
    NordicArts::NordicEngine::Player  oPlayer;
    NordicArts::NordicEngine::Player *pPlayer = &oPlayer;
    
    pPlayer->setLife(16);
    REQUIRE(pPlayer->getLife() == 16);
}
