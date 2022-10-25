#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
enum Method
{
    GREEDY,
    BACKTRACKING
};

int colors_max = 4;     // Maximum number of colors
Method method = GREEDY; // Method to use

void greedy_coloring(int n)
{
    vector<int> colors(n + 1, 0);        // Vector of colors
    vector<vector<int>> adj_list(n + 1); // Adjacency list

    // Instead of using an adjacency matrix, we use an adjacency list
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            if (x == 1)
            {
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }

    vector<bool> visited(n + 1, false); // Vector of visited nodes
    int current_color = 0;              // Current color

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            queue<int> q;
            q.push(i);

            while (!q.empty())
            {
                int current_node = q.front();
                q.pop();
                for (int neighbor : adj_list[current_node])
                {
                    if (colors[current_node] == colors[neighbor])
                    {
                        colors[neighbor]++;
                    }
                    current_color = max(current_color, max(colors[current_node], colors[neighbor]));

                    if (current_color > colors_max - 1)
                    {
                        cout << "No es posible asignar colores a los nodos" << endl;
                        return;
                    }

                    if (!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Node: " << i << ", Assigned Color: " << colors[i] << endl;
    }
}

bool backtracking_coloring(vector<vector<bool>> &adjMatrix, vector<int> &colors, int node = 0)
{
    if (node == adjMatrix.size())
    {
        return true;
    }

    for (int color = 0; color < colors_max; color++)
    {
        bool isValid = true;
        for (int i = 0; i < adjMatrix.size() - 1; i++)
        {
            if (adjMatrix[node][i] && colors[i] == color)
            {
                isValid = false;
                break;
            }
        }
        if (isValid)
        {
            colors[node] = color;
            if (backtracking_coloring(adjMatrix, colors, node + 1))
            {
                return true;
            }
            colors[node] = -1;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    // Optimizing cin and cout
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Parsing Arguments

    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-m")
        {
            if (string(argv[i + 1]) == "greedy")
            {
                method = GREEDY;
            }
            else if (string(argv[i + 1]) == "backtracking")
            {
                method = BACKTRACKING;
            }
            else
            {
                cerr << "Invalid method" << endl;
                return 1;
            }
        }
        else if (string(argv[i]) == "-c")
        {
            colors_max = stoi(argv[i + 1]);
        }
    }

    int n; // Number of nodes
    cin >> n;

    if (method == GREEDY)
    {
        greedy_coloring(n);
    }
    else
    {
        vector<vector<bool>> adjMatrix(n, vector<bool>(n, false));
        vector<int> colors(n, 0);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                int x;
                cin >> x;
                if (x == 1)
                {
                    adjMatrix[i][j] = true;
                    adjMatrix[j][i] = true;
                }
            }

        if (!backtracking_coloring(adjMatrix, colors))
        {
            cout << "No es posible asignar colores a los nodos" << endl;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                cout << "Node: " << i << ", Assigned Color: " << colors[i] << endl;
            }
        }
    }

    return 0;
}
