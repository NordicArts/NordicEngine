#include "Main.hpp"
#include <NordicEngine/Player/Player.hpp>
#include <NordicEngine/Color/Color.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Shaders/Simple.hpp>

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

TEST_CASE("Settings", "[settings]") {
    NordicArts::NordicEngine::Settings oSettings;
    oSettings.setup();

    SECTION("Window Mode") {
        oSettings.setWindowMode(true);
        
        REQUIRE(oSettings.isWindowed() == true);
    }

    SECTION("Resolution") {
        oSettings.setResolutionVerbose(1920, 1080);

        REQUIRE(oSettings.getResolutionWidth() == 1920);
        REQUIRE(oSettings.getResolutionHeight() == 1080);
    }

    SECTION("FSAA") {
        oSettings.setFSAA(16);

        REQUIRE(oSettings.getFSAA() == 16);
    }

    SECTION("VSync") {
        oSettings.setVSync(true);

        REQUIRE(oSettings.getVSync() == true);
    }

    SECTION("OpenGL") {
        oSettings.setOpenGLVerbose(4, 9);
    
        REQUIRE(oSettings.getOpenGLMajor() == 4);
        REQUIRE(oSettings.getOpenGLMinor() == 9);
    }

    SECTION("FOV") {
        oSettings.setFOV(45);

        REQUIRE(oSettings.getFOV() == 45);
        REQUIRE(oSettings.getFOVCalc() == 90);
    }
}


TEST_CASE("Player", "[player]") {
    NordicArts::NordicEngine::Player  oPlayer;

    oPlayer.setup();    
    oPlayer.addPlayer();

    SECTION("Set Life") {
        oPlayer.setLife(16);

        REQUIRE(oPlayer.getLife() == 16);
    }

    SECTION("Increase Life") {
        oPlayer.setLife(16);
        oPlayer.incrementLife();

        REQUIRE(oPlayer.getLife() == 17);
    }

    SECTION("Decrease Life") {
        oPlayer.setLife(16);
        oPlayer.decrementLife();
        
        REQUIRE(oPlayer.getLife() == 15);
    }
}

TEST_CASE("Shaders", "[shaders]") {
//    NordicArts::NordicEngine::Shaders::Simple oShaders;
    
//    oShaders.LoadShaders("GameFiles/Shaders/Simple.vertex", "GameFiles/Shaders/Simple.fragment");
}

TEST_CASE("Should Fail", "[forcedFailer]") {
    REQUIRE(true == false);
}
