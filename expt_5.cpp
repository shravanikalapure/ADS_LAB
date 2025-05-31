#include <iostream>

using namespace std;
#define MAX 100
#define INF 1000000000 // Large value to represent infinity

class SupplyChain {
    int locations;
    int graph[MAX][MAX];

public:
    SupplyChain(int loc) {
        locations = loc;
        for (int i = 0; i < loc; i++) {
            for (int j = 0; j < loc; j++) {
                graph[i][j] = (i == j) ? 0 : INF;
            }
        }
    }

    void addRoute(int u, int v, int distance) {
        graph[u][v] = distance;
        graph[v][u] = distance; // Undirected graph
    }

    int findMinDistance(int dist[], bool visited[]) {
        int min = INF, minIndex = -1;
        for (int i = 0; i < locations; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i], minIndex = i;
            }
        }
        return minIndex;
    }

    void dijkstra(int src) {
        int dist[MAX];
        bool visited[MAX] = {false};
        
        for (int i = 0; i < locations; i++) {
            dist[i] = INF;
        }
        dist[src] = 0;

        for (int count = 0; count < locations - 1; count++) {
            int u = findMinDistance(dist, visited);
            if (u == -1) break;
            visited[u] = true;

            for (int v = 0; v < locations; v++) {
                if (!visited[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        cout << "Shortest distances from source:\n";
        for (int i = 0; i < locations; i++) {
            cout << "To location " << i << " -> Distance: " << (dist[i] == INF ? -1 : dist[i]) << "\n";
        }
    }
};

int main() {
    int locations, routes;
    cout << "Enter number of locations: ";
    cin >> locations;
    SupplyChain sc(locations);

    cout << "Enter number of routes: ";
    cin >> routes;
    cout << "Enter routes (start end distance):\n";
    for (int i = 0; i < routes; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        sc.addRoute(u, v, d);
    }

    int source;
    cout << "Enter source location: ";
    cin >> source;
    sc.dijkstra(source);
    
    return 0;
}