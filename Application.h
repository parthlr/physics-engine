//
// Created by ParthSchool on 1/4/2020.
//

#ifndef PHYSICS_ENGINE_APPLICATION_H
#define PHYSICS_ENGINE_APPLICATION_H

#include "TransformObject.h"

class Application {

    private:
        std::vector<TransformObject> objects;

    public:
        int screenWidth = 1920;
        int screenHeight = 1080;

        Application();

        void execute();

        void addObject(TransformObject &object);

};


#endif //PHYSICS_ENGINE_APPLICATION_H
