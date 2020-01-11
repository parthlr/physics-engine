//
// Created by ParthSchool on 1/9/2020.
//

#ifndef TEST_SHADER_H
#define TEST_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {

public:
    unsigned int ID;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void use();
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setVec2(const std::string &name, glm::vec2 &value);
    void setVec2(const std::string &name, float x, float y);
    void setVec3(const std::string &name, glm::vec3 &value);
    void setVec3(const std::string &name, float x, float y, float z);
    void setVec4(const std::string &name, glm::vec4 &value);
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, glm::mat2 &mat);
    void setMat3(const std::string &name, glm::mat3 &mat);
    void setMat4(const std::string &name, glm::mat4 &mat);

};


#endif //TEST_SHADER_H
