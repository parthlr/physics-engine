//
// Created by ParthSchool on 1/4/2020.
//

#include "Application.h"
#include "Physics.h"

void Application::init() {

}

void Application::execute() {
    for (TransformObject object : objects) {
        Physics::updateRotation(object);
        Physics::updatePosition(object);
    }
}

void Application::addObject(TransformObject object) {
    objects.push_back(object);
}
