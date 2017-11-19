/* We have a sparse graph with, possibly, negative edges. We want to compute the all-pairs shortest path. Floyd Warshall may be too slow.
Algorithm: 
1) A new node q is added to the graph, connected by zero-weight edges to each of the other nodes.
2) Bellman–Ford algorithm is used, starting from the new vertex q, to find for each vertex v the minimum weight h(v) of a path from q to v. 
If this step detects a negative cycle, the algorithm is terminated as the shortest-path is undefined.
3) edges of the original graph are reweighted using the values computed by the Bellman–Ford algorithm: 
an edge from u to v, having length w(u,v), is given the new length w(u,v) + h(u) − h(v).
4) q is removed, and Dijkstra's algorithm is used to find the shortest paths from each node s to every other vertex in the reweighted graph.
5) Dijkstra from every node. The shortest path in this new graph is the same as in the initial graph although it's weight changes.
The idea is to do dijkstra by storing "weight in new graph" and "weight in old graph" sorting by the first one.
