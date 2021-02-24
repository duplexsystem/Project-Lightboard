//
// Created by duplex on 2/20/21.
//

#ifndef PROJECT_LIGHTBOARD_RENDERMANAGER_H
#define PROJECT_LIGHTBOARD_RENDERMANAGER_H


class renderManager {
    public:
        static void initRender();

        static void pollRender();

        static void cleanupRender();
};


#endif //PROJECT_LIGHTBOARD_RENDERMANAGER_H
