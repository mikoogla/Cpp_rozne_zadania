#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

template <typename T>
struct counter
{
public:
    static int objects_created;
    static int objects_alive;

    counter()
    {
        ++objects_created;
        ++objects_alive;
    }

    counter(const counter&)
    {
        ++objects_created;
        ++objects_alive;
    }
protected:
    ~counter()
    {
        --objects_alive;
    }
};
template <typename T> int counter<T>::objects_created( 0 );
template <typename T> int counter<T>::objects_alive( 0 );

class Point: counter<Point>{
public:
    float x = 0;
    float y = 0;

    void create()
    {
        cout<<"x:";
        cin>>x;
        cout<<"y:";
        cin>>y;
    }
    void create(float x_x, float y_y)
    {
        x = x_x;
        y = y_y;
    }
    void random()
    {
        x = rand()%10;
        y = rand()%10;
    }
    void view()
    {
        cout<<"("<<x<<", "<<y<<") \n";
    }
    Point operator+(Point k)
    {
        Point result;
        result.x = this->x + k.x;
        result.y = this->y + k.y;
        return result;
    }
    Point operator-(Point k)
    {
        Point result;
        result.x = this->x - k.x;
        result.y = this->y - k.y;
        return result;
    }
    Point operator*(int k)
    {
        Point result;
        result.x = this->x * (float)k;
        result.y = this->y * (float)k;
        return result;
    }
};

class Vector: counter<Vector>
{
public:
    Point A;
    Point B;
    Vector()
    {
        A.random();
        B.random();
    }
    Vector(float Ax, float Ay, float Bx, float By)
    {
        A.create(Ax, Ay);
        B.create(Bx, By);
    }
    ~Vector()
    {
        cout<<"\tZadanie wykonane\n";
    }
    void view()
    {
        cout<<"A: "; A.view();
        cout<<"B: "; B.view();
        cout<<"length: "<<length()<<"\n";
    }
    Vector operator+(Vector n)
    {
        Vector result;
        result.A = this->A + n.A;
        result.B = this->B + n.B;
        return result;
    }
    Vector operator-(Vector n)
    {
        Vector result;
        result.A = this->A - n.A;
        result.B = this->B - n.B;
        return result;
    }
    Vector operator*(int n)
    {
        Vector result;
        result.A = this->A * n;
        result.B = this->B * n;
        return result;
    }
    double length()
    {
        double length = pow(pow(B.x - A.x,2) + pow(B.y-A.y,2),0.5);
        return length;
    }
};

void current_state()
{
    printf("[Created points: %d\tVectors: %d]\n", counter<Point>::objects_created, counter<Vector>::objects_created);
    printf("[Active points: %d\tVectors: %d]\n", counter<Point>::objects_alive, counter<Vector>::objects_alive);
}

int main() {
    cout<<"_____points are generated randomly_____\n";
    srand(time(NULL));
    Vector v1, v2, result(0, 0, 0, 0);

    cout<<"_____v1:_____\n"; v1.view();
    cout<<"_____v2:_____\n"; v2.view();
    current_state();

    cout<<"_____v1 + v2:_____\n";
    result = v1+v2;
    result.view();
    current_state();

    cout<<"_____v1 - v2:_____\n";
    result = v1-v2;
    result.view();
    current_state();

    int random = rand()%20-10;

    cout<<"_____v1 * "<<random<<":_____\n";
    result = v1*random;
    result.view();
    current_state();

    return 0;
}