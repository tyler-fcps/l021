#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <random>

using namespace std;

class Vector
{
public:
    double x, y;

    Vector() {}

    Vector(double x, double y) : x(x), y(y) {}

    double len()
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    Vector norm()
    {
        return *this / this->len();
    }

    double dot(Vector const &obj)
    {
        return this->x * obj.x + this->y * obj.y;
    }

    Vector operator+(Vector const &obj)
    {
        return Vector(this->x + obj.x, this->y + obj.y);
    }

    Vector operator-(Vector const &obj)
    {
        return Vector(this->x - obj.x, this->y - obj.y);
    }

    Vector operator/(double div)
    {
        return Vector(this->x / div, this->y / div);
    }
};

bool check_convex(Vector &p1, Vector &p2, Vector &p3, Vector &p4)
{
    Vector a, b, c;
    a = p3 - p1;
    b = (p2 - p1).norm();
    c = (p4 - p1).norm();

    return a.dot(b + c) >= 0;
}

int main()
{
    auto p = new Vector[4];

    // Generate random numbers
    random_device os_seed;
    mt19937 gen(os_seed());
    uniform_real_distribution<> xy(0, 1);

    for (int i = 0; i < 4; i++)
    {
        p[i] = Vector(xy(gen), xy(gen));
    }

    int i = 0;
    while (!check_convex(p[0], p[1], p[2], p[3]))
    {
        p[4] = Vector(xy(gen), xy(gen));
        cout << "Failed " << i << endl;
        i++;
    }

    // Create and open a text file
    ofstream out("points.txt");

    // Write data
    out << setprecision(17) << "("
        << p[0].x << "," << p[0].y << ") , ("
        << p[1].x << "," << p[1].y << ") , ("
        << p[2].x << "," << p[2].y << ") , ("
        << p[3].x << "," << p[3].y << ")" << endl;

    // Close the file
    out.close();
}