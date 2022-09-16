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

bool in_triangle(Vector &p0, Vector &p1, Vector &p2, Vector &p3)
{
    auto sign = [](Vector &p1, Vector &p2, Vector &p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    };

    double l1, l2, l3;
    l1 = sign(p0, p1, p2);
    l2 = sign(p0, p2, p3);
    l3 = sign(p0, p3, p1);

    bool neg, pos;
    neg = (l1 < 0) || (l2 < 0) || (l3 < 0);
    pos = (l1 > 0) || (l2 > 0) || (l3 > 0);

    return !neg || !pos;
}

void part1()
{
    // Open log
    ofstream log("log.txt");
    // Make vecs
    auto p = new Vector[4];
    // Generate random numbers
    random_device os_seed;
    mt19937 gen(os_seed());
    uniform_real_distribution<> xy(0, 1);
    // Printing lambda
    auto print_vec = [&](auto vec)
    { log << "(" << vec.x << ", " << vec.y << ")"; };

    log << "Inital Points: ";
    for (int i = 0; i < 4; i++)
    {
        p[i] = Vector(xy(gen), xy(gen));
        log << "p" << i << " = ";
        print_vec(p[i]);
        log << ", ";
    }
    log << endl;

    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        while (in_triangle(p[(i + 0) % 4], p[(i + 1) % 4], p[(i + 2) % 4], p[(i + 3) % 4]))
        {
            log << "Failed (" << count << "), point p" << i << " is inside the rest" << endl;
            p[3] = Vector(xy(gen), xy(gen));
            log << "New p3 is ";
            print_vec(p[3]);
            log << endl;
            count++;
            i = 0;
        }
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
    log.close();
}

int main()
{
    part1();
}