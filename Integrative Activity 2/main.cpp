#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
// Find function
int find(vector<int> &parent, int x)
{
    if (parent[x] == x)
    {
        return x;
    }
    return find(parent, parent[x]);
}

// Union function
void Union(vector<int> &parent, int x, int y)
{
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// Kruskal's algorithm
void kruskal(vector<vector<int>> &graph)
{
    vector<int> parent(graph.size());

    int min = 0;
    int count = 0;
    for (int i = 0; i < graph.size(); i++)
    {
        parent[i] = i;
    }

    while (count < graph.size() - 1)
    {
        int min = INT32_MAX, a = -1, b = -1;
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph.size(); j++)
            {
                if (find(parent, i) != find(parent, j) && graph[i][j] < min)
                {
                    min = graph[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        Union(parent, a, b);

        cout << "(" << a << ", " << b << ")" << endl;

        count++;
    }
}

// Travelling Salesman Problem
void travelling_salesman(vector<vector<int>> &graph)
{
    vector<bool> visited(graph.size(), false);
    visited[0] = true;

    int value = 0;
    int current = 0;
    int prev = 0;
    cout << "0 -> ";
    for (int i = 1; i < graph.size(); i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            if (prev != j && !visited[j] && (graph[prev][j] < value || value == 0))
            {
                value = graph[prev][j];
                current = j;
            }
        }
        visited[current] = true;

        prev = current;
        cout << current << " -> ";
        value = 0;
    }
    cout << "0";
    cout << endl;
}

// BFS
bool bfs(vector<vector<int>> &rGraph, vector<int> &parent)
{
    int V = rGraph.size();
    vector<bool> visited(V, false);

    queue<int> q;
    q.push(0);
    visited[0] = true;
    parent[0] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[V - 1] == true);
}

void ford_fulkerson(vector<vector<int>> &graph)
{
    int u, v;

    int V = graph.size();

    vector<vector<int>> rGraph(V, vector<int>(V));

    for (u = 0; u < V; u++)
    {
        for (v = 0; v < V; v++)
        {
            rGraph[u][v] = graph[u][v];
        }
    }

    vector<int> parent(V);

    int max_flow = 0;

    while (bfs(rGraph, parent))
    {
        int path_flow = INT32_MAX;
        for (v = V - 1; v != 0; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = V - 1; v != 0; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    cout << max_flow << endl;
}

enum Orientation
{
    COLINEAR,
    CLOCKWISE,
    COUNTERCLOCKWISE
};

struct Point
{
    int x;
    int y;
};

Orientation getOrientation(Point p1, Point p2, Point p3)
{
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

    if (val == 0)
        return COLINEAR;
    return (val > 0) ? CLOCKWISE : COUNTERCLOCKWISE;
}

int distance(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

Point initialPoint;
void convex_hull(vector<Point> &points)
{

    int minY = points[0].y, min = 0;

    for (int i = 1; i < points.size(); i++)
    {
        int y = points[i].y;

        if ((y < minY) || (minY == y && points[i].x < points[min].x))
        {
            minY = points[i].y;
            min = i;
        }
    }

    Point temp = points[0];
    points[0] = points[min];
    points[min] = temp;

    initialPoint = points[0];

    sort(points.begin() + 1, points.end(), [](Point p1, Point p2)
         {
             Orientation orientation = getOrientation(initialPoint, p1, p2);

             if (orientation == COLINEAR)
                 return distance(initialPoint, p1) < distance(initialPoint, p2);
             return orientation == COUNTERCLOCKWISE; });

    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    for (int i = 3; i < points.size(); i++)
    {
        while (getOrientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != COUNTERCLOCKWISE)
        {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    for (int i = 0; i < hull.size(); i++)
    {
        cout << "(" << hull[i].x << ", " << hull[i].y << ")" << endl;
    }
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    vector<vector<int>> neighborhoods(n);
    vector<vector<int>> data_flow(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;
            if (temp == 0)
            {
                neighborhoods[i].push_back(INT32_MAX);
            }
            else
            {
                neighborhoods[i].push_back(temp);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;
            data_flow[i].push_back(temp);
        }
    }

    vector<Point> points(n);
    for (int i = 0; i < n; i++)
    {
        string point;
        cin >> point;
        point = point.substr(1, point.size() - 2);
        int comma = point.find(',');
        points[i].x = stoi(point.substr(0, comma));
        points[i].y = stoi(point.substr(comma + 1, point.size() - comma));
    }
    cout << "-- Kruskal's Algorithm --" << endl;
    kruskal(neighborhoods);
    cout << "-- Travelling Salesman --" << endl;
    travelling_salesman(neighborhoods);
    cout << "-- Ford-Fulkerson --" << endl;
    ford_fulkerson(data_flow);
    cout << "-- Convex Hull --" << endl;
    if (n < 3)
    {
        cout << "Convex Hull not possible" << endl;
        return 0;
    }
    convex_hull(points);
}
