//
// Created by Parth on 12/23/2019.
//

#ifndef PHYSICS_ENGINE_POLYGON_H
#define PHYSICS_ENGINE_POLYGON_H

#include <vector>
#include <array>
#include <string>

class Polygon {

    private:
        void calculateBounds();

    protected:
        float position[2];
        std::vector<float> vertices;
        std::vector<std::array<float, 2>> normals;
        float momentOfInertia;
        float bounds[4];

        void initializeVertices();
        void calculateMomentOfInertia();

    public:
        int numberOfVertices;
        float rotation;
        float mass = 1.0;

        Polygon();

        void setPosition(float x, float y);
        float* getPosition();
        virtual void setVertices(float dx, float dy);
        virtual void setVertices(float angle);
        float* getVertices();
        virtual void calculateNormals();
        std::vector<std::array<float, 2>> getNormals();
        float getMomentOfInertia();
        virtual std::string getType();
};


#endif //PHYSICS_ENGINE_POLYGON_H
