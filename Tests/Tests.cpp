#include "Main.hpp"
#include <NordicEngine/Storage/Storage.hpp>

TEST_CASE("Storage" "[storage]") {
    NordicArts::NordicEngine::Storage  oStorage;
    
    REQUIRE(oStorage.destroyDatabase() == true);
}
