#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

void dijkstra(vector<vector<int>> graph, int src)
{
    vector<int> dist(graph.size(), INT16_MAX);
    vector<bool> visited(graph.size(), false);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        for (int v = 0; v < graph.size(); v++)
        {
            if (graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < graph.size(); i++)
        if (src + 1 != i + 1)
            cout << "node " << src + 1 << " to node " << i + 1 << " : " << ((dist[i] == INT16_MAX) ? "INF" : to_string(dist[i])) << endl;
}

// Floyd-Warshall's algorithm
void floydWarshall(vector<vector<int>> graph)
{
    vector<vector<int>> dist(graph.size(), vector<int>(graph.size()));

    for (int i = 0; i < graph.size(); i++)
        for (int j = 0; j < graph.size(); j++)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < graph.size(); k++)
    {
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph.size(); j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j] && dist[i][k] != INT16_MAX && dist[k][j] != INT16_MAX)
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            cout << ((dist[i][j] == INT16_MAX) ? "INF" : to_string(dist[i][j])) << " ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; // Size of matrix (n x n)
    cin >> n;

    vector<vector<int>> adjmatrix(n, vector<int>(n, INT16_MAX)); // Adjacency matrix initialized with INT16_MAX
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            if (x != -1)
                adjmatrix[i][j] = x;
        }
    }
    cout << "Dijkstra: " << endl;
    for (int i = 0; i < n; i++)
    {
        dijkstra(adjmatrix, i);
    }
    cout << endl
         << "Floyd: " << endl;
    floydWarshall(adjmatrix);

    return 0;
}
