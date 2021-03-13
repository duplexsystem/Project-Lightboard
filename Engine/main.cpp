#include <iostream>
#include <Engine/Math/fastMath.h>
#include "Render/renderManager.h"

void init() {
    renderManager::initRender();
}

void poll() {
    renderManager::pollRender();
}

void cleanup() {
    renderManager::cleanupRender();
}

int main() {
    try {
        init();
        poll();
        cleanup();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}