// Graham's Scan
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

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

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    if (n < 3)
    {
        cout << "Convex Hull not possible" << endl;
        return 0;
    }

    vector<Point> points(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    int minY = points[0].y;

    int minIndex = 0;

    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;
        if (y < minY || (y == minY && points[i].x < points[minIndex].x))
        {
            minY = y;
            minIndex = i;
        }
    }

    Point temp = points[0];
    points[0] = points[minIndex];
    points[minIndex] = temp;

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

    for (int i = 3; i < n; i++)
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

    return 0;
}
