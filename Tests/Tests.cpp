#include "Main.hpp"
#include <NordicEngine/Storage/Storage.hpp>
#include <NordicEngine/Color/Color.hpp>

TEST_CASE("Storage" "[storage]") {
    NordicArts::NordicEngine::Storage  oStorage;
    
    REQUIRE(oStorage.destroyDatabase() == true);
}

TEST_CASE("Color", "[color]") {
    SECTION("Create Black Color") {
        NordicArts::NordicEngine::Color oColor(0, 0, 0);

        REQUIRE(oColor == NordicArts::NordicEngine::Color::Black);
    }


    SECTION("Create Magenta Color") {
        NordicArts::NordicEngine::Color oColor(255, 0, 255);

        REQUIRE(oColor == NordicArts::NordicEngine::Color::Magenta);    
    }


    SECTION("Hex Color") {
        NordicArts::NordicEngine::Color oColor("#648a87");

        REQUIRE(oColor.getRed() == 100);        
        REQUIRE(oColor.getGreen() == 138);
        REQUIRE(oColor.getBlue() == 135);
    }
}

