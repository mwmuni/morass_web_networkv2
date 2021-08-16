#pragma once

#include <vector>
#include "rand.h"

// #define rand_double(i, j) ((rand() % j + i) * 1.)
// #define rand_double(i) ((rand() % i) * 1.)

using std::vector;
using morassRandom::random;

namespace Node_ns
{
    struct Edge {
        unsigned int id;
        double edge_multiplier;
        double edge_fixed;
        unsigned int num_users = 0;
    };

    class Node
    {
        private:
        random* rand;
        unsigned int id {};
        double charge = 0.0;
        double threshold = 5.0;
        double temp_charge = 0.0;
        unsigned int timeout = 0;
        unsigned int TIMEOUT_WAIT = 3;
        vector<Edge*> outgoing; // Nodes do not manage the deletion of these edges
        double decay_multiplier {};
        double decay_fixed;

        public:
        Node(unsigned int id, random* rand) : id{id}, rand{rand}, decay_multiplier{rand->randDouble(0.1, 1.)}, decay_fixed{rand->randDouble(3.)}{};
        Node(unsigned int id, double decay_multiplier, double decay_fixed, random* rand) :
        id{id}, decay_multiplier{decay_multiplier}, decay_fixed{decay_fixed}{};
        ~Node() {};
        double pulse();
        void receive(double pulse);
        void decay();
        void assimilate();
        void add_edge(Edge*);
        bool add_unique_edge(Edge*);
        bool has_edge(unsigned int id);
        unsigned int get_id();
        vector<Edge*> get_edges();
    };
}