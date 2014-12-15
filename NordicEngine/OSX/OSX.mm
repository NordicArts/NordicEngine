#include <Nordicengine/OSX/OSX.hpp>

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>

namespace NordicArts {
    namespace NordicEngine {
        std::string OSSpecific::ResourcePath(std::string cFileName) {
            NSString* pFileName     = [NSString stringWithCString: cFileName.c_str() encoding:NSUTF8StringEncoding];
            NSString* pPath         = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent: pFileName];

            return std::string([pPath cStringUsingEncoding: NSUTF8StringEncoding]);
        }
    };
};
