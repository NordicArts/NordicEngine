#include <NordicEngine/Engine.hpp>

namespace NordicArts {
    namespace NordicEngine {
        const char *getBuildNumber() {
            std::ostringstream output;
            output << NORDICARTS_NORDICENGINE_BUILDNUMBER;
            return output.str().c_str();
        }

        void throwError(const std::ostringstream &cMessage) {
            return throwError(cMessage.str().c_str());
        }
        void throwError(const std::string &cMessage) {
            throw Exception("Error Thrown: " + cMessage, true);
        }
        void throwError(const std::string &cFunction, const std::string &cMessage) {
            std::string cError = "Function: ";
            cError += cFunction;
            cError += ", ";
            cError += cMessage;

            throw Exception("Error Thrown in " + cError, true);
        }
    }
};
