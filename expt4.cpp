#include <iostream>
#include <queue>

using namespace std;

#define MAX 100  // Maximum number of departments
#define INF 1000000000  // Large value to represent infinity

class Graph {
    int V;
    int adjMatrix[MAX][MAX];

public:
    Graph(int V) {
        this->V = V;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adjMatrix[i][j] = (i == j) ? 0 : INF;
            }
        }
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void primMST() {
        int key[MAX];
        int parent[MAX];
        bool inMST[MAX] = {false};
        
        for (int i = 0; i < V; i++) key[i] = INF, parent[i] = -1;
        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = -1;
            for (int i = 0; i < V; i++) {
                if (!inMST[i] && (u == -1 || key[i] < key[u])) {
                    u = i;
                }
            }

            inMST[u] = true;
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "Minimum Spanning Tree (MST):\n";
        for (int i = 1; i < V; i++) {
            cout << "Department " << parent[i] << " - " << i << " (Distance: " << key[i] << ")\n";
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of departments: ";
    cin >> V;
    Graph campus(V);

    cout << "Enter number of connections: ";
    cin >> E;

    cout << "Enter connections (department1 department2 distance):\n";
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        campus.addEdge(u, v, weight);
    }

    campus.primMST();
    
    return 0;
}
