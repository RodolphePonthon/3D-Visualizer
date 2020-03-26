#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm/glm.hpp>

using namespace std;


class Shader {
private:

    // the program ID
    unsigned int ID;

public:

    // Constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // Use the shader
    void use();
    // Utility uniform functions
    void setBool(const string& name, bool value) const;
    void setInt(const string& name, int value) const;
    void setFloat(const string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec3(const std::string& name, const glm::vec3& vec) const;
    
    // Getter and Setter
    void setID(unsigned int i);
    unsigned int getID(void) const;
};

#endif