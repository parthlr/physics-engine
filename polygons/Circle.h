//
// Created by ParthSchool on 12/23/2019.
//

#ifndef PHYSICS_ENGINE_CIRCLE_H
#define PHYSICS_ENGINE_CIRCLE_H


#include "Polygon.h"

class Circle : public Polygon {

    protected:
        void calculateMomentOfInertia();
        void initializeVertices();

    public:
        float radius;

        Circle(float circleRadius);

};


#endif //PHYSICS_ENGINE_CIRCLE_H
