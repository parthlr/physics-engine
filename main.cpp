#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TransformObject.h"
#include "polygons/Rectangle.h"
#include "polygons/Circle.h"
#include "Physics.h"
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    /*Circle circle(0.05);
    Rectangle rect(1, 1);
    Polygon* poly1 = &circle;
    Polygon* poly2 = &rect;
    TransformObject obj1(poly1);
    TransformObject obj2(poly2);
    obj1.addPhysics();
    obj2.addPhysics();
    obj1.setPosition(-1.0, 0.0);
    obj1.setVelocity(1.0, 0.0);
    obj2.setPosition(1.0, 0.0);
    obj2.setVelocity(-1.0, 0.0);
    obj2.rotation = M_PI_4;

    int iterations = 0;
    while (iterations < 500) {
        Physics::updatePosition(obj1);
        Physics::updatePosition(obj2);
        Physics::updateRotation(obj1);
        Physics::updateRotation(obj2);
        std::cout << "X1: " << obj1.getPosition()[0] << " Y1: " << obj1.getPosition()[1] << "\n";
        std::cout << "X2: " << obj2.getPosition()[0] << " Y2: " << obj2.getPosition()[1] << "\n";
        //std::cout << "R1: " << obj1.rotation << "\n";
        //std::cout << "R2: " << obj2.rotation << "\n";
        float penetration1;
        float penetration2;
        int faceIndex1;
        int faceIndex2;
        std::array<float, 2> polygonContactPoint;
        std::array<float, 2> polygonAxis;
        if (Physics::collisionDetected(obj1, obj2, penetration1, faceIndex1)) {
            std::cout << "Collision Detected" << "\n";
            Physics::resolveCollision(obj1, obj2, penetration1, faceIndex1);
        }
        //if (Physics::polygonCollisionDetected(obj1, obj2, penetration1, polygonContactPoint, polygonAxis)) {
        //    std::cout << "Collision Detected" << "\n";
        //   Physics::resolvePolygonCollision(obj1, obj2, penetration1, polygonContactPoint, polygonAxis);
        //}
        iterations++;
    }*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Physics Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 1920, 1080);

    Circle circle(0.05);
    Rectangle rect(1, 1);
    Polygon* poly1 = &circle;
    Polygon* poly2 = &rect;
    Shader shader1("E:/C++/physics-engine/shaders/test_vertex_shader.vs", "E:/C++/physics-engine/shaders/test_fragment_shader.fragment");
    Shader shader2("E:/C++/physics-engine/shaders/test_vertex_shader.vs", "E:/C++/physics-engine/shaders/test_fragment_shader.fragment");
    TransformObject obj1(poly1, shader1);
    TransformObject obj2(poly2, shader2);
    obj1.addPhysics();
    obj2.addPhysics();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    obj1.setPosition(0.0, 0.0);
    obj1.setVelocity(1.0, 0.0);
    obj2.setPosition(0.5, 0.0);
    obj2.setVelocity(-1.0, 0.0);
    glfwSwapBuffers(window);
    glfwPollEvents();

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Physics::updatePosition(obj1);
        Physics::updatePosition(obj2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
