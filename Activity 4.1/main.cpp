#include <iostream>
#include <vector>

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

class LineSegment
{
public:
    LineSegment(Point p1, Point p2)
    {
        this->p1 = p1;
        this->p2 = p2;
    }

    Point p1;
    Point p2;

    Orientation getOrientation(Point p)
    {
        int val = (p2.y - p1.y) * (p.x - p2.x) - (p2.x - p1.x) * (p.y - p2.y);

        if (val == 0)
            return COLINEAR;
        return (val > 0) ? CLOCKWISE : COUNTERCLOCKWISE;
    }

    bool onSegment(Point p)
    {
        if (p.x <= max(p1.x, p2.x) && p.x >= min(p1.x, p2.x) && p.y <= max(p1.y, p2.y) && p.y >= min(p1.y, p2.y))
            return true;
        return false;
    }

    bool doesItIntersect(LineSegment l)
    {
        Orientation o1 = getOrientation(l.p1);
        Orientation o2 = getOrientation(l.p2);
        Orientation o3 = l.getOrientation(p1);
        Orientation o4 = l.getOrientation(p2);

        if (o1 != o2 && o3 != o4)
            return true;

        if (o1 == COLINEAR && onSegment(l.p1))
            return true;

        if (o2 == COLINEAR && onSegment(l.p2))
            return true;

        if (o3 == COLINEAR && l.onSegment(p1))
            return true;

        if (o4 == COLINEAR && l.onSegment(p2))
            return true;

        return false;
    }
};

int main(int argc, char const *argv[])
{

    int n;
    cin >> n;

    for (int i = 0; i < n / 4; i++)
    {
        Point p1, p2, p3, p4;
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;

        LineSegment line1(p1, p2);
        LineSegment line2(p3, p4);

        if (line1.doesItIntersect(line2))
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }

    return 0;
}
