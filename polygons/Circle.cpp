//
// Created by Parth on 12/23/2019.
//

#include <cmath>
#include "Circle.h"
#include <glad/glad.h>

Circle::Circle(float circleRadius) {
    radius = circleRadius;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    initializeVertices();
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    calculateMomentOfInertia();
}

void Circle::initializeVertices() {
    numberOfVertices = 122;
    float angle = 0.0;
    float glVertices[numberOfVertices * 3];
    vertices.push_back(0.0);
    vertices.push_back(0.0);
    vertices.push_back(0.0);
    glVertices[0] = 0.0;
    glVertices[1] = 0.0;
    glVertices[2] = 0.0;
    int vertexIndex = 3;
    for (int i = 1; i < numberOfVertices; i++) {
        vertices.push_back(radius * cos(angle));
        vertices.push_back(radius * sin(angle));
        vertices.push_back(0.0);

        glVertices[vertexIndex] = radius * cos(angle);
        glVertices[vertexIndex + 1] = radius * sin(angle);
        glVertices[vertexIndex + 2] = 0.0;

        angle += (2 * M_PI) / 120;
        vertexIndex += 3;
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glVertices), glVertices, GL_STATIC_DRAW);
}

void Circle::calculateMomentOfInertia() {
    momentOfInertia = 0.5 * mass * pow(radius, 2);
}

std::string Circle::getType() {
    return "Circle";
}