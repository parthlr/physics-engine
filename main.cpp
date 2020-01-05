#include <iostream>
#include "TransformObject.h"
#include "polygons/Rectangle.h"
#include "polygons/Circle.h"
#include "Physics.h"
#include <cmath>

int main() {
    Circle circle(0.05);
    Rectangle rect(1, 1);
    Polygon* poly1 = &circle;
    Polygon* poly2 = &rect;
    TransformObject obj1(poly1);
    TransformObject obj2(poly2);
    obj1.addPhysics();
    obj2.addPhysics();
    obj1.setPosition(-1.0, 0.0);
    obj1.setVelocity(1.0, 0.0);
    obj2.setPosition(1.0, 0.0);
    obj2.setVelocity(-1.0, 0.0);
    obj2.rotation = M_PI_4;

    int iterations = 0;
    while (iterations < 500) {
        Physics::updatePosition(obj1);
        Physics::updatePosition(obj2);
        Physics::updateRotation(obj1);
        Physics::updateRotation(obj2);
        std::cout << "Vx1: " << obj1.getVelocity()[0] << " Vy1: " << obj1.getVelocity()[1] << "\n";
        std::cout << "Vx2: " << obj2.getVelocity()[0] << " Vy2: " << obj2.getVelocity()[1] << "\n";
        //std::cout << "R1: " << obj1.rotation << "\n";
        //std::cout << "R2: " << obj2.rotation << "\n";
        float penetration;
        int faceIndex;
        if (Physics::collisionDetected(obj1, obj2, penetration, faceIndex)) {
            std::cout << "Collision Detected" << "\n";
            Physics::resolveCollision(obj1, obj2, penetration, faceIndex);
        }
        iterations++;
    }
    return 0;
}
