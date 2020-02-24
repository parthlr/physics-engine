//
// Created by ParthSchool on 1/4/2020.
//

#include "Application.h"
#include "Physics.h"

Application::Application() {
    objects.reserve(5);
}

void Application::execute() {
    for (TransformObject &object : objects) {
        Physics::updateRotation(object);
        Physics::updatePosition(object);
    }
    for (TransformObject &object1 : objects) {
        for (TransformObject &object2 : objects) {
            if (&object1 != &object2) {
                float penetration;
                int faceIndex;
                if (Physics::collisionDetected(object1, object2, penetration, faceIndex)) {
                    Physics::resolveCollision(object1, object2, penetration, faceIndex);
                    continue;
                }
                float overlap;
                std::array<float, 2> contactPoint;
                std::array<float, 2> axis;
                if (Physics::polygonCollisionDetected(object1, object2, overlap, contactPoint, axis)) {
                    Physics::resolvePolygonCollision(object1, object2, overlap, contactPoint, axis);
                }
            }
        }
    }
}

void Application::addObject(TransformObject &object) {
    objects.push_back(object);
}
