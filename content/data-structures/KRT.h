/**
 * Author: DeMen100ns
 * Date: 2023
 * License: CC0
 * Description: Kruskal Reconstruction Tree
 *
 * Suppose you are given a weighted (connected) undirected graph of $N$ vertices and $M$ edges. 
 * Let's define an ordering of the edges, for example, the edges are ordered in the ascending/descending order of their weights. The reachability tree can help you with: \\
 * - Find the minimal/maximal weight of the edges when traversing from vertex $𝑢$ to vertex $𝑣$ \\
 * - Find the set of vertices that are reachable from a given vertex using the first $x$ edges, for some arbitrary $x$. 
 * You can store some information in this set of reachable vertices, such as the maximum value or the sum of values of all the reachable vertices.
 */

int getRoot(int u) {
  if (u == dsu[u]) return u;
  return dsu[u] = getRoot(dsu[u]);
}

void addEdge(int u, int v) {
  u = getRoot(u); v = getRoot(v);

  dsu[n] = n;
  dsu[u] = dsu[v] = n;

  adj[n].push_back(u);
  if (u != v) adj[n].push_back(v);

  ++n;
}
