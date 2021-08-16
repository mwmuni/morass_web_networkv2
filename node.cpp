
#include "node.h"

using namespace Node_ns;

double Node::pulse() {
    if (timeout == 0 && potential >= threshold) {
        double pulsed_amount = potential;
        potential = 0.0;
        timeout = TIMEOUT_WAIT;
        return pulsed_amount;
    }
    else {
        timeout = (timeout > 0) ? (timeout-1) : 0;
    }
    return 0.0;
}

void Node::receive(double pulse) {
    if (timeout == 0)
        temp_potential += pulse;
}

void Node::decay() {
    double result = potential * decay_multiplier - decay_fixed;
    if (result < 0.0) {
        potential = 0.0;
    } else {
        potential = result;
    }
}

void Node::assimilate() {
    potential += temp_potential;
    temp_potential = 0.0;
}

bool Node::has_edge(unsigned int id) {
    for (Edge* e : outgoing) {
        if (id == e->id)
            return true;
    }
    return false;
}

void Node::add_edge(Edge* node) {
    outgoing.emplace_back(node);
}

bool Node::add_unique_edge(Edge* node) {
    bool found_existing = false;
    for (auto e : outgoing) {
        if (e->id == node->id) {
            found_existing = true;
            break;
        }
    }
    if (!found_existing)
        outgoing.emplace_back(node);
    return found_existing;
}

void Node::set_decay(double fixed, double multiplier) {
    decay_fixed = fixed;
    decay_multiplier = multiplier;
}

vector<Edge*> Node::get_edges() {
    return outgoing;
}

unsigned int Node::num_outgoing_edges() {
    return outgoing.size();
}

unsigned int Node::get_id() {
    return id;
}