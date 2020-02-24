#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TransformObject.h"
#include "polygons/Rectangle.h"
#include "polygons/Circle.h"
#include "Physics.h"
#include <array>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "Physics Engine", NULL, NULL);
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
    glViewport(0, 0, 500, 500);

    Rectangle rect1(1, 1);
    Rectangle rect2(1, 1);
    Polygon* poly1 = &rect1;
    Polygon* poly2 = &rect2;
    Shader shader1("E:/C++/physics-engine/shaders/test_vertex_shader.vs", "E:/C++/physics-engine/shaders/test_fragment_shader.fragment");
    Shader shader2("E:/C++/physics-engine/shaders/test_vertex_shader.vs", "E:/C++/physics-engine/shaders/test_fragment_shader_green.fragment");
    TransformObject obj1(poly1, shader1);
    TransformObject obj2(poly2, shader2);
    obj1.addPhysics();
    obj2.addPhysics();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    obj1.setPosition(-1.0, -1.0);
    obj1.setVelocity(0.53, 0.5);
    obj2.setPosition(1.0, 1.0);
    obj2.setVelocity(-0.53, -0.5);
    glfwSwapBuffers(window);
    glfwPollEvents();

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Physics::updateRotation(obj1);
        Physics::updateRotation(obj2);
        Physics::updatePosition(obj1);
        Physics::updatePosition(obj2);
        float penetration;
        int faceIndex;
        if (Physics::collisionDetected(obj1, obj2, penetration, faceIndex)) {
            Physics::resolveCollision(obj1, obj2, penetration, faceIndex);
        }
        float overlap;
        std::array<float, 2> contactPoint;
        std::array<float, 2> axis;
        if (Physics::polygonCollisionDetected(obj1, obj2, overlap, contactPoint, axis)) {
            Physics::resolvePolygonCollision(obj1, obj2, overlap, contactPoint, axis);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
