//
// Created by Parth on 12/26/2019.
//

#ifndef PHYSICS_ENGINE_RECTANGLE_H
#define PHYSICS_ENGINE_RECTANGLE_H


#include "Polygon.h"

class Rectangle : public Polygon {

    private:
        unsigned int EBO;

    protected:
        void calculateMomentOfInertia();
        void initializeVertices();

    public:
        float width;
        float height;

        Rectangle(float rectangleWidth, float rectangleHeight);
        virtual void setVertices(float dx, float dy);
        void calculateNormals();
        virtual std::string getType();

};


#endif //PHYSICS_ENGINE_RECTANGLE_H
