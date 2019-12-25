//
// Created by ParthSchool on 12/20/2019.
//

#include "Physics.h"

void Physics::updatePosition(TransformObject &transformObject) {
    float xVelocity = transformObject.getVelocity()[0] + (transformObject.getAcceleration()[0] * deltaTime);
    float yVelocity = transformObject.getVelocity()[1] + (transformObject.getAcceleration()[1] * deltaTime);
    float newVelocity[2] = {xVelocity, yVelocity};

    float xPosition = transformObject.getPosition()[0] + (transformObject.getVelocity()[0] * deltaTime);
    float yPosition = transformObject.getPosition()[1] + (transformObject.getVelocity()[1] * deltaTime);
    float newPosition[2] = {xPosition, yPosition};

    transformObject.setVelocity(newVelocity);
    transformObject.setPosition(newPosition);
}

void Physics::updateRotation(TransformObject &transformObject) {
    float angularVelocity = transformObject.angularVelocity + (transformObject.angularAcceleration * deltaTime);
    float rotation = transformObject.rotation + (transformObject.angularVelocity * deltaTime);

    if (rotation > 360)
        rotation -= 360;
    else if (rotation < 0)
        rotation += 360;

    transformObject.angularVelocity = angularVelocity;
    transformObject.rotation = rotation;
}