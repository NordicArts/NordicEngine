#include <NordicEngine/OS/nonWindows/OSX/OSX.hpp>

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>

namespace NordicArts {
    namespace NordicEngine {
        std::string OSSpecific::getPath(std::string cFileName) {
            return getResourcePath(cFileName);
        }

        std::string OSSpecific::getResourcePath(std::string cFileName) {
            NSString* pFileName     = [NSString stringWithCString: cFileName.c_str() encoding:NSUTF8StringEncoding];
            NSString* pPath         = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent: pFileName];

            return std::string([pPath cStringUsingEncoding: NSUTF8StringEncoding]);
        }

        bool OSSpecific::deleteFile(std::string cFileName) {
            if (remove(cFileName.c_str()) != 0) {
                return false;
            }

            return true;
        }
    };
};
