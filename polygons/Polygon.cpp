//
// Created by ParthSchool on 12/23/2019.
//

#include "Polygon.h"

Polygon::Polygon() {

}

void Polygon::calculateBounds() {
    bounds[0] = vertices[0];
    bounds[1] = vertices[0];
    bounds[2] = vertices[1];
    bounds[3] = vertices[1];
    for (int i = 1; i < vertices.size() / 3; i++) {
        int vertex = i * 3;
        bounds[0] = std::min(bounds[0], vertices[vertex]);
        bounds[1] = std::max(bounds[1], vertices[vertex]);
        bounds[2] = std::min(bounds[2], vertices[vertex + 1]);
        bounds[3] = std::max(bounds[3], vertices[vertex + 1]);
    }
}

float* Polygon::getVertices() {
    return vertices.data();
}

float Polygon::getMomentOfInertia() {
    return momentOfInertia;
}
