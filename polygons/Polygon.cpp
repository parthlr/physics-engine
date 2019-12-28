//
// Created by Parth on 12/23/2019.
//

#include "Polygon.h"
#include <cmath>

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

void Polygon::setPosition(float x, float y) {
    setVertices(x - position[0], y - position[1]);
    position[0] = x;
    position[1] = y;
}

float* Polygon::getPosition() {
    return position;
}

void Polygon::setVertices(float dx, float dy) {
    int vertexIndex = 0;
    for (int i = 0; i < numberOfVertices; i++) {
        vertices[vertexIndex] += dx;
        vertices[vertexIndex + 1] += dy;
        vertexIndex += 3;
    }
}

void Polygon::setVertices(float angle) {
    int vertexIndex = 0;
    for (int i = 0; i < numberOfVertices; i++) {
        float x = vertices[vertexIndex] - position[0];
        float y = vertices[vertexIndex + 1] - position[1];
        vertices[vertexIndex] = (x * cos(angle)) - (y * sin(angle));
        vertices[vertexIndex + 1] = (y * cos(angle)) + (x * sin(angle));
        vertexIndex += 3;
    }
}

float* Polygon::getVertices() {
    return vertices.data();
}

void Polygon::calculateNormals() {}

std::vector<std::array<float, 2>> Polygon::getNormals() {
    return normals;
}

float Polygon::getMomentOfInertia() {
    return momentOfInertia;
}

std::string Polygon::getType() {
    return "Polygon";
}
