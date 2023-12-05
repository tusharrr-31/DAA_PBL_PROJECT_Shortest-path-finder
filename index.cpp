#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const int INF = std::numeric_limits<int>::max();

class Graph {
public:
    int vertices;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;

    Graph(int v) : vertices(v), adjacencyList(v) {}

    void addEdge(int u, int v, int weight) {
        adjacencyList[u].emplace_back(v, weight);
        adjacencyList[v].emplace_back(u, weight); // Uncomment for directed graph
    }

    std::vector<int> dijkstra(int start);
};

std::vector<int> Graph::dijkstra(int start) {
    std::vector<int> distance(vertices, INF);
    distance[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& neighbor : adjacencyList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}

int main() {
    Graph graph(6);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 3, 2);
    graph.addEdge(4, 5, 5);

    int startNode = 0;
    std::vector<int> shortestDistances = graph.dijkstra(startNode);

    std::cout << "Shortest Distances from Node " << startNode << ":\n";
    for (int i = 0; i < shortestDistances.size(); ++i) {
        std::cout << "Node " << i << ": " << shortestDistances[i] << "\n";
    }

    return 0;
}
