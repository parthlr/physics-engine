//
// Created by ParthSchool on 12/23/2019.
//

#ifndef PHYSICS_ENGINE_POLYGON_H
#define PHYSICS_ENGINE_POLYGON_H

#include <vector>

class Polygon {

    private:
        void calculateBounds();

    protected:
        std::vector<float> vertices;
        float momentOfInertia;
        float bounds[4];

        void initializeVertices();
        void calculateMomentOfInertia();

    public:
        int numberOfVertices;

        Polygon();

        float* getVertices();
        float getMomentOfInertia();
};


#endif //PHYSICS_ENGINE_POLYGON_H
