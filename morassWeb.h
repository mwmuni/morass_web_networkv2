#pragma once

#include <vector>
#include "node.h"
#include "rand.h"

using Node_ns::Node;
using Node_ns::Edge;
using std::vector;
using std::pair;
using morassRandom::random;

namespace MorassWeb_ns {
    class MorassWeb {
        private:
        random rand;
        vector<Edge*> edges;
        vector<Node*> nodes;
        void decay();
        void assimilate();

        public:
        MorassWeb() {};
        ~MorassWeb();
        //? pair<from_id, to_id, pulse>
        vector<pair<pair<unsigned int, unsigned int>, double>> step();
        void inject(int node_id, double amount);
        void make_random_web();
    };
}