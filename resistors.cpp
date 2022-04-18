#include <iostream>
#include <cmath>

using namespace std;

class Resistor {
private:
    double resistance;
public:
    Resistor() {
        resistance = 0;
    }

    explicit Resistor(double input) {
        resistance = input;
    }

    double r() const {
        return resistance;
    }

    void r(double input) {
        resistance = input;
    }

    friend Resistor operator+(Resistor, Resistor);

    friend Resistor operator*(Resistor, Resistor);

    friend ostream &operator<<(ostream &, Resistor);
};

Resistor operator+(Resistor r1, Resistor r2) {
    Resistor result;
    result.r(r1.r() + r2.r());
    return result;
}

Resistor operator*(Resistor r1, Resistor r2) {
    Resistor result;
    result.r(1 / r1.r() + 1 / r2.r());
    result.r(pow(result.r(), -1));
    return result;
}

ostream &operator<<(ostream &Out, const Resistor input) {
    Out << "Resistance: " << input.r() << endl;
    return Out;
}

int main() {

    Resistor r1(12), r2(10);
    Resistor r3 = r1 + r2;
    cout << r3;
    r3 = r1 * r2;
    cout << r3;
    return 0;
}