// STL implementation of Dijkstra algorithm for Shortest paths (single source all other vertices) 
#include <iostream> 
#include <vector>
#include <queue>

using namespace std;
# define INF 0x3f3f3f3f 

// iPair ==> Integer Pair 
typedef pair<int, int> iPair;

// This class represents a directed graph using 
// adjacency list representation 
class Graph
{
	int V; // No. of vertices 

	// In a weighted graph, we need to store vertex 
	// and weight pair for every edge 
	vector<vector< iPair>> adj;

public:
	Graph(int V); // Constructor 

	// function to add an edge to graph 
	void addEdge(int u, int v, int w);

	// Print MST using Prim's algorithm 
	void shortestPath(int src = 0);
};

// Allocates memory for adjacency list 
Graph::Graph(int V)
{
	this->V = V;
	adj.resize(V);
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	//adj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices - Dijkstra algorithm
void Graph::shortestPath(int src)
{
	// Create a priority queue to store vertices that 
	// are being preinMST. This is weird syntax in C++. 
	// Refer below link for details of this syntax 
	// http://geeksquiz.com/implement-min-heap-using-stl/ 
	priority_queue< iPair, vector <iPair>, greater<iPair>> pq;

	vector<int> dist(V, INF);

	// Insert source itself in priority queue and initialize 
	// its key as distance(weight). 
	pq.push(make_pair(0, src));
	dist[src] = 0;

	/* Looping till priority queue becomes empty */
	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		for (auto it = adj[u].begin(); it != adj[u].end(); ++it)
		{
			int v = it->first;
			int weight = it->second;

			if (weight + dist[u] < dist[v])
			{
				dist[v] = weight + dist[u];
				pq.push(make_pair(weight, v));
			}
		}
	}

	// Print edges of MST using parent array 
	for (int i = 0; i < V; ++i)
		printf("%d - %d\n", i, dist[i]);

}

// Driver program to test methods of graph class 
int main()
{
	// create the graph given in above fugure 
	int V = 4; // 9
	Graph g(V);

	// making above shown graph 
	/*g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);*/

	g.addEdge(0, 1, 8);
	g.addEdge(0, 2, 0);
	g.addEdge(1, 2, 1);
	g.addEdge(0, 3, 99);
	g.addEdge(3, 1, -300);

	g.shortestPath(0);

	return 0;
}
