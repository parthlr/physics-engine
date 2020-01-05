//
// Created by Parth on 12/23/2019.
//

#include <cmath>
#include "Circle.h"

Circle::Circle(float circleRadius) {
    radius = circleRadius;
    initializeVertices();
    calculateMomentOfInertia();
}

void Circle::initializeVertices() {
    numberOfVertices = 122;
    float angle = 0.0;
    vertices.push_back(0.0);
    vertices.push_back(0.0);
    vertices.push_back(0.0);
    int vertIndex = 3;
    for (int i = 1; i < numberOfVertices; i++) {
        vertices.push_back(radius * cos(angle));
        vertices.push_back(radius * sin(angle));
        vertices.push_back(0.0);

        angle += (2 * M_PI) / 120;
    }
}

void Circle::calculateMomentOfInertia() {
    momentOfInertia = 0.5 * mass * pow(radius, 2);
}

std::string Circle::getType() {
    return "Circle";
}