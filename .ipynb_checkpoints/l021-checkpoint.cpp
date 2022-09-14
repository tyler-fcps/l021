#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <random>

using namespace std;

class Point {
    public:
        double x, y;

    Point(double x, double y): x(x), y(y) {}

    Point() {
        // Generate random numbers
        random_device os_seed;
        mt19937 generator(os_seed());
        uniform_real_distribution<> distribute_xy(0, 1);

        x = distribute_xy(generator);
        y = distribute_xy(generator);
    }
};

double sign(Point * p1, Point * p2, Point * p3) {
    return (p1 -> x - p3 -> x) * (p2 -> y - p3 -> y) - (p2 -> x - p3 -> x) * (p1 -> y - p3 -> y);
}

bool PointInTriangle(Point * pt, Point * v1, Point * v2, Point * v3) {
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

int main() {
    Point * p1, * p2, * p3;
    p1 = new Point();
    p2 = new Point();
    p3 = new Point();

    Point * p4 = new Point();
    while (PointInTriangle(p4, p1, p2, p3)) {
        p4 = new Point();
    }
    
    // Create and open a text file
    ofstream out("points.txt");

    // Write data
    out << setprecision(17) << "(" 
        << p1->x << "," << p1->y << ") , ("
        << p2->x << "," << p2->y << ") , ("
        << p3->x << "," << p3->y << ") , ("
        << p4->x << "," << p4->y << ")" << endl;

    // Close the file
    out.close();
}