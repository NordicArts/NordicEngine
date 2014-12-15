#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        const char *getBuildNumber() {
            std::ostringstream output;
            output << NORDICENGINE_BUILDNUMBER;
            return output.str().c_str();
        }
    }
};
