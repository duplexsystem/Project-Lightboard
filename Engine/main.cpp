#include <iostream>
#include <Engine/Math/fastMath.h>
#include <bitset>
#include <cmath>

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
//    try {
//        init();
//        poll();
//        cleanup();
//    } catch (const std::exception& e) {
//        std::cerr << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }

    for (int i = 0; i < 20000; i++) {
        std::cout << i << std::endl << fastMath::getDigitsInNumber(i) << std::endl << std::endl;
    }

    return EXIT_SUCCESS;
}