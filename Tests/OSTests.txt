#include "Main.hpp"
#include <NordicEngine/Storage/Storage.hpp>

TEST_CAST("Storage" "[storage]") {
    NordicArts::NordicEngine::Storage oStorage;
    
    REQUIRE(oStorage.deleteDatabase() == true);
}
