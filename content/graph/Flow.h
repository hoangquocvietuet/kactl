/**
 * Description: flow algorithms
*/

## Disjoint paths

find maximum number paths

#### Edge-disjoint paths

It turns out that the maximum number of edge-disjoint paths equals the
maximum flow of the graph, assuming that the capacity of each edge is one. After
the maximum flow has been constructed, the edge-disjoint paths can be found
greedily by following paths from the source to the sink.

#### Node-disjoint paths

A standard method for this is to divide each node into two nodes such
that the first node has the incoming edges of the original node, the second node
has the outgoing edges of the original node, and there is a new edge from the first
node to the second node.

## Maximum matchings

#### Hall's theorem

Assume that we want to find a matching that contains all left nodes. Let X
be any set of left nodes and let f (X) be the set of their neighbors. According to
Hall’s theorem, a matching that contains all left nodes exists exactly when for
each X, the condition |X| ≤ |f (X)| holds

#### Kőnig’s theorem

A minimum node cover of a graph is a minimum set of nodes such that each
edge of the graph has at least one endpoint in the set. In a general graph, finding
a minimum node cover is a NP-hard problem. However, if the graph is bipartite,
Konig’s theorem ˝ tells us that the size of a minimum node cover and the size
of a maximum matching are always equal. Thus, we can calculate the size of a
minimum node cover using a maximum flow algorithm.

The nodes that do not belong to a minimum node cover form a maximum
independent set. This is the largest possible set of nodes such that no two
nodes in the set are connected with an edge

## Path covers

A path cover is a set of paths in a graph such that each node of the graph
belongs to at least one path

#### Node-disjoint path cover

We can find a minimum node-disjoint path cover by constructing a matching
graph where each node of the original graph is represented by two nodes: a left
node and a right node. There is an edge from a left node to a right node if there
is such an edge in the original graph. In addition, the matching graph contains a
source and a sink, and there are edges from the source to all left nodes and from
all right nodes to the sink.

Each edge in the maximum matching of the matching graph corresponds to
an edge in the minimum node-disjoint path cover of the original graph. Thus, the
size of the minimum node-disjoint path cover is n− c, where n is the number of
nodes in the original graph and c is the size of the maximum matching.

#### General path cover

A general path cover is a path cover where a node can belong to more than
one path

A minimum general path cover can be found almost like a minimum node-disjoint path cover. It suffices to add some new edges to the matching graph so that there is an edge a → b always when there is a path from a to b in the
original graph (possibly through several edges).

#### Dilworth’s theorem

An antichain is a set of nodes of a graph such that there is no path from any
node to another node using the edges of the graph. Dilworth’s theorem states
that in a directed acyclic graph, the size of a minimum general path cover equals
the size of a maximum antichain.