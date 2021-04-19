#include <iostream>
#include <Engine/Math/fastMath.h>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iostream>
#include<vector>
using namespace std;
using namespace std::chrono;

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
// C++ program to find out execution time of
// of functions




        // Get starting timepoint
        auto start = high_resolution_clock::now();

        // Call the function, here sort()
    for (long i = 0; i < 1000001; i++) {
        std::cout << fastMath::getDigitsInNumber(i);
    }

        // Get ending timepoint
        auto stop = high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get durarion. To cast it to proper unit
        // use duration cast method
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Time taken by function: "
             << duration.count() << " microseconds" << endl;

        return 0;

    return EXIT_SUCCESS;
}