//
//  Log.cpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 7/28/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#include "Tools.hpp"

#ifdef WINDOWS
#define INFO_ICON "HEARTH"
#else
#define INFO_ICON "💚"
#endif

enum LogType {
    
    LogTypeInfo,
    LogTypeWarning,
    LogTypeError
};

string logTypeString(LogType type) {
    
    switch (type) {
        case LogTypeInfo:    return INFO_ICON + string(" INFO ") + INFO_ICON;
        case LogTypeWarning: return "💛 WARNING 💛";
        case LogTypeError:   return "❤️ ERROR ❤️";
    }
}

void log(string message, string file, string function, int line, LogType type) {
    
    auto fileName = StringTools::fileName(file);
    
    cout << "[" << logTypeString(type) << "] [" << fileName << "::" << function << " - " << line << "] " << message << endl;
}

void Log::info(string message, string file, string function, int line) {
        
    log(message, file, function, line, LogTypeInfo);
}

void Log::warning(string message, string file, string function, int line) {
    
    log(message, file, function, line, LogTypeWarning);
}

void Log::error(string message, string file, string function, int line) {
    
    log(message, file, function, line, LogTypeError);
}
