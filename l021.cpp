#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <random>

using namespace std;

class Point
{
public:
    double x, y;

    Point(double x, double y) : x(x), y(y) {}

    Point()
    {
        // Generate random numbers
        random_device os_seed;
        mt19937 generator(os_seed());
        uniform_real_distribution<> distribute_xy(0, 1);

        x = distribute_xy(generator);
        y = distribute_xy(generator);
    }
};

bool check_convex(Point &p1, Point &p2, Point &p3, Point &p4)
{
    return false;
}

int main()
{
    auto ps = new Point[4];

    for (int i = 0; i < 4; i++)
    {
        ps[i] = Point();
    }

    for (int i = 0; i < 4; i++)
    {
        if (!check_convex(ps[(i + 0) % 4], ps[(i + 1) % 4], ps[(i + 2) % 4], ps[(i + 3) % 4]))
        {
            ps[i] = Point();
        }
    }

    // Create and open a text file
    ofstream out("points.txt");

    // Write data
    // out << setprecision(17) << "("
    //     << p1->x << "," << p1->y << ") , ("
    //     << p2->x << "," << p2->y << ") , ("
    //     << p3->x << "," << p3->y << ") , ("
    //     << p4->x << "," << p4->y << ")" << endl;

    // Close the file
    out.close();
}