//
// Created by Parth on 12/20/2019.
//

#ifndef PHYSICS_ENGINE_TRANSFORMOBJECT_H
#define PHYSICS_ENGINE_TRANSFORMOBJECT_H

#include "polygons/Polygon.h"
#include "polygons/Circle.h"
#include "polygons/Rectangle.h"

class TransformObject {

    private:
        float position[2] = {0.0, 0.0};
        float velocity[2] = {0.0, 0.0};
        float acceleration[2] = {0.0, 0.0};

        float centerOfMass[2];

        Polygon* polygon;

        void calculateCenterOfMass();

    public:
        float rotation = 0.0;
        float angularVelocity = 0.0;
        float angularAcceleration = 0.0;
        float mass = -1.0;
        float elasticity;
        bool hasPhysics;

        TransformObject();
        TransformObject(Polygon* shape);
        void setPosition(float x, float y);
        float* getPosition();
        void setVelocity(float x, float y);
        float* getVelocity();
        void setAcceleration(float x, float y);
        float* getAcceleration();
        Polygon* getPolygon();
        void addPhysics();
        void addForce(const float force[2]);
        void addForceAtPosition(float forcePosition[2], float force[2]);
        void addTorque(float torquePosition[2], float torque[2]);
        void setCenterOfMass(float x, float y);
        float* getCenterOfMass();
};


#endif //PHYSICS_ENGINE_TRANSFORMOBJECT_H
