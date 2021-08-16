#include <stdlib.h>
#include <iostream>
#include <vector>
#include "morassWeb.h"
// #include <chrono>

using MorassWeb_ns::MorassWeb;
// using std::chrono::high_resolution_clock;
// using std::chrono::microseconds;

#define print(str) std::cout << str << std::endl

int main() {
    // for (int i = 0; i < 100; i++) {
    //     MorassWeb* web = new MorassWeb();
    //     web->make_random_web();
    //     delete web;
    // }

    // high_resolution_clock time;

    MorassWeb* web = new MorassWeb();

    // auto start = time.now();
    web->make_random_web();
    web->init_input_node(0);
    // auto stop = time.now();

    // print("Random web creation took " << duration_cast<microseconds>(stop - start).count() << " microseconds");

    long long unsigned int total_pulses = 0;

    // start = time.now();
    for (int i = 0; i < 10; i++) {
        print("Step " << i+1 << " ---------------------------");
        web->inject(0, 5.);
        auto pulses = web->step();
        total_pulses += pulses.size();
        for (auto p : pulses) {
            print("Pulse from " << p.first.first << " to " << p.first.second << " was " << p.second);
        }
        print("---------------------------------");
        print("");
    }
    // stop = time.now();

    print("Total pulses: " << total_pulses);
    // print("Calculating pulses took " << duration_cast<microseconds>(stop - start).count() << " microseconds");

    return 0;
}