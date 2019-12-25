//
// Created by ParthSchool on 12/20/2019.
//

#ifndef PHYSICS_ENGINE_TRANSFORMOBJECT_H
#define PHYSICS_ENGINE_TRANSFORMOBJECT_H

#include "polygons/Polygon.h"

class TransformObject {

    private:
        float position[2] = {0.0, 0.0};
        float velocity[2] = {0.0, 0.0};
        float acceleration[2] = {0.0, 0.0};

        float centerOfMass[2];

        Polygon polygon;

    public:
        float rotation = 0.0;
        float angularVelocity = 0.0;
        float angularAcceleration = 0.0;
        float mass = -1.0;
        bool hasPhysics;

        TransformObject();
        TransformObject(Polygon objectShape);
        void setPosition(const float *newPosition);
        float* getPosition();
        void setVelocity(const float *newVelocity);
        float* getVelocity();
        void setAcceleration(const float *newAcceleration);
        float* getAcceleration();
        void addPhysics();
        void addForce(const float force[2]);
        void addForceAtPosition(float forcePosition[2], float force[2]);
        void addTorque(float torquePosition[2], float torque[2]);
        void calculateCenterOfMass();
        float* getCenterOfMass();
};


#endif //PHYSICS_ENGINE_TRANSFORMOBJECT_H
