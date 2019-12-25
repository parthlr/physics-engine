//
// Created by ParthSchool on 12/20/2019.
//

#include <cmath>
#include "TransformObject.h"

TransformObject::TransformObject() {
    hasPhysics = false;
}

TransformObject::TransformObject(Polygon objectShape) {
    polygon = objectShape;
}

void TransformObject::setPosition(const float *newPosition) {
    position[0] = newPosition[0];
    position[1] = newPosition[1];
}

float* TransformObject::getPosition() {
    return position;
}

void TransformObject::setVelocity(const float *newVelocity) {
    velocity[0] = newVelocity[0];
    velocity[1] = newVelocity[1];
}

float* TransformObject::getVelocity() {
    return velocity;
}

void TransformObject::setAcceleration(const float *newAcceleration) {
    acceleration[0] = newAcceleration[0];
    acceleration[1] = newAcceleration[1];
}

float* TransformObject::getAcceleration() {
    return acceleration;
}

void TransformObject::addPhysics() {
    hasPhysics = true;
}

void TransformObject::addForce(const float force[2]) {
    float xAcceleration = ((mass * acceleration[0]) + force[0]) / mass;
    float yAcceleration = ((mass * acceleration[1]) + force[1]) / mass;
    float newAcceleration[2] = {xAcceleration, yAcceleration};
    setAcceleration(newAcceleration);
}

void TransformObject::addForceAtPosition(float forcePosition[2], float force[2]) {
    float r[2] = {forcePosition[0] - centerOfMass[0], forcePosition[1] - centerOfMass[1]};
    float torque[2] = {r[0] * force[1], -r[1] * force[0]};
    addTorque(forcePosition, torque);
}

void TransformObject::addTorque(float torquePosition[2], float torque[2]) {
    float T = sqrt(pow(torque[0], 2) + pow(torque[1], 2));
    float r = sqrt(pow(torquePosition[0] - centerOfMass[0], 2) + pow(torquePosition[1] - centerOfMass[1], 2));
    float I = polygon.getMomentOfInertia() + (mass * pow(r, 2));
    angularAcceleration = T / I;
}

void TransformObject::calculateCenterOfMass() {
    float* vertices = polygon.getVertices();
    float xPositions = 0.0;
    float yPositions = 0.0;
    for (int i = 0; i < polygon.numberOfVertices; i++) {
        xPositions += *vertices;
        yPositions += *vertices++;
        *vertices++;
    }
    centerOfMass[0] = xPositions / polygon.numberOfVertices;
    centerOfMass[1] = yPositions / polygon.numberOfVertices;
}

float* TransformObject::getCenterOfMass() {
    return centerOfMass;
}