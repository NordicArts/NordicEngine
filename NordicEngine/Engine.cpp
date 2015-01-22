#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        const char *getBuildNumber() {
            std::ostringstream output;
            output << NORDICENGINE_BUILDNUMBER;
            return output.str().c_str();
        }

        void throwError(const std::ostringstream &cMessage) {
            return throwError(cMessage.str().c_str());
        }
        void throwError(const std::string &cMessage) {
            throw Exception("Error Thrown: " + cMessage, true);
        }
    }
};
