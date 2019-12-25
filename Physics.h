//
// Created by ParthSchool on 12/20/2019.
//

#ifndef PHYSICS_ENGINE_PHYSICS_H
#define PHYSICS_ENGINE_PHYSICS_H

#include "TransformObject.h"

class Physics {

    private:
        static float gravity[2];

    public:
        constexpr static float deltaTime = 0.1f;

        static void updatePosition(TransformObject &transformObject);
        static void updateRotation(TransformObject &transformObject);
        static void setGravity(float x, float y);
        static float getGravityX();
        static float getGravityY();
};


#endif //PHYSICS_ENGINE_PHYSICS_H
