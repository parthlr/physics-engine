#include <iostream>
#include "TransformObject.h"
#include "polygons/Rectangle.h"
#include "Physics.h"

int main() {
    Rectangle rect1(1, 1);
    Rectangle rect2(1, 1);
    Polygon* poly1 = &rect1;
    Polygon* poly2 = &rect2;
    TransformObject obj1(poly1);
    TransformObject obj2(poly2);
    obj1.mass = 1.0;
    obj2.mass = 1.0;
    obj1.setPosition(-1.0, 0.0);
    obj1.setVelocity(1.0, 0.0);
    obj2.setPosition(1.0, 0.0);
    obj2.setVelocity(-1.0, 0.0);

    int iterations = 0;
    while (iterations < 500) {
        Physics::updatePosition(obj1);
        Physics::updatePosition(obj2);
        std::cout << "X1: " << obj1.getPosition()[0] << " Y1: " << obj1.getPosition()[1] << "\n";
        std::cout << "X2: " << obj2.getPosition()[0] << " Y2: " << obj2.getPosition()[1] << "\n";
        if (Physics::collisionDetected(obj1, obj2)) {
            std::cout << "Collision Detected" << "\n";
        }
        iterations++;
    }
    return 0;
}
