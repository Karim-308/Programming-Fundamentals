#include <iostream>
using namespace std;
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Triangle.h"

int main() {
    Circle c(5);
    cout << "Circle area: " << c.area() << "\n";

    Rectangle r(3, 4);
    cout << "Rectangle area: " << r.area() << "\n";

    Square s(2);
    cout << "Square side: " << s.getSide() << ", area: " << s.area() << "\n";

    Triangle t(3, 6);
    cout << "Triangle area: " << t.area() << "\n";

    return 0;
}
