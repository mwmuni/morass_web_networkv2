
#include "morassWeb.h"
#include <random>
#include <iostream>
#include "time.h"


using namespace MorassWeb_ns;
using Node_ns::Edge;

#define print(str) std::cout << str << std::endl

void MorassWeb::make_random_web() {
    // std::srand(time(NULL));
    unsigned int NUM_NODES = 100;
    unsigned int NUM_EDGES = 100;
    for (unsigned int i = 0; i < NUM_NODES; i++) {
        nodes.emplace_back(new Node(i, &rand));
    }
    for (unsigned int i = 0; i < NUM_EDGES; i++) {
        edges.emplace_back(new Edge({0, rand.randDouble(-1., 4.), rand.randDouble(-1., 4.)}));
    }

    for (auto e : edges) {
        e->id = rand.rand() % nodes.size();
    }

    unsigned int MAX_ATTEMPTS = 10;
    unsigned int attempts = 0;
    bool edge_added = false;
    Edge* curr_rand_edge = nullptr;
    for (auto n : nodes) {
        int num_connections = rand.rand() % 4 + 1;
        for (int i = 0; i < num_connections; i++) {
            while (!edge_added && attempts < MAX_ATTEMPTS) {
                while ((curr_rand_edge = edges[rand.rand() % nodes.size()])->id == n->get_id()) {}
                edge_added = !n->add_unique_edge(curr_rand_edge);
                edge_added ? curr_rand_edge->num_users++ : 0;
                attempts++;
            }
            if (attempts == MAX_ATTEMPTS) {
                i--;
            }
            attempts = 0;
            edge_added = false;
        }
    }

    print(edges.size());
    
    for (int i = edges.size()-1; i >= 0; i--) {
        if (edges[i]->num_users == 0) {
            auto tmp = edges[i];
            edges.erase(edges.begin()+i);
            delete tmp;
        }
    }

    print(edges.size());

    print("Web Created");
}

vector<pair<pair<unsigned int, unsigned int>, double>> MorassWeb::step() {
    double pulsed;
    double pulse_amount;
    vector<pair<pair<unsigned int, unsigned int>, double>> all_pulses;

    for (auto n : nodes) {
        pulsed = n->pulse();
        if (pulsed != 0.0) {
            // TODO: Can keep track of what neurons fired, and to which neurons
            for (auto e : n->get_edges()) {
                pulse_amount = (pulsed + e->edge_fixed) * e->edge_multiplier;
                nodes[e->id]->receive(pulse_amount);
                all_pulses.emplace_back(pair<pair<unsigned int, unsigned int>, double>(
                                              pair<unsigned int, unsigned int>(n->get_id(), e->id),
                                                                                pulse_amount));
            }
        }
    }

    assimilate();
    decay();

    return all_pulses;
}

void MorassWeb::assimilate() {
    for (auto n : nodes) {
        n->assimilate();
    }
}

void MorassWeb::decay() {
    for (auto n : nodes) {
        n->decay();
    } 
}

// Will not increase charge if node is on cooldown
void MorassWeb::inject(int id, double amount) {
    nodes[id]->receive(amount);
    nodes[id]->assimilate();
}

MorassWeb::~MorassWeb() {
    for (auto n : nodes) {
        delete n;   
    }
    for (auto e : edges) {
        delete e;
    }
    nodes.clear();
    edges.clear();
}