//
// Created by duplex on 2/22/21.
//

#ifndef PROJECT_LIGHTBOARD_WINDOWMANAGER_H
#define PROJECT_LIGHTBOARD_WINDOWMANAGER_H


#include <cstdint>

class windowManager {
    public:
        static void initWindow();

        static const char** getWindowExtents(uint32_t);

        static void pollWindow();

        static bool shouldClose();

        static void cleanupWindow();
};


#endif //PROJECT_LIGHTBOARD_WINDOWMANAGER_H
