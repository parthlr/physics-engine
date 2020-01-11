//
// Created by Parth on 12/26/2019.
//

#include "Rectangle.h"
#include <cmath>
#include <glad/glad.h>

Rectangle::Rectangle(float rectangleWidth, float rectangleHeight) {
    width = rectangleWidth;
    height = rectangleHeight;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    initializeVertices();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    calculateNormals();
    calculateMomentOfInertia();
}

void Rectangle::initializeVertices() {
    numberOfVertices = 4;
    float glVertices[numberOfVertices * 3];
    unsigned int glIndices[6] = {0, 1, 3, 1, 2, 3};

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

    for (int i = 0; i < vertices.size(); i++) {
        glVertices[i] = vertices[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glVertices), glVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glIndices), glIndices, GL_STATIC_DRAW);
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
    momentOfInertia = (1.0 / 12.0) * mass * (pow(height, 2) + pow(width, 2));
}

void Rectangle::setVertices(float dx, float dy) {
    Polygon::setVertices(dx, dy);
    calculateNormals();
}

std::string Rectangle::getType() {
    return "Rectangle";
}