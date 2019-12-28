//
// Created by Parth on 12/20/2019.
//

#include "Physics.h"
#include "polygons/Circle.h"
#include <string>
#include <cmath>
#include <cfloat>

void Physics::updatePosition(TransformObject &transformObject) {
    float xVelocity = transformObject.getVelocity()[0] + (transformObject.getAcceleration()[0] * deltaTime);
    float yVelocity = transformObject.getVelocity()[1] + (transformObject.getAcceleration()[1] * deltaTime);

    float dx = transformObject.getVelocity()[0] * deltaTime;
    float dy = transformObject.getVelocity()[1] * deltaTime;

    float xPosition = transformObject.getPosition()[0] + dx;
    float yPosition = transformObject.getPosition()[1] + dy;

    float xCM = transformObject.getCenterOfMass()[0] + dx;
    float yCM = transformObject.getCenterOfMass()[1] + dy;

    transformObject.setVelocity(xVelocity, yVelocity);
    transformObject.setPosition(xPosition, yPosition);
    transformObject.setCenterOfMass(xCM, yCM);
    transformObject.getPolygon()->calculateNormals();
}

void Physics::updateRotation(TransformObject &transformObject) {
    float angularVelocity = transformObject.angularVelocity + (transformObject.angularAcceleration * deltaTime);
    float rotation = transformObject.rotation + (transformObject.angularVelocity * deltaTime);

    if (rotation > 2 * M_PI)
        rotation -= (2 * M_PI);
    else if (rotation < 0)
        rotation += (2 * M_PI);

    transformObject.angularVelocity = angularVelocity;
    transformObject.rotation = rotation;
    transformObject.getPolygon()->setVertices(rotation);
}

void Physics::calculateProjection(Rectangle* rectangle, float axisX, float axisY, float &minProjection, float &maxProjection) {
    float axisMagnitude = sqrt(pow(axisX, 2) + pow(axisY, 2));
    float axisUnit[2] = {axisX / axisMagnitude, axisY / axisMagnitude};
    float* vertices = rectangle->getVertices();
    minProjection = ((vertices[0]) * axisX) + ((vertices[1]) * axisY);
    maxProjection = ((vertices[0]) * axisX) + ((vertices[1]) * axisY);
    int vertexIndex = 3;
    for (int i = 1; i < rectangle->numberOfVertices; i++) {
        float projection = ((vertices[vertexIndex]) * axisX) + ((vertices[vertexIndex + 1]) * axisY);
        minProjection = std::min(projection, minProjection);
        maxProjection = std::max(projection, maxProjection);
        vertexIndex += 3;
    }
}

bool Physics::rectangleRectangleCollision(Rectangle* rectangle1, Rectangle* rectangle2) {
    std::vector<std::array<float, 2>> normals1 = rectangle1->getNormals();
    std::vector<std::array<float, 2>> normals2 = rectangle2->getNormals();
    for (int i = 0; i < normals1.size(); i++) {
        float rect1MinProjection;
        float rect1MaxProjection;
        float rect2MinProjection;
        float rect2MaxProjection;
        calculateProjection(rectangle1, normals1[i][0], normals1[i][1], rect1MinProjection, rect1MaxProjection);
        calculateProjection(rectangle2, normals1[i][0], normals1[i][1], rect2MinProjection, rect2MaxProjection);
        if (rect1MaxProjection < rect2MinProjection || rect1MinProjection > rect2MaxProjection) {
            return false;
        }
    }
    for (int i = 0; i < normals2.size(); i++) {
        float rect1MinProjection;
        float rect1MaxProjection;
        float rect2MinProjection;
        float rect2MaxProjection;
        calculateProjection(rectangle1, normals2[i][0], normals2[i][1], rect1MinProjection, rect1MaxProjection);
        calculateProjection(rectangle2, normals2[i][0], normals2[i][1], rect2MinProjection, rect2MaxProjection);
        if (rect1MaxProjection < rect2MinProjection || rect1MinProjection > rect2MaxProjection) {
            return false;
        }
    }
    return true;
}

std::array<float, 2> Physics::getSupportPoint(Rectangle* rectangle, float axisX, float axisY) {
    float bestProjection = -FLT_MAX;
    std::array<float, 2> bestVertex;
    float* vertices = rectangle->getVertices();
    int vertexIndex = 0;
    for (int i = 0; i < rectangle->numberOfVertices; i++) {
        float projection = (vertices[vertexIndex] * axisX) + (vertices[vertexIndex + 1] * axisY);
        if (projection > bestProjection) {
            bestVertex[0] = vertices[vertexIndex];
            bestVertex[1] = vertices[vertexIndex + 1];
            bestProjection = projection;
        }
        vertexIndex += 3;
    }
    return bestVertex;
}

float Physics::getPenetration(int &faceIndex, Rectangle* rectangle1, Rectangle* rectangle2) {
    float bestDistance = -FLT_MAX;
    std::vector<std::array<float, 2>> normals1 = rectangle1->getNormals();
    float* vertices = rectangle1->getVertices();
    int vertexIndex = 0;
    int bestIndex = 0;
    for (int i = 0; i < rectangle1->numberOfVertices; i++) {
        std::array<float, 2> normal = normals1[i];
        std::array<float, 2> supportPoint = getSupportPoint(rectangle2, -normal[0], -normal[1]);
        std::array<float, 2> vertex = {vertices[vertexIndex], vertices[vertexIndex + 1]};
        float penetrationDistance = (normal[0] * (supportPoint[0] - vertex[0])) + (normal[1] * (supportPoint[1] - vertex[1]));
        if (penetrationDistance > bestDistance) {
            bestDistance = penetrationDistance;
            bestIndex = i;
        }
        vertexIndex += 3;
    }
    faceIndex = bestIndex;
    return bestDistance;
}

bool Physics::collisionDetected(TransformObject object1, TransformObject object2) {
    if (object1.getPolygon()->getType() == "Rectangle" && object2.getPolygon()->getType() == "Rectangle") {
        int index1;
        int index2;
        float penetration1 = getPenetration(index1, (Rectangle*)object1.getPolygon(), (Rectangle*)object2.getPolygon());
        float penetration2 = getPenetration(index2, (Rectangle*)object2.getPolygon(), (Rectangle*)object1.getPolygon());
        if (penetration1 >= 0 || penetration2 >= 0) {
            return false;
        }
        return true;
    }
    return false;
}