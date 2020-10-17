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

	void BFS(int src = 0);
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

void Graph::BFS(int src) {
	vector<bool> visited(V, false);
	queue<int> q;
	q.push(src);
	visited[src] = true;

	while (!q.empty()) {
		auto item = q.front();
		cout << item << " ";
		q.pop();

		for (auto i : adj[item]) {
			if (!visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
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

	g.BFS(0);
}