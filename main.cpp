#include <iostream>
#include "TransformObject.h"
#include "polygons/Circle.h"
#include "Physics.h"

int main() {
    Circle circle(2);
    TransformObject obj(circle);
    obj.mass = 1.0;
    float force[2] = {1.0, 1.0};
    obj.addForce(force);
    //obj.angularAcceleration = 1.0;
    int iterations = 0;
    while (iterations < 1000) {
        Physics::updatePosition(obj);
        std::cout << "X: " << obj.getPosition()[0] << " Y: " << obj.getPosition()[1] << "\n";
        iterations++;
    }
    return 0;
}
