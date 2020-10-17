#include <iostream> 
#include <vector>
#include <queue>

using namespace std;

class Graph
{
	int V; // No. of vertices 

	vector<vector<int>> adj;

public:
	Graph(int V);

	void addEdge(int u, int v);

	void DFS(int src = 0);

private:
	void DFSUtil(int v, vector<bool>& visited);
};

Graph::Graph(int V)
{
	this->V = V;
	adj.resize(V);
}

void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void Graph::DFSUtil(int v, vector<bool>& visited) {
	cout << v << " ";
	visited[v] = true;
	for (auto i : adj[v]) {
		if (!visited[i]) {
			DFSUtil(i, visited);
		}
	}
}
//T: O(V + E)
void Graph::DFS(int src) {
	vector<bool> visited(V, false);
	DFSUtil(src, visited); // start from source vertex
	// Handling Disconnected Graph
	for (int v = 0; v < V; v++) {
		if (!visited[v])
			DFSUtil(v, visited);
	}
	
}

int main() {
	int V = 5;
	Graph g(V);

	g.addEdge(0, 1);
	g.addEdge(0, 4);
	g.addEdge(1, 4);
	g.addEdge(2, 1);
	g.addEdge(2, 3);
	g.addEdge(3, 1);
	g.addEdge(3, 4);

	g.DFS(2);
}