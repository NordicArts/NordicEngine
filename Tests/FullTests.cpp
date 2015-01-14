#include "Main.hpp"
#include <NordicEngine/Player/Player.hpp>

TEST_CASE("Color", "[color]") {
    NordicArts::NordicEngine::Color oColor;

    SECTION("Create a Color") {
        
    }
}


TEST_CASE("Player", "[player]") {
    NordicArts::NordicEngine::Player  oPlayer;
    NordicArts::NordicEngine::Player *pPlayer = &oPlayer;

    pPlayer->setup();    
    pPlayer->setLife(16);
    pPlayer->addPlayer();

    REQUIRE(pPlayer->getLife() == 16);
}
