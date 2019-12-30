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

bool Physics::rectangleCircleCollision(Rectangle* rectangle, Circle* circle) {
    float maxProjection = -FLT_MAX;
    float* vertices = rectangle->getVertices();
    float boxCircle[2] = {circle->getPosition()[0] - rectangle->getPosition()[0], circle->getPosition()[1]- rectangle->getPosition()[1]};
    float boxCircleLength = sqrt(pow(boxCircle[0], 2) + pow(boxCircle[1], 2));
    float boxCircleUnit[2] = {boxCircle[0] / boxCircleLength, boxCircle[1] / boxCircleLength};
    int vertexIndex = 0;
    for (int i = 0; i < rectangle->numberOfVertices; i++) {
        float projection = ((vertices[vertexIndex] - rectangle->getPosition()[0]) * boxCircleUnit[0]) + ((vertices[vertexIndex + 1] - rectangle->getPosition()[1]) * boxCircleUnit[1]);
        if (projection > maxProjection) {
            maxProjection = projection;
        }
        vertexIndex += 3;
    }
    if (boxCircleLength - maxProjection - circle->radius >= 0) {
        return false;
    }
    return true;
}

bool Physics::circleCircleCollision(Circle* circle1, Circle* circle2) {
    float distanceVector[2] = {circle2->getPosition()[0] - circle1->getPosition()[0], circle2->getPosition()[1] - circle1->getPosition()[1]};
    float distance = sqrt(pow(distanceVector[0], 2) + pow(distanceVector[1], 2));
    return circle1->radius + circle2->radius >= distance;
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
    } else if (object1.getPolygon()->getType() == "Rectangle" && object2.getPolygon()->getType() == "Circle") {
        return rectangleCircleCollision((Rectangle*)object1.getPolygon(), (Circle*)object2.getPolygon());
    } else if (object1.getPolygon()->getType() == "Circle" && object2.getPolygon()->getType() == "Rectangle") {
        return rectangleCircleCollision((Rectangle*)object2.getPolygon(), (Circle*)object1.getPolygon());
    } else if (object1.getPolygon()->getType() == "Circle" && object2.getPolygon()->getType() == "Circle") {
        return circleCircleCollision((Circle*)object1.getPolygon(), (Circle*)object2.getPolygon());
    }
    return false;
}