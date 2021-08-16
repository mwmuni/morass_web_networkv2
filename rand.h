#pragma once
#include <random>
#include <time.h>

namespace morassRandom {
class random {
    private:
    std::uniform_int_distribution<int> dist;
    std::uniform_real_distribution<double> doubleDist;
    std::mt19937_64 rng;
    // std::random_device rd;

    public:
    random() {
        rng = std::mt19937_64(time(NULL));
        dist = std::uniform_int_distribution<int>(0, INT_MAX);
        doubleDist = std::uniform_real_distribution<double>();
    }

    int rand() {
        return dist(rng);
    }

    int rand(int upto) {
        return rand() % upto;
    }

    int rand(int from, int upto) {
        return (rand() % (upto - from)) + from;
    }

    double randDouble() {
        return doubleDist(rng);
    }

    double randDouble(double upto) {
        return randDouble() * upto;
    }

    double randDouble(double from, double upto) {
        return (randDouble() * (upto - from)) + from;
    }
};
}