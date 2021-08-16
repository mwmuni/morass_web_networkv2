# Morass Web v2

The goal behind this rewrite was to make the Morass Web faster and more stable, with a slight difference in node pulsing philosophy.

Nodes no longer directly pass messages to each other, despite each node containing a list of connected nodes, these lists only contain the id of the connected node rather than the memory address.

IDs are no longer updated upon deletion of edges. The edge vector is not indexed using edge IDs.

## Biologically inspired additions

- Nodes now have a cooldown after firing, and will ignore pulses during cooldown.
- Nodes can now share outgoing edges.
- Unused edges are now pruned.
- Pulse strength is fixed in the edge.

## Planned components

- Edges will have an `edge_health` which will decrease as negative feedback is received, and increased as positive feedback is received. Edges with 0 `edge_health` will be removed from all nodes.
  - Positive feedback is defined as a target neuron firing soon after a pulse.
  - Negative feedback is defined as a target neuron failing to fire after ~2 steps.
  - Positive and negative feedback can be also transmitted using backpropagation-through-time
- Neurons will either locally (traversal radius) or globally have states
  - Formation state; will send out new connections randomly.
  - Supressing state; will alter the rate of decay.
  - Wildcard state; will change the edge value to another predefined value during this state.
- Network 'dreaming'; will repeatedly give previous inputs to network and allow neurons to fire without backpropagating error, allowing for natural pruning and strengthening of connections. 


# Morass Web

The Morass Web Network is a threshold-gated propagation network. Each step, the potential of a node will be checked against the activation threshold and will fire if the potential meets or exceeds the threshold, pulsing to all connected neighbours.

The v2 of this model has a different goal for learning; connections will be strengthened and destroyed based on the usefulness of edges in addition to backpropagating error, with both targeting the `edge_health` of edges. An edge that loses all of its health is removed.