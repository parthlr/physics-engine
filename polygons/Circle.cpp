//
// Created by ParthSchool on 12/23/2019.
//

#include <cmath>
#include "Circle.h"

Circle::Circle(float circleRadius) {
    radius = circleRadius;
    initializeVertices();
    calculateMomentOfInertia();
}

void Circle::initializeVertices() {
    int numVertices = 122;
    //float vertices[numVertices * 3];
    float angle = 0.0;
    vertices.push_back(0.0);
    vertices.push_back(0.0);
    vertices.push_back(0.0);
    int vertIndex = 3;
    for (int i = 1; i < numVertices; i++) {
        vertices.push_back(radius * cos(angle) / 1920);
        vertices.push_back(radius * sin(angle) / 1080);
        vertices.push_back(0.0);

        angle += (2 * M_PI) / 122;
        numberOfVertices++;
    }
}

void Circle::calculateMomentOfInertia() {
    momentOfInertia = M_PI * pow(radius, 4) / 4;
}