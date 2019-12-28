//
// Created by Parth on 12/26/2019.
//

#include "Rectangle.h"

Rectangle::Rectangle(float rectangleWidth, float rectangleHeight) {
    width = rectangleWidth;
    height = rectangleHeight;
    initializeVertices();
    calculateNormals();
    calculateMomentOfInertia();
}

void Rectangle::initializeVertices() {
    numberOfVertices = 4;

    vertices.push_back(-0.1 * (width / 2));
    vertices.push_back(0.1 * (height / 2));
    vertices.push_back(0.0);

    vertices.push_back(0.1 * (width / 2));
    vertices.push_back(0.1 * (height / 2));
    vertices.push_back(0.0);

    vertices.push_back(0.1 * (width / 2));
    vertices.push_back(-0.1 * (height / 2));
    vertices.push_back(0.0);

    vertices.push_back(-0.1 * (width / 2));
    vertices.push_back(-0.1 * (height / 2));
    vertices.push_back(0.0);
}

void Rectangle::calculateNormals() {
    normals.clear();
    std::array<float, 2> normal1 = {-(vertices[4] - vertices[1]), (vertices[3] - vertices[0])};
    std::array<float, 2> normal2 = {-(vertices[7] - vertices[4]), (vertices[6] - vertices[3])};
    std::array<float, 2> normal3 = {-(vertices[10] - vertices[7]), (vertices[9] - vertices[6])};
    std::array<float, 2> normal4 = {-(vertices[1] - vertices[10]), (vertices[0] - vertices[9])};
    normals.push_back(normal1);
    normals.push_back(normal2);
    normals.push_back(normal3);
    normals.push_back(normal4);
}

void Rectangle::calculateMomentOfInertia() {

}

void Rectangle::setVertices(float dx, float dy) {
    Polygon::setVertices(dx, dy);
    calculateNormals();
}

std::string Rectangle::getType() {
    return "Rectangle";
}