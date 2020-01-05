//
// Created by Parth on 12/20/2019.
//

#include "Physics.h"
#include "polygons/Circle.h"
#include <string>
#include <cmath>
#include <cfloat>
#include <iostream>

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
    transformObject.getPolygon()->rotation = rotation;
    transformObject.getPolygon()->setVertices(rotation);
}

bool Physics::rectangleCircleCollision(Rectangle* rectangle, Circle* circle, float &maxPenetration, int &faceIndex) {
    float maxProjection = -FLT_MAX;
    int bestIndex = 0;
    float* vertices = rectangle->getVertices();
    float boxCircle[2] = {circle->getPosition()[0] - rectangle->getPosition()[0], circle->getPosition()[1]- rectangle->getPosition()[1]};
    float boxCircleLength = sqrt(pow(boxCircle[0], 2) + pow(boxCircle[1], 2));
    float boxCircleUnit[2] = {boxCircle[0] / boxCircleLength, boxCircle[1] / boxCircleLength};
    int vertexIndex = 0;
    for (int i = 0; i < rectangle->numberOfVertices; i++) {
        float projection = ((vertices[vertexIndex] - rectangle->getPosition()[0]) * boxCircleUnit[0]) + ((vertices[vertexIndex + 1] - rectangle->getPosition()[1]) * boxCircleUnit[1]);
        if (projection > maxProjection) {
            maxProjection = projection;
            bestIndex = i;
        }
        vertexIndex += 3;
    }
    if (boxCircleLength - maxProjection - circle->radius >= 0) {
        return false;
    }
    maxPenetration = maxProjection;
    faceIndex = bestIndex;
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

std::array<float, 2> Physics::calculateContactPoint(Rectangle* rectangle, Circle* circle, float maxPenetration, int faceIndex) {
    std::array<float, 2> contactPoint;
    float vertex[2] = {rectangle->getVertices()[faceIndex * 3], rectangle->getVertices()[(faceIndex * 3) + 1]};
    float circleToVertex[2] = {vertex[0] - circle->getPosition()[0], vertex[1] - circle->getPosition()[1]};
    if (pow(circleToVertex[0], 2) + pow(circleToVertex[1], 2) <= circle->radius) {
        contactPoint = {vertex[0], vertex[1]};
    } else {
        float negativeNormal[2] = {-rectangle->getNormals()[faceIndex][0], -rectangle->getNormals()[faceIndex][1]};
        float negativeNormalMagnitude = sqrt(pow(negativeNormal[0], 2) + pow(negativeNormal[1], 2));
        float circleNormal[2] = {negativeNormal[0] / negativeNormalMagnitude, negativeNormal[1] / negativeNormalMagnitude};
        contactPoint = {(circle->radius - maxPenetration) * circleNormal[0], (circle->radius - maxPenetration) * circleNormal[1]};
    }
    return contactPoint;
}

bool Physics::polygonCollisionDetected(TransformObject object1, TransformObject object2, float &maxPenetration1, float &maxPenetration2, int &faceIndex1, int &faceIndex2) {
    if (object1.getPolygon()->getType() == "Rectangle" && object2.getPolygon()->getType() == "Rectangle") {
        maxPenetration1 = getPenetration(faceIndex1, (Rectangle*)object1.getPolygon(), (Rectangle*)object2.getPolygon());
        maxPenetration2 = getPenetration(faceIndex2, (Rectangle*)object2.getPolygon(), (Rectangle*)object1.getPolygon());
        if (maxPenetration1 >= 0 || maxPenetration2 >= 0) {
            return false;
        }
        return true;
    }
    return false;
}

bool Physics::collisionDetected(TransformObject object1, TransformObject object2, float &maxPenetration, int &faceIndex) {
    if (object1.getPolygon()->getType() == "Rectangle" && object2.getPolygon()->getType() == "Circle") {
        return rectangleCircleCollision((Rectangle*)object1.getPolygon(), (Circle*)object2.getPolygon(), maxPenetration, faceIndex);
    } else if (object1.getPolygon()->getType() == "Circle" && object2.getPolygon()->getType() == "Rectangle") {
        return rectangleCircleCollision((Rectangle*)object2.getPolygon(), (Circle*)object1.getPolygon(), maxPenetration, faceIndex);
    } else if (object1.getPolygon()->getType() == "Circle" && object2.getPolygon()->getType() == "Circle") {
        return circleCircleCollision((Circle*)object1.getPolygon(), (Circle*)object2.getPolygon());
    }
    return false;
}

void Physics::resolveCollision(TransformObject &object1, TransformObject &object2, float penetration, int faceIndex) {
    float distance[2] = {object2.getPosition()[0] - object1.getPosition()[0], object2.getPosition()[1] - object1.getPosition()[1]};
    float distanceMagnitude = sqrt(pow(distance[0], 2) + pow(distance[1], 2));
    float collisionNormal[2] = {distance[0] / distanceMagnitude, distance[1] / distanceMagnitude};

    float relativeVelocity[2] = {object2.getVelocity()[0] - object1.getVelocity()[0], object2.getVelocity()[1] - object1.getVelocity()[1]};
    float normalVelocity = (relativeVelocity[0] * collisionNormal[0]) + (relativeVelocity[1] * collisionNormal[1]);
    float elasticity = std::min(object1.elasticity, object2.elasticity);
    float impulseConstant = (-(1 + elasticity) * normalVelocity) / ((1 / object1.mass) + (1 / object2.mass));

    float impulse[2] = {impulseConstant * collisionNormal[0], impulseConstant * collisionNormal[1]};
    object1.setVelocity(object1.getVelocity()[0] - ((1 / object1.mass) * impulse[0]), object1.getVelocity()[1] - ((1 / object1.mass) * impulse[1]));
    object2.setVelocity(object2.getVelocity()[0] + ((1 / object2.mass) * impulse[0]), object2.getVelocity()[1] + ((1 / object2.mass) * impulse[1]));

    std::array<float, 2> contactPoint;
    if (object1.getPolygon()->getType() == "Rectangle" && object2.getPolygon()->getType() == "Circle") {
        contactPoint = calculateContactPoint((Rectangle*)object1.getPolygon(), (Circle*)object2.getPolygon(), penetration, faceIndex);
    } else if (object1.getPolygon()->getType() == "Circle" && object2.getPolygon()->getType() == "Rectangle") {
        contactPoint = calculateContactPoint((Rectangle*)object2.getPolygon(), (Circle*)object1.getPolygon(), penetration, faceIndex);
    }
    std::cout << "Contact X: " << contactPoint[0] << " Contact Y: " << contactPoint[1] << "\n";
    float r1[2] = {contactPoint[0] - object1.getPosition()[0], contactPoint[1] - object1.getPosition()[1]};
    float r2[2] = {contactPoint[0] - object2.getPosition()[0], contactPoint[1] - object2.getPosition()[1]};

    float contactImpulse1 = (r1[0] * impulse[1]) - (r1[1] * impulse[0]);
    float contactImpulse2 = (r2[0] * impulse[1]) - (r2[1] * impulse[0]);

    object1.angularVelocity -= (1 / object1.getPolygon()->getMomentOfInertia()) * contactImpulse1;
    object2.angularVelocity += (1 / object2.getPolygon()->getMomentOfInertia()) * contactImpulse2;
}